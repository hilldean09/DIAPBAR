// Diapbar class file

#include "diapbar.hpp"
#include "diapbar_core.hpp"

namespace Diapbar {

  // Constructors //

  /**
   * Constructor for the Do-It-All-Progress-Bar.
   *
   * @param[in] formatPtr a pointer to a char array of at least length 4. Defaults to nullptr.
   */
  Diapbar::Diapbar( char* formatPtr ) {
    initInvalidAtr();

    initBarFormat( formatPtr );

    isInitialised_ = verifyInit();
  }

  /**
   * Constructor for the Do-It-All-Progress-Bar.
   *
   * @param[in] barLength the desired length of the bar, excluding the opening and closing characters.
   * @param[in] formatPtr a pointer to a char array of at least length 4. Defaults to nullptr.
   */
  Diapbar::Diapbar( int barLength, char* formatPtr ) {
    initInvalidAtr();

    initBarLength( barLength );
    initStringCache();

    initBarFormat( formatPtr );

    isInitialised_ = verifyInit();
  }

  /**
   * Constructor for the Do-It-All-Progress-Bar.
   *
   * @param[in] trackerPtr a poinnter to an int variable that indicates the completion progress.
   * @param[in] goal an integer defining the tracker value needed for 100% completion.
   * @param[in] barLength the desired length of the bar, excluding the opening and closing characters.
   * @param[in] formatPtr a pointer to a char array of at least length 4. Defaults to nullptr.
   */
  Diapbar::Diapbar( int* trackerPtr, int goal, int barLength, char* formatPtr ) {
    initInvalidAtr();

    initTrackerPtr( trackerPtr );
    initGoal( goal );

    initBarLength( barLength );
    initStringCache();

    initBarFormat( formatPtr );

    isInitialised_ = verifyInit();
  }


  // Initialisers //
  
  /**
   * Initialises the instance post-construction.
   *
   * @param[in] barLength the desired length of the bar, excluding the opening and closing characters.
   */
  void Diapbar::initialise( int barLength ) {
    if( !isInitialised_ ) {
      initBarLength( barLength );
      initStringCache();

      isInitialised_ = verifyInit();
    }
  }

  /**
   * Initialises the instance post-construction.
   *
   * @param[in] trackerPtr a poinnter to an int variable that indicates the completion progress.
   * @param[in] goal an integer defining the tracker value needed for 100% completion.
   */
  void Diapbar::initialise( int* trackerPtr, int goal ) {
    if( !isInitialised_ ) {
      initTrackerPtr( trackerPtr );
      initGoal( goal );

      isInitialised_ = verifyInit();
    }
  }

  /**
   * Initialises the instance post-construction.
   *
   * @param[in] trackerPtr a poinnter to an int variable that indicates the completion progress.
   * @param[in] goal an integer defining the tracker value needed for 100% completion.
   * @param[in] barLength the desired length of the bar, excluding the opening and closing characters.
   */
  void Diapbar::initialise( int* trackerPtr, int goal, int barLength ) {
    if( !isInitialised_ ) {
      initTrackerPtr( trackerPtr );
      initGoal( goal );

      initBarLength( barLength );
      initStringCache();

      isInitialised_ = verifyInit();
    }
  }

  /**
   * Initialise invalid attributes.
   *
   * Run at the beginning of constructors
   */
  void Diapbar::initInvalidAtr() {
    setTrackerPtr( nullptr );
    setGoal( -1 );

    barLength_ = -1;
    stringCache_ = nullptr;
  }

  /// Initialises the tracker pointer attribute
  void Diapbar::initTrackerPtr( int* trackerPtr ) {
    setTrackerPtr( trackerPtr );
  }

  /// Initalise the goal attribute
  void Diapbar::initGoal( int goal ) {
    setGoal( goal );
  }

  /// Initialise the bar length attribute
  void Diapbar::initBarLength( int barLength ) {
    if( !verifyCacheInit() ) {
      barLength_ = barLength;
    }
  }

