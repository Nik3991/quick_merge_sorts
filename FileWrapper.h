#ifndef FILEWRAPPER_H
#define FILEWRAPPER_H

#include <fstream>
#include <climits>
#include <iostream>
using namespace std;

enum type {READ, WRITE};

class FileWrapper
{
public:
    ~FileWrapper()
    {
        closeFile();
    }

    unsigned short* readFile(int _count_of_elements)
    {
        unsigned short* result_ptr = nullptr;
        if (m_InFile.is_open())
        {
            int count_of_bytes = _count_of_elements * 2;
            char* read_data = new char[count_of_bytes];
            m_InFile.read(read_data, count_of_bytes);
            result_ptr = reinterpret_cast<unsigned short*>(read_data);
        }
        return result_ptr;
    }

    void writeFile(const unsigned short* _data_ptr, int _count_of_elements)
    {
        int count_of_bytes = _count_of_elements * 2;
        const char* _data_to_write = reinterpret_cast<const char*>(_data_ptr);
        m_OutFile.write(_data_to_write, count_of_bytes);
    }

    void openFile(const char * _path_ptr, type _type)
    {
        if (_type == READ)
        {
            m_InFile.open(_path_ptr, ios::binary);
        } else if (_type == WRITE)
        {
            m_OutFile.open(_path_ptr, ios::binary);
        }
    }

    void closeFile()
    {
        if (m_OutFile)
        {
            m_OutFile.flush();
            m_OutFile.close();
        }
        if (m_InFile)
        {
            m_InFile.close();
        }
    }

private:
    ofstream m_OutFile;
    ifstream m_InFile;
};
#endif // FILEWRAPPER_H
