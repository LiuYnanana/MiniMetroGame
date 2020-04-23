#include "File.h"

File::File() {}

void File::ReadTxt(std::string file, std::vector<std::string>& file_data) {
    std::ifstream infile;
    infile.open(file.data());   //将文件流对象与文件连接起来 
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

    std::string s;
    while (getline(infile, s))
    {
        file_data.push_back(s);
    }
    infile.close();
}

File::~File(){}
