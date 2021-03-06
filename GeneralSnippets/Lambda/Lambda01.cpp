// =====================================================================================
// Lambda Methods
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

namespace Lambda {

    // Callable // hmm, ist nicht sonders "Objekt-Orientiert"
    auto myCompare (int n1, int n2) -> bool {
        return n1 < n2;
    }

    // Functor : 
    // Callable
    // Eine Klasse, die den Aufruf-Operator operator() implementiert
    class MyComparer {

    private:
        int m_value;

    public:
        bool operator() (const int& n1, const int& n2) {
            int tmp = m_value;
            m_value = 123;  // nur ein Beispiel f?r den Zugriff auf eine Instanzvariable
            return n1 < n2;
        }
    };

    void test_01() {

        // local class within function possible

        // IST FAST SCHON EIN LAMBDA :)
        struct MyInternalComparer {
            bool operator() (int n1, int n2) {
                return n1 < n2;
            }
        };

        std::vector<int> myVector;
        myVector.push_back(5);
        myVector.push_back(9);
        myVector.push_back(1);
        myVector.push_back(3);
        myVector.push_back(7);
        myVector.push_back(8);

        for (int n : myVector) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        // Funktion // Callable
        std::sort(std::begin(myVector), std::end(myVector), myCompare);
        // or
        // Die Klasse "MyComparer" ist "weit weg"
        std::sort(std::begin(myVector), std::end(myVector), MyComparer());
        // or
        // Die Klasse "MyInternalComparer" ist "nicht so weit weg"
        std::sort(std::begin(myVector), std::end(myVector), MyInternalComparer());

        for (int n : myVector) {
            std::cout << n << ' ';
        }
    }

    void test_02() {

        std::vector<int> myVector;
        myVector.push_back(50);
        myVector.push_back(90);
        myVector.push_back(10);
        myVector.push_back(30);
        myVector.push_back(70);
        myVector.push_back(80);

        for (int n : myVector) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        //myVector.push_back(50);
        //myVector.push_back(90);
        //myVector.push_back(10);
        //myVector.push_back(30);
        //myVector.push_back(70);
        //myVector.push_back(80);

        std::sort(
            std::begin(myVector),
            std::end(myVector),
            [] (int n1, int n2) {
                std::cout << n1 << " mit " << n2 << std::endl;
                return n1 > n2;
            }
        );

        for (int n : myVector) {
            std::cout << n << ' ';
        }
    }

    int ffff(int, int, int) { return 0; };

    void test_03() {

        // quasi shortest lambda on earth: no parameters, capturing and doing nothing
        auto nothing = []{};
        nothing();

        // c'tor notation
        auto itsOne ([] () { return 1; });
        auto itsTwo ([] () { return 2; });
        std::cout << itsOne() << ", " << itsTwo() << std::endl;

        // "copy-c'tor" notation
        auto itsFour = [] { return 4; };
        auto itsFive = [] { return 5; };
        std::cout << itsFour() << ", " << itsFive() << std::endl;

        // notation without 'auto'
        // class to describe 'callable'

        // function pointer prototype:
        // nur als Beispiel :)
        int (*fp)(int, int, int) = ffff;

        std::function<int(int, int, int)> 
            itsThree([] (int x, int y, int z){ return 3; });

        // works with anything that defines the plus 'operator+'
        auto plus = [] (auto l, auto r) { return l + r; };
        std::cout << plus(1, 2) << std::endl;
        std::cout << plus(std::string{ "a" }, "b") << std::endl;
        std::cout << plus(itsOne(), itsTwo()) << std::endl;

        // inline-definition and direct invocation of lambda funtion
        std::cout << [] (auto l, auto r) { return l + r; } (11, 12) << std::endl;
    }

    void test_04_beispiel() {

        std::vector<int> numbers(10);
        auto variable = 0;

        // Will Vektor vorbelegen mit 1, 2, 3, 4, 5, 6, ...

        // std::generate - klassisches STL
        std::generate(
            std::begin(numbers), 
            std::end(numbers), 
            [&] () mutable {   // Kapselung
                std::cout << "var = " << variable << std::endl;
                return ++variable; 
        });

        // C++ 20 - range based loop  // ist eine Alternative zu std::generate
        //auto variable = 0;
        //for (int& wert : numbers) {
        //    wert = variable;
        //    variable += 10;
        //}
    }

