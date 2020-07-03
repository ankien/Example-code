#include<iostream>
#include<filesystem>
#include<string>
#include<fstream>
#include<map>

// Uses even/odd sequencing to store 12-bit codes in an 8-bit vector
// Even: Index at 0, 2, 4, ...
//  Odd: Index at 1, 3, 5, ...

void encode(std::string& input, std::vector<unsigned char>& packedArray) {
    int16_t dictSize = 256;
    std::map<std::string,int16_t> dictionary; // only using 12 bits of int
    for(int i = 0; i < dictSize; i++) {
        dictionary[std::string(1,i)] = i;
    }

    bool even=true;
    std::string curr;
    for(char& next : input) {
        std::string extendedDictionary = curr + next;
        if(dictionary.count(extendedDictionary)) {
            curr = extendedDictionary;
        } else {
            if(even) {
                packedArray.push_back(dictionary[curr] & 0xFF);
                packedArray.push_back((dictionary[curr] >> 8) & 0xF);
                even = false;
            } else {
                packedArray.at(packedArray.back()) |= dictionary[curr] << 4;
                packedArray.push_back(dictionary[curr] & 0xFF0);
                even = true;
            }
            dictionary[extendedDictionary] = dictSize++;
            curr = next;
        }
    }

    if(!curr.empty()) {
        if(even) {
            packedArray.push_back(dictionary[curr] & 0xFF);
            packedArray.push_back((dictionary[curr] >> 8) & 0xF);
            even = false;
        } else {
            packedArray.at(packedArray.back()) |= dictionary[curr] << 4;
            packedArray.push_back(dictionary[curr] & 0xFF0);
            even = true;
        }
    }
}

// need to redesign for 12-bit LSB
void decode(std::string& input, std::vector<unsigned char>& unpackedArray) {
    int dictSize = 256;
    std::map<int16_t,std::string> dictionary; // only using 12 bits
    for(int i = 0; i < dictSize; i++) {
        dictionary[i] = std::string(1,i);
    }

    std::string w(1,input.at(0)); // wtf is w
    std::string decodedString = w;
    std::string newEntry;
    int sequences;
    bool even=true;
    for(int i = 1; i < input.size(); i++) {
        int16_t curr;
        if(even) {
            curr = input.at(i-1) + ((input.at(i) & 0xF) << 8);
            even=false;
        }
        else {
            curr = ((input.at(i-1) & 0xF0) >> 4) + ((input.at(i) & 0xF) << 8); // fix?
            even=true;
            i++;
        }

        if(dictionary.count(curr)) {
            newEntry = dictionary[curr];
        } else if() {

        }
    }
}