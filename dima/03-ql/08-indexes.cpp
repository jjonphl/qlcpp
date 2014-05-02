#include "qlpch.h"

using namespace QuantLib;
using namespace std;

void testIndex1() {
    EURLibor1M index;
    
    cout << "Name: " << index.familyName() << endl;
    cout << "Business day convention: " << index.businessDayConvention() << endl;
    cout << "End of month rule: " << index.endOfMonth() << endl;
    cout << "Tenor: " << index.tenor() << endl;
    cout << "Calendar: " << index.fixingCalendar() << endl;
    cout << "Day counter: " << index.dayCounter() << endl;
    cout << "Currency: " << index.currency() << endl;
}

int main(int argc, char *argv[]) {
    testIndex1();

    return 0;
}
