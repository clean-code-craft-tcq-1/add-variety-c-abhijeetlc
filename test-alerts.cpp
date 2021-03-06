#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

/* ------------------*************---------------------
Flow of test / code 

checkAndAlert()
    \  /
     \/
classifyTemperatureBreach()
    \  /
     \/
 inferBreach()
 
 ------------------*************--------------------- */
    
TEST_CASE("infers the breach according to limits") {
  REQUIRE(checkAndAlert(TO_CONTROLLER,PASSIVE_COOLING,30) != TOO_LOW);
}
