#include<iostream>
#include<filesystem>
#include<string>
#include<fstream>
#include<map>

void encode(std::string& input, std::vector<unsigned char>& packedArray) {
    int16_t dictSize = 256;
    std::map<std::string,int16_t> dictionary; // only using 12 bits of int
    for(int i = 0; i < dictSize; i++) {
        dictionary[std::string(1,i)] = i;
    }

    bool odd=true;
    std::string w;
    for(char& c : input) {
        std::string wc = w + c;
        if(dictionary.count(wc)) {
            w = wc;
        } else {
            if(odd) {
                packedArray.push_back(dictionary[w] & 0xFF);
                packedArray.push_back((dictionary[w] >> 8) & 0xF);
                odd = false;
            } else {
                packedArray.at(packedArray.back()) |= dictionary[w] << 4;
                packedArray.push_back(dictionary[w] & 0xFF0);
                odd = true;
            }
            dictionary[wc] = dictSize++;
            w = c;
        }
    }

    if(!w.empty()) {
        if(odd) {
            packedArray.push_back(dictionary[w] & 0xFF);
            packedArray.push_back((dictionary[w] >> 8) & 0xF);
            odd = false;
        } else {
            packedArray.at(packedArray.back()) |= dictionary[w] << 4;
            packedArray.push_back(dictionary[w] & 0xFF0);
            odd = true;
        }
    }
}

// need to redesign for 12-bit LSB
void decode(std::string& input, std::vector<unsigned char> unpackedArray) {
    int dictSize = 256;
    std::map<int,std::string> dictionary;
    for(int i = 0; i < dictSize; i++) {
        dictionary[i] = std::to_string(i);
    }

    std::string w = std::to_string(input.at(0));
    std::string decodedString = w;
    std::string entry;
    for(int i = 1; i < input.size(); i++) {
        int k = input.at(i);
        if(dictionary.count(k)) {
            entry = dictionary[k];
        } else if(k == dictSize) {
            entry = w + w[0];
        } else {
            throw "String not found at k";
        }

        decodedString+=entry;

        dictionary[dictSize++] = w + entry[0];

        w = entry;
    }

    input.assign(decodedString);
}