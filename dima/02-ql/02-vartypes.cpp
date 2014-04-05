#include <iostream>
#include <ql/quantlib.hpp>

using namespace std;
using namespace QuantLib;

// exercise
Real myReciproke(Real x) {
    QL_REQUIRE(x != 0, "Zero number!");
    return 1/x;
}

int main(int argc, char *argv) {
    Real x = 3.1416;

    std::cout << "myReciproke: " << myReciproke(x) << std::endl;
}
