// Diapbar header file

#ifndef DIAPBAR_H
#define DIAPBAR_H

#include <string>
#include <iostream>

#include "diapbar_core.hpp"

namespace Diapbar {

template <typename NumT = int>
class Diapbar {
  public:

    // Constuctors //
      Diapbar( char* formatPtr = nullptr );
      Diapbar( int barLength, char* formatPtr = nullptr  );
      Diapbar( NumT* trackerPtr, NumT goal, int barLength, char* formatPtr = nullptr  );


    // Initialisers //
      void initialise( int barLength );
      void initialise( NumT* trackerPtr, NumT goal );
      void initialise( NumT* trackerPtr, NumT goal, int barLength );


    // Accessors //
      char* getStringCache() const { return stringCache_; }
      int getDisplayLength() const;


    // Mutators //
      void setBarFormat( char* formatPtr );

      char* buildBarToCache() const;


    // Operators //
      explicit operator std::string() const;


    // Misc //
      ~Diapbar();

  private:
    // Attributes
      NumT* trackerPtr_;
      NumT goal_;

      mutable char* stringCache_;
      int barLength_;

      Core::BarFormat barFormat_;

      bool isInitialised_;


    // Initialisers
      void initInvalidAtr();

      void initTrackerPtr( NumT* trackerPtr );
      void initGoal( NumT goal );
      void initBarLength( int barLength );
      void initStringCache();

      void initBarFormat( char* formatPtr );


    // Verifiers //
      bool verifyInit() const;
      bool verifyCacheInit() const;


    // Accessors
      NumT* getTrackerPtr() const { return trackerPtr_; }
      NumT getTrackerValue() const { return *(trackerPtr_); }

      NumT getGoal() const { return goal_; }
      
      int getBarLength() const { return barLength_; }

      char getOpenChar() const { return barFormat_.openChar; }
      char getFillChar() const { return barFormat_.fillChar; }
      char getEmptyChar() const { return barFormat_.emptyChar; }
      char getCloseChar() const { return barFormat_.closeChar; }
    
      int getFillLength() const;
      int getLeftLength() const;

      int getFullLength() const;


    // Mutators
      void setTrackerPtr( NumT* trackerPtr ) { trackerPtr_ = trackerPtr; }
      void setGoal( NumT goal ) { goal_ = goal; }

      // Set barlength cannot be included trivially due to the cache's dependency on it
      
      void setBarFormat( Core::BarFormat barFormat ) { barFormat_ = barFormat; }


    // Methods
      std::string buildStringFromCache() const;

};

}

#endif 
