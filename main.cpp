#include <random>
#include <limits>
#include <map>
#include <sstream>
#include "sorter.h"

const int n = 15;
const int m = 5;
double waitReading;
double waitWriting;
double waitMoving;
double waitScrolling;

//функия для запуска одного теста
void test(int i, int size, Sorter* sorter);
//обработка конфигурационного файла
int configurations(std::string configFile);

int main(int argc, char* argv[])
{
    if(argv == nullptr || argc != 3)
    {
        std::cerr << "Your command line must have only two files: input file and output file" << std::endl;
        return -1;
    }
    if (configurations("config.txt") == 0)
    {
        std::string input = argv[1];
        std::string output = argv[2];
        Tape inputTape(input, std::ios::in, n);
        Tape outputTape(output, std::ios::out, n);
        Sorter sorter;
        sorter.sortTape(&inputTape, &outputTape, m, n);
    }
    return 0;
}

int configurations(std::string config)
{
    std::ifstream configFile(config);
    std::string line;
    std::map<std::string, double> configValues;

    if (!configFile.is_open()) {
        std::cerr << "Ошибка при открытии файла конфигурации." << std::endl;
        return -1;
    }
    while(getline(configFile, line))
    {
        std::istringstream iss(line);
        std::string key;
        double value;
        if (getline(iss, key, '='))
        {
            iss >> value;
            configValues[key] = value;
        }
    }
    waitReading = configValues["waitReading"];
    waitWriting = configValues["waitWriting"];
    waitMoving = configValues["waitMoving"];
    waitScrolling = configValues["waitScrolling"];
    return 0;
}

void test(int i, int size, Sorter* sorter)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    Tape betw("./tests/hello" + std::to_string(i) + ".txt", std::ios::in | std::ios::out, size);
    std::vector<int> vect;
    for (int j = 0; j < size; ++j) {
        int a = distrib(gen);
        vect.push_back(a);
        betw.write(&a);
    }
    betw.scroll(0);
    std::sort(vect.begin(), vect.end());
    std::vector<int> res;
    Tape goodbye("./tests/goodbye" + std::to_string(i) + ".txt", std::ios::out, size);
    sorter->sortTape(&betw, &goodbye, i, size, &res);
    for(int k = 0; k < size; k++)
    {
        if(vect[k] != res[k])
        {
            std::cout << "not equals in " << k << std::endl;
            break;
        }
        if(k == size - 1)
        {
            std::cout << "Test Passed " << std::endl;
        }
    }
    res.clear();
    vect.clear();   
}