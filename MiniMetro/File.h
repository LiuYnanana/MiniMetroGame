#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <iostream>
#include "MyLogger.h"
extern bool end;
class File
{
public:
	File();
	void ReadTxt(std::string, std::vector<std::string>& );
	~File();
private:
	MyLogger* myLoger = NULL;
};



