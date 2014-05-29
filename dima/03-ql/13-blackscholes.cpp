#include "qlpch.h"
#include <boost/shared_ptr.hpp>

using namespace QuantLib;
using namespace std;

void testBlackScholes1() {
    Real s0 = 100.0, k = 105.0;
    Real rd = 0.034, rf = 0.021, tau = 0.5, vol = 0.177;
    Real domDisc = exp(-rd * tau), forDisc = exp(-rf * tau);
    Real stdDev = vol * sqrt(tau);

    boost::shared_ptr<PlainVanillaPayoff> vanillaPut(
            new PlainVanillaPayoff(Option::Put, k));
    boost::shared_ptr<AssetOrNothingPayoff> aonCall(
            new AssetOrNothingPayoff(Option::Call, k));

    BlackScholesCalculator vanillaPutPricer(vanillaPut, s0, forDisc, stdDev, domDisc);
    BlackScholesCalculator aonCallPricer(aonCall, s0, forDisc, stdDev, domDisc);

    cout << "------------------- Vanilla Put -------------------------" << endl;
    cout << "Value: " << vanillaPutPricer.value() << endl;
    cout << "Delta: " << vanillaPutPricer.delta() << endl;
    cout << "Gamma: " << vanillaPutPricer.gamma() << endl;
    cout << "Vega: " << vanillaPutPricer.vega(tau) << endl;
    cout << "Theta: " << vanillaPutPricer.theta(tau) << endl;
    cout << "Delta fwd: " << vanillaPutPricer.deltaForward() << endl;
    cout << "Gamma fwd: " << vanillaPutPricer.gammaForward() << endl;
    cout << "------------------- AON Call -------------------------" << endl;
    cout << "Value: " << aonCallPricer.value() << endl;
    cout << "Delta: " << aonCallPricer.delta() << endl;
    cout << "Gamma: " << aonCallPricer.gamma() << endl;
    cout << "Vega: " << aonCallPricer.vega(tau) << endl;
    cout << "Theta: " << aonCallPricer.theta(tau) << endl;
    cout << "Delta fwd: " << aonCallPricer.deltaForward() << endl;
    cout << "Gamma fwd: " << aonCallPricer.gammaForward() << endl;
}

int main(int argc, char *argv[]) {
    testBlackScholes1();

    return 0;
}
