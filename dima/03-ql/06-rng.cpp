#include "qlpch.h"
#include <boost/foreach.hpp>

using namespace QuantLib;
using namespace std;

void testRandom1() {
    BigInteger seed = SeedGenerator::instance().get();
    //seed = 873212726;   // from Dima example
    cout << "Seed 1: " << seed << endl;

    MersenneTwisterUniformRng unifMt(seed);
    LecuyerUniformRng unifLec(seed);
    KnuthUniformRng unifKnuth(seed);

    cout << "Mersenne Twister: " << unifMt.next().value << endl;
    cout << "Lecuyer: " << unifLec.next().value << endl;
    cout << "Knuth: " << unifKnuth.next().value << endl;

    seed = SeedGenerator::instance().get();

    cout << "----------------------------------------" << endl;
    cout << "Seed 2: " << seed << endl;  // why? rng seed not updated...
    cout << "Mersenne: " << unifMt.next().value << endl;
    cout << "Lecuyer: " << unifLec.next().value << endl;
    cout << "Knuth: " << unifKnuth.next().value << endl;
}

void testRandom2() {
    BigInteger seed = 12324;
    MersenneTwisterUniformRng runif(seed);
    BoxMullerGaussianRng<MersenneTwisterUniformRng> rnorm(runif);

    cout << rnorm.next().value << endl;
    cout << rnorm.next().value << endl;
    cout << rnorm.next().value << endl;
    cout << rnorm.next().value << endl;
    cout << rnorm.next().value << endl;
}

Real evInv(boost::math::extreme_value_distribution<> d, const Real& x) {
    return quantile(d,x);
}

// rng = unif rng + inv func
void testRandom3() {
    boost::math::extreme_value_distribution<> d(0.0, 0.1);
    boost::function<Real (Real)> invEv = boost::bind(evInv, d, _1);

    BigInteger seed = 12324;
    MersenneTwisterUniformRng runif(seed);
    RandomSequenceGenerator<MersenneTwisterUniformRng> runifSeq(10, runif);

    InverseCumulativeRsg<RandomSequenceGenerator<MersenneTwisterUniformRng>,
        boost::function<Real (Real)> > rev(runifSeq, invEv);

    vector<Real> sample = rev.nextSequence().value;
    BOOST_FOREACH(Real x, sample) cout << x << endl;
}

// quasi rng / low discrepancy numbers
void testRandom4() {
    Size dim = 5;

    SobolRsg sobol(dim);
    HaltonRsg halton(dim);
    FaureRsg faure(dim);

    vector<Real> sampleSobol(sobol.dimension()),
        sampleHalton(halton.dimension()),
        sampleFaure(faure.dimension());

    sampleSobol = sobol.nextSequence().value;
    sampleHalton = halton.nextSequence().value;
    sampleFaure = faure.nextSequence().value;

    BOOST_FOREACH(Real x, sampleSobol) cout << "Sobol: " << x << endl;
    BOOST_FOREACH(Real x, sampleHalton) cout << "Halton: " << x << endl;
    BOOST_FOREACH(Real x, sampleFaure) cout << "Faure: " << x << endl;
}

// demo: IncrementalStatistics
void testRandom5() {
    SobolRsg sobol(1);

    MersenneTwisterUniformRng runif(12324);
    BoxMullerGaussianRng<MersenneTwisterUniformRng> bmGauss(runif);

    IncrementalStatistics sobolStat, bmStat;
    MoroInverseCumulativeNormal invGauss;

    Size numSim = 10000;
    Real currSobolNum;

    for (Size j=1; j <= numSim; ++j) {
        bmStat.add(bmGauss.next().value);
        currSobolNum = (sobol.nextSequence().value)[0];
        sobolStat.add(invGauss(currSobolNum));
    }

    cout << "Box-Muller:" << endl;
    cout << "\tmean:" << bmStat.mean() << endl;
    cout << "\tvariance:" << bmStat.variance() << endl;
    cout << "\tskew:" << bmStat.skewness() << endl;
    cout << "\tkurtosis:" << bmStat.kurtosis() << endl;
    cout << "Sobol:" << endl;
    cout << "\tmean:" << sobolStat.mean() << endl;
    cout << "\tvariance:" << sobolStat.variance() << endl;
    cout << "\tskew:" << sobolStat.skewness() << endl;
    cout << "\tkurtosis:" << sobolStat.kurtosis() << endl;
}

int main(int argc, char *argv[]) {
    //testRandom1();
    //testRandom2();
    //testRandom3();
    //testRandom4();
    testRandom5();
    
    return 0;
}
