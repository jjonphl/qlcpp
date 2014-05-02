#include "qlpch.h"

using namespace QuantLib;
using namespace std;

// there are differences in method signature b/w slides & QL 1.4
void testYield1() {
    DayCounter dc = ActualActual();
    InterestRate rate(0.0341, dc, Simple, Annual);

    cout << "Rate: " << rate << endl;
    Date d1(10, Sep, 2009), d2 = d1 + 3*Months;

    Real compFactor = rate.compoundFactor(d1, d2);
    cout << "Compound factor: " << compFactor << endl;
    cout << "Discount factor: " << rate.discountFactor(d1, d2) << endl;
    //cout << "Equivalent rate: " << rate.equivalentRate(d1, d2, dc, Continuous, Semiannual) << endl;
    cout << "Equivalent rate: " << rate.equivalentRate(dc, Continuous, Semiannual, d1, d2) << endl;

    // not in QL 1.4
    //Real implRate = InterestRate::impliedRate(compFactor, d1, d2, dc, Simple, Annual);
    Real implRate = InterestRate::impliedRate(compFactor, dc, Simple, Annual, d1, d2);
    cout << "Implied rate from compound factor: " << implRate << endl;
}

int main(int argc, char *argv[]) {
    testYield1();

    return 0;
}
