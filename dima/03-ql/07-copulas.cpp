#include "qlpch.h"

using namespace QuantLib;
using namespace std;

void testCopula1() {
    GaussianCopula gauss(0.7);
    GumbelCopula gumbel(1.7);

    Real x = 0.7, y = 0.2;

    cout << "Gauss copula: " << gauss(x, y) << endl;
    cout << "Gumbel copula: " << gumbel(x, y) << endl;
}

int main(int argc, char *argv[]) {
    testCopula1();

    return 0;
}
