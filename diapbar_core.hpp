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

}

#endif
