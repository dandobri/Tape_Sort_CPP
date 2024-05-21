#include "tape.h"
Tape::Tape(std::string name, std::ios::openmode mode, int tapeSize) : tapeSize(tapeSize)
{
    file.open(name, mode);
    if(!file.is_open())
    {
        std::ofstream(name).close();
        file.open(name, mode);
    }
}
Tape::~Tape()
{
    if(file.is_open())
    {
        file.close();
    }
}

void Tape::waitRead()
{
    #ifdef _WIN32
        Sleep(waitReading);
    #else
        sleep(waitReading);
    #endif
}
void Tape::waitWrite()
{
    #ifdef _WIN32
        Sleep(waitWriting);
    #else
        sleep(waitWriting);
    #endif
}
void Tape::waitMove()
{
    #ifdef _WIN32
        Sleep(waitMoving);
    #else
        sleep(waitMoving);
    #endif
}
void Tape::waitScroll()
{
    #ifdef _WIN32
        Sleep(waitScrolling);
    #else
        sleep(waitScrolling);
    #endif
}


void Tape::read(int* num)
{
    waitRead();
    std::streampos pos;
    if(positions.empty())
    {
        pos = 0;
    } else {
        pos = positions.back();
    }
    file.seekg(pos, std::ios::beg);
    file >> *num;
    file.seekp(pos, std::ios::beg);
}
void Tape::write(int* num)
{
    waitWrite();
    positions.push_back(file.tellg());
    file << " " << *num ;
}


bool Tape::moveFront()
{
    if(file.eof())
    {
        return false;
    }
    waitMove();
    int num;
    file >> num;
    positions.push_back(file.tellg());
    return true;
}
bool Tape::moveBack()
{
    if(positions.empty())
    {
        return false;
    } else
    {
        waitMove();
        file.seekp(positions.back(), std::ios::beg);
        positions.pop_back();
    }
    return true;
}
void Tape::scroll(long pos)
{
    for(int i = positions.size() - 1; i > -1; i--)
    {
        if(i != pos - 1)
        {
            positions.pop_back();
        } else 
        {
            break;
        }
    }
    if(positions.empty())
    {
        positions.push_back(0);   
    }
    file.seekp(positions.back(), std::ios::beg);
}