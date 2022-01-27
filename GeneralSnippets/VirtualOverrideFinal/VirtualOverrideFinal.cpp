// =====================================================================================
// virtual, override und final
// =====================================================================================

#include <iostream>

namespace VirtualOverrideFinal{

    class Base
    {
    public:
        virtual void func(int);
    };

    class Derived : public Base
    {
    public:
        virtual void func(int) override;  // C# "höheres C/C++" : mit virtual: zumindest einheitlich
    };

    void Base::func(int n)
    {
        std::cout << "Base::func [" << n << "]" << std::endl;
    }

    void Derived::func(int n)
    {
        std::cout << "Derived::func " << n << "]" << std::endl;
    }

    // =========================================================

    class Driver
    {
    public:
        virtual void send(int) final {};  // Diese Methode kann immer nur INDIREKT aufgerufen werden

        // JAVA
        /* final */   /* virtual*/ void sendJ(int) {};
        // versus 

        void send2(int) {};   // Nicht virtuelle Methode // wird KLASSISCH vererbt an alle Kinder
    };

    class KeyboardDriver : public Driver
    {
    public:
        void send2(int) {};  // PROBLEMATISCH // VERDECKUNG // NO Go
       // virtual void send(int) override final {};  // cannot be overriden anymore
    };

    class MouseDriver final : public Driver // cannot be used as base class anymore
    {
    public:
       // void send(int) {};  // cannot be overriden anymore
    };

    //class TrackballDriver : public MouseDriver
    //{};

    //class SpecialKeyboardDriver : public KeyboardDriver
    //{
    //public:
    //    void send(int) final;  // cannot be overriden anymore
    //};

    // =========================================================

    void test_01()
    {
        Base* ptr;
        ptr = new Derived();
        ptr->func(123);
    }
}

void main_virtual_override_final()
{
    int32_t x{};

    using namespace VirtualOverrideFinal;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
