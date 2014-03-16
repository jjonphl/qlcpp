#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>

template<typename T>
struct is_shared_ptr {
    static const bool value = false;
};

template<typename T>
struct is_shared_ptr<boost::shared_ptr<T> > {
    static const bool value = true;
};

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    int *ip;
    boost::shared_ptr<int> isp;
    std::vector<int> ivec;


    cout << "*ptr: " << is_shared_ptr<int *>::value << endl;
    cout << "shared_ptr<int>: " << is_shared_ptr<boost::shared_ptr<int> >::value << endl;

    cout << "distance: " << std::distance(ivec.begin(), ivec.end()) << endl;
    ivec.push_back(1);
    ivec.push_back(2);
    ivec.push_back(3);
    cout << "distance: " << std::distance(ivec.begin(), ivec.end()) << endl;
    return 0;
}
