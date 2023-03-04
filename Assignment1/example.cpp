#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <bitset>
#include <algorithm>
#include <typeinfo>
using namespace std;

extern int PC;
extern char* mem_addr;
extern const int map_addr;
extern map<int, fstream*> file;
extern vector<int> idx;

char* mem_addr = (char*) malloc(6291456);
vector<int> idx;
const int map_addr = 0x00400000;

class Labelling{

    public:

        Labelling(std::string name, int32_t address, string data_type = "instruction", string content = ""){
        this->name = name;
        this->address = address;
        this->data_type = data_type;
        this->content = content;
        }

        std::string getName(){
            return name;
        }

        int32_t getAddress(){
            return address;
        }

        string getData_type(){
            return data_type;
        }

        string getContent(){
            return content;
        }


    private:

        std::string name;
        int32_t address;
        std::string data_type;
        std::string content;

        friend bool operator==(Labelling label, string string);
        friend bool operator==(string string, Labelling label);
};

bool operator==(Labelling label, string string){

    return label.getName() == string;

}

bool operator==(string string, Labelling label){

    return label.getName() == string;
}

vector<Labelling> labels;
vector<string> data_types {

    ".ascii", ".asciiz", ".word", ".byte", ".half"

};

map<string, string> R{

    {"add", "100000"}, {"addu", "100001"}, {"and", "100100"}, {"div", "011010"}, {"divu", "011011"},
    {"jalr", "001001"}, {"jr", "001000"}, {"mfhi", "010000"}, {"mflo", "010010"}, {"mthi", "010001"},
    {"mtlo", "010011"}, {"mult", "011000"}, {"multu", "011001"}, {"nor", "100111"}, {"or", "100101"},
    {"sll", "000000"}, {"sllv", "000100"}, {"slt", "101010"}, {"sltu", "101011"}, {"sra", "000011"},
    {"srav", "000111"}, {"srl", "000010"}, {"srlv", "000110"}, {"sub", "100010"}, {"subu", "100011"},
    {"syscall", "001100"}, {"xor", "100110"}, {"clo","100001"}, {"clz", "100000"}, {"mul", "011000"},
    {"madd", "000000"}, {"maddu", "000001"}, {"msub", "000100"}, {"msubu", "000101"}, {"teq", "110100"},
    {"tne", "110110"}, {"tge", "110000"}, {"tgeu", "110001"}, {"tlt", "110010"}, {"tltu", "110011"},

};

map<string, string> I {

    {"addi", "001000"}, {"addiu", "001001"}, {"andi", "001100"}, {"beq", "000100"}, {"bgez", "000001"},
    {"bgezal", "000001"}, {"bgtz", "000111"}, {"blez", "000110"}, {"bltz", "000001"}, {"bne", "000101"},
    {"lb", "100000"}, {"lbu", "100100"}, {"lh", "100001"}, {"lhu", "100101"}, {"lui", "001111"},
    {"lw", "100011"}, {"ori", "001101"}, {"sb", "101000"}, {"slti", "001010"}, {"sc", "111000"},
    {"sltiu", "001011"}, {"sh", "101001"}, {"sw", "101011"}, {"xori", "001110"}, {"tlti", "000001"},
    {"bltzal", "000001"}, {"swr", "101110"}, {"swl", "101010"}, {"ll", "110000"}, {"tltiu", "000001"},
    {"lwr", "100110"}, {"lwl", "100010"}, {"tgei", "000001"}, {"tgeiu", "000001"}, {"tnei", "000001"},
    {"teqi", "000001"}
};

map<string, string> J {

    {"j", "000010"}, {"jal", "000011"}

};

