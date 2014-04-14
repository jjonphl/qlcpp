#include <iostream>
#include <ql/quantlib.hpp>

using namespace std;
using namespace QuantLib;

void DateTesting1() {

    Date myDate(12, Aug, 2009);
    std::cout << myDate << std::endl;

    myDate++;
    std::cout << myDate << std::endl;

    myDate += 12*Days;
    std::cout << myDate << std::endl;

    myDate -= 2*Months;
    std::cout << myDate << std::endl;

    myDate--;
    std::cout << myDate << std::endl;

    Period p(10, Weeks);
    myDate += p;
    std::cout << myDate << std::endl;
}

void DateTesting2() {
    Date myDate(12, Aug, 2009);

    cout << "Original date: " << myDate << endl;
    cout << "Weekday: " << myDate.weekday() << endl;
    cout << "Day of month: " << myDate.dayOfMonth() << endl;
    cout << "Day of year: " << myDate.dayOfYear() << endl;
    cout << "Month: " << myDate.month() << endl;

    int month = myDate.month();
    cout << "Month via int: " << month << endl;
    cout << "Year: " << myDate.year() << endl;

    int serialNum = myDate.serialNumber();
    cout << "Serial number: " << serialNum << endl;
}

void DateTesting3() { // static functions
    cout << "Today: " << Date::todaysDate() << endl;
    cout << "Min Date: " << Date::minDate() << endl;
    cout << "Max Date: " << Date::maxDate() << endl;
    cout << "Is leap year?: " << Date::isLeap(2011) << endl;
    cout << "End of month: " << Date::endOfMonth(Date(4,Aug,2009)) << endl;
    cout << "Is month end?: " << Date::isEndOfMonth(Date(29,Sep,2009)) << endl;
    cout << "Is month end?: " << Date::isEndOfMonth(Date(30,Sep,2009)) << endl;
    cout << "Next week day: " << Date::nextWeekday(Date(1,Sep,2009), Friday) << endl;
    cout << "nth week day: " << Date::nthWeekday(3, Wed, Sep, 2009) << endl;
}

void DateTesting4() {
    Date d = Settings::instance().evaluationDate();

    cout << "Eval date (default): " << d << endl;

    Settings::instance().evaluationDate() = Date(5, Jan, 1995);
    d = Settings::instance().evaluationDate();
    cout << "Eval date (after): " << d << endl;
}

int main(int argc, char *argv[]) {
    //DateTesting1();
    //DateTesting2();
    //DateTesting3();
    DateTesting4();
    
    return 0;
}

