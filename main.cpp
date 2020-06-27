//#define DOUBLY_LINKED_LIST_H
#define LZW_H

#if defined(DOUBLY_LINKED_LIST_H)
#include "doubly linked list.h"
#elif defined(LZW_H)
#include "lzw.h"
#endif

#include <cstdarg>

int main(unsigned char argc, ...) {
    va_list args;
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

    /// LZW Test Cases ///
    #elif defined(LZW_H)
    va_start(args, argc);
    std::string executableName = va_arg(args, const char*);
    std::string mode = va_arg(args, const char*);
    std::string fileName = va_arg(args, const char*);
    if(argc < 3) {
        std::cout << "Path to executable, -encode or -decode, and file must be given as arguments.\n";
        return 1;
    }

    if((mode != "-encode") || (mode != "-decode")) {
        std::cout << "Wrong arguments, use -encode or -decode.\n";
        return 1;
    } 
    else if(mode == "-encode") { // encode into new file
        std::fstream oldFile(fileName, std::fstream::in | std::fstream::binary);
        std::vector<byte> data((std::istreambuf_iterator<char>(oldFile)), std::istreambuf_iterator<char>());
        oldFile.close;

        encode(data);

        // load encoded data into new file
        std::string encodedFileName = std::filesystem::path(fileName).filename().string() + ".lzw";
        std::fstream encodedFile(encodedFileName, std::fstream::out | std::fstream::binary);
        for(const byte &i : data) { encodedFile << i; }
        encodedFile.close;
    } 
    else if(fileName == "-decode" && (std::filesystem::path(fileName).extension().string()==".lzw")) { // decode existing file
        std::fstream oldFile(fileName, std::fstream::in | std::fstream::binary);
        std::vector<byte> data((std::istreambuf_iterator<char>(oldFile)), std::istreambuf_iterator<char>());
        oldFile.close;

        decode(data);

        // put decoded data into new file
        std::string decodedFileName = std::filesystem::path(std::filesystem::path(fileName).stem().string()).stem().string() 
        + "(uncompressed)"
        + std::filesystem::path(std::filesystem::path(fileName).stem().string()).extension().string();
        std::fstream decodedFile(decodedFileName, std::fstream::out | std::fstream::binary);
        for(const byte &i : data) { decodedFile << i; }
        decodedFile.close;
    }
    #endif
    return 0;
}