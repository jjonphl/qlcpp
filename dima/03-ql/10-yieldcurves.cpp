#include "qlpch.h"
#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>

using namespace QuantLib;
using namespace std;

void testYield2() {
    vector<Date> dates;
    vector<DiscountFactor> dfs;

    Calendar cal = TARGET();
    Date today(11,Sep,2009);
    EURLibor1M libor;
    DayCounter dc = libor.dayCounter();

    Natural settlementDays = 2;
    Date settlement = cal.advance(today, settlementDays, Days);

    dates.push_back(settlement);
    dates.push_back(settlement + 1*Days);
    dates.push_back(settlement + 1*Weeks);
    dates.push_back(settlement + 1*Months);
    dates.push_back(settlement + 2*Months);
    dates.push_back(settlement + 3*Months);
    dates.push_back(settlement + 6*Months);
    dates.push_back(settlement + 9*Months);
    dates.push_back(settlement + 1*Years);
    dates.push_back(settlement + 1*Years + 3*Months);
    dates.push_back(settlement + 1*Years + 6*Months);
    dates.push_back(settlement + 1*Years + 9*Months);
    dates.push_back(settlement + 2*Years);

    dfs.push_back(1.0);
    dfs.push_back(0.9999656);
    dfs.push_back(0.9999072);
    dfs.push_back(0.9996074);
    dfs.push_back(0.9990040);
    dfs.push_back(0.9981237);
    dfs.push_back(0.9951358);
    dfs.push_back(0.9929456);
    dfs.push_back(0.9899849);
    dfs.push_back(0.9861596);
    dfs.push_back(0.9815178);
    dfs.push_back(0.9752363);
    dfs.push_back(0.9680804);

    Date d1 = settlement + 1*Years + 3*Months;
    InterpolatedDiscountCurve<LogLinear> curve(dates, dfs, dc, cal);

    cout << "Zero rate: " << curve.zeroRate(d1, dc, Simple, Annual) << endl;
    cout << "Discount: " << curve.discount(d1) << endl;
    cout << "1Y3M-1Y6M fwd rate: " << curve.forwardRate(d1, d1+3*Months, dc, Continuous) << endl;
}

template<class T, size_t N>
size_t size(T (&)[N]) {
    return N;
}

vector<boost::shared_ptr<RateHelper> > getRateHelpers() {
    vector<boost::shared_ptr<RateHelper> > instruments;

    // deposits: 15
    Rate depositRates[] = {/*0.21875,*/ 
        0.24063, 0.24375, 0.24375, 0.25813, 0.29969,
        0.44438, 0.59125, 0.68250, 0.79125, 0.98750, 0.99750, 1.08125,
        1.116625 /*, 1.26125*/}; 
    Period depositTenors[] = {/*1*Days,*/ 
        1*Weeks, 2*Weeks, 1*Months, 2*Months, 
        3*Months, 4*Months, 5*Months, 6*Months, 7*Months, 8*Months, 9*Months,
        10*Months, 11*Months /*, 1*Years*/};
    for (size_t i = 0; i < size(depositRates); i++) {
        boost::shared_ptr<IborIndex> libor(new USDLibor(depositTenors[i]));
        boost::shared_ptr<RateHelper> deposit(new DepositRateHelper(
                    depositRates[i]/100.0, libor));
        instruments.push_back(deposit);
    }

    cout << "Done with deposits" << endl;

    // FRA
    Rate fraBidRates[] = {/*0.325, 0.368, 0.395, 0.450, 0.526, 0.590, 0.692,
        0.805, 0.904,*/ 1.267, 1.650, 2.013/*, 2.361*/};
    Rate fraAskRates[] = {/*0.400, 0.388, 0.445, 0.470, 0.546, 0.610, 0.712,
        0.825, 0.924,*/ 1.287, 1.670, 2.033/*, 2.381*/};
    Natural fraMonthStart[] = {/*1, 2, 3, 4, 5, 6, 7, 8, 9, */12, 15, 18/*, 21*/};
    //Natural fraMonthEnd[]   = {4, 5, 6, 7, 8, 9, 10, 11, 12, 15, 18, 21, 24};
    boost::shared_ptr<IborIndex> libor3m(new USDLibor(3*Months));
    for (size_t i = 0; i < size(fraBidRates); i++) {
        boost::shared_ptr<RateHelper> fra(new FraRateHelper(
                    fraAskRates[i]/100.0, fraMonthStart[i], libor3m));
        instruments.push_back(fra);
    }

    cout << "Done with FRA" << endl;

    // swaps
    Rate swapRates[] = {0.572, 1.226, 1.846, 2.324, 2.678, 2.958, 3.180, 3.340,
        3.474, 3.588, 3.916, 4.029, 4.109};
    Period swapTenors[] = {1*Years, 2*Years, 3*Years, 4*Years, 5*Years, 6*Years,
        7*Years, 8*Years, 9*Years, 10*Years, 15*Years, 20*Years, 30*Years};
    for (size_t i = 0; i < size(swapRates); i++) {
        boost::shared_ptr<SwapIndex> liborSwap(new UsdLiborSwapIsdaFixAm(swapTenors[i]));
        boost::shared_ptr<RateHelper> swap(new SwapRateHelper(
                    swapRates[i]/100.0, liborSwap));
        instruments.push_back(swap);
    }

    cout << "Done with swaps" << endl;
    return instruments;
}

