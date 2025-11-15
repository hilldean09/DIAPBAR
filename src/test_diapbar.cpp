
#include <iostream>
#include <string>

#include "diapbar.hpp"

void runStringTest( Diapbar::Diapbar<int>* testingBar, int* trackerPtr, int goal ) {
  int tmp;

  for( int ii = 0; ii <= goal; ii++ ) {
    tmp = ( (int) ( ii / 0.0015351834 ) ) % 3;

    *trackerPtr = ii;
    
    std::cout << '\r' << (std::string) *testingBar;

  }
  
  std::cout << std::endl;

}

template <typename NumT, typename ConvT = std::string>
int runGeneralTest( Diapbar::Diapbar<NumT> &testingBar, NumT* trackerPtr, NumT goal) {
  int tmp;

  for( int ii = 0; ii <= goal; ii++ ) {
    tmp = ( (int) ( ii / 0.0015351834 ) ) % 3;

    *trackerPtr = ii;
    
    std::cout << '\r' << (ConvT) testingBar;

  }
  
  std::cout << std::endl;

  return tmp;
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

  // string_view test
  runGeneralTest<int, std::string_view>( testingBar, &tracker, goal );

  // Copy constructor test 
  Diapbar::Diapbar copiedBar = testingBar;
  runGeneralTest<int>( copiedBar, &tracker, goal );

  return 0;
}
