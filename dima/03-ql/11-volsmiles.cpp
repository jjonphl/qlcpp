#include "qlpch.h"
#include <boost/shared_ptr.hpp>
#include <boost/assign/std/vector.hpp>

using namespace QuantLib;
using namespace std;

void testVolatility1() {
    Time tau = 0.45, st = sqrt(tau);

    static const Rate _strikes[] = { 78.0, 88.0, 98.0, 108.0, 118.0, 128.0 };
    vector<Rate> strikes(_strikes, _strikes + size(_strikes));

    static const Real _sigmas[] = { 0.2406, 0.2213, 0.2102, 0.2156, 0.2299, 0.2501 };
    vector<Handle<Quote> > vols(size(_sigmas));
    for (int i = 0; i < size(_sigmas); i++) {
        boost::shared_ptr<Quote> q(new SimpleQuote(_sigmas[i]*st));
        Handle<Quote> h(q);
        vols[i] = h;
    }

    InterpolatedSmileSection<Cubic> smile(tau, strikes, vols, vols[2]);
    
    Real k1 = 88.0, k2 = 93.0;

    cout << "Min strike: " << smile.minStrike() << endl;
    cout << "Max strike: " << smile.maxStrike() << endl;
    cout << "Atm vol: " << smile.atmLevel() << endl;
    cout << "vol(k1): " << smile.volatility(k1) << endl;
    cout << "variance(k1): " << smile.variance(k1) << endl;
    cout << "vol(k2): " << smile.volatility(k2) << endl;
    cout << "variance(k2): " << smile.variance(k2) << endl;
}

void testVolatility2() {
    DayCounter dc = ActualActual();
    Calendar eurexCal = Germany(Germany::Eurex);

    using namespace boost::assign;

    Date settlementDate(27, Sep, 2009);
    settlementDate = eurexCal.adjust(settlementDate);

    vector<Date> dateVec;

    vector<Size> days;
    days += 13, 41, 75, 165, 256, 345, 524, 703;

    for (Size i = 0; i < days.size(); ++i) {
        dateVec.push_back(settlementDate + days[i]*Days);
    }

    vector<Real> strikes;
    strikes += 100, 500, 2000, 3400, 3600, 3800, 4000, 4200, 4400, 4500,
            4600, 4800, 5000, 5200, 5400, 5600, 7500, 10000, 20000, 30000;

    vector<Volatility> vols;
    vols += 1.015873, 1.015873, 1.015873, 0.89729, 0.796493, 0.730914,
         0.631335, 0.568895, 0.711309, 0.711309, 0.711309, 0.641309, 0.635593,
         0.583653, 0.508045, 0.463182, 0.516034, 0.500534, 0.500534, 0.500534,
         0.448706, 0.416661, 0.375470, 0.353442, 0.516034, 0.482263, 0.447713,
         0.387703, 0.355064, 0.337438, 0.316966, 0.306859, 0.497587, 0.464373,
         0.430764, 0.374052, 0.344336, 0.328607, 0.310619, 0.301865, 0.479511,
         0.446815, 0.414194, 0.361010, 0.334204, 0.320301, 0.304664, 0.297180,
         0.461866, 0.429645, 0.398092, 0.348638, 0.324680, 0.312512, 0.299082,
         0.292785, 0.444801, 0.413014, 0.382634, 0.337026, 0.315788, 0.305239,
         0.293855, 0.288660, 0.428604, 0.397219, 0.368109, 0.326282, 0.307555,
         0.298483, 0.288972, 0.284791, 0.420971, 0.389782, 0.361317, 0.321274,
         0.303697, 0.295302, 0.286655, 0.282948, 0.413749, 0.382754, 0.354917,
         0.316532, 0.300016, 0.292251, 0.284420, 0.281164, 0.400889, 0.370272,
         0.343525, 0.307904, 0.293204, 0.286549, 0.280189, 0.277767, 0.390685,
         0.360399, 0.334344, 0.300507, 0.287149, 0.281380, 0.276271, 0.274588,
         0.383477, 0.353434, 0.327580, 0.294408, 0.281867, 0.276746, 0.272655,
         0.271617, 0.379106, 0.349214, 0.323160, 0.289618, 0.277362, 0.272641,
         0.269332, 0.268846, 0.377073, 0.347258, 0.320776, 0.286077, 0.273617,
         0.269057, 0.266293, 0.266265, 0.399925, 0.369232, 0.338895, 0.289042,
         0.265509, 0.255589, 0.249308, 0.249665, 0.423432, 0.406891, 0.373720,
         0.314667, 0.281009, 0.263281, 0.246451, 0.242166, 0.453704, 0.453704,
         0.453704, 0.381255, 0.334578, 0.305527, 0.268909, 0.251367, 0.517748,
         0.517748, 0.517748, 0.416577, 0.364770, 0.331595, 0.287423, 0.264285; 

    Matrix blackVolMatrix(strikes.size(), dateVec.size()); 

	for (Size i=0; i < strikes.size(); ++i){
        for (Size j=0; j < dateVec.size(); ++j) {
            blackVolMatrix[i][j] = vols[i*dateVec.size()+j];
        }
	}

    BlackVarianceSurface volSurf(settlementDate, eurexCal,dateVec,
            strikes,blackVolMatrix,dc);

    Date d=settlementDate+130*Days;
    Real K=3755.0;

    cout << "Bilinear Interpolation:" << volSurf.blackVol(d,K) << endl;
	volSurf.setInterpolation<Bicubic>(Bicubic());
    cout << "Bicubic Interpolation:" << volSurf.blackVol(d,K) << endl;
}

int main(int argc, char *argv[]) {
    //testVolatility1();
    testVolatility2();

    return 0;
}