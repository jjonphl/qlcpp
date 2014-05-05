#include <iostream>
#include <ql/quantlib.hpp>
#include <cmath>
#include <boost/math/distributions.hpp>
#include <boost/function.hpp>

template<class T, size_t N>
size_t size(T (&)[N]) {
    return N;
}
