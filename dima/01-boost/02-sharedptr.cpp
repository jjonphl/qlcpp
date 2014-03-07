#include <iostream>
#include <stdexcept>
#include <boost/shared_ptr.hpp>

class A {
    private:
        double myValue_;

    public:
        A(const double& myValue):myValue_(myValue) {
            std::cout << "Constructor of A" << std::endl;
        }
        ~A() {
            std::cout << "Destructor of A with value " << myValue_ << std::endl;
        }
        double getValue() const {
            return myValue_;
        }
};

void testSharedPtrA() {
    // the usual way
    A* ptr_myA = new A(1.0);
    delete ptr_myA;
}

void testSharedPtrB() {
    // not deleted, memory leak
    A* ptr_myA = new A(1.0);
    throw std::runtime_error("Error occurred for class A.");
    delete ptr_myA;
}

void testSharedPtrC() {
    // automatically deleted when shared_ptr goes out of scope
    boost::shared_ptr<A> bptr_myA(new A(1.0));
}

void testSharedPtrD() {
    // e.g. when porting old code to boost
    // take care of delete-ing
    A* ptr_myA = new A(1.0);
    boost::shared_ptr<A> bptr_myA(ptr_myA);
    std::cout << bptr_myA->getValue() << std::endl;
}

void testSharedPtrE() {
    // A should be delete-d on uncaught exception
    boost::shared_ptr<A> bptr_myA(new A(1.0));
    throw std::runtime_error("Error occurred in testSharedPtr");
}

void testSharedPtrF() {
    // memory leak demo
    A* ptr_myA = new A(1.0);
    ptr_myA = new A(2.0);
    delete ptr_myA;
}

void testSharedPtrG() {
    // behavior when reassigning
    boost::shared_ptr<A> bptr_myA(new A(1.0));
    bptr_myA.reset(new A(2.0));  // is dealloc done as part of reset or later?
    std::cout << "Is dealloc done as part of reset or later?\n";
    std::cout << "This should be printed before destructor of 1 if the latter\n";
}

int main(int argc, char *argv[]) {
    std::cout << "Test A\n======\n";
    testSharedPtrA();


    std::cout << "\nTest B\n======\n";
    try {
        testSharedPtrB();
    } catch (std::exception &e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }


    std::cout << "\nTest C\n======\n";
    testSharedPtrC();


    std::cout << "\nTest D\n======\n";
    testSharedPtrD();

    std::cout << "\nTest E\n======\n";
    try {
        testSharedPtrE();
    } catch (std::exception &e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    std::cout << "\nTest F\n======\n";
    testSharedPtrF();

    std::cout << "\nTest G\n======\n";
    testSharedPtrG();


    return 0;
}
