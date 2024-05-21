#ifndef TAPE_H
#define TAPE_H
extern double waitReading;
extern double waitMoving;
extern double waitScrolling;
extern double waitWriting;

#include <fstream>
#include <vector>
#include <iostream>
#include <cstdio>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif
class Tape
{
    private:
        void waitRead();
        void waitWrite();
        void waitMove();
        void waitScroll();
        std::fstream file;
        int tapeSize;
        std::vector<std::streampos> positions;
    public:
        Tape(std::string name, std::ios::openmode mode, int tapeSize);
        ~Tape();
        void read(int* num);
        void write(int *num);
        void scroll(long pos);
        bool moveFront();
        bool moveBack();
};
#endif