map<string, int> registers = {

    {"$zero", 0}, {"$at", 1}, {"$v0", 2}, {"$v1", 3}, {"$a0", 4}, {"$a1", 5}, {"$a2", 6}, {"$a3", 7},
    {"$t0", 8}, {"$t1", 9}, {"$t2", 10}, {"$t3", 11}, {"$t4", 12}, {"$t5", 13}, {"$t6", 14}, {"$t7", 15},
    {"$s0", 16}, {"$s1", 17}, {"$s2", 18}, {"$s3", 19}, {"$s4", 20}, {"$s5", 21}, {"$s6", 22}, {"$s7", 23},
    {"$t8", 24}, {"$t9", 25}, {"$k0", 26}, {"$k1", 27}, {"$gp", 28}, {"$sp", 29}, {"$fp", 30}, {"$ra", 31}

};

struct memory_PC{
    vector<string> memory;
    int eText, data;
    vector<int> registers;

};

int data_input(string fin, int currentAddress){
    string data_type, data, tempData;
    int temp = fin.find('.');
    data_type = fin.substr(temp+1, fin.find(' ', temp)-temp-1);

    if(data_type == "asciiz"){
        temp = fin.find('"');
        data = fin.substr(temp+1, fin.find('"', temp+1)-temp-1);
        temp = data.length();
        for(int i = 0; i<temp; i++){
            mem_addr[currentAddress+i-map_addr] = data[i];
        }
        mem_addr[currentAddress+temp-map_addr] = '\0';
        temp++;
        if(temp%4 != 0) temp+=4-(temp%4);
        currentAddress+=temp;

    }else if(data_type == "ascii"){
        temp = fin.find('"');
        data = fin.substr(temp+1, fin.find('"', temp+1)-temp-1);
        temp = data.length();
        for(int i = 0; i<temp; i++){
            mem_addr[currentAddress+i-map_addr] = data[i];
        }
        if(temp%4 != 0) temp+=4-(temp%4);
        currentAddress+=temp;

    }else if(data_type == "word"){
        temp = fin.find(' ', temp);
        data = fin.substr(temp+1, fin.length()-temp-1);
        tempData.clear();
        for(int i = 0; i<int(data.length()); i++){
            if(data[i] == ' ') continue;
            else if(data[i] == ','){
                if(isdigit(tempData[0])) temp = stoi(tempData);
                for(int i = 3; i>=0; i--){
                    mem_addr[currentAddress-map_addr+i] = temp%256;
                    temp/=256;
                }
                currentAddress+=4;
                tempData.clear();
            }
            else tempData+=data[i];
        }
        if(tempData.length()!=0){
            if(isdigit(tempData[0])) temp = stoi(tempData);
            for(int i = 3; i>=0; i--){
                mem_addr[currentAddress-map_addr+i] = temp%256;
                temp/=256;
            }
            currentAddress+=4;
            tempData.clear();
        }
    }else if(data_type == "half"){
        temp = fin.find(' ', temp);
        data = fin.substr(temp+1, fin.length()-temp-1);
        tempData.clear();
        for(int i = 0; i<int(data.length()); i++){
            if(data[i] == ' ') continue;
            else if(data[i] == ','){
                if(isdigit(tempData[0])) temp = stoi(tempData);
                for(int i = 1; i>=0; i--){
                    mem_addr[currentAddress-map_addr+i] = temp%256;
                    temp/=256;
                }
                currentAddress+=2;
                tempData.clear();
            }
            else tempData+=data[i];
        }
        if(tempData.length()!=0){
            if(isdigit(tempData[0])) temp = stoi(tempData);
            for(int i = 1; i>=0; i--){
                mem_addr[currentAddress-map_addr+i] = temp%256;
                temp/=256;
            }
            currentAddress+=2;
            tempData.clear();
        }
    }else if(data_type == "byte"){
        temp = fin.find(' ', temp);
        data = fin.substr(temp+1, fin.length()-temp-1);
        tempData.clear();
        for(int i = 0; i<int(data.length()); i++){
            if(data[i] == ' ') continue;
            else if(data[i] == ','){
                if(isdigit(tempData[0])) temp = stoi(tempData);
                mem_addr[currentAddress-map_addr] = temp%256;
                temp/=256;
                currentAddress++;
                tempData.clear();
            }
            else tempData+=data[i];
        }
        if(tempData.length()!=0){
            if(isdigit(tempData[0])) temp = stoi(tempData);
            mem_addr[currentAddress-map_addr] = temp%256;
            temp/=256;
            currentAddress++;
            tempData.clear();
        }
    }
    return currentAddress;
}

