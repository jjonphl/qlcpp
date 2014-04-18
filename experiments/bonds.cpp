#include <iostream>
#include <ql/quantlib.hpp>
//#include "qlpch.h"

using namespace QuantLib;
using namespace std;

void test1() {
    Settings::instance().evaluationDate() = Date(17, Apr, 2017);

    Natural settlementDays = 2;
    Real faceAmount = 100.0;
    DayCounter dc = Thirty360(Thirty360::EurobondBasis);
    Schedule sched(Date(15, Jan, 2014),   // effectiveDate (issue date)
                   Date(15, Jan, 2024),   // terminationDate (maturity)
                   Period(Semiannual),
                   TARGET(),
                   Unadjusted,            // bdc
                   Unadjusted,            // terminationDate bdc
                   DateGeneration::Backward,
                   false);                // always end of month

    FixedRateBond bond(settlementDays, 
                       faceAmount, 
                       sched,
                       std::vector<Rate>(1, 0.045),  // uniform coupon (len=1)
                       dc,                           // accrualDayCounter
                       ModifiedFollowing,            // accrualConvention
                       100.0,                        // redemption
                       Date(15, Jan, 2014));         // issueDate

    cout << "Issue date: " << bond.issueDate() << endl;
    cout << "Maturity date: " << bond.maturityDate() << endl;
    cout << "Settlement date: " << bond.settlementDate() << endl;

    InterestRate yield(0.03, dc, Simple, Annual);
    //InterestRate yield(0.015, dc, Compounded, Semiannual);

    // expected: 112.57326469
    // output: 112.771 (Compounded)
    // output: 112.569 (Simple)
    cout << "Clean price: " << BondFunctions::cleanPrice(bond, yield, Date(22, Apr, 2014));

}

int main(int argc, char *argv[]) {
    test1();

    return 0;
}
