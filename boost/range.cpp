#include <iostream>
#include <stdexcept>
#include <boost/static_assert.hpp>
#include <boost/type_traits/has_less_equal.hpp>
#include <boost/type_traits/has_greater_equal.hpp>
#include <boost/type_traits/has_equal_to.hpp>

using std::cout;

template<class Type = double> class Range {
    private:
        Type lo;
        Type hi;

    public:
        // Constructors
        Range();
        Range(const Type& low, const Type& high);
        Range(const Range<Type>& ran2);

        // Destructor
        /*virtual*/ ~Range();

        // Modifiers
        void low(const Type& t1);
        void high(const Type& t1);

        // Accessors
        Type low() const;
        Type high() const;
        Type spread() const;

        // Boolean functions
        bool left(const Type& value) const;    // is low() == value?
        bool right(const Type& value) const;
        bool contains(const Type& value) const; // range contains value?

        // copy-assignment
        Range<Type>& operator =(const Range<Type>& ran2);
};

template<class Type> Range<Type>::Range() {
    BOOST_STATIC_ASSERT(boost::has_greater_equal<Type>::value);
    BOOST_STATIC_ASSERT(boost::has_less_equal<Type>::value);
}

template<class Type> Range<Type>::Range(const Type& low, const Type& high) {
    this->lo = low;
    this->hi = high;
}

template<class Type> Range<Type>::Range(const Range<Type>& ran2) {
    this->lo = ran2.lo;
    this->hi = ran2.hi;
}

template<class Type> void Range<Type>::low(const Type& t1) {
    if (t1 <= this->hi) {
        this->lo = t1;
    } else {
        throw std::runtime_error("low is bigger than this->hi");
    }
}

template<class Type> void Range<Type>::high(const Type& t1) {
    if (t1 >= this->lo) {
        this->hi = t1;
    } else {
        throw std::runtime_error("high is smaller than this->lo");
    }
}

template<class Type> Type Range<Type>::low() const {
    return this->lo;
}

template<class Type> Type Range<Type>::high() const {
    return this->hi;
}

template<class Type> Type Range<Type>::spread() const {
    return this->hi - this->lo;
}

template<class Type> bool Range<Type>::left(const Type& value) const {
    return this->lo == value;
}

template<class Type> bool Range<Type>::right(const Type& value) const {
    return this->hi == value;
}

template<class Type> bool Range<Type>::contains(const Type& value) const {
    return value >= this->lo && value <= this->hi;
}


template<class Type> Range<Type>& Range<Type>::operator =(const Range<Type>& ran2) {
    this->lo = ran2.low();
    this->hi = ran2.high();
    return this;
}

template<class Type> Range<Type>::~Range() {
    std::cout << "Deconstructing range...\n";
}

struct Foo {
    int a;
};

int main(int argc, char *argv[]) {
    Range<int> irange(0, 100);
    Range<int> irange2;
    Range<std::string> srange(std::string("a"), std::string("z"));
    Range<std::string> srange2;

    cout << "Hello world!\n";
    cout << "Is 5 included? " << irange.contains(5) << std::endl;
    cout << "Is 100 included? " << irange.contains(100) << std::endl;
    cout << "Is 500 included? " << irange.contains(500) << std::endl;
    cout << "Left: " << irange.low() << std::endl;
    cout << "Right: " << irange.high() << std::endl;

    cout << "Is x included? " << srange.contains(std::string("x")) << std::endl;
    cout << "Is x included? " << srange2.contains(std::string("x")) << std::endl;
    cout << "srange2 value: [" << srange2.low() << "]\n";
    cout << "irange2 low: [" << irange2.low() << "]\n";
    cout << "irange2 high: [" << irange2.high() << "]\n";

    Range<Foo> foorange;

    return 0;
}
