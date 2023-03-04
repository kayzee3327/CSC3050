#include "phase1.hpp"
#include "phase2.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

LabelTable labelTable;
unsigned int PC = 0x400000;

std::unordered_map<std::string, std::string> R_funct{

    {"add", "100000"}, 
    {"addu", "100001"}, 
    {"and", "100100"}, 
    {"div", "011010"}, 
    {"divu", "011011"},
    {"jalr", "001001"}, 
    {"jr", "001000"}, 
    {"mfhi", "010000"}, 
    {"mflo", "010010"}, 
    {"mthi", "010001"},
    {"mtlo", "010011"}, 
    {"mult", "011000"}, 
    {"multu", "011001"}, 
    {"nor", "100111"}, 
    {"or", "100101"},
    {"sll", "000000"}, 
    {"sllv", "000100"}, 
    {"slt", "101010"}, 
    {"sltu", "101011"}, 
    {"sra", "000011"},
    {"srav", "000111"}, 
    {"srl", "000010"}, 
    {"srlv", "000110"}, 
    {"sub", "100010"}, 
    {"subu", "100011"},
    {"syscall", "001100"}, 
    {"xor", "100110"}

};

std::unordered_map<std::string, std::string> I_opcd {

    {"addi", "001000"}, 
    {"addiu", "001001"}, 
    {"andi", "001100"}, 
    {"beq", "000100"}, 
    {"bgez", "000001"},
    {"bgtz", "000111"}, 
    {"blez", "000110"}, 
    {"bltz", "000001"}, 
    {"bne", "000101"},
    {"lb", "100000"}, 
    {"lbu", "100100"}, 
    {"lh", "100001"}, 
    {"lhu", "100101"}, 
    {"lui", "001111"},
    {"lw", "100011"}, 
    {"ori", "001101"}, 
    {"sb", "101000"}, 
    {"slti", "001010"}, 
    {"sltiu", "001011"}, 
    {"sh", "101001"}, 
    {"sw", "101011"}, 
    {"xori", "001110"}, 
    {"lwl", "100010"},
    {"lwr", "100110"}, 
    {"swl", "101010"},
    {"swr", "101110"}
};

std::unordered_map<std::string, std::string> J_opcd{

    {"j", "000010"}, {"jal", "000011"}

};

std::unordered_map<std::string, int> registers {

    {"$zero", 0}, 
    {"$at", 1}, 
    {"$v0", 2}, {"$v1", 3}, 
    {"$a0", 4}, {"$a1", 5}, {"$a2", 6}, {"$a3", 7},
    {"$t0", 8}, {"$t1", 9}, {"$t2", 10}, {"$t3", 11}, {"$t4", 12}, {"$t5", 13}, {"$t6", 14}, {"$t7", 15},
    {"$s0", 16}, {"$s1", 17}, {"$s2", 18}, {"$s3", 19}, {"$s4", 20}, {"$s5", 21}, {"$s6", 22}, {"$s7", 23},
    {"$t8", 24}, {"$t9", 25}, 
    {"$k0", 26}, {"$k1", 27}, 
    {"$gp", 28}, 
    {"$sp", 29}, 
    {"$fp", 30}, 
    {"$ra", 31}

};

std::unordered_map<std::string, std::string> rt_notes {
    {"bgez", "00001"},
    {"bgtz", "00000"},
    {"blez", "00000"},
    {"bltz", "00000"},
};

char what_type(std::string instruction){
    if(R_funct.find(instruction) != R_funct.end()){
        return 'R';
    }
    else if(I_opcd.find(instruction) != I_opcd.end()){
        return 'I';
    }
    else if(J_opcd.find(instruction) != J_opcd.end()){
        return 'J';
    }
    else{
        std::cout << "what_type: invalid instruction: " << instruction;
        exit(0);
    }
}

std::string get_offset_str(std::string offsetAndBase){
    size_t left = offsetAndBase.find('(');
    
    return offsetAndBase.substr(0,left);
}

std::string get_base_str(std::string offsetAndBase){
    size_t left = offsetAndBase.find('(');
    size_t right = offsetAndBase.find(')');
    return offsetAndBase.substr(left + 1,right - left - 1);
}

std::string get_offset_str_branch(unsigned int PC, unsigned int target){
    std::string ans;
    unsigned int offset = (target - PC - 4) / 4; // minus 4 is important
    ans = int_to_bin_str(offset,16);
    return ans;
}

void print_instruction(InstructionPartVec v){
    for(auto it=v.begin();it!=v.end();it++){
        std::cout << *it << "  ";
    }
}

std::string translate(std::string line){
    std::istringstream istring(line);
    std::string instruction, var, vars = "";
    InstructionPartVec instructionPartVec;
    size_t commaPos;

    istring >> std::skipws >> instruction;
    instructionPartVec.push_back(instruction);

    while(1){
        istring >> std::skipws >> var;
        vars = vars + var;
        if(istring.eof()) break;
    }

    vars = vars + ",";
    commaPos = vars.find(',');
    while(commaPos != vars.npos){
        std::string temp = vars.substr(0,commaPos);
        instructionPartVec.push_back(temp);
        vars = vars.substr(commaPos+1);
        commaPos = vars.find(',');
    }
    std::cout << "Processing: " << line;
    std::cout << std::endl;
    if(what_type(instruction) == 'R'){
        return translate_R(instructionPartVec);
    }
    else if(what_type(instruction) == 'I'){
        return translate_I(instructionPartVec);
    }
    else if(what_type(instruction) == 'J'){
        return translate_J(instructionPartVec);
    }
    else {
        std::cout << "translate: invalid instruction : ";
        print_instruction(instructionPartVec);
        exit(0);
    }
    
}

