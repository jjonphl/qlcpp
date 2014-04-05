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

int main(int argc, char *argv[]) {
    //DateTesting1();
    DateTesting2();
    
    return 0;
}

