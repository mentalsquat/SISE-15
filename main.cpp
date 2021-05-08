#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <filesystem>
#include "State.h"
#include "AStar.h"

std::shared_ptr<State> readFile(const char* path);

int main(int argc, char* argv[]) {

//    if(argc != 6) {
//        std::cout << "Wrong number of arguments" << std::endl;
//        return EXIT_FAILURE;
//    }

//    std::filesystem::path p = std::filesystem::current_path();
//    std::cout << p.relative_path() << std::endl;



    std::string algorithm;
    std::string order;
    std::string startState;

    auto *solution = new Solution();
    solution->numberOfVisitedStates = 0;
    solution->numberOfProcessedStates = 0;
    solution->maxRecursiveDepth = 0;
    solution->elapsedTime = 0;
    solution->lengthOfSolution = -1;
    std::shared_ptr<State> initialState = readFile("../4x4_01_00001.txt");

    AStar Astar(initialState, "hamm", solution);
    std::shared_ptr<State> x;
    Astar.FindSolution(x);
    std::cout << "XD";


    return 0;
}

std::shared_ptr<State> readFile(const char* path) {
    std::ifstream file(path);
    std::string line;

    unsigned int **arr;
    unsigned int width = 0, height = 0;
    unsigned int x, y;
    std::vector<std::vector<unsigned int>> array;

    if(file.is_open()) {
        file >> height >> width;
       // arr = new unsigned int *[height];
        array.resize(height);
        for(size_t i = 0; i < height; i++) {
            //arr[i] = new unsigned int[width];
            array[i] = std::vector<unsigned int>(width);
            for(size_t j = 0; j < width; j++) {
                //file >> arr[i][j];
                file >> array[i][j];
                if(array[i][j] == 0) {
                    x = i;
                    y = j;
                }
            }
        }
        file.close();
    } else
        std::cout << "Unable to open file" << std::endl;

    std::shared_ptr<State> state = std::make_shared<State>(array, x, y, height, width);

    array.clear();

    return state;
}