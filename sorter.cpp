#include "sorter.h"

void Sorter::sortTape(Tape* input, Tape* output, int max_memory, int size, std::vector<int>* res_vect)
{
    std::vector<int> numBuffer;
    std::vector<Tape*> tapeBuffer;
    int num;
    int tape_number = 0;

    input->read(&num);
    numBuffer.push_back(num);
    while(input->moveFront())
    {
        if(numBuffer.size() >= max_memory)
        {
            Tape *out = new Tape("./tmp/tape" + std::to_string(max_memory) + std::to_string(tape_number++) + ".txt", std::ios::in | std::ios::out, size);
            sortAndSaveBlock(numBuffer, out);
            tapeBuffer.push_back(out);
        }
        input->read(&num);
        numBuffer.push_back(num);
    }
    if(!numBuffer.empty())
    {
        Tape* out = new Tape("./tmp/tape" + std::to_string(max_memory) + std::to_string(tape_number++) + ".txt", std::ios::in | std::ios::out, size);
        sortAndSaveBlock(numBuffer, out);
        tapeBuffer.push_back(out);
    }
    std::vector<bool> isFinished(tape_number, false);
    int count = 0;
    while(count < size)
    {
        num = findMin(tapeBuffer, isFinished, output);
        output->write(&num);
        if(res_vect != nullptr)
        {
            res_vect->push_back(num);
        }
        count++;
    }
    for(auto tape: tapeBuffer)
    {
        delete tape;
    }
}

int Sorter::findMin(std::vector<Tape*>& tapeBuffer, std::vector<bool>& isFinished, Tape* result)
{
    int min = std::numeric_limits<int>::max();
    int minPointer = 0;
    int num;
    for(int i = 0; i < tapeBuffer.size(); i++)
    {
        if(!isFinished[i])
        {
            tapeBuffer[i]->read(&num);
            if(num < min)
            {
                minPointer = i;
                min = num;
            }
        }
    }
    if(!tapeBuffer[minPointer]->moveFront())
    {
        isFinished[minPointer] = true;
    }
    return min;
}

void Sorter::sortAndSaveBlock(std::vector<int>& numBuffer, Tape* out)
{
    std::sort(numBuffer.begin(), numBuffer.end());
    for(int n: numBuffer)
    {
        out->write(&n);
    }
    out->scroll(0);
    numBuffer.clear();
}