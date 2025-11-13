
#include <iostream>
#include <string>

#include "diapbar.hpp"

void runDiapbarTest( Diapbar::Diapbar testingBar, int* trackerPtr, int goal ) {
  int tmp;

  char* stringCache = testingBar.getStringCache();
  int stringCacheLen = testingBar.getFullLength();

  for( int ii = 0; ii <= goal; ii++ ) {
    tmp = ( (int) ( ii / 0.0015351834 ) ) % 3;

    *trackerPtr = ii;

    std::cout << '\r';

    testingBar.buildBarToCache();
    std::cout.write( stringCache, stringCacheLen );
    
  }

  std::cout << std::endl;

}

void runStringTest( Diapbar::Diapbar* testingBar, int* trackerPtr, int goal ) {
  int tmp;

  for( int ii = 0; ii <= goal; ii++ ) {
    tmp = ( (int) ( ii / 0.0015351834 ) ) % 3;

    *trackerPtr = ii;
    
    std::cout << '\r' << (std::string) *testingBar;

  }
  
  std::cout << std::endl;

}

int main() {

  int tracker;
  int goal = 2000000;
  int barLength = 10;

  Diapbar::Diapbar testingBar;

  // Instancing test
  testingBar.initialise( barLength );
  testingBar.initialise( &tracker, goal );

  runStringTest( &testingBar, &tracker, goal );

  // setBarFormat test
  char tmpFormat[4] = {'/', '=', ' ', '/' };
  testingBar.setBarFormat( tmpFormat );

  runStringTest( &testingBar, &tracker, goal );


  return 0;
}
