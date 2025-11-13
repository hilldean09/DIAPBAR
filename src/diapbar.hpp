// Diapbar header file

#ifndef DIAPBAR_H
#define DIAPBAR_H

#include "diapbar_core.hpp"

namespace Diapbar {

class Diapbar {
  public:
    Diapbar( char* formatPtr = nullptr );
    Diapbar( int barLength, char* formatPtr = nullptr  );
    Diapbar( int* trackerPtr, int goal, int barLength, char* formatPtr = nullptr  );

    void initialise( int barLength );
    void initialise( int* trackerPtr, int goal );
    void initialise( int* trackerPtr, int goal, int barLength );

    char* getStringCache() const { return stringCache_; }
    int getFullLength() const { return ( barLength_ + 2 ); }

    void setBarFormat( char* formatPtr );

    char* buildBarToCache() const;

  private:
    // Attributes
      int* trackerPtr_;
      int goal_;

      mutable char* stringCache_;
      int barLength_;

      Core::BarFormat barFormat_;

      bool isInitialised_;

    // Initialisers
      void initInvalidAtr();

      void initTrackerPtr( int* trackerPtr );
      void initGoal( int goal );
      void initBarLength( int barLength );
      void initStringCache();

      void initBarFormat( char* formatPtr );

      // Verifier
      bool verifyInit() const;
      bool verifyCacheInit() const;

    // Accessors
      int* getTrackerPtr() const { return trackerPtr_; }
      int getTrackerValue() const { return *(trackerPtr_); }

      int getGoal() const { return goal_; }
      
      int getBarLength() const { return barLength_; }

      char getOpenChar() const { return barFormat_.openChar; }
      char getFillChar() const { return barFormat_.fillChar; }
      char getEmptyChar() const { return barFormat_.emptyChar; }
      char getCloseChar() const { return barFormat_.closeChar; }
    
    // Mutators
      void setTrackerPtr( int* trackerPtr ) { trackerPtr_ = trackerPtr; }
      void setGoal( int goal ) { goal_ = goal; }

      // Set barlength cannot be included trivially due to the cache's dependency on it
      
      void setBarFormat( Core::BarFormat barFormat ) { barFormat_ = barFormat; }

    // Methods
      int getFillLength() const;
      int getLeftLength() const;

  /**
   * String standard library functionallity
   */ 
  #ifdef _GLIBCXX_STRING

  #endif

  /**
   * String view standard library functionallity
   */
  #ifdef _GLIBCXX_STRING_VIEW

  #endif
};

}

#endif 