// from DIMA example code

std::vector<boost::shared_ptr<RateHelper> > getRateHelperVector(){

	std::vector<boost::shared_ptr<RateHelper> > instruments;

	std::vector<Rate> liborRates;
	liborRates.push_back(0.24375);
	liborRates.push_back(0.25813);
					 liborRates.push_back(0.29969);
					 liborRates.push_back(0.44438);
					 liborRates.push_back(0.59125);
					 liborRates.push_back(0.68250);
					 liborRates.push_back(0.79125);
					 liborRates.push_back(0.89750);
					 liborRates.push_back(0.99750);
					 liborRates.push_back(1.08125);
					 liborRates.push_back(1.16625);
					 liborRates.push_back(1.26125);



//	liborRates+=0.24375,0.25813,0.29969,0.44438,0.59125, 0.68250,0.79125,
//				0.89750,0.99750,1.08125,1.16625,1.26125;



	BOOST_FOREACH(Rate& x, liborRates) x/=100.0;

	std::vector<Rate> fraRates;
	fraRates.push_back(1.267);
	fraRates.push_back(1.650);
	fraRates.push_back(2.013);

	BOOST_FOREACH(Rate& x, fraRates) x/=100.0;

	std::vector<Rate> swapRates;
	swapRates.push_back(1.226);
swapRates.push_back(1.846);
swapRates.push_back(2.324);
swapRates.push_back(2.678);
swapRates.push_back(2.958);
swapRates.push_back(3.180);
swapRates.push_back(3.340);
swapRates.push_back(3.474);
swapRates.push_back(3.588);



	BOOST_FOREACH(Rate& x, swapRates) x/=100.0;

// ++++++++++++++++++++ 1w USD Libor ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> libor1w(new SimpleQuote(0.0024063));
	Handle<Quote> libor1wHandle(libor1w);
	//index
	boost::shared_ptr<IborIndex> libor1wIndex(new  USDLibor(Period(1,Weeks)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper1w(new 
			DepositRateHelper(libor1wHandle,libor1wIndex));
	instruments.push_back(rateHelper1w);
// ++++++++++++++++++++ 2w USD Libor ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> libor2w(new SimpleQuote(0.0024375));
	Handle<Quote> libor2wHandle(libor2w);
	//index
	boost::shared_ptr<IborIndex> libor2wIndex(new  USDLibor(Period(2,Weeks)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper2w(new 
			DepositRateHelper(libor2wHandle,libor2wIndex));
	instruments.push_back(rateHelper2w);
// ++++++++++++++++++++ 1m USD Libor ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> libor1m(new SimpleQuote(liborRates[0]));
	Handle<Quote> libor1mHandle(libor1m);
	//index
	boost::shared_ptr<IborIndex> libor1mIndex(new  USDLibor(Period(1,Months)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper1m(new 
			DepositRateHelper(libor1mHandle,libor1mIndex));
	instruments.push_back(rateHelper1m);
// ++++++++++++++++++++ 2m USD Libor ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> libor2m(new SimpleQuote(liborRates[1]));
	Handle<Quote> libor2mHandle(libor2m);
	//index
	boost::shared_ptr<IborIndex> libor2mIndex(new  USDLibor(Period(2,Months)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper2m(new 
			DepositRateHelper(libor2mHandle,libor2mIndex));
	instruments.push_back(rateHelper2m);
// ++++++++++++++++++++ 3m USD Libor ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> libor3m(new SimpleQuote(liborRates[2]));
	Handle<Quote> libor3mHandle(libor3m);
	//index
	boost::shared_ptr<IborIndex> libor3mIndex(new  USDLibor(Period(3,Months)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper3m(new 
			DepositRateHelper(libor3mHandle,libor3mIndex));
	instruments.push_back(rateHelper3m);
// ++++++++++++++++++++ 4m USD Libor ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> libor4m(new SimpleQuote(liborRates[3]));
	Handle<Quote> libor4mHandle(libor4m);
	//index
	boost::shared_ptr<IborIndex> libor4mIndex(new  USDLibor(Period(4,Months)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper4m(new 
			DepositRateHelper(libor4mHandle,libor4mIndex));
	instruments.push_back(rateHelper4m);
// ++++++++++++++++++++ 5m USD Libor ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> libor5m(new SimpleQuote(liborRates[4]));
	Handle<Quote> libor5mHandle(libor5m);
	//index
	boost::shared_ptr<IborIndex> libor5mIndex(new  USDLibor(Period(5,Months)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper5m(new 
			DepositRateHelper(libor5mHandle,libor5mIndex));
	instruments.push_back(rateHelper5m);
// ++++++++++++++++++++ 6m USD Libor ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> libor6m(new SimpleQuote(liborRates[5]));
	Handle<Quote> libor6mHandle(libor6m);
	//index
	boost::shared_ptr<IborIndex> libor6mIndex(new  USDLibor(Period(6,Months)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper6m(new 
			DepositRateHelper(libor6mHandle,libor6mIndex));
	instruments.push_back(rateHelper6m);
// ++++++++++++++++++++ 7m USD Libor ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> libor7m(new SimpleQuote(liborRates[6]));
	Handle<Quote> libor7mHandle(libor7m);
	//index
	boost::shared_ptr<IborIndex> libor7mIndex(new  USDLibor(Period(7,Months)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper7m(new 
			DepositRateHelper(libor7mHandle,libor7mIndex));
	instruments.push_back(rateHelper7m);
// ++++++++++++++++++++ 8m USD Libor ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> libor8m(new SimpleQuote(liborRates[7]));
	Handle<Quote> libor8mHandle(libor8m);
	//index
	boost::shared_ptr<IborIndex> libor8mIndex(new  USDLibor(Period(8,Months)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper8m(new 
			DepositRateHelper(libor8mHandle,libor8mIndex));
	instruments.push_back(rateHelper8m);
// ++++++++++++++++++++ 9m USD Libor ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> libor9m(new SimpleQuote(liborRates[8]));
	Handle<Quote> libor9mHandle(libor9m);
	//index
	boost::shared_ptr<IborIndex> libor9mIndex(new  USDLibor(Period(9,Months)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper9m(new 
			DepositRateHelper(libor9mHandle,libor9mIndex));
	instruments.push_back(rateHelper9m);
// ++++++++++++++++++++ 10m USD Libor ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> libor10m(new SimpleQuote(liborRates[9]));
	Handle<Quote> libor10mHandle(libor10m);
	//index
	boost::shared_ptr<IborIndex> libor10mIndex(new  USDLibor(Period(10,Months)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper10m(new 
			DepositRateHelper(libor10mHandle,libor10mIndex));
	instruments.push_back(rateHelper10m);
// ++++++++++++++++++++ 11m USD Libor ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> libor11m(new SimpleQuote(liborRates[10]));
	Handle<Quote> libor11mHandle(libor11m);
	//index
	boost::shared_ptr<IborIndex> libor11mIndex(new  USDLibor(Period(11,Months)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper11m(new 
			DepositRateHelper(libor11mHandle,libor11mIndex));
	instruments.push_back(rateHelper11m);
// ++++++++++++++++++++ 12m USD Libor ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> libor12m(new SimpleQuote(liborRates[11]));
	Handle<Quote> libor12mHandle(libor12m);
	//index
	boost::shared_ptr<IborIndex> libor12mIndex(new  USDLibor(Period(12,Months)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper12m(new 
			DepositRateHelper(libor12mHandle,libor12mIndex));
	instruments.push_back(rateHelper12m);
// ++++++++++++++++++++ 12X15 FRA ++++++++++++++++++++++++++++++++++++++++
	boost::shared_ptr<Quote> fra12x15m(new SimpleQuote(fraRates[0]));
	Handle<Quote> fra12x15mHandle(fra12x15m);
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper12x15m(new 
			FraRateHelper(fra12x15mHandle,Period(12,Months),
								  libor3mIndex));
	instruments.push_back(rateHelper12x15m);	
// ++++++++++++++++++++ 15X18 FRA ++++++++++++++++++++++++++++++++++++++++
	boost::shared_ptr<Quote> fra15x18m(new SimpleQuote(fraRates[1]));
	Handle<Quote> fra15x18mHandle(fra15x18m);
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper15x18m(new 
			FraRateHelper(fra15x18mHandle,Period(15,Months),libor3mIndex));
	instruments.push_back(rateHelper15x18m);	
// ++++++++++++++++++++ 18X21 FRA ++++++++++++++++++++++++++++++++++++++++
	boost::shared_ptr<Quote> fra18x21m(new SimpleQuote(fraRates[2]));
	Handle<Quote> fra18x21mHandle(fra18x21m);
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper18x21m(new 
			FraRateHelper(fra18x21mHandle,Period(18,Months),libor3mIndex));
	instruments.push_back(rateHelper18x21m);	
// ++++++++++++++++++++ 2Y USD ISDA Fix Swap ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> swap2y(new SimpleQuote(swapRates[0]));
	Handle<Quote> swap2yHandle(swap2y);
	//index
	boost::shared_ptr<SwapIndex> swap2yIndex(new  UsdLiborSwapIsdaFixAm(Period(2,Years)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper2y(new 
			SwapRateHelper(swap2yHandle,swap2yIndex));
	instruments.push_back(rateHelper2y);
// ++++++++++++++++++++ 3y USD ISDA Fix Swap ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> swap3y(new SimpleQuote(swapRates[1]));
	Handle<Quote> swap3yHandle(swap3y);
	//index
	boost::shared_ptr<SwapIndex> swap3yIndex(new  UsdLiborSwapIsdaFixAm(Period(3,Years)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper3y(new 
			SwapRateHelper(swap3yHandle,swap3yIndex));
	instruments.push_back(rateHelper3y);
// ++++++++++++++++++++ 4y USD ISDA Fix Swap ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> swap4y(new SimpleQuote(swapRates[2]));
	Handle<Quote> swap4yHandle(swap4y);
	//index
	boost::shared_ptr<SwapIndex> swap4yIndex(new  UsdLiborSwapIsdaFixAm(Period(4,Years)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper4y(new 
			SwapRateHelper(swap4yHandle,swap4yIndex));
	instruments.push_back(rateHelper4y);
// ++++++++++++++++++++ 5y USD ISDA Fix Swap ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> swap5y(new SimpleQuote(swapRates[3]));
	Handle<Quote> swap5yHandle(swap5y);
	//index
	boost::shared_ptr<SwapIndex> swap5yIndex(new  UsdLiborSwapIsdaFixAm(Period(5,Years)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper5y(new 
			SwapRateHelper(swap5yHandle,swap5yIndex));
	instruments.push_back(rateHelper5y);
// ++++++++++++++++++++ 6y USD ISDA Fix Swap ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> swap6y(new SimpleQuote(swapRates[4]));
	Handle<Quote> swap6yHandle(swap6y);
	//index
	boost::shared_ptr<SwapIndex> swap6yIndex(new  UsdLiborSwapIsdaFixAm(Period(6,Years)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper6y(new 
			SwapRateHelper(swap6yHandle,swap6yIndex));
	instruments.push_back(rateHelper6y);
// ++++++++++++++++++++ 7y USD ISDA Fix Swap ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> swap7y(new SimpleQuote(swapRates[5]));
	Handle<Quote> swap7yHandle(swap7y);
	//index
	boost::shared_ptr<SwapIndex> swap7yIndex(new  UsdLiborSwapIsdaFixAm(Period(7,Years)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper7y(new 
			SwapRateHelper(swap7yHandle,swap7yIndex));
	instruments.push_back(rateHelper7y);
// ++++++++++++++++++++ 8y USD ISDA Fix Swap ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> swap8y(new SimpleQuote(swapRates[6]));
	Handle<Quote> swap8yHandle(swap8y);
	//index
	boost::shared_ptr<SwapIndex> swap8yIndex(new  UsdLiborSwapIsdaFixAm(Period(8,Years)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper8y(new 
			SwapRateHelper(swap8yHandle,swap8yIndex));
	instruments.push_back(rateHelper8y);
// ++++++++++++++++++++ 9y USD ISDA Fix Swap ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> swap9y(new SimpleQuote(swapRates[7]));
	Handle<Quote> swap9yHandle(swap9y);
	//index
	boost::shared_ptr<SwapIndex> swap9yIndex(new  UsdLiborSwapIsdaFixAm(Period(9,Years)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper9y(new 
			SwapRateHelper(swap9yHandle,swap9yIndex));
	instruments.push_back(rateHelper9y);

// ++++++++++++++++++++ 10y USD ISDA Fix Swap ++++++++++++++++++++++++++++++++++++++++
// Quote and Handle setup
	boost::shared_ptr<Quote> swap10y(new SimpleQuote(swapRates[8]));
	Handle<Quote> swap10yHandle(swap10y);
	//index
	boost::shared_ptr<SwapIndex> swap10yIndex(new  UsdLiborSwapIsdaFixAm(Period(10,Years)));
	// initialize rate helper
	boost::shared_ptr<RateHelper> rateHelper10y(new 
			SwapRateHelper(swap10yHandle,swap10yIndex));
	instruments.push_back(rateHelper10y);
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	return instruments;
}

void testYield4() {

    Calendar cal = TARGET();
    Date today(11, Sep, 2009);
    Natural settlementDays = 2;
    Date settlement = cal.advance(today, settlementDays, Days);
    DayCounter dc = Actual360();

    Settings::instance().evaluationDate() = today;

    cout << "Settlement date: " << settlement << endl;

    vector<boost::shared_ptr<RateHelper> > instruments = getRateHelpers();
    //vector<boost::shared_ptr<RateHelper> > instruments = getRateHelperVector();


    boost::shared_ptr<YieldTermStructure> yieldCurve;
    yieldCurve = boost::shared_ptr<YieldTermStructure>(new 
            PiecewiseYieldCurve<ZeroYield,Linear>(settlement, instruments, dc));

    Date d1 = settlement + 1*Years;
    Date d2 = d1 + 3*Months;

    cout << "Zero 3M: " << yieldCurve->zeroRate(settlement+3*Months,dc,Simple) << endl;
    cout << "Zero 6M: " << yieldCurve->zeroRate(settlement+6*Months,dc,Simple) << endl;
    cout << "Zero 9M: " << yieldCurve->zeroRate(settlement+9*Months,dc,Simple) << endl;
    cout << "Fwd 12x15: " << yieldCurve->forwardRate(d1,d2,dc,Simple) << endl;
    cout << "Fwd 15x18: " << yieldCurve->forwardRate(d2,d2+3*Months,dc,Simple) << endl;

    // check swap rate
    Handle<YieldTermStructure> ycHandle(yieldCurve);
    boost::shared_ptr<IborIndex> libor3m(new USDLibor(Period(3,Months),ycHandle));
    boost::shared_ptr<SwapIndex> swap8yIndex(new UsdLiborSwapIsdaFixAm(Period(8,Years)));

    VanillaSwap swap = MakeVanillaSwap(Period(8,Years), libor3m)
        .withEffectiveDate(settlement)
        .withFixedLegConvention(swap8yIndex->fixedLegConvention())
        .withFixedLegTenor(swap8yIndex->fixedLegTenor());

    cout << "8Y Swap: " << swap.fairRate() << endl;
}

int main(int argc, char *argv[]) {
    //testYield2();
    testYield4();

    return 0;
}
