#include "qlpch.h"
#include <vector>
#include <algorithm>

using namespace QuantLib;
using namespace std;

void testInterpolation1() {
    vector<Real> x(5), y(x.size());

    x[0] = 0.0;
    x[1] = 1.0;
    x[2] = 2.0;
    x[3] = 3.0;
    x[4] = 4.0;

    transform(x.begin(), x.end(), y.begin(), (double (*)(double))std::exp);

    LinearInterpolation linInt(x.begin(), x.end(), y.begin());

    cout << "exp(0.0) = " << linInt(0.0) << endl;
    cout << "exp(0.5) = " << linInt(0.5) << endl;
    cout << "exp(1.0) = " << linInt(1.0) << endl;
}

void testInterpolation2() {
    vector<Real> strike(5), vol(strike.size());

    strike[0] = 70.0; vol[0] = 0.241;
    strike[1] = 80.0; vol[1] = 0.224;
    strike[2] = 90.0; vol[2] = 0.201;
    strike[3] = 100.0; vol[3] = 0.211;
    strike[4] = 110.0; vol[4] = 0.226;

    CubicNaturalSpline interp(strike.begin(), strike.end(), vol.begin());

    cout << "vol(strike=70.0) = " << interp(70.0) << endl;
    cout << "vol(strike=75.0) = " << interp(75.0) << endl;
    cout << "vol(strike=79.0) = " << interp(79.0) << endl;
}

void testInterpolation3() {
    vector<Real> strike(5), vol(strike.size());

    strike[0] = 70.0; vol[0] = 0.241;
    strike[1] = 80.0; vol[1] = 0.224;
    strike[2] = 90.0; vol[2] = 0.201;
    strike[3] = 100.0; vol[3] = 0.211;
    strike[4] = 110.0; vol[4] = 0.226;

    CubicNaturalSpline cubic1(strike.begin(), strike.end(), vol.begin());

    // continuous 2nd deriv 
    CubicInterpolation cubic2(strike.begin(), strike.end(), vol.begin(),
            CubicInterpolation::Spline, false,
            CubicInterpolation::SecondDerivative, 0.0,
            CubicInterpolation::SecondDerivative, 0.0);

    cout << "Nat cub: " << cubic1(75.0) << endl;
    cout << "Nat cub manual: " << cubic1(75.0) << endl;
}

int main(int argc, char *argv[]) {
    testInterpolation1();

    testInterpolation2();

    testInterpolation3();

    return 0;
}