void text_input(memory_PC &memory, vector<string> temp){
    for (int i = 0; i < temp.size(); i++){
        int Lim = memory.data;
        int Cur = memory.eText;
        if (Cur <= Lim){
            memory.memory[memory.eText] = temp[i];
            memory.eText += 1;
            memory.registers[29] = memory.eText;
        }
    }
}

int32_t findLabels(string label){

    for(auto & elem: labels){

        if(label == elem){

            return elem.getAddress();

        }

    }
    return -1;
}

string convertRegister(string reg){

    string outcome;

    for(char const & c: reg){

        if(isdigit(c) != 0) {

            return reg;

        } else break;
    }

    auto it = registers.find(reg);

    if(it != registers.end()){

        outcome = bitset<5>(it->second).to_string();

        return outcome;

    } else return "";
}

string R_type(string instruction,string rd, string rs, string rt, string shamt, string funct){

    string operators;
    if (instruction == "clo" || instruction == "clz" || instruction == "mul" || instruction == "madd" || instruction == "maddu" || instruction == "msub" || instruction == "msubu"){
        operators = "011100";
    }
    else{
        operators = "000000";
    }
    string dest_reg = convertRegister(rd);
    string first_reg = convertRegister(rs);
    string second_reg = convertRegister(rt);
    int shmts = stoi(shamt);
    string shift_amt = bitset<5>(shmts).to_string();

    return operators + first_reg + second_reg + dest_reg + shift_amt + funct;

}

string I_type(string instruction, string op, string rt, string rs, string immediate){

    string dest_reg = convertRegister(rt);
    string first_reg = convertRegister(rs);
    int shmts = stoi(immediate);
    string imm_val = bitset<16>(shmts).to_string();

    return op + first_reg + dest_reg + imm_val;

}

string J_type(string operators, string address){
    int shmts = stoi(address);
    string address_val = bitset<26>(shmts).to_string();

    return operators + address_val;
}

void parseLine (string output, vector <vector<string>> & token, int counter1){
    vector <string> column;
    output.erase(std::remove(output.begin(), output.end(), ','), output.end());

    int length_line = output.length();
    int pos = 0;
    for (int i = 0; i < length_line; i++){
        if (output[i] == ' '){
            int len = i-pos;
            if (output.substr(pos,len)!= ""){
                column.push_back(output.substr(pos,len));
            }
            pos = i+1;
        }
    }
    column.push_back(output.substr(pos));
    if (column[0] != ""){
        token.push_back(column);
        counter1 += 1;
    }
}

string removeComments(string arg, string str){

int found = str.find(arg);

while (true){
    if (found == -1)break;
    else{
        str.erase(found);
        found=str.find(arg,found);
    }
  }
return str;
}

string removeTabOrSpace(string output){
    string formatted_line;

    if(output.at(0) == '\t' || output.at(0) == ' '){
        formatted_line = output.substr(1);
    } else formatted_line = output;
    if(formatted_line.back() == '\t' || formatted_line.back() == ' '){
        formatted_line = formatted_line.substr(0, output.size() - 1);
    }
    return formatted_line;
}

string final_data(string str){
    string output = removeComments("#", str);
    output = removeTabOrSpace(output);
    return output;
}

string addresing (string fin, int line_counter){

    string nText = removeComments(".", fin );
    int found = fin.find(":");

    while (true){
        if (found == -1)break;
        else{
            Labelling address (nText.substr(0,found), 0x4000000 + (line_counter) * 4);
            labels.push_back(address);
            nText.erase(0,found+1);
            found=nText.find(":",found);
        }
    }
    return nText;
}

