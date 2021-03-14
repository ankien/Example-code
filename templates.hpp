#include <utility>
#include <cstdint>
#include <cstdio>

/*
    Made up 32-bit binary instruction format for the purpose of testing template metaprogramming.
    The idea is to compute suboperations of instructions at compile time.
    
    DATA PROCESSING:
    0b0000'0000'AAXX'XXXX'XXXX'XYYY'YYYY'YYYY
    AA = add (00), sub (01), div (10), mul (11)
    X = 11-bit unsigned integer (operand 1)
    Y = 11-bit unsigned integer (operand 2)
    result of operation is placed into result register

    DATA TRANSFER:
    0b0000'0001'0LXX'XXXX'XXXX'XXXX'XXXX'XXXX
    X = 30-bit unsigned integer
    L = load into result register if true, store into memory if not

    All undefined instructions place 0 into the result register
*/

uint32_t resultRegister = 0;
uint32_t memory = 0; // only 32-bits of memory? how sad :^)

template<uint8_t aa>
void dataProcessing(uint32_t instruction) {
    uint32_t op1 = (instruction & 0x3FF800) >> 11;
    uint16_t op2 = instruction & 0x7FF;
    switch(aa) {
        case 0b00:
            resultRegister = op1 + op2;
            break;
        case 0b01:
            resultRegister = op1 - op2;
            break;
        case 0b10:
            resultRegister = op1 / op2;
            break;
        case 0b11:
            resultRegister = op1 * op2;
    }
}

template<uint8_t ld>
void dataTransfer(uint32_t instruction) {
    uint32_t op1 = instruction & 0x3FFFFF;
    if(ld)
        resultRegister = op1;
    else
        memory = op1;
}

void undefined(uint32_t instruction) {
    resultRegister = 0;
}

template<typename T, uint16_t Begin, class Func, T ...Is>
constexpr void staticFor(Func&& f, std::integer_sequence<T, Is...>) {
    (f(std::integral_constant<T, Begin + Is>{}), ...);
}

template<typename T, uint16_t Begin, uint16_t End, class Func>
constexpr void staticFor(Func&& f) {
    staticFor<T, Begin>(static_cast<Func&&>(f), std::make_integer_sequence<T, End - Begin>{});
}

#define DECODING_OPS(i) switch(i >> 2) {                            \
                            case 0b0000'0000:                       \
                            {                                       \
                                const uint8_t aa = i & 0x3;         \
                                container[i] = &dataProcessing<aa>; \
                                break;                              \
                            }                                       \
                            case 0b0000'0001:                       \
                            {                                       \
                                const uint8_t ld = i & 0x1;         \
                                container[i] = &dataTransfer<ld>;   \
                                break;                              \
                            }                                       \
                            default:                                \
                                container[i] = &undefined;          \
                            }

template<uint16_t indexes>
struct templatedLUT {
    constexpr templatedLUT() : container() { // since you can't have uninitialized fields in a constexpr function
        // Since MSVC has a small unchangeable recursion depth (1024?), this staticFor is split into two parts;
        // it would just be 0 - 1024 on other compilers
        staticFor<uint16_t, 0, 512>([&](auto i) {
            DECODING_OPS(i)
        });
        staticFor<uint16_t, 512, 1024>([&](auto i) {
            DECODING_OPS(i)
        });
    }
    void (*container[indexes])(uint32_t); // we only need 8 bits (indexes = 256) to decode a function,
                                          // but 10 bits (indexes = 1024) are used for suboperation decoding
};

inline uint8_t getLUTIdx(uint32_t instruction) {
    return instruction >> 22;
}