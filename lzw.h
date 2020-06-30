#include<iostream>
#include<filesystem>
#include<fstream>
#include<map>

void encode(std::string& input) {
    int dictSize = 256;
    std::map<std::string,int> dictionary;

    for(int i = 0; i < dictSize; i++) {
        dictionary[(char*) i] = i;
    }

    std::string encodedString;
    std::string w;
    for(char& c : input) {
        std::string wc = w + c;
        if(dictionary.count(wc)) {
            w = wc;
        } else {
            encodedString += dictionary[w];
            dictionary[wc] = dictSize++;
            w = c;
        }
    }

    // write w to input data
    input.assign(encodedString);
}

void decode(std::string& input) {
    
}