// Diapbar class file

#ifndef DIAPBAR_CPP
#define DIAPBAR_CPP
#include "diapbar_core.hpp"
#include <string>

namespace Diapbar {

  // Constructors //

  /**
   * Constructor for the Do-It-All-Progress-Bar.
   *
   * @param[in] formatPtr a pointer to a char array of at least length 4. Defaults to nullptr.
   */
  template <typename NumT>
  Diapbar<NumT>::Diapbar( char* formatPtr ) {
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
  template <typename NumT>
  Diapbar<NumT>::Diapbar( int barLength, char* formatPtr ) {
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
  template <typename NumT>
  Diapbar<NumT>::Diapbar( NumT* trackerPtr, NumT goal, int barLength, char* formatPtr ) {
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
  template <typename NumT>
  void Diapbar<NumT>::initialise( int barLength ) {
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
  template <typename NumT>
  void Diapbar<NumT>::initialise( NumT* trackerPtr, NumT goal ) {
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
  template <typename NumT>
  void Diapbar<NumT>::initialise( NumT* trackerPtr, NumT goal, int barLength ) {
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
  template <typename NumT>
  void Diapbar<NumT>::initInvalidAtr() {
    setTrackerPtr( nullptr );
    setGoal( (NumT) -1 );

    barLength_ = -1;
    stringCache_ = nullptr;
  }

  /// Initialises the tracker pointer attribute
  template <typename NumT>
  void Diapbar<NumT>::initTrackerPtr( NumT* trackerPtr ) {
    setTrackerPtr( trackerPtr );
  }

  /// Initalise the goal attribute
  template <typename NumT>
  void Diapbar<NumT>::initGoal( NumT goal ) {
    setGoal( goal );
  }

  /// Initialise the bar length attribute
  template <typename NumT>
  void Diapbar<NumT>::initBarLength( int barLength ) {
    if( !verifyCacheInit() ) {
      barLength_ = barLength;
    }
  }

  /// Initialise the string cache
  template <typename NumT>
  void Diapbar<NumT>::initStringCache() {
    if( !verifyCacheInit() ) {
      int fullLength = getFullLength();

      stringCache_ = new char[ fullLength ];

      for( int ii = 0; ii < fullLength; ii++ ) {
        stringCache_[ ii ] = ' ';
      }
    }
  }

  /// Initialise barFormat to default or input
  template <typename NumT>
  void Diapbar<NumT>::initBarFormat( char* formatPtr ) {
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
  template <typename NumT>
  bool Diapbar<NumT>::verifyInit() const {
    bool output = false;

    if( verifyCacheInit() && 
        ( trackerPtr_ != nullptr ) && 
        ( goal_ != (NumT) -1 ) &&
        ( barLength_ != -1 ) ) {

      output = true;
    }

    return output;
  }

  /**
   * Returns a boolean indicating whether the
   * cache is initialised.
   */
  template <typename NumT>
  bool Diapbar<NumT>::verifyCacheInit() const {
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
  template <typename NumT>
  int Diapbar<NumT>::getFillLength() const {
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
  template <typename NumT>
  int Diapbar<NumT>::getLeftLength() const {
    // Dependent on getFillLength() to reduce code reuse
    return (int) getBarLength() - getFillLength();
  }

  /**
   * Returns the number of characters required
   * to display the bar.
   */
  template <typename NumT>
  int Diapbar<NumT>::getDisplayLength() const {
    return getFullLength();
  }

  /**
   * Calculates the nummber of characters required
   * to fully display the bar.
   */
  template <typename NumT>
  int Diapbar<NumT>::getFullLength() const {
    // +2 for opening and closing characters
    return getBarLength() + 2;
  }


  // Mutators //

  /**
   * Sets the display format of the progress bar.
   *
   * @param[in] formatPtr a pointer to a char array of at least length 4.
   */
  template <typename NumT>
  void Diapbar<NumT>::setBarFormat( char* formatPtr ) {
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
  template <typename NumT>
  char* Diapbar<NumT>::buildBarToCache() const {
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
  template <typename NumT>
  std::string Diapbar<NumT>::buildStringFromCache() const {
    buildBarToCache();

    return std::string( (const char*) getStringCache(), getFullLength() );
  }
  

  // Operators //

  template <typename NumT>
  Diapbar<NumT>::operator std::string() const {
    return buildStringFromCache();
  }

  // Misc //

  /// Destructor
  template <typename NumT>
  Diapbar<NumT>::~Diapbar() {
    // Freeing the string cache
    if( verifyCacheInit() ) {
      delete[] stringCache_;
      stringCache_ = nullptr;
    }
  }
} 

#endif
