#include "File.h"

File::File() {}

void File::ReadTxt(std::string file, std::vector<std::string>& file_data) {
    std::ifstream infile;
    infile.open(file.data());   //���ļ����������ļ��������� 
    assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 

    std::string s;
    while (getline(infile, s))
    {
        file_data.push_back(s);
    }
    infile.close();
}

File::~File(){}