void machineCode(vector<string> token, vector<string> & code, int line_counter){
    map<string, string>::iterator N1;
    string outcome;

    if (token[0] == "add"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "addu"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "and"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "clo"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "clz"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "div"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "divu"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "mult"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "multu"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "mul"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "madd"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "msub"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "maddu"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "msubu"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "nor"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "or"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "ori"){
        N1 = I.find(token[0]);
         outcome = I_type(token[0], N1->second, token[1], token[2], token[3]);
        code.push_back(outcome);
    }
    else if (token[0] == "sll"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], token[3], N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "sllv"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "sra"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], token[3], N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "srav"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "srl"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], token[3], N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "srlv"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "sub"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "subu"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "mfhi"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], "0", "0", "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "mflo"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], "0", "0", "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "mthi"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], "0", "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "mtlo"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], "0", "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "jalr"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2],"0", "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "jr"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1],"0", "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "tge"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "tgeu"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "teq"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "tne"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "syscall"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", "0", "0", "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "slt"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "sltu"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "xor"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], token[1], token[2], token[3], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "tlt"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], "0", N1->second);
        code.push_back(outcome);
    }
    else if (token[0] == "tltu"){
        N1 = R.find(token[0]);
         outcome = R_type(token[0], "0", token[1], token[2], "0", N1->second);
        code.push_back(outcome);
    }


    //I type instruction sets


    else if (token[0] == "addi"){
        N1 = I.find(token[0]);
         outcome = I_type(token[0], N1->second, token[1], token[2], token[3]);
        code.push_back(outcome);
    }
    else if (token[0] == "addiu"){
        N1 = I.find(token[0]);
         outcome = I_type(token[0], N1->second, token[1], token[2], token[3]);
        code.push_back(outcome);
    }
    else if (token[0] == "andi"){
        N1 = I.find(token[0]);
         outcome = I_type(token[0], N1->second, token[1], token[2], token[3]);
        code.push_back(outcome);
    }
    else if (token[0] == "xori"){
        N1 = I.find(token[0]);
         outcome = I_type(token[0], N1->second, token[1], token[2], token[3]);
        code.push_back(outcome);
    }
    else if (token[0] == "lui"){
        N1 = I.find(token[0]);
         outcome = I_type(token[0], N1->second, 0, token[1], token[2]);
        code.push_back(outcome);
    }
    else if (token[0] == "slti"){
        N1 = I.find(token[0]);
         outcome = I_type(token[0], N1->second, token[1], token[2], token[3]);
        code.push_back(outcome);
    }
    else if (token[0] == "sltiu"){
        N1 = I.find(token[0]);
         outcome = I_type(token[0], N1->second, token[1], token[2], token[3]);
        code.push_back(outcome);
    }
    else if (token[0] == "beq"){
        N1 = I.find(token[0]);
        if (findLabels(token[3]) == -1){
             outcome = I_type(token[0], N1->second, token[1], token[2], token[3]);
            code.push_back(outcome);
        }
        else{
            int addressR = findLabels(token[3]) - (0x400000 + ((line_counter *4) + 4));
             outcome = I_type(token[0], N1->second, token[2], token[1], to_string(addressR/4));
            code.push_back(outcome);
        }
    }
    else if (token[0] == "bgez"){
        N1 = I.find(token[0]);
        if (findLabels(token[2]) == -1){
             outcome = I_type(token[0], N1->second, "00001", token[1], token[2]);
            code.push_back(outcome);
        }
        else{
            int addressR = findLabels(token[2]) - (0x400000 + ((line_counter *4) + 4));
             outcome = I_type(token[0], N1->second, "00001", token[1], to_string(addressR/4));
            code.push_back(outcome);
        }
    }
    else if (token[0] == "bgezal"){
        N1 = I.find(token[0]);
        if (findLabels(token[2]) == -1){
             outcome = I_type(token[0], N1->second, "10001", token[1], token[2]);
            code.push_back(outcome);
        }
        else{
            int addressR = findLabels(token[2]) - (0x400000 + ((line_counter *4) + 4));
             outcome = I_type(token[0], N1->second, "10001", token[1], to_string(addressR/4));
            code.push_back(outcome);
        }
    }
    else if (token[0] == "bgtz"){
        N1 = I.find(token[0]);
        if (findLabels(token[2]) == -1){
             outcome = I_type(token[0], N1->second, "00000", token[1], token[2]);
            code.push_back(outcome);
        }
        else{
            int addressR = findLabels(token[2]) - (0x400000 + ((line_counter *4) + 4));
             outcome = I_type(token[0], N1->second, "00000", token[1], to_string(addressR/4));
            code.push_back(outcome);
        }
    }
    else if (token[0] == "blez"){
        N1 = I.find(token[0]);
        if (findLabels(token[2]) == -1){
             outcome = I_type(token[0], N1->second, "00000" ,token[1], token[2]);
            code.push_back(outcome);
        }
        else{
            int addressR = findLabels(token[2]) - (0x400000 + ((line_counter *4) + 4));
             outcome = I_type(token[0], N1->second, "00000" ,token[1] , to_string(addressR/4));
            code.push_back(outcome);
        }
    }
    else if (token[0] == "bltzal"){
        N1 = I.find(token[0]);
        if (findLabels(token[2]) == -1){
             outcome = I_type(token[0], N1->second, "10000", token[1], token[2]);
            code.push_back(outcome);
        }
        else{
            int addressR = findLabels(token[2]) - (0x400000 + ((line_counter *4) + 4));
             outcome = I_type(token[0], N1->second, "10000", token[1], to_string(addressR/4));
            code.push_back(outcome);
        }
    }
    else if (token[0] == "bltz"){
        N1 = I.find(token[0]);
        if (findLabels(token[2]) == -1){
             outcome = I_type(token[0], N1->second, "00000", token[1], token[2]);
            code.push_back(outcome);
        }
        else{
            int addressR = findLabels(token[2]) - (0x400000 + ((line_counter *4) + 4));
             outcome = I_type(token[0], N1->second, "00000", token[1], to_string(addressR/4));
            code.push_back(outcome);
        }
    }
    else if (token[0] == "bne"){
        N1 = I.find(token[0]);
        if (findLabels(token[3]) == -1){
             outcome = I_type(token[0], N1->second, token[2], token[1], token[3]);
            code.push_back(outcome);
        }
        else{
            int addressR = findLabels(token[3]) - (0x400000 + ((line_counter *4) + 4));
             outcome = I_type(token[0], N1->second, token[2], token[1], to_string(addressR/4));
            code.push_back(outcome);
        }
    }
    else if (token[0] == "teqi"){
        N1 = I.find(token[0]);
         outcome = I_type(token[0], N1->second, "01100", token[1], token[2]);
        code.push_back(outcome);
    }
    else if (token[0] == "tnei"){
        N1 = I.find(token[0]);
         outcome = I_type(token[0], N1->second, "01110", token[1], token[2]);
        code.push_back(outcome);
    }

    else if (token[0] == "tgei"){
        N1 = I.find(token[0]);
         outcome = I_type(token[0], N1->second, "01000", token[1], token[2]);
        code.push_back(outcome);
    }
    else if (token[0] == "tgeiu"){
        N1 = I.find(token[0]);
         outcome = I_type(token[0], N1->second, "01001", token[1], token[2]);
        code.push_back(outcome);
    }

    else if (token[0] == "tlti"){
        N1 = I.find(token[0]);
         outcome = I_type(token[0], N1->second, "01010", token[1], token[2]);
        code.push_back(outcome);
    }
    else if (token[0] == "tltiu"){
        N1 = I.find(token[0]);
         outcome = I_type(token[0], N1->second, "01011", token[1], token[2]);
        code.push_back(outcome);
    }
    else if (token[0] == "lb"){
        N1 = I.find(token[0]);

        size_t OB = token[2].find('(');
        size_t CB = token[2].find(')');
        string rs = token[2].substr(OB + 1, CB - OB - 1);
        string immediates = token[2].substr(0, OB);

         outcome = I_type(token[0], N1->second, token[1], rs, immediates);
        code.push_back(outcome);
    }
    else if (token[0] == "lbu"){
        N1 = I.find(token[0]);

        size_t OB = token[2].find('(');
        size_t CB = token[2].find(')');
        string rs = token[2].substr(OB + 1, CB - OB - 1);
        string immediates = token[2].substr(0, OB);

         outcome = I_type(token[0], N1->second, token[1], rs, immediates);
        code.push_back(outcome);
    }
    else if (token[0] == "lh"){
        N1 = I.find(token[0]);

        size_t OB = token[2].find('(');
        size_t CB = token[2].find(')');
        string rs = token[2].substr(OB + 1, CB - OB - 1);
        string immediates = token[2].substr(0, OB);

         outcome = I_type(token[0], N1->second, token[1], rs, immediates);
        code.push_back(outcome);
    }
    else if (token[0] == "lhu"){
        N1 = I.find(token[0]);

        size_t OB = token[2].find('(');
        size_t CB = token[2].find(')');
        string rs = token[2].substr(OB + 1, CB - OB - 1);
        string immediates = token[2].substr(0, OB);

         outcome = I_type(token[0], N1->second, token[1], rs, immediates);
        code.push_back(outcome);
    }
    else if (token[0] == "lw"){
        N1 = I.find(token[0]);

        size_t OB = token[2].find('(');
        size_t CB = token[2].find(')');
        string rs = token[2].substr(OB + 1, CB - OB - 1);
        string immediates = token[2].substr(0, OB);

         outcome = I_type(token[0], N1->second, token[1], rs, immediates);
        code.push_back(outcome);
    }
    else if (token[0] == "lwl"){
        N1 = I.find(token[0]);

        size_t OB = token[2].find('(');
        size_t CB = token[2].find(')');
        string rs = token[2].substr(OB + 1, CB - OB - 1);
        string immediates = token[2].substr(0, OB);

         outcome = I_type(token[0], N1->second, token[1], rs, immediates);
        code.push_back(outcome);
    }
    else if (token[0] == "lwr"){
        N1 = I.find(token[0]);

        size_t OB = token[2].find('(');
        size_t CB = token[2].find(')');
        string rs = token[2].substr(OB + 1, CB - OB - 1);
        string immediates = token[2].substr(0, OB);

         outcome = I_type(token[0], N1->second, token[1], rs, immediates);
        code.push_back(outcome);
    }
    else if (token[0] == "ll"){
        N1 = I.find(token[0]);

        size_t OB = token[2].find('(');
        size_t CB = token[2].find(')');
        string rs = token[2].substr(OB + 1, CB - OB - 1);
        string immediates = token[2].substr(0, OB);

         outcome = I_type(token[0], N1->second, token[1], rs, immediates);
        code.push_back(outcome);
    }
    else if (token[0] == "sb"){
        N1 = I.find(token[0]);

        size_t OB = token[2].find('(');
        size_t CB = token[2].find(')');
        string rs = token[2].substr(OB + 1, CB - OB - 1);
        string immediates = token[2].substr(0, OB);

         outcome = I_type(token[0], N1->second, token[1], rs, immediates);
        code.push_back(outcome);
    }
    else if (token[0] == "sh"){
        N1 = I.find(token[0]);

        size_t OB = token[2].find('(');
        size_t CB = token[2].find(')');
        string rs = token[2].substr(OB + 1, CB - OB - 1);
        string immediates = token[2].substr(0, OB);

         outcome = I_type(token[0], N1->second, token[1], rs, immediates);
        code.push_back(outcome);
    }
    else if (token[0] == "sw"){
        N1 = I.find(token[0]);

        size_t OB = token[2].find('(');
        size_t CB = token[2].find(')');
        string rs = token[2].substr(OB + 1, CB - OB - 1);
        string immediates = token[2].substr(0, OB);

         outcome = I_type(token[0], N1->second, token[1], rs, immediates);
        code.push_back(outcome);
    }
    else if (token[0] == "swl"){
        N1 = I.find(token[0]);

        size_t OB = token[2].find('(');
        size_t CB = token[2].find(')');
        string rs = token[2].substr(OB + 1, CB - OB - 1);
        string immediates = token[2].substr(0, OB);

         outcome = I_type(token[0], N1->second, token[1], rs, immediates);
        code.push_back(outcome);
    }
    else if (token[0] == "swr"){
        N1 = I.find(token[0]);

        size_t OB = token[2].find('(');
        size_t CB = token[2].find(')');
        string rs = token[2].substr(OB + 1, CB - OB - 1);
        string immediates = token[2].substr(0, OB);

         outcome = I_type(token[0], N1->second, token[1], rs, immediates);
        code.push_back(outcome);
    }
    else if (token[0] == "sc"){
        N1 = I.find(token[0]);

        size_t OB = token[2].find('(');
        size_t CB = token[2].find(')');
        string rs = token[2].substr(OB + 1, CB - OB - 1);
        string immediates = token[2].substr(0, OB);

         outcome = I_type(token[0], N1->second, token[1], rs, immediates);
        code.push_back(outcome);
    }

    // J type instruction sets

    else if (token[0] == "j"){
        N1 = J.find(token[0]);
        if(findLabels(token[1]) == -1){
             outcome = J_type(N1->second,token[1]);
            code.push_back(outcome);
        }
        else{
             outcome = J_type(N1->second,to_string(findLabels(token[1])/4));
            code.push_back(outcome);
        }
    }
    else if (token[0] == "jal"){
        N1 = J.find(token[0]);
        if(findLabels(token[1]) == -1){
             outcome = J_type(N1->second,token[1]);
            code.push_back(outcome);
        }
        else{
             outcome = J_type(N1->second,to_string(findLabels(token[1])>>2));
            code.push_back(outcome);
        }
    }
}

