// =====================================================================================
// Auto.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>

namespace Auto_Examples {

    std::map<long, std::string> getFunction() { return {}; };

    void test_01_a() {

        // var werBinIch; // JavaScript ! NICHT in C++
        // Type Deduction : Typableitung
        auto werBinIch1 = 123;
        int werBinIch2 = 123;

        using namespace std::string_literals;

        123.55, 123.55f, 123.55F, 123, 123l, 123ll,
            '?', "ABC", // const char* , 
            "ABC"s; // std::string

        auto n = 123;    // n is type of int

        auto result = getFunction();

        std::map<long, std::string> result2 = getFunction();
    }

    auto sum(float f1, double f2)
    {
        return f1 + f2;
    }

    auto anotherSum(bool flag, float f1, double f2)
    {
        if (flag)
            return (double) f1;  // float
        else
            return f2;   // double
    }

    // Das ist jetzt was ganz was anderes :)
    // Generische Funktion
    auto sum2(auto f1, auto f2)
    {
        return f1 + f2;
    }

    template <typename T1, typename T2>
    auto sum3(T1 f1, T2 f2) -> T1 // trailing return type
    {
        return f1 + f2;
    }

    template <typename T1, typename T2>
    auto sum4(T1 f1, T2 f2) 
        -> decltype (std::declval<T1>() + std::declval<T2>())   // trailing return type
    {   
        return f1 + f2;
    }

    template <typename T1, typename T2>
    auto sum5(T1 f1, T2 f2)
        -> decltype (f1 + f2)   // trailing return type
    {
        return f1 + f2;
    }

    // Template Programmierung: Verbessungen zur Hantierung von Typen

    template <typename T1, typename T2>
    decltype (std::declval<T1>() + std::declval<T2>()) 
    sum6(T1 f1, T2 f2)
    {
        return f1 + f2;
    }


    auto result = sum3<short, long> (123, 456);



    auto foo(bool flag, char ch, double d) -> double
    {
        if (flag) {
            return ch;
        }
        else {
            return d;
        }
    }

    void test_01_b() {

        auto result = sum(1.0, 2.0);  // float

        auto value = foo(true, '!', 123.456);   // double
    }

    class Contact
    {
        std::string m_name;
        size_t m_number;

    public:
        auto getName() const { return m_name; }
        auto getMobileNumber() const { return m_number; }
    };

    template <typename Type, typename ...Args>
    auto my_make_unique(Args&&... args) // no return type
    {
        return std::unique_ptr<Type>(new Type(std::forward<Args>(args)...));
    }

    const std::string message{ "This is an important message :)" };

    const std::string& getMessage()
    {
        return message;
    }

    void test_01_c() {

        auto msg = getMessage();
        std::cout << "Message: " << msg << std::endl;

        // or
        const auto& msg2 = getMessage();
        std::cout << "Message: " << msg2 << std::endl;

        // but:
        decltype(getMessage()) msg3 = getMessage();
        std::cout << "Message: " << msg3 << std::endl;
    }

    auto make_planet()
    {
        struct Planet { std::string name; int moons; bool rings; };

        return Planet{ "Saturn", 82, true };
    }

    void test_01_d() {

        // using automatic return type deduction
        auto planet = make_planet();

        std::cout
            << planet.name << ' '
            << planet.moons << ' '
            << planet.rings << std::endl;

        // using automatic return type deduction & structured binding
        auto [name, num_moons, has_rings] = make_planet();

        std::cout
            << name << ' '
            << num_moons << ' '
            << has_rings << std::endl;
    }

    // define a generic lambda
    auto isGreaterThanFifty = [](const auto& n) { return n > 50; };

    void test_01_e_01()
    {
        std::vector<int> intValues{ 44, 65, 22, 77, 2 };

        // use generic lambda with a vector of integers
        auto it1 = std::find_if(std::begin(intValues), std::end(intValues), isGreaterThanFifty);
        if (it1 != std::end(intValues)) {
            std::cout << "Found a value: " << *it1 << std::endl;
        }

        std::vector<double> doubleValues{ 24.0, 75.0, 12.0, 87.0, 12.0 };

        // use exactly the *same* generic lambda with a vector of doubles
        auto it2 = std::find_if(std::begin(doubleValues), std::end(doubleValues), isGreaterThanFifty);
        if (it2 != std::end(doubleValues)) {
            std::cout << "Found a value: " << *it2 << std::endl;
        }
    }

    template <typename T>
    bool isGreaterThanFiftyEx(const T& n)
    {
        return n > 50;
    };

    void test_01_e_02()
    {
        std::vector<int> intValues{ 44, 65, 22, 77, 2 };

        // use template function with a vector of integers
        auto it1 = std::find_if(std::begin(intValues), std::end(intValues), isGreaterThanFiftyEx<int>);
        if (it1 != std::end(intValues)) {
            std::cout << "Found a value: " << *it1 << std::endl;
        }

        std::vector<double> doubleValues{ 24.0, 75.0, 12.0, 87.0, 12.0 };

        // use exactly the *same* template function with another specialization with a vector of doubles
        auto it2 = std::find_if(std::begin(doubleValues), std::end(doubleValues), isGreaterThanFiftyEx<double>);
        if (it2 != std::end(doubleValues)) {
            std::cout << "Found a value: " << *it2 << std::endl;
        }
    }

    template <typename RetType, typename T1, typename T2>
    RetType add(const T1& t1, const T2& t2)
    {
        return t1 + t2;
    }

    template <typename T1, typename T2, typename RetType>
    RetType add2(const T1& t1, const T2& t2)
    {
        return t1 + t2;
    }

    template <typename RetType = long, typename T1, typename T2>
    RetType add3(const T1& t1, const T2& t2)
    {
        return t1 + t2;
    }

    void test_01_f()
    {
        // works - specifying all template parameters
        auto result = add<long, int, int>(10, 20);

        // works too - only the return template parameter type needs to be specified
        auto result1 = add<long>(10, 20);

        // works too - only the return template parameter type needs to be specified
        auto result2 = add3(10, 20);
    }

    decltype(auto) getFirstCharacter(const std::string& s)
    {
        return s[0];
    }

    void test_01_g()
    {
        auto ch1 = getFirstCharacter(std::string{ "ABC" });
        decltype(auto) ch2 = getFirstCharacter(std::string{ "ABC" });
    }

    void foo(const std::string& s) {
        std::cout << "Signature: const&" << std::endl;
    }

    void foo(std::string&& s) {
        std::cout << "Signature: &&" << std::endl;
    }

    auto callingFoo = [](auto&& s) {
        std::cout << "Calling foo(): " << s;
        foo(std::forward<decltype(s)>(s));
    };

    void test_01_h()
    {
        const std::string str{ "Hello World with LValue" };
        callingFoo(str);
        callingFoo("Hello World with RValue");
    }
}

void main_auto()
{
    using namespace Auto_Examples;
    test_01_a();
    test_01_b();
    test_01_c();
    test_01_d();
    test_01_e_01();
    test_01_e_02();
    test_01_f();
    test_01_g();
    test_01_h();
}

// =====================================================================================
// End-of-File
// =====================================================================================
