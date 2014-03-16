#include <boost/function.hpp>
#include <boost/bind.hpp>

double myCall(const double& spot, const double& strike) {
    return std::max(spot - strike, 0.0);
}

double myPut(const double&spot, const double& strike) {
    return std::max(strike - spot, 0.0);
}

void printRes(boost::function<double(double,double)> f,
        const double& x, const double& y) {
    std::cout << "Result: " << f(x,y) << std::endl;
}

void testingFunction1() {
    double s = 112.5, K = 105.0;
    boost::function<double(double, double)> funcPtr;

    funcPtr = myCall;
    printRes(funcPtr, s, K);

    funcPtr = myPut;
    printRes(funcPtr, s, K);
}

class FunctionClass {
    private:
        double a_;
    public:
        FunctionClass(const double& a) : a_(a) {}

        double multWithA(const double& x) const { return a_*x; }
        double operator() (const double& x) const {return a_*x; }
};

void testingFunction2() {
    FunctionClass myClass(2.0);

    double x = 12.0;

    boost::function<double(FunctionClass*, double)> funcPtr, funcPtr1;

    funcPtr = &FunctionClass::multWithA;
    funcPtr1 = &FunctionClass::operator();

    std::cout << myClass.multWithA(x) << std::endl;
    std::cout << funcPtr(&myClass, x) << std::endl;
    std::cout << funcPtr1(&myClass, x) << std::endl;

    // bind the function with the class instance
    boost::function<double (double)> funcPtrNew;
    funcPtrNew = boost::bind(funcPtr, &myClass, _1);

    std::cout << funcPtrNew(x) << std::endl;
}

double myMult(const double &x, const double &y) {
    return x*y;
}

void testingFunction3() {
    boost::function<double (double,double)> myMultPtr;
    myMultPtr = boost::ref(myMult);
    std::cout << myMultPtr(3.0, 3.0) << std::endl;
}


int main(int argc, char *argv[]) {
    testingFunction1();
    testingFunction2();
    testingFunction3();
}
