#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <filesystem>
#include <Windows.h>
#include <unistd.h>
#include <chrono>
#include "State.h"
#include "AStar.h"

State* readFile(const char* path);

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
    State* initialState = readFile("../4x4_07_00121.txt");

    auto start = std::chrono::high_resolution_clock::now();
    AStar Astar(initialState, "hamm", solution);
    Astar.FindSolution();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << duration.count();

    return 0;
}

State* readFile(const char* path) {
    std::ifstream file(path);
    std::string line;

    unsigned int **arr;
    unsigned int width = 0, height = 0;
    unsigned int x, y;
    std::vector<std::vector<unsigned int>> array;

    if(file.is_open()) {
        file >> height >> width;
        array.resize(height);
        for(size_t i = 0; i < height; i++) {
            array[i] = std::vector<unsigned int>(width);
            for(size_t j = 0; j < width; j++) {
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

    auto *state = new State(array, x, y, height, width);

    array.clear();

    return state;
}