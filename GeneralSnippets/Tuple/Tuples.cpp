// =====================================================================================
// std::tuple
// =====================================================================================

#include <iostream>
#include <vector>
#include <tuple>
#include <string>

namespace TupleSamples {

    // =======================================================
    // demonstrating simple operations on a std::tuple

    void test_01()
    {
        // declaring tuple 
        std::tuple <char, int, double> values;  // ab C++ 11

        // tuple: "Struktur f?r Schreibfaule" :)

        // assigning values to tuple using std::make_tuple
        values = std::make_tuple('A', 10, 15.5);
        
        // just in one statement
        std::tuple <char, int, double> moreValues{ 'Z', 100, 99.99 };

        // accessing tuple values using std::get 

        constexpr int n{ 1 };

        std::cout << "The values of tuple are : ";
        std::cout 
            << std::get<0>(values) << " - " 
            << std::get<1>(values) << " - " 
            << std::get<2>(values)
            << std::endl;

        // use std::get to change single values of a tuple 
        std::get<0>(values) = 'B';
        std::get<2>(values) = 30.5;

        // printing tuple values again
        std::cout << "The modified values of tuple are : ";
        std::cout
            << std::get<0>(values) << " - "
            << std::get<1>(values) << " - "
            << std::get<2>(values)
            << std::endl;
    }

    // =======================================================
    // demonstrating use of std::vector with std::tuple elements

    // 99% funktioniert
    typedef std::tuple<int, char, double, std::string>     EineZeile;

    // Aber: Man sollte auf using umsteigen 
    using Row = std::tuple<int, char, double, std::string>;

    // forward declaration
    std::string rowToString(const Row& row);

    void test_02()
    {
        Row row1 = std::make_tuple(10, 'A', 1.11, "Mueller");
        Row row2 = std::make_tuple(11, 'B', 2.22, "Sepp");
        Row row3 = std::make_tuple(12, 'C', 3.33, "Hans");

        std::vector<Row> mySheet;

        mySheet.push_back(row1);
        mySheet.push_back(row2);
        mySheet.push_back(row3);

        for (const Row& row : mySheet) {
            std::cout << rowToString(row) << std::endl;
        }
    }

    std::string rowToString(const Row& row) 
    {
        int n = std::get<0>(row);
        char ch = std::get<1>(row);
        double d = std::get<2>(row);
        std::string s = std::get<3>(row);

        return "Id: " + 
            std::to_string(n) + ", " + std::to_string(ch) + ", " + 
            std::to_string(d) + ", " + s;
    }

    // =======================================================
    // same example, but using C++ 17 structured binding (pair, array, struct, tuple)

    void test_03() 
    {
        Row row1 = std::make_tuple(10, 'A', 1.11, "Mueller");
        Row row2 = std::make_tuple(11, 'B', 2.22, "Sepp");
        Row row3 = std::make_tuple(12, 'C', 3.33, "Hans");

        std::vector<Row> mySheet;

        mySheet.push_back(row1);
        mySheet.push_back(row2);
        mySheet.push_back(row3);

        // C++ 17 structured binding
        const auto& [id, abbr, val, name] = mySheet[0];

        std::cout
            << "Id:    " << id << std::endl      // ohne std::get => structured binding
            << "Abbr:  " << abbr << std::endl
            << "Value: " << val << std::endl
            << "Name:  " << name << std::endl;

        // Range Based Loop + Structured Binding
        for (const auto& [id, abbr, val, name] : mySheet) {   // C++ 17

            std::cout 
                << "Id:    " << id << std::endl
                << "Abbr:  " << abbr << std::endl
                << "Value: " << val << std::endl
                << "Name:  " << name << std::endl;
        }
    }

    // =======================================================
    // retrieving number of elements of a std::tuple

    void test_04()
    {
        // declaring tuple 
        std::tuple <char, int, double> tuple { 'A', 10, 15.5 };

        // retrieve number of elements with std::tuple_size
        std::cout << "std::tuple size: ";
        std::cout << std::tuple_size<decltype(tuple)>::value << std::endl;

        // or
        using MyTuple = std::tuple<char, int, double>;
        std::cout << "std::tuple size: ";
        std::cout << std::tuple_size<MyTuple>::value << std::endl;

        // or
        std::cout << "std::tuple size: ";
        std::cout << std::tuple_size<std::tuple<char, int, double>>::value << std::endl;
    }
}

void main_tuples()
{
    using namespace TupleSamples;
    //test_01();
    test_02();
    //test_03();
    //test_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
