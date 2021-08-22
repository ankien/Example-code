#include "global object.hpp"

Something::A a;

Something::A::A() {
    num1 = 69;
    num2 = 420;
    stringy = " ^ this is funny";
}

void Something::A::funky() {
    num1 = 77;
    num2 = 666;
    stringy = " ^ this is spooky";
}