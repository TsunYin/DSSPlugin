#pragma once
#include <string>
#include <vector>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

std::vector<std::string> split(const std::string &s, char delim);

std::vector<std::string> split_and_trim(std::string &s, char delim);

std::string lower_case(std::string s);

std::string trim(std::string s);