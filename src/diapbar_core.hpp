// Core assets for all diapbar derivatives

#ifndef DIAPBAR_CORE_H
#define DIAPBAR_CORE_H

namespace Diapbar::Core {

  /**
  * Defines the basic bar format.
  *
  * I.e. the opening, filling (completed), empty (uncompleted), and closing characters.
  */
  struct BarFormat {

    char openChar;
    char fillChar;
    char emptyChar;
    char closeChar;

  };

  constexpr BarFormat DEFAULT_BAR_FORMAT = BarFormat{ '[', '#', ' ', ']' };


  template <typename NumT>
  class Diapbar_Base {
    public:

    // Initialiseers //
      virtual void initialise( int barLength ) = 0;
      virtual void initialise( NumT* trackerPtr, NumT goal ) = 0;
      virtual void initialise( NumT* trackerPtr, NumT goal, int barLength ) = 0;

    // Accessors //
      virtual char* getStringCache() const = 0;

      virtual int getDisplayLength() const = 0;
      virtual int getCacheLength() const = 0;

    // Mutators //
      virtual void setBarFormat( char* formatPtr ) = 0;

      virtual char* buildBarToCache() const = 0;


  };
}

}
#endif
