// Core assets for all diapbar derivatives

#ifndef DIAPBAR_CORE_H
#define DIAPBAR_CORE_H

#include <string>
#include <string_view>

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


    // <string> functionallity //
    #if( DIAPBAR_ALLOW_STRING == 1 )
    public:
      virtual explicit operator std::string() const = 0;
      virtual void setBarFormat( std::string format ) = 0;

    #endif


    // <string_view> functionallity //
    #if( DIAPBAR_ALLOW_STRING_VIEW == 1 )
    public:
      virtual explicit operator std::string_view() const = 0;
      virtual void setBarFormat( std::string_view format ) = 0;

    #endif


  };
}

#endif
