#include <iostream>
#include <ql/quantlib.hpp>
#include <vector>
#include <boost/foreach.hpp>

using namespace std;
using namespace QuantLib;

// DateGeneration::Rule
// Backward - backward from termination date to effective date
// Forward - forward from effective date to termination date
// Zero - no intermediate dates b/w effective & termination dates
// ThirdWednesday - all dates in b/w eff & term dates are on 3rd Wed of
//    the month (forward calc)
// Twentieth - used for CDS schedules in emerging markets, all dates b/w eff
//    & term dates are 20th of the month
// TwentiethIMM - used for CDS schedules, all dates b/w eff & term dates are
//    20th of an IMM month

// Schedule(...) constructor arguments:
// const Date& effectiveDate -
// const Date& terminationDate -
// const Period& tenor - freq of the schedule (e.g. 3*Months)
// const Calendar& calendar -
// BusinessDayConvention convention - for in b/w dates
// BusinessDayConvention terminationDateConversion - for term date only
// DateGeneration::Rule rule - 
// bool endOfMonth - if eff date is end of month, enforce sched dates
//    to be end of month too (e.g. April 30th, May 31st, ...)
// const Date& firstDate = Date() - odd first
// const Date& nextToLastDate = Date() - odd last

// Schedule functions
// Size size() - # of dates
// const Date& operator[](Size i) - indexer
// Date previousDate(const Date& refDate) - 
// Date nextDate(const Date& refDate) - 
// const std::vector<Date>& dates() - 

void scheduleTesting1(DateGeneration::Rule rule) {
    Date begin(30, Sep, 2009), end(15, Jun, 2012);
    Calendar cal = Japan();

    BusinessDayConvention bdc = BusinessDayConvention(Following);

    Period tenor(6, Months);

    Schedule sched(begin, end, tenor, cal, bdc, bdc, rule, true);

    std::vector<Date> dates = sched.dates();

    BOOST_FOREACH(Date d, dates) cout << d << endl;
}

void scheduleTesting3() {
    Date begin(30, Sep, 2009), end(15, Jun, 2012);
    Calendar cal = Japan();

    BusinessDayConvention bdc = BusinessDayConvention(Following);

    Period tenor(6, Months);

    DateGeneration::Rule rule = DateGeneration::Forward;

    Schedule sched(begin, end, tenor, cal, bdc, bdc, rule, true);

    Date refDate(3, Aug, 2010);
    cout << "Date: " << refDate << endl;
    cout << "Next date: " << sched.nextDate(refDate) << endl;
    cout << "Prev date: " << sched.previousDate(refDate) << endl;
}

int main(int argc, char *argv[]) {

    // last date should be 2012-06-15, but I'm producing 2012-06-29!! wtf!
    cout << "Forward: \n";
    scheduleTesting1(DateGeneration::Forward);

    //cout << "\n\nBackward: \n";
    //scheduleTesting1(DateGeneration::Backward);

    //scheduleTesting3();
    
    return 0;
}
