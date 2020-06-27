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
    } else if(mode == "-encode") { // encode into new file
        std::fstream oldFile(fileName, std::fstream::in);
        // load oldFile into memory
        std::vector<??> data;
        for() {  }
        oldFile.close;

        encode(data);

        std::string encodedFileName = std::filesystem::path(fileName).stem().string() + ".lzw";
        std::fstream newFile(encodedFileName, std::fstream::out);
        // load encode into newFile
        newFile.close;
    } else if(fileName == "-decode" && (std::filesystem::path(fileName).extension().string()==".lzw")) { // decode existing file
        decode();
    }
    #endif
    return 0;
}