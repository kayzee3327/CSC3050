#include "phase1.hpp"
#include "phase2.hpp"
#include <iostream>
#include <fstream>

void compare(std::string outputFilePath, std::string expectedFilePath){
    std::ifstream output(outputFilePath, std::ios::in);
    std::ifstream expected(expectedFilePath, std::ios::in);
    std::string so, se;
    int cnt=1;
    bool flag = true;
    while(getline(output, so) and getline(expected, se)){
        if(so != se){
            std::cout << "Found difference at line " << cnt << " of " << outputFilePath << std::endl;
            flag = false;
            std::cout << "output: \t\t" << so << std::endl;
            std::cout << "expected output: \t" << se << std::endl;
        }
        cnt++;
    }
    if(flag) std::cout << "same as expected";
}

int main(){
    std::string expectedPath;
    std::string inPath;
    std::string outPath;

    std::cout << "Please enter input file path: " << std::endl;
    std::cin >> inPath;
    std::cout << std::endl;

    std::cout << "Please enter output file path: " << std::endl;
    std::cin >> outPath;
    std::cout << std::endl;

    std::cout << "Please enter expected output file path: " << std::endl;
    std::cin >> expectedPath;
    std::cout << std::endl;

    LabelTable labelTable = phase1(inPath);
    phase2(inPath,outPath,labelTable);
    compare(outPath, expectedPath);
    return 0;
}