// =====================================================================================
// Attributes.cpp
// =====================================================================================

#include <iostream>

// #define DEMONSTATE_WARNINGS_AND_ERRORS 1

namespace StandardAttributes {

    [[ nodiscard ]] int discard_test()
    {
        return 123;
    }

    void test_01()
    {
        int result = discard_test();

        // another call to discard_test:
        // 'warning: discarding return value of function with 'nodiscard' attribute'
      //  discard_test();
    }

    [[ noreturn ]] void criticalFunction() {
        throw "error";
    }

    void not_yet_ready()
    {
        // set debug mode in compiler or 'R'
        [[ maybe_unused ]] char mg_brk = 'D';

        // compiler does not emit any warnings
        // or error on this unused variable
    }

    void not_yet_ready_too()
    {
        // set debug mode in compiler or 'R'
        char mg_brk = 'D';
    }

#if defined (DEMONSTATE_WARNINGS_AND_ERRORS)

    // for class/struct/union
    struct [[ deprecated ]] Struct {};

    // for Functions
    [[ deprecated("Reason for deprecation") ]] void f() {}

    // for namespaces
    namespace [[ deprecated ]] any_namespace {}

    // For variables (including static data members)
    [[ deprecated ]] int x;

    [[ deprecated ]] void test_deprecated()
    {
        Struct s{};
        f();
        x = 123;
    }

#endif

    void complicatedSwitch(int n)
    {
        switch (n)
        {
        case 1:
            std::cout << "Digit 1 processed" << std::endl;
            break;
        case 2:
            std::cout << "Digit 2 (partially ) processed" << std::endl;
            [[ fallthrough ]]; //(dont forget the semicolon) suppressing warning
        case 3:
            std::cout << "And some code for Digit 2 and Digit 3" << std::endl;
            break;
        case -1:
            std::cout << "Undefined Digit" << std::endl;
        }
    }
}

void main_attributes()
{
    using namespace StandardAttributes;
}

// =====================================================================================
// End-of-File
// =====================================================================================
