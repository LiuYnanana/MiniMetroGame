#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <ostream>
class File
{
public:
	File();
	void ReadTxt(std::string, std::vector<std::string>& );
	~File();
};


