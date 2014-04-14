#include <iostream>
#include <ql/quantlib.hpp>
#include <boost/foreach.hpp>

using namespace std;
using namespace QuantLib;

// calendar functions:
// isBusinessDay(const Date& d)
// isHoliday(const Date& d)
// isWeekend(Weekday w)
// isEndOfMonth(const Date& d)
// Date endOfMonth(const Date& d)

void CalendarTesting1() {
    Calendar frankfCal = Germany(Germany::FrankfurtStockExchange);
    Calendar saudiCal = SaudiArabia();
    Date nyEve(31, Dec, 2009);

    cout << "Is business day? (Frankfurt): " << frankfCal.isBusinessDay(nyEve) << endl;
    cout << "Is holiday? (Frankfurt): " << frankfCal.isHoliday(nyEve) << endl;
    cout << "Is weekend? (Saudi Arabia): " << saudiCal.isWeekend(Saturday) << endl;
    cout << "Is last business day? (Frankfurt): " << frankfCal.isEndOfMonth(Date(30,Dec,2009)) << endl;
    cout << "Last business day? (Frankfurt): " << frankfCal.endOfMonth(nyEve) << endl;
}

// customizing calendars
// addHoiday(const Date& d)
// removeHoliday(const Date &d)
// std::vector<Date> holidayList(const Calendar& calendar, const Date& from, const Date& to, bool includeWeekends)

void CalendarTesting2() {
    Calendar frankfCal = Germany(Germany::FrankfurtStockExchange);
    Date d1(24, Dec, 2009), d2(30, Dec, 2009), d3(31, Dec, 2009);

    frankfCal.addHoliday(d2);
    frankfCal.removeHoliday(d3);

    cout << "Is business day?: " << frankfCal.isBusinessDay(d2) << endl;
    cout << "Is business day?: " << frankfCal.isBusinessDay(d3) << endl;

    std::vector<Date> holidays = frankfCal.holidayList(frankfCal, d1, d2, false);
    cout << "------------------------------" << endl;
    BOOST_FOREACH(Date d, holidays) cout << d << endl;
}

// BusinessDayConvention enum(?)
// * Following
// * ModifiedFollowing
// * Preceding
// * ModifiedPreceding
// * Unadjusted
//
// Calendar functions
// Date adjust(const Date&, BusinessDayConvention convention)
// Date advance(const Date&, const Periond&, DayConvention, bool endOfMonth)
// BigInteger businessDaysBetween(const Date& from, const Date& to, 
//     bool includeFirst, bool includeLast) - # of business days

void CalendarTesting3() {
    Calendar frankfCal = Germany(Germany::FrankfurtStockExchange);

    Date d1(31,Oct,2009), d2(1,Jan,2010);

    cout << "Date 2 adjust (Preceding): " << frankfCal.adjust(d2, BusinessDayConvention(Preceding)) << endl;
    cout << "Date 2 adjust (ModifiedPreceding): " << frankfCal.adjust(d2, BusinessDayConvention(ModifiedPreceding)) << endl;

    Period mat(2, Months);
    cout << "Date 1 month adv: " << frankfCal.advance(d1, mat, BusinessDayConvention(Following), false) << endl;
    cout << "Date 1 month adv: " << frankfCal.advance(d1, mat, BusinessDayConvention(ModifiedFollowing), false) << endl;

    cout << "Business days b/w: " << frankfCal.businessDaysBetween(d1, d2, false, false) << endl;
}

int main(int argc, char *argv[]) {
    //CalendarTesting1();
    //CalendarTesting2();
    CalendarTesting3();

    return 0;
}
