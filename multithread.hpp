#include <thread>
#include <cstdio>
#include <cstdint>
#include <string>
#include <chrono>
#include <regex>

void searchStr(uint8_t threadId, const char* string) {
    auto startTime = std::chrono::system_clock::now();

    static std::string someStr = 
    "This is a test sentence that is being searched for letters by multiple threads!";

    std::regex words_regex(string);
    auto words_begin = std::sregex_iterator(
        someStr.begin(), someStr.end(), words_regex);
    auto words_end = std::sregex_iterator();

    auto endTime = std::chrono::system_clock::now();
    auto span = endTime - startTime;

    printf("Search for %s(count=%lld) performed by threadID(%d) in %lld ms\n",string,std::distance(words_begin, words_end),threadId,span.count());
}