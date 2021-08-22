#pragma once
#include <iostream>
#include <string>

namespace Something
{

struct A {
    int num1;
    int num2;
    std::string stringy;
    A();
    void funky();
};

}

extern Something::A a;