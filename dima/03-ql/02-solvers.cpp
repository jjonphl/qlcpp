#include "qlpch.h"

using namespace QuantLib;
using namespace std;

Real blackScholesPrice(const Real& spot, const Real& strike, const Rate& rd,
        const Rate& rf, const Volatility& vol, const Time& tau, const Integer& phi) {
    boost::math::normal_distribution<> d;
    Real dp, dm, fwd, stdDev, res, domDf, forDf;

    domDf = std::exp(-rd*tau);
    forDf = std::exp(-rf*tau);
    fwd = spot * forDf / domDf;
    stdDev = vol * std::sqrt(tau);

    dp = (std::log(fwd/strike) + 0.5*stdDev*stdDev) / stdDev;
    dm = (std::log(fwd/strike) - 0.5*stdDev*stdDev) / stdDev;

    res = phi * domDf * (fwd * boost::math::cdf(d, phi*dp) - 
            strike * boost::math::cdf(d, phi*dm));
    return res;
}

Real impliedVolProblem(const Real& spot, const Real& strike, const Rate& rd,
        const Rate& rf, const Volatility& vol, const Time& tau,
        const Integer& phi, const Real& price) {
    return blackScholesPrice(spot, strike, rd, rf, vol, tau, phi) - price;
}

void testSolver1() {
    Real spot = 100.0;
    Real strike = 110.0;
    Rate rd = 0.002, rf = 0.01;
    Time tau = 0.5;
    Integer phi = 1;
    Real vol = 0.1423;

    // calculate Black-Scholes price
    Real price = blackScholesPrice(spot, strike, rd, rf, vol, tau, phi);

    // setup solver
    Bisection solver1;
    Brent solver2;
    Ridder solver3;
    Real accuracy = 0.00001, guess = 0.25;
    Real min = 0.0, max = 1.0;

    // setup function to solve
    boost::function<Real (Volatility)> f;
    f = boost::bind(&impliedVolProblem, spot, strike, rd, rf, _1, tau, phi, price);

    Real res1 = solver1.solve(f, accuracy, guess, min, max);
    Real res2 = solver2.solve(f, accuracy, guess, min, max);
    Real res3 = solver3.solve(f, accuracy, guess, min, max);

    cout << "Input volatility: " << vol << endl;
    cout << "Implied volatility (Bisection): " << res1 << endl;
    cout << "Implied volatility (Brent): " << res2 << endl;
    cout << "Implied volatility (Ridder): " << res3 << endl;
}


class BlackScholesClass {
    private:
        Real _spot, _strike, _price, _logFwd;
        Real _dp, _domDf, _forDf, _fwd, _sqrtTau;
        Rate _rd, _rf;
        Integer _phi;
        Time _tau;
        boost::math::normal_distribution<> d;

    public:
        BlackScholesClass(const Real& spot, const Real& strike, 
                const Rate& rd, const Rate& rf, const Time& tau, 
                const Integer& phi, const Real& price) :
            _spot(spot), _strike(strike), _rd(rd), _rf(rf), _phi(phi),
            _tau(tau), _price(price), _sqrtTau(std::sqrt(tau)) {

            _domDf = std::exp(- _rd*_tau);
            _forDf = std::exp(- _rf*_tau);
            _fwd = _spot * _forDf/_domDf;
            _logFwd = std::log(_fwd/_strike);
        }

        Real operator()(const Volatility& x) const {
            return impliedVolProblem(_spot, _strike, _rd, _rf, x, _tau, 
                    _phi, _price);
        }

        Real derivative(const Volatility& x) const {
            // vega
            Real stdDev = x * _sqrtTau;
            Real dp = (_logFwd + 0.5*stdDev*stdDev) / stdDev;
            return _spot*_forDf*boost::math::pdf(d,dp)*_sqrtTau; 
        }
};

void testSolver2() {
    Real spot = 100.0;
    Real strike = 110.0;
    Rate rd = 0.002, rf = 0.01, tau = 0.5;
    Integer phi=1;
    Real vol = 0.1423;

    Real price = blackScholesPrice(spot, strike, rd, rf, vol, tau, phi);

    BlackScholesClass f(spot, strike, rd, rf, tau, phi, price);

    Newton solver1;
    Real accuracy=0.0001, guess = 0.10;
    Real step = 0.001;

    Real res = solver1.solve(f, accuracy, guess, step);

    cout << "Input volatility: " << vol << endl;
    cout << "Implied volatility (Newton): " << res << endl;
}

int main(int argc, char *argv[]) {
    testSolver1();

    cout << "\n\n";

    testSolver2();

    return 0;
}
