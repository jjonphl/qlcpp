#include <boost/random.hpp>
#include <boost/foreach.hpp>

void randomFunc1() {
    unsigned long seed = 12411;
    boost::mt19937 rng(seed);
    boost::uniform_int<> six(1,6);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > unsix(rng, six);

    std::cout << unsix() << std::endl;
    std::cout << unsix() << std::endl;
    std::cout << unsix() << std::endl;
}

void randomFunc2() {
    unsigned long seed = 89210;
    boost::lagged_fibonacci1279 rng(seed);
    boost::normal_distribution<> norm(10, 0.1); // mu=10, sd=0.1
    boost::variate_generator<boost::lagged_fibonacci1279&, boost::normal_distribution<> > rnorm(rng, norm);

    std::cout << rnorm() << std::endl;
    std::cout << rnorm() << std::endl;
    std::cout << rnorm() << std::endl;
}

void randomFunc3() {
    unsigned long seed = 12411;
    boost::mt19937 rng(seed);
    boost::cauchy_distribution<> cdist;
    boost::variate_generator<boost::mt19937&, boost::cauchy_distribution<> > cauchy(rng, cdist);

    std::cout << cauchy() << std::endl;
    std::cout << cauchy() << std::endl;
    std::cout << cauchy() << std::endl;

    rng.seed(seed);
    std::cout << "--------" << std::endl;
    std::cout << cauchy() << std::endl;
    std::cout << cauchy() << std::endl;
    std::cout << cauchy() << std::endl;
}

void randomFunc4() {
    unsigned long seed = 24061;
    boost::mt19937 rng(seed);
    boost::uniform_on_sphere<double, std::vector<double> > unsph_dist(5);
    boost::variate_generator<boost::mt19937&, 
       boost::uniform_on_sphere<double, std::vector<double> > > 
           unsph(rng, unsph_dist);

    std::vector<double> res = unsph();

    BOOST_FOREACH(double x, res) std::cout << x << std::endl;
    
    double sum = 0.0;
    BOOST_FOREACH(double x, res) sum += (x*x);
    std::cout << "--------------\n";
    std::cout << "Vector length: " << std::sqrt(sum) << std::endl;
}

int main(int argc, char *argv[]) {
    std::cout << "Uniform int {1, ..., 6}:\n";
    randomFunc1();

    std::cout << "\nNormal N(mu=10, sd=0.1):\n";
    randomFunc2();

    std::cout << "\nCauchy (reseed after 3rd):\n";
    randomFunc3();

    std::cout << "\nUniform on sphere (5d):\n";
    randomFunc4();
}
