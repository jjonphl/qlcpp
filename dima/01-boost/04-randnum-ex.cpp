#include <boost/math/distributions.hpp>
#include <boost/random.hpp>

class RChisq {
    private:
        boost::uniform_01<> runif;
        boost::math::chi_squared_distribution<> pchisq;
        boost::mt19937 rng;


    public:
        RChisq(double df) : pchisq(df), runif(), rng() { 
            rng.seed();
        };

        double operator() () {
            return quantile(pchisq, runif(rng));
        }
};

int main(int argc, char *argv[]) {
    RChisq rchisq(10);

    for (int i = 0; i < 10; i++) {
        std::cout << rchisq() << std::endl;
    }

    return 0;
}
