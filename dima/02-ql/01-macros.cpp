#include <iostream>
#include <ql/quantlib.hpp>

using namespace QuantLib;
using namespace std;


void testingMacros1() {
    double x = 0.0;
    QL_REQUIRE(x != 0, "Zero number!");
}

void testingMacros2() {
    QL_FAIL("Failed!");
}


void testingMacros3() {
    std::cout << "Current QL version: " << QL_LIB_VERSION << std::endl;
}

int main(int argc, char *argv[]) {

    testingMacros3();
    
    try {
        testingMacros1();
    } catch(std::exception &e) {
        std:cout << e.what() << std::endl;
        return -1;
    } catch(...) {
        std::cout << "unknown error" << std::endl;
        return 1;
    }

    return 0;
}
