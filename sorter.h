#ifndef SORTER_H
#define SORTER_H
#include "tape.h"
#include <algorithm>
class Sorter
{
    private:
        int findMin(std::vector<Tape*>& tapeBuffer, std::vector<bool>& isFinished, Tape* result);
        void sortAndSaveBlock(std::vector<int>& numBuffer, Tape* out);
    public:
        void sortTape(Tape* input, Tape* output, int max_memory, int size, std::vector<int>* res_vect = nullptr);
};
#endif