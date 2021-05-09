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
#include "BFS.h"
#include "DFS.h"

State* readFile(char* path);
void writeToFile(std::string basic, std::string extended, Solution *solution);

int main(int argc, char* argv[]) {

//    if(argc != 6) {
//        std::cout << "Wrong number of arguments" << std::endl;
//        return EXIT_FAILURE;
//    }
//
//    std::string algorithm = argv[1];
//    std::string order = argv[2];
//    std::string readPathFile = argv[3];
//    std::string basicPathFile = argv[4];
//    std::string advancePathFile = argv[5];

    auto *solution = new Solution();
    solution->numberOfVisitedStates = 0;
    solution->numberOfProcessedStates = 0;
    solution->maxRecursiveDepth = 0;
    solution->elapsedTime = 0;
    solution->lengthOfSolution = -1;

    std::string s = "../data/";
   // s.append(readPathFile);
    //std::cout << s << std::endl;
    State* initialState = readFile("D:\Studia\Semestr6\SISE\SISE-15\4x4_01_0001.txt");

    std::chrono::steady_clock::time_point t1, t2;

//    if(algorithm == "bfs") {
//        BFS bfs(initialState, order, solution);
//        t1 = std::chrono::steady_clock::now();
//        bfs.FindSolution();
//        t2 = std::chrono::steady_clock::now();
//    } else if (algorithm == "dfs") {
//        DFS dfs(initialState, order, solution);
//        t1 = std::chrono::steady_clock::now();
//        dfs.FindSolution();
//        t2 = std::chrono::steady_clock::now();
//    } else if (algorithm == "astr") {
//        if(order == "manh") {
//            AStar Astar(initialState, "manh", solution);
//            t1 = std::chrono::steady_clock::now();
//            Astar.FindSolution();
//            t2 = std::chrono::steady_clock::now();
//        } else if(order == "hamm") {
//            AStar Astar(initialState, "hamm", solution);
//            t1 = std::chrono::steady_clock::now();
//            Astar.FindSolution();
//            t2 = std::chrono::steady_clock::now();
//        }
//    }
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
//    long long d = duration.count() * 1e-3;
//    double result = (int)(d * 1000 + .5);
//
//    solution->elapsedTime = (double) result / 1000;

    writeToFile("basic.txt", "extented.txt", solution);

    return 0;
}

State* readFile(char* path) {
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

void writeToFile(std::string basic, std::string extended, Solution *solution) {
    std::ofstream basicFile(basic);

    if(basicFile.is_open()) {
        basicFile << solution->lengthOfSolution << "\n";
        basicFile << solution->searchOrder;
    } else
        std::cout << "Unable to open basic file" << std::endl;

    basicFile.close();

    std::ofstream extendedFile(extended);

    if(extendedFile.is_open()) {
        extendedFile << solution->lengthOfSolution << "\n";
        extendedFile << solution->numberOfVisitedStates << "\n";
        extendedFile << solution->numberOfProcessedStates << "\n";
        extendedFile << solution->maxRecursiveDepth << "\n";
        extendedFile << solution->elapsedTime << "\n";
    } else
        std::cout << "Unable to open basic file" << std::endl;

    extendedFile.close();


}