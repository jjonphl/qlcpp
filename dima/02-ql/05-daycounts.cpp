#include <iostream>
#include <ql/quantlib.hpp>

using namespace std;
using namespace QuantLib;

void dayCounterTesting1() {
    DayCounter dc = Thirty360();
    Date d1(1, Oct, 2009);
    Date d2 = d1 + 2*Months;

    cout << "Days between d1/d2: " << dc.dayCount(d1, d2) << std::endl;
    cout << "Year fraction d1/d2: " << dc.yearFraction(d1, d2) << std::endl;
}

int main(int argc, char *argv[]) {
    dayCounterTesting1();

    return 0;
}
