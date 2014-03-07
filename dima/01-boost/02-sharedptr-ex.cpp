#include <iostream>
#include <stdexcept>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

// Write a function which allocates a std::vector<double> vector of size 100
// using the shared_ptr class. Fill the vector at index i with the number i,
// e.g.vec[i]=i by using a standard for loop. Calculate the sum of the vector
// by using the BOOST_FOREACH macro.
void ex1() {
    boost::shared_ptr<std::vector<double> > vec(new std::vector<double>(100));

    for (int i=0; i < 100; i++) {
        (*vec)[i] = i;
    }

    double sum = 0.0;

    BOOST_FOREACH(double x, *vec) sum += x;

    std::cout << "Sum: " << sum << std::endl;
}

int main(int argc, char *argv[]) {
    ex1();
    return 0;
}
