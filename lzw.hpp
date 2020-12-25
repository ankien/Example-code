#include<iostream>
#include<filesystem>
#include<fstream>
#include<map>

// Uses even/odd sequencing to store 12-bit codes in an 8-bit vector
// Even: Index at [0-1), [3-4), [6-7), ...
//  Odd: Index at (1-2], (4-5], (7-8], ...

void encode(std::string& input, std::vector<unsigned char>& packedArray) {
    uint16_t dictSize = 256;
    std::map<std::string,uint16_t> dictionary; // only using 12 bits of int
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
                packedArray.push_back((dictionary[curr] & 0xF00) >> 8);
                even = false;
            } else {
                packedArray.at(packedArray.size()-1) |= ((dictionary[curr] & 0xF) << 4);
                packedArray.push_back((dictionary[curr] & 0xFF0) >> 4);
                even = true;
            }
            dictionary[extendedDictionary] = dictSize++;
            curr = next;
        }
    }

    if(!curr.empty()) {
        if(even) {
            packedArray.push_back(dictionary[curr] & 0xFF);
            packedArray.push_back((dictionary[curr] & 0xF00 ) >> 8);
        } else {
            packedArray.at(packedArray.size()-1) |= ((dictionary[curr] & 0xF) << 4);
            packedArray.push_back((dictionary[curr] & 0xFF0) >> 4);
        }
    }
}

void decode(std::string& input, std::vector<unsigned char>& unpackedArray) {
    int dictSize = 256;
    std::map<uint16_t,std::string> dictionary; // only using 12 bits
    for(int i = 0; i < dictSize; i++) {
        dictionary[i] = std::string(1,i);
    }
    
    uint16_t curr;
    uint16_t next;
    std::string newEntry;
    std::string output;
    bool even=true;
    for(int i = 1; i < input.size(); i++) {
        if(even) {
            curr = input.at(i-1) + ((input.at(i) & 0xF) << 8);
            output = dictionary[curr];
            newEntry = dictionary[curr].at(0);
            // add curr + next to dictionary here
            if((input.size() - i) > 1) {
                next = ((input.at(i) & 0xF0) >> 4) + (input.at(i+1) << 4);
                newEntry = dictionary[curr];
                newEntry += dictionary[next].at(0);
            }
            dictionary[dictSize++] = newEntry;
            even=false;
        }
        else {
            curr = ((input.at(i-1) & 0xF0) >> 4) + (input.at(i) << 4);
            output = dictionary[curr];
            newEntry = dictionary[curr].at(0);
            // ditto for odd
            if((input.size() - i) > 2) {
                next = input.at(i+1) + ((input.at(i+2) & 0xF) << 8);
                newEntry = dictionary[curr];
                newEntry += dictionary[next].at(0);
            }
            dictionary[dictSize++] = newEntry;
            even=true;
            i++;
        }

        for(char character : output)
            unpackedArray.push_back(character);

        newEntry="";
    }
}