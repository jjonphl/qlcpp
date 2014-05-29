#include "qlpch.h"

using namespace QuantLib;
using namespace std;

// payoffs & exercises

// <ql/instruments/payoffs.hpp>
// * PlainVanillaPayoff = max(\phi (S_T - K), 0)
//     - \phi = 1 for call, \phi = -1 for put
// * PercentageStrikePayoff = max(\phi (S_T - m*S_T), 0)
//     - m = moneyness variagle, e.g. m=1.10
// * AssetOrNothing = S_T I(\phi S_T > \phi K)
//     - I(.) = indicator function
// * CashOrNothingPayoff = C I(\phi S_T > \phi K)
//     - C = cash
// * GapPayoff = max(\phi (S_T-K_2), 0 ) I(\phi S_T > \phi K_1)
void testPayoff1() {
    Real s0 = 100.0, sT = 123.0;
    Real k1 = 105.0, k2 = 112.0;
    Real moneyness = 1.10, cash = 10.0;

    PlainVanillaPayoff vanillaCall(Option::Call, k1);
    PlainVanillaPayoff vanillaPut(Option::Put, k1);

    PercentageStrikePayoff percentageCall(Option::Call, moneyness);
    PercentageStrikePayoff percentagePut(Option::Put, moneyness);

    AssetOrNothingPayoff aonCall(Option::Call, k1);
    AssetOrNothingPayoff aonPut(Option::Put, k1);

    CashOrNothingPayoff conCall(Option::Call, k1, cash);
    CashOrNothingPayoff conPut(Option::Put, k1, cash);

    GapPayoff gapCall(Option::Call, k1, k2);
    GapPayoff gapPut(Option::Call, k1, k2);

    cout << "S(0): " << s0 << ", S(T): " << sT << endl;
    cout << "Strike: " << k1 << endl;
    cout << "Gap strike: " << k2 << ", Moneyness strike: " << moneyness << endl;
    cout << "Vanilla call payout: " << vanillaCall(sT) << endl;
    cout << "Vanilla put payout: " << vanillaPut(sT) << endl;
    cout << "Percentage call payout: " << percentageCall(sT) << endl;
    cout << "Percentage put payout: " << percentagePut(sT) << endl;
    cout << "AssetOrNothing call payout: " << aonCall(sT) << endl;
    cout << "AssetOrNothing put payout: " << aonPut(sT) << endl;
    cout << "CashOrNothing call payout: " << conCall(sT) << endl;
    cout << "CashOrNothing put payout: " << conPut(sT) << endl;
    cout << "Gap call payout: " << gapCall(sT) << endl;
    cout << "Gap put payout: " << gapPut(sT) << endl;
}

// <ql/exercise.hpp>
// * EuropeanExercise
// * AmericanExercise
// * BermudanExercise


int main(int argc, char *argv) {
    testPayoff1();

    return 0;
}