void view(vector <vector<string>> token, vector<string> code, string f_out){
    for (int i = 0; i < token.size(); i++){
        for (int j = 0; j < token[i].size(); j++)
        {    
            cout << token[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i<token.size(); i++){
        machineCode(token[i],code, i);
    }

    ofstream outFile(f_out);

    for (int i = 0; i<code.size(); i++){
        outFile << code[i] << endl;
    }
    outFile.close();
}

void readfile(string f_in, string f_out ){
    vector <vector<string>> token;
    vector<string> code;
    string text, fin;
    int mode;
    int counter1 = 0;
    int counter2 = 0;

    ifstream inFile(f_in);

    while (getline (inFile, text)) {
        fin = final_data(text);

        if (fin.find(".data") != string::npos) {
            mode = 0;
            continue;
        }
        if (fin.find(".text") != string::npos) {
            mode = 1;
            continue;
        }

        if (mode == 1){
            fin = addresing(fin, counter1);
            parseLine(fin, token, counter1);
        }

        if (mode == 0){
            if (fin != ".data"){
                int found = fin.find(":");
                while (true){
                    if (found == -1)break;
                    else{
                        string NQ = fin.substr(0, found);
                        string CT = fin.substr(found+1);
                        for(const auto & data_type: data_types){
                            if (CT.find(data_type)){
                                Labelling address(NQ, 0x10000000 + (counter2) * 4, data_type, CT);
                                labels.push_back(address);
                            }
                        }
                    }
                }
                counter2 += 1;
            }
        }
    }
    view(token,code,f_out);
    inFile.close();
}

int main(int argc, char* argv[]){
    if(argc != 4){
        std::cerr << "Error, wrong number of inputs" << endl;
        exit(1);
    }
    string filename(argv[1]);
    string inputs(argv[2]);
    string output(argv[3]);
    readfile(filename, output);
    return 0;
}