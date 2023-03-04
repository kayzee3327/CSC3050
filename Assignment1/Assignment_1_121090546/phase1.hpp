#ifndef _PHASE_1_HPP
#define _PHASE_1_HPP

#include "labelTable.hpp"
#include <string>

LabelTable phase1(std::string inputFilePath);
void read_labels(std::string inputFilePath, LabelTable & labelTable); // read and store the label

std::string int_to_bin_str(int PC, int bitLength);
std::string int_to_hex_str(unsigned int PC, int bitLength = -1, bool uppercase = false);

#endif