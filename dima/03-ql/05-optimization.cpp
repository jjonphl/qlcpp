#include "qlpch.h"

using namespace QuantLib;
using namespace std;

class RosenBrockFunction : public CostFunction {
    public:
        Real value(const Array& x) const {
            QL_REQUIRE(x.size() == 2, "Rosenbrock function is 2-dim.");
            Real res = (1-x[0])*(1-x[0]) +
                100*(x[1]-x[0]*x[0])*(x[1]-x[0]*x[0]);
            return res;
        }
        Disposable<Array> values(const Array& x) const {
            QL_REQUIRE(x.size() == 2, "Rosenbrock function is 2-dim.");
            Array res(1);
            res[0] = value(x);
            return res;
        }
}; 

void testOptimizer1() {
    Size maxIterations = 1000;
    Size minStatIterations = 100;
    Real rootEpsilon = 1e-8;
    Real functionEpsilon = 1e-9;
    Real gradientEpsilon = 1e-5;

    EndCriteria ec(maxIterations, minStatIterations,
            rootEpsilon, functionEpsilon, gradientEpsilon);

    RosenBrockFunction f;
    NoConstraint constraint;

    Problem prob1(f, constraint, Array(2, 0.1));
    Problem prob2(f, constraint, Array(2, 0.1));

    Simplex solver1(0.1);
    ConjugateGradient solver2;

    EndCriteria::Type sol1 = solver1.minimize(prob1, ec);
    EndCriteria::Type sol2 = solver2.minimize(prob2, ec);

    cout << "Simplex: " << sol1 << endl;
    cout << "\tRoot: " << prob1.currentValue() << endl;
    cout << "\tMin F value: " << prob1.functionValue() << endl;
    cout << "Complex conjugate: " << sol2 << endl;
    cout << "\tRoot: " << prob2.currentValue() << endl;
    cout << "\tMin F value: " << prob2.functionValue() << endl;
}

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


class CallProblemFunction : public CostFunction {
    private:
        Real _c1, _c2, _c3, _c4;
        Real _k1, _k2, _k3, _k4;
        Rate _rd, _rf;
        Integer _phi;
        Time _tau;
    public:
        CallProblemFunction(const Rate& rd, const Rate& rf, 
                const Time& tau, const Integer& phi, 
                const Real& k1, const Real& k2, const Real& k3, const Real &k4,
                const Real& c1, const Real& c2, const Real& c3, const Real &c4) :
            _rd(rd), _rf(rf), _tau(tau), _phi(phi),
            _k1(k1), _k2(k2), _k3(k3), _k4(k4),
            _c1(c1), _c2(c2), _c3(c3), _c4(c4)  { }

        Real value(const Array& x) const {
            // squared error
            Array res0 = values(x);
            Real res = res0[0]*res0[0] + res0[1]*res0[1] +
                res0[2]*res0[2] + res0[3]*res0[3];
            return res;
        }

        Disposable<Array> values(const Array& x) const {
            Array res(4);
            res[0] = blackScholesPrice(x[0],_k1,_rd,_rf,x[1],_tau,_phi) - _c1;
            res[1] = blackScholesPrice(x[0],_k2,_rd,_rf,x[1],_tau,_phi) - _c2;
            res[2] = blackScholesPrice(x[0],_k3,_rd,_rf,x[1],_tau,_phi) - _c3;
            res[3] = blackScholesPrice(x[0],_k4,_rd,_rf,x[1],_tau,_phi) - _c4;

            return res;
        }
};

void testOptimizer2() {
    // market parameters: the optimizer's output should be close to this
    Real spot = 98.51;
    Volatility vol = 0.134;
    Real k1 = 87.0, k2 = 96.0, k3 = 103.0, k4 = 110.0;
    Rate rd = 0.002, rf = 0.01;
    Integer phi = 1;
    Time tau = 0.6;

    // calc Black-Scholes price
    Real c1 = blackScholesPrice(spot, k1, rd, rf, vol, tau, phi);
    Real c2 = blackScholesPrice(spot, k2, rd, rf, vol, tau, phi);
    Real c3 = blackScholesPrice(spot, k3, rd, rf, vol, tau, phi);
    Real c4 = blackScholesPrice(spot, k4, rd, rf, vol, tau, phi);

    CallProblemFunction f(rd, rf, tau, phi, k1, k2, k3, k4, c1, c2, c3, c4);

    Size maxIterations = 1000;
    Size minStatIterations = 100;
    Real rootEpsilon = 1e-5;
    Real functionEpsilon = 1e-5;
    Real gradientEpsilon = 1e-5;

    EndCriteria ec(maxIterations, minStatIterations, 
            rootEpsilon, functionEpsilon, gradientEpsilon);

    Array x0(2);    // initial guess
    x0[0] = 80.0; x0[1] = 0.20;

    NoConstraint constraint;
    Problem prob(f, constraint, x0);
    LevenbergMarquardt solver;
    EndCriteria::Type sol = solver.minimize(prob, ec);

    cout << "Criteria: " << sol << endl;
    cout << "Solution: (" << spot << ", " << vol << ")" << endl;
    cout << "Root: " << prob.currentValue() << endl;
    cout << "Min function value: " << prob.functionValue() << endl;
}

int main(int argc, char *argv[]) {
    testOptimizer1();
    testOptimizer2();

    return 0;
}

