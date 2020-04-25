#include "File.h"

File::File() {
    myLoger = MyLogger::GetInstance();
}

void File::ReadTxt(std::string file, std::vector<std::string>& file_data) {
    std::ifstream infile;
    try {
        infile.open(file.data());   //将文件流对象与文件连接起来 
        if (infile.is_open() == false) throw "open file failed";

        std::string s;
        while (getline(infile, s))
        {
            file_data.push_back(s);
        }
        infile.close();
    }
    catch (const char* str_err) {
        int days = 1;
        LOG4CPLUS_ERROR(myLoger->rootLog, str_err << "file name" << file.c_str());
    }
    
}

File::~File(){}
