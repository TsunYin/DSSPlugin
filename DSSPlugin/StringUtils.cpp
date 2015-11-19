#pragma once
#include "stdafx.h"
#include "StringUtils.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <regex>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}
std::vector<std::string> split_and_trim(std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);

	std::vector<std::string> trimmed (elems.size());
	for (int i = 0; i < elems.size(); i++) {
		trimmed[i] = trim(elems[i]);
	}
	return trimmed;
}


std::string lower_case(std::string s) {
	std::string data(s);
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}

std::string trim(std::string target) {
	std::string s(target);
	size_t p = s.find_first_not_of(" \t");
	s.erase(0, p);

	p = s.find_last_not_of(" \t");
	if (std::string::npos != p)
		s.erase(p + 1);

	return s;
}