  /// Initialise the string cache
  void Diapbar::initStringCache() {
    if( !verifyCacheInit() ) {
      int fullLength = getFullLength();

      stringCache_ = new char[ fullLength ];

      for( int ii = 0; ii < fullLength; ii++ ) {
        stringCache_[ ii ] = ' ';
      }
    }
  }

  /// Initialise barFormat to default or input
  void Diapbar::initBarFormat( char* formatPtr ) {
    if( formatPtr == nullptr ) {
      setBarFormat( Core::DEFAULT_BAR_FORMAT );
    }

    else {
      setBarFormat( formatPtr );
    }
  }


  // Verifiers //
  
  /**
   * Returns a boolean indicating whether the 
   * class is fully initialised.
   */
  bool Diapbar::verifyInit() const {
    bool output = false;

    if( verifyCacheInit() && 
        ( trackerPtr_ != nullptr ) && 
        ( goal_ != -1 ) &&
        ( barLength_ != -1 ) ) {

      output = true;
    }

    return output;
  }

  /**
   * Returns a boolean indicating whether the
   * cache is initialised.
   */
  bool Diapbar::verifyCacheInit() const {
    bool output = false;

    if( stringCache_ != nullptr ) {
      output = true;
    }

    return output;
  }


  // Accessors //

  /**
  * Returns the number characters that should
  * be used to represent completed progress.
  */
  int Diapbar::getFillLength() const {
    // Formula format was chosen to hopefully reduce the risk of floating point shenanigans
    int barLength = getBarLength();

    int output = (int) ( getTrackerValue() * barLength ) / getGoal();

    if( output > barLength ) {
      output = barLength;
    }
    else if( output < 0 ) {
      output = 0;
    }

    return output;
  }

  /**
  * Returns the number characters that should
  * be used to represent uncompleted progress.
  */
  int Diapbar::getLeftLength() const {
    // Dependent on getFillLength() to reduce code reuse
    return (int) getBarLength() - getFillLength();
  }


  // Mutators //

  /**
   * Sets the display format of the progress bar.
   *
   * @param[in] formatPtr a pointer to a char array of at least length 4.
   */
  void Diapbar::setBarFormat( char* formatPtr ) {
    setBarFormat( Core::BarFormat{ formatPtr[ 0 ],
                               formatPtr[ 1 ],
                               formatPtr[ 2 ],
                               formatPtr[ 3 ] } );
  }

  /**
   * Builds the bar display to the cache.
   *
   * @returns a pointer to the stringCache_ attribute.
   */
  char* Diapbar::buildBarToCache() const {
    // Storing needed attributes to reduce function calls.
    int barLength = getBarLength();
    
    char openChar = getOpenChar();
    char fillChar = getFillChar();
    char emptyChar = getEmptyChar();
    char closeChar = getCloseChar();

    int fillIdx = getFillLength();

    stringCache_[ 0 ] = openChar;

    int ii;

    // Completion characters
    for( ii = 1; ii <= fillIdx; ii++ ) {
      stringCache_[ ii ] = fillChar;
    }

    // Left characters
    for( ii = fillIdx + 1; ii <= barLength; ii++ ) {
      stringCache_[ ii ] = emptyChar;
    }

    stringCache_[ barLength + 1 ] = closeChar;

    return getStringCache();
  }


  // Methods //

  /**
   * Builds and returns a std::string representation
   * of the progress bar.
   *
   * Relies on the stringCache_ attribute.
   */
  std::string Diapbar::buildStringFromCache() const {
    buildBarToCache();

    return std::string( (const char*) getStringCache(), getFullLength() );
  }
  

  // Operators //

  Diapbar::operator std::string() const {
    return buildStringFromCache();
  }

  // Misc //

  /// Destructor
  Diapbar::~Diapbar() {
    // Freeing the string cache
    if( verifyCacheInit() ) {
      delete stringCache_;
      stringCache_ = nullptr;
    }
  }
} 
