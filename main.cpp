/* Uncomment to run different tests! */
//#define DOUBLY_LINKED_LIST_H
#define MULTITHREAD_H
//#define LZW_H

#if defined(DOUBLY_LINKED_LIST_H)
#include "doubly linked list.hpp"
#elif defined(MULTITHREAD_H)
#include "multithread.hpp"
#elif defined(LZW_H)
#include "lzw.hpp"
#endif

#include <cstdarg>

int main(unsigned char argc, char* argv[]) {
    /// Doubly Linked List Test Cases ///
    #if defined(DOUBLY_LINKED_LIST_H)
    DoublyLinkedList<int> list;
    std::cout << "Testing front insert.\n";
    list.frontInsert(1);
    list.printList();
    list.frontInsert(4);
    list.printList();
    list.frontInsert(7);
    list.printList();
    std::cout << "Testing end insert.\n";
    list.rearInsert(3);
    list.printList();
    list.rearInsert(6);
    list.printList();
    list.rearInsert(9);
    list.printList();
    std::cout << "Insert after head.\n";
    list.insertAfter(list.head, 8);
    list.printList();
    std::cout << "Testing deletes.\n";
    list.deleteNode(list.head);
    list.printList();
    list.deleteByValue(3,'t');
    list.deleteByValue(8,'t');
    list.printList();

    /// Multithreaded Test Cases ///
    #elif defined(MULTITHREAD_H)
    std::thread t1(searchStr,1,"ea");
    std::thread t2(searchStr,2,"ad");
    std::thread t3(searchStr,3,"ed");
    std::thread t4(searchStr,4,"a");
    std::thread t5(searchStr,5,"tt");
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    /// LZW Test Cases ///
    #elif defined(LZW_H)
    std::string mode = argv[1];
    std::string fileName = argv[2];
    if(argc < 3) {
        std::cout << "Path to executable, -encode or -decode, and file must be given as arguments.\n";
        return 1;
    }

    if((mode != "-encode") && (mode != "-decode")) {
        std::cout << "Wrong arguments, use -encode or -decode.\n";
        return 1;
    } 
    else if(mode == "-encode") { // encode with 12-bit LSB into new file
        std::fstream oldFile(fileName, std::fstream::in | std::fstream::binary);
        std::string data((std::istreambuf_iterator<char>(oldFile)), std::istreambuf_iterator<char>());
        oldFile.close();

        std::vector<unsigned char> me;
        encode(data, me);

        // load encoded data into new file
        std::string encodedFileName = std::filesystem::path(fileName).filename().string() + ".lzw";
        std::fstream yourMom(encodedFileName, std::fstream::out | std::fstream::binary);
        for(unsigned char i : me) { yourMom << i; }
        yourMom.close();
    } 
    else if(mode == "-decode" && (std::filesystem::path(fileName).extension().string()==".lzw")) { // decode existing file
        std::fstream oldFile(fileName, std::fstream::in | std::fstream::binary);
        std::string data((std::istreambuf_iterator<char>(oldFile)), std::istreambuf_iterator<char>());
        oldFile.close();

        std::vector<unsigned char> unpackedArray;
        decode(data, unpackedArray);

        // put decoded data into new file
        std::string decodedFileName = std::filesystem::path(std::filesystem::path(fileName).stem().string()).stem().string() 
        + "(uncompressed)"
        + std::filesystem::path(std::filesystem::path(fileName).stem().string()).extension().string();
        std::fstream decodedFile(decodedFileName, std::fstream::out | std::fstream::binary);
        for(unsigned char i : unpackedArray) { decodedFile << i; }
        decodedFile.close();
    }
    #endif
    return 0;
}