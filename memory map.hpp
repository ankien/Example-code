#pragma once
#include <Windows.h>

void* mappedFile(const char* filepath) {
    HANDLE file = CreateFileA(filepath,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    return MapViewOfFile(
    CreateFileMappingA(file,NULL,PAGE_READWRITE,0,4096,NULL),
    FILE_MAP_ALL_ACCESS,
    0,
    0,
    0);
}