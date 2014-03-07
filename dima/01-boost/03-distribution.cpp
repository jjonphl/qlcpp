#include <boost/math/distributions.hpp>

void distributionFunc1() {
    boost::math::normal_distribution<> d(0.5, 1);  // mu=0.5, sd=1
    std::cout << "CDF: " << cdf(d, 0.2) << std::endl;
    std::cout << "PDF: " << pdf(d, 0.0) << std::endl;
    std::cout << "Inverse: " << quantile(d, 0.1) << std::endl;
    std::cout << "Mode: " << mode(d) << std::endl;
    std::cout << "Variance: " << variance(d) << std::endl; // extract params??
    std::cout << "SD: " << standard_deviation(d) << std::endl;
    std::cout << "Skew: " << skewness(d) << std::endl;
    std::cout << "Kurtosis: " << kurtosis(d) << std::endl;
    std::cout << "Excess kurt: " << kurtosis_excess(d) << std::endl;

    std::pair<double, double> sup = support(d);
    std::cout << "Left support: " << sup.first << std::endl;
    std::cout << "Right support: " << sup.second << std::endl;
}

void distributionFunc2() {
    double leftBound=0.0, rightBound=2.0;
    boost::math::uniform_distribution<> d1(leftBound, rightBound);

    double numTrials=10, probTrial=0.2;
    boost::math::binomial_distribution<> d2(numTrials, probTrial);

    double degFreedom = 20;
    boost::math::students_t_distribution<> d3(degFreedom);
    boost::math::chi_squared_distribution<> d4(degFreedom);

    double mean=0.0, var=0.20;
    boost::math::lognormal_distribution<> d5(mean, var);
    boost::math::cauchy_distribution<> d6(mean, var);

    double degFreedom1 = 20, degFreedom2 = 35;
    boost::math::fisher_f_distribution<> d7(degFreedom1, degFreedom2);

    double nonCentPar = 0.2;
    boost::math::non_central_chi_squared_distribution<> d8(degFreedom1, nonCentPar);

    double arrivRate = 0.2;
    boost::math::poisson_distribution<> d9(arrivRate);
    boost::math::exponential_distribution<> d10(arrivRate);
}

int main(int argc, char *argv[]) {
    distributionFunc1();
    distributionFunc2();
    return 0;
}