    void test_04() {
        // defining new variables in the lambda capture:
        // we can declare a new variable that is only visible in the scope of the lambda.
        // we do so by defining a variable in the lambda-capture without specifying its type

        // lambda with variable definition
        auto dummy = 123;  // Type Deduction / Typableitung

        auto lambda = [variable = 10] () mutable { return ++variable; };

       // auto lambda = []() { auto variable = 10;  return ++variable; };

        std::cout << lambda() << std::endl;
        std::cout << lambda() << std::endl;
        std::cout << lambda() << std::endl;

        return;




        // Captures default to 'const value':
        // The mutable keyword removes the 'const' qualification from all captured variables
        auto counter = [count = 50]() mutable { 
            ++count; 
            return count;
        };

        for (size_t i{}; i < 5; ++i) {
            std::cout << counter() << " ";
        }
        std::cout << std::endl;
    }

    void test_05() {

        // Closure
        int n = 1;
        int m = 2;

        // innere Funktion
        auto l1 = [=] () {  // std::generate
            std::cout << "Copy:      " << n << " " << m << std::endl;
        };

        auto l2 = [&] {
            std::cout << "Reference: " << n << " " << m << std::endl;
        };

        auto l3 = [&n, m] {
            std::cout << "Both:      " << n << " " << m << std::endl;
        };

        n = 3;
        m = 4;

        l1();
        l2();
        l3();
    }

    auto test_06_helper_a() {

        int n = 1;
        int m = 2;

        auto lambda = [=] {
            std::cout << "Copy:      " << n << " " << m << std::endl;
        };

        return lambda;
    }

    auto test_06_helper_b() {

        int n = 1;
        int m = 2;

        auto lambda = [&] {
            std::cout << "Reference: " << n << " " << m << std::endl;
        };

        return lambda;                                  // I would't do this never ever :-)
    }

    void test_06() {

        auto outerLambda1 = test_06_helper_a();
        auto outerLambda2 = test_06_helper_b();
        outerLambda1();
        outerLambda2();
    }

    std::pair<
        std::function<void(std::string const&)>, 
        std::function<void(std::string const&)>
    > 
    test_07_helper_a() {

        int n = 1;
        int m = 2;

        std::function<void(std::string const&)> lambda1 = [=](std::string const& info) {
            std::cout << info << "Copy:      " << n << " " << m << std::endl;
        };

        std::function<void(std::string const&)> lambda2 = [&](std::string const& info) {
            std::cout << info << "Reference: " << n << " " << m << std::endl;
        };

        return std::pair<
            std::function<void(std::string const&)>,
            std::function<void(std::string const&)>>(lambda1, lambda2);
    }

    void test_07_helper_b(std::function<void(std::string const&)> lambda) {
        lambda("in test_helper ");
    }

    void test_07() {

        auto [lambda1, lambda2] = test_07_helper_a();

        lambda1("in test_07     ");
        test_07_helper_b(lambda1);

        lambda2("in test_05     ");
        test_07_helper_b(lambda2);
    }

    template <typename T, typename U>
    auto add = [](const T& t, const U& u) -> decltype (t + u)
    {
        return t + u;
    };

    void test_08() {
         
        int n = 1;
        double d = 2.7;

        auto result1 = add<int, double>(n, d);
        std::cout << result1 << std::endl;
    }

    void test_09() {

        // Example demonstrating so called 'Currying':

        // This means that we take a function that can accept some parameters
        // and store it in another function object, which accepts *fewer* parameters.

        // In our example, we define a 'plusTen' function which accepts a single parameter.
        // This parameter is forwarded to the 'plus' function. The second parameter equals 10,
        // which is being saved in the function object:

        auto plus = [](auto l, auto r) { return l + r; };

        auto plusTen = [plus](int x) { return plus(10, x); };

        std::cout << plusTen(5) << std::endl;
    }

    void test_10() {

        auto itsOne([] () noexcept { return 1; });
        auto itsTwo = [] () noexcept { return 2; };
        std::cout << itsOne() << ", " << itsTwo() << std::endl;
    }
}

void main_lambdas()
{
    using namespace Lambda;
    //test_01();
    //test_02();
    //test_03();
    //test_04();
    test_04_beispiel();
    //test_05();
    //test_06();
    //test_07();
    //test_08();
    //test_09();
    //test_10();
}

// =====================================================================================
// End-of-File
// =====================================================================================
