#include "phase1.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

std::string int_to_bin_str(int PC, int bitLength){
    unsigned int *x;
    x = new unsigned int;
    *x = PC;
    std::string ans = "";
    std::string bin[2] = {"0","1"};
    while(1){
        if(*x == 0) break;
        if(ans.length() == bitLength) break;
        ans = bin[*x % 2] + ans;
        *x /= 2;
    }
    delete x;
    if(ans.length() < bitLength){
        if(PC >= 0){
            for(int i=ans.length();i<bitLength;i++){
                ans = "0" + ans;
            }
        }
        else {
            for(int i=ans.length();i<bitLength;i++){
                ans = "1" + ans;
            }
        }
    }
    return ans;
}

std::string int_to_hex_str(unsigned int PC, int bitLength, bool uppercase){
    std::string ans = "";
    std::string hex_lower[16] = {
        "0","1","2","3",
        "4","5","6","7",
        "8","9","a","b",
        "c","d","e","f"
    };
    std::string hex_upper[16] = {
        "0","1","2","3",
        "4","5","6","7",
        "8","9","A","B",
        "C","D","E","F"
    };

    while(PC != 0){
        if(uppercase){
            ans = hex_upper[PC % 16] + ans;
        }
        else {
            ans = hex_lower[PC % 16] + ans;
        }
        PC /= 16;
    }

    if(bitLength == -1){
        return ans;
    }
    else {
        for(int i=ans.length();i<bitLength;i++){
            ans = "0" + ans;
        }
        return ans;
    }
}

void read_labels(std::string inputFilePath, LabelTable & labelTable){
    std::ifstream f_in(inputFilePath, std::ios::in);
    std::string line, subs;
    int labelPosInLine;
    unsigned int PC = 0x400000;

    if(!f_in.is_open()){
        std::cerr << "target file unopen";
        exit(0);
    }

    while(getline(f_in,line)){
        if (line.find(".text") == line.npos){
            continue;
        }
        else{
            break;
        }
    }

    while(getline(f_in,line)){
        if (line.find(':') != line.npos){
            labelPosInLine = line.find(':');
            subs = line.substr(0, labelPosInLine);
            if (labelTable.find(subs) != labelTable.end()){
                std::cout << "duplicate label";
                exit(0);
            }
            else {
                labelTable.insert(std::pair<std::string, unsigned int> {subs, PC});
                PC -= 4;
            }
        }
        PC = PC + 4;
    }
    f_in.close();
}

LabelTable phase1(std::string inputFilePath){
    LabelTable labelTable;
    read_labels(inputFilePath, labelTable);
    return labelTable;
}