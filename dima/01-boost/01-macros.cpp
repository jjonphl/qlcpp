#include <vector>
#include <boost/current_function.hpp>
#include <boost/foreach.hpp>
#include <boost/static_assert.hpp>
#include <boost/detail/lightweight_test.hpp>

#define MY_NUM 1300

void testMacroA() {
    std::cout << "You have called: " << BOOST_CURRENT_FUNCTION << std::endl;
}

void testMacroB() {
    BOOST_STATIC_ASSERT(MY_NUM != 1400);
}

void testMacroC() {
    std::vector<double> myVec(10);
    
    BOOST_FOREACH(double &x, myVec) x = 10.0;
    BOOST_FOREACH(double x, myVec) std::cout << x << std::endl;
}

void testMacroD() {
    BOOST_ERROR("Failure of this function");
    double x = 0.0;
    BOOST_TEST(x != 0);
}

int main(int argc, char **argv) {
    testMacroA();
    testMacroB();
    testMacroC();
    testMacroD();
}
