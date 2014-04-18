#include <iostream>
#include <ql/quantlib.hpp>

using namespace QuantLib;
using namespace std;

void inspectors() {
    Rate r = 0.0341;
    DayCounter dc = ActualActual();
    Compounding c = Continuous;
    Frequency freq = Annual;

    InterestRate rate(r, dc, c, freq); 

    cout << "Inspectors:\n===========\n\n";
    cout << "rate: " << rate.rate() << endl;
    cout << "day count: " << rate.dayCounter() << endl;
    cout << "compounding: " << rate.compounding() << endl;
    cout << "frequency: " << rate.frequency() << endl;
}

void discounting() {
    Rate r = 0.0341;
    DayCounter dc = ActualActual();
    Compounding c = Continuous;
    Frequency freq = Annual;

    Date valueDate(14, Apr, 2014);
    Date d1(30, Apr, 2014);

    InterestRate rate(r, dc, c, freq); 

    cout << "Discount factor: " << rate.discountFactor(valueDate, d1) << endl;

}

void compounding() {
}

void conversions() {
    // equivalentRate() - e.g. use different day count, frequency, etc
    // return a new InterestRate() object s.t. the existing int rate has
    // the same rate as the resulting int rate for the time period
}

void impliedRate() {
    // impliedRate() - returns the rate that will result to the desired
    // compound factor and time period
}

int main(int argc, char *argv[]) {
    //discounting();

    return 0;
}