std::string translate_R(InstructionPartVec parts){
    std::string ans = "000000";
    // rd, rs, rt
    if(parts[0] == "add" or parts[0] == "and" or parts[0] == "addu" or parts[0] == "nor" or parts[0] == "or" or parts[0] == "slt" or parts[0] == "sltu" or parts[0] == "sub" or parts[0] == "subu" or parts[0] == "xor"){
        ans = ans + int_to_bin_str(registers[parts[2]],5) + int_to_bin_str(registers[parts[3]],5) + int_to_bin_str(registers[parts[1]],5) + "00000" + R_funct[parts[0]];
    }
    // rs, rt
    else if(parts[0] == "div" or parts[0] == "divu" or parts[0] == "mult" or parts[0] == "multu"){
        ans = ans + int_to_bin_str(registers[parts[1]],5) + int_to_bin_str(registers[parts[2]],5) + "00000" + "00000" + R_funct[parts[0]];
    }
    // rd, rs
    else if(parts[0] == "jalr"){
        ans = ans + int_to_bin_str(registers[parts[2]],5) + "00000" + int_to_bin_str(registers[parts[1]],5) + "00000" + R_funct[parts[0]];
    }
    // rs
    else if(parts[0] == "jr" or parts[0] == "mthi" or parts[0] == "mtlo"){
        ans = ans + int_to_bin_str(registers[parts[1]],5) + "00000" + "00000" + "00000" + R_funct[parts[0]];
    }
    // rd
    else if(parts[0] == "mfhi" or parts[0] == "mflo"){
        ans = ans + "00000" + "00000" + int_to_bin_str(registers[parts[1]],5) + "00000" + R_funct[parts[0]];
    }
    // rd, rt, sa
    else if(parts[0] == "sll" or parts[0] == "sra" or parts[0] == "srl"){
        ans = ans + "00000" + int_to_bin_str(registers[parts[2]],5) + int_to_bin_str(registers[parts[1]],5) + int_to_bin_str(std::stoi(parts[3]),5) + R_funct[parts[0]];
    }
    // rd, rt, rs
    else if(parts[0] == "sllv" or parts[0] == "srav" or parts[0] == "srlv"){
        ans = ans + int_to_bin_str(registers[parts[3]],5) + int_to_bin_str(registers[parts[2]],5) + int_to_bin_str(registers[parts[1]],5) + "00000" + R_funct[parts[0]];
    }
    else if(parts[0] == "syscall"){
        ans = ans + "00000" + "00000" + "00000" + "00000" + "001100";
    }
    else {
        std::cout << "translate_R: invalid instruction: ";
        print_instruction(parts);
        exit(0);
    }
    return ans;
    
}
std::string translate_I(InstructionPartVec parts){
    std::string ans = "";
    
    // rt, rs, immediate
    if(parts[0] == "addi" or parts[0] == "addiu" or parts[0] == "andi" or parts[0] == "ori" or parts[0] == "slti" or parts[0] == "sltiu" or parts[0] == "xori"){
        ans = I_opcd[parts[0]] + int_to_bin_str(registers[parts[2]],5) + int_to_bin_str(registers[parts[1]],5) + int_to_bin_str(std::stoi(parts[3]),16);
    }
    // rs, rt, label
    else if(parts[0] == "beq" or parts[0] == "bne"){
        ans = I_opcd[parts[0]] + int_to_bin_str(registers[parts[1]],5) + int_to_bin_str(registers[parts[2]],5) + get_offset_str_branch(PC, labelTable[parts[3]]);
    }
    // rs, label
    else if(parts[0] == "bgez" or parts[0] == "bgtz" or parts[0] == "blez" or parts[0] == "bltz"){
        ans = I_opcd[parts[0]] + int_to_bin_str(registers[parts[1]],5) + rt_notes[parts[0]] + get_offset_str_branch(PC, labelTable[parts[2]]);
    }
    // rt, immediate(rs)
    else if(parts[0] == "lb" or parts[0] == "lbu" or parts[0] == "lh" or parts[0] == "lhu" or parts[0] == "lw" or parts[0] == "sb" or parts[0] == "sh" or parts[0] == "sw" or parts[0] == "lwl" or parts[0] == "swl" or parts[0] == "lwr" or parts[0] == "swr"){
        ans = I_opcd[parts[0]] + int_to_bin_str(registers[get_base_str(parts[2])],5) + int_to_bin_str(registers[parts[1]],5) + int_to_bin_str(std::stoi(get_offset_str(parts[2])),16);
    }
    // rt, immediate
    else if(parts[0] == "lui"){
        ans = I_opcd[parts[0]] + "00000" + int_to_bin_str(registers[parts[1]],5) + int_to_bin_str(std::stoi(parts[2]),16);
    }
    else {
        std::cout << "translate_I: invalid instruction: ";
        print_instruction(parts);
        exit(0);
    }
    return ans;
}
std::string translate_J(InstructionPartVec parts){
    return J_opcd[parts[0]] + int_to_bin_str(labelTable[parts[1]]/4,26); 
}
void phase2(std::string inputFilePath, std::string outputFilePath, LabelTable l){
    std::ifstream f_in(inputFilePath);
    std::ofstream f_out(outputFilePath);
    std::string line;
    labelTable = l;

    if(!f_in.is_open() or !f_out.is_open()){
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
        if(line.find(":") != line.npos or line.find(".") != line.npos){
            continue;
        }
        else if(!line.empty()){
            f_out << translate(line) << std::endl;
            PC += 4;
        }
        else {
            continue;
        }
    }
    f_in.close();
    f_out.close();
}