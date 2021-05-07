#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <filesystem>
#include "State.h"


void readFile(const char* path);

class Person {
public:
    int age;
    explicit Person(int a) : age(a) {}
};

int main(int argc, char* argv[]) {

//    if(argc != 6) {
//        std::cout << "Wrong number of arguments" << std::endl;
//        return EXIT_FAILURE;
//    }

//    std::filesystem::path p = std::filesystem::current_path();
//    std::cout << p.relative_path() << std::endl;

    readFile("../4x4_01_00001.txt");

    std::string algorithm;
    std::string order;
    std::string startState;

   // algorithm = argv[1];

    return 0;
}

void readFile(const char* path) {
    std::ifstream file(path);
    std::string line;

    unsigned int **arr;
    unsigned int width = 0, height = 0;
    unsigned int x, y;

    if(file.is_open()) {
        file >> height >> width;
        arr = new unsigned int *[height];

        for(size_t i = 0; i < height; i++) {
            arr[i] = new unsigned int[width];
            for(size_t j = 0; j < width; j++) {
                file >> arr[i][j];
                if(arr[i][j] == 0) {
                    x = i;
                    y = j;
                }
            }
        }
        file.close();
    } else
        std::cout << "Unable to open file" << std::endl;

    std::shared_ptr<State> state = std::make_shared<State>(arr, x, y, height, width);

    for(size_t col = 0; col < height; col++)
        delete [] arr[col];
    delete [] arr;
}