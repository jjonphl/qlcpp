#include "qlpch.h"

using namespace QuantLib;
using namespace std;

Real callFunc(Real spot, Real strike, Rate r, Volatility vol, Time tau, Real x) {
    Real mean = log(spot) + (r - 0.5*vol*vol) * tau;
    Real sd = vol*sqrt(tau);

    boost::math::lognormal_distribution<> d(mean, sd);
    return (x - strike) * boost::math::pdf(d, x) * exp(-r * tau);
}

Real computeBlackScholes(Real s0, Real k, Rate r, Time tau, Volatility sigma) {
    Real d1 = (log(s0/k) + (r + 0.5*sigma*sigma)*tau) / (sigma * sqrt(tau));
    Real d2 = d1 - (sigma * sqrt(tau));

    boost::math::normal_distribution<> std_norm;
    return s0 * boost::math::cdf(std_norm, d1) -
        k * exp(-r * tau) * boost::math::cdf(std_norm, d2);
}

void testIntegration4() {
    Real spot = 100.0;
    Rate r = 0.03;
    Time tau = 0.5;
    Volatility vol = 0.20;
    Real strike = 110.0;

    Real a = strike, b = strike*10.0;

    boost::function<Real (Real)> f;
    f = boost::bind(&callFunc, spot, strike, r, vol, tau, _1);

    Real absAcc = 0.00001;   // abs accuracy
    Size maxEval = 1000;     // max # eval
    SimpsonIntegral numInt(absAcc, maxEval);

    cout << "Call value: " << numInt(f, a, b) << endl;
    cout << "Call value (Black-Scholes): " << computeBlackScholes(spot, strike, r, tau, vol);

}

Real normalPdf(Real x) {
    boost::math::normal_distribution<> std_norm;
    return boost::math::pdf(std_norm, x);
}

Real normalCdf(Real x) {
    boost::math::normal_distribution<> std_norm;
    return boost::math::cdf(std_norm, x);
}

void testIntegration2() {

    boost::function<Real (Real)> pdf(normalPdf);

    GaussLaguerreIntegration gLagInt(16);        // [0,\infty)
    GaussHermiteIntegration gHerInt(16);         // (-\infty,\infty)
    GaussChebyshevIntegration gChebInt(64);      // (-1,1)
    GaussChebyshev2ndIntegration gChebInt2(64);  // (-1,1)

    Real analytical = normalCdf(1) - normalCdf(-1);

    cout << "Laguerre [0,\\infty) : " << gLagInt(pdf) << endl;
    cout << "Hermite (-\\infty,\\infty) : " << gHerInt(pdf) << endl;
    cout << "Analytical [-1,1] : " << analytical << endl;
    cout << "Cheb [-1,1] : " << gChebInt(pdf) << endl;
    cout << "Cheb 2 [-1,1] : " << gChebInt2(pdf) << endl;
}

// scale a [-1,1] integrator
// \int_{a}^{b} f(x) dx = \frac{b-a}{2} \int_{-1}^{1} 
//     f(\frac{b-1}{2} x + \frac{b+a}{2}) dx
Real normalPdf2(const Real& x, const Real& a, const Real& b) {
    boost::math::normal_distribution<> std_norm;
    Real t1 = 0.5*(b-a), t2 = 0.5*(b+a);
    return t1 * boost::math::pdf(std_norm, t1*x + t2);
}

void testIntegration3() {
    Real a = -1.96, b = 1.96;
    boost::function<Real (Real)> pdf;

    pdf = boost::bind(normalPdf2, _1, a, b);

    GaussChebyshevIntegration gChebInt(64);      // [-1,1]

    Real analytical = normalCdf(b) - normalCdf(a);

    cout << "Analytical: " << analytical << endl;
    cout << "Chebyshev: " << gChebInt(pdf) << endl;

}

int main(int argc, char *argv[]) {

    cout << "testIntegration4\n================\n";
    testIntegration4();

    cout << "\n\ntestIntegration2\n================\n";
    testIntegration2();

    cout << "\n\ntestIntegration3\n================\n";
    testIntegration3();

    return 0;
}
