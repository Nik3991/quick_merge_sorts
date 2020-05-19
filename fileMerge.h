#ifndef FILEMERGE_H
#define FILEMERGE_H

#include <FileWrapper.h>
#include <quickSort.h>

using namespace std;

template <typename File, typename Data>
void fileMerge(File& _file_1, int _size1, File& _file_2, int _size2, File& _result_file)
{
    int index1 = 0, index2 = 0;

    Data* readedData1_ptr = _file_1.readFile(1);
    Data* readedData2_ptr = _file_2.readFile(1);
    Data prevWrited = 0;

    auto write = [&](Data*& _d_ptr, File& _file, int& _index, int _size)
    {
        _result_file.writeFile(_d_ptr, 1);
        prevWrited = _d_ptr[0];

        delete _d_ptr;
        _d_ptr = nullptr;
        _index++;
        if (_index < _size)
        {
            _d_ptr = _file.readFile(1);
        }
    };

    while (index1 < _size1 && index2 < _size2)
    {
        if (*readedData1_ptr <= *readedData2_ptr)
        {
            write(readedData1_ptr, _file_1, index1, _size1);
        } else if (*readedData2_ptr <= *readedData1_ptr)
        {
            write(readedData2_ptr, _file_2, index2, _size2);
        }
    }

    while (index1 < _size1)
    {
        write(readedData1_ptr, _file_1, index1, _size1);
    }

    while (index2 < _size2)
    {
        write(readedData2_ptr, _file_2, index2, _size2);
    }

    delete readedData1_ptr;
    delete readedData2_ptr;
}

void sortFileData(const char* _data_file_name,
                  const char* _buffer1,
                  const char* _buffer2,
                  const int _data_size,
                  const int _buffer_size)
{
    FileWrapper dataFile;
    dataFile.openFile(_data_file_name, READ);

    int max_reached_level = 0;

    auto mergeFiles = [](const char* _f1_name_ptr, int _f1_size,
                         const char* _f2_name_ptr, int _f2_size)
    {
        static bool flag = false;
        const char* name_ptr = flag ? "tmp1" : "tmp2";
        flag = !flag;

        FileWrapper sorted_1;
        sorted_1.openFile(_f1_name_ptr, READ);

        FileWrapper sorted_2;
        sorted_2.openFile(_f2_name_ptr, READ);

        // - - - - - merge files - - - - - - -

        FileWrapper resultFile;
        resultFile.openFile(name_ptr, WRITE);
        fileMerge<FileWrapper, unsigned short>(sorted_1, _f1_size, sorted_2, _f2_size, resultFile);
        resultFile.closeFile();
        // - - - - - - - - - - - - - - - - - - - - - -

        return name_ptr;
    };

    auto sortData = [](const char* _file_name, int _portion, FileWrapper& _data)
    {
        unsigned short* data_portion_ptr = _data.readFile(_portion);
        quickSort(data_portion_ptr, _portion);

        FileWrapper sorted_data_file;
        sorted_data_file.openFile(_file_name, WRITE);
        sorted_data_file.writeFile(data_portion_ptr, _portion);
        sorted_data_file.closeFile();
        delete[] data_portion_ptr;
    };

    for (int ix = 0; ix < _data_size; ix += _buffer_size * 2)
    {
        sortData(_buffer1, _buffer_size, dataFile);
        sortData(_buffer2, _buffer_size, dataFile);

        const char* tmp_name = mergeFiles(_buffer1, _buffer_size, _buffer2, _buffer_size);

        int level = 2;
        bool file_exist = ifstream(to_string(level).c_str()).good();
        while (file_exist)
        {
            tmp_name = mergeFiles(to_string(level).c_str(),
                       level * _buffer_size,
                       tmp_name,
                       level * _buffer_size);
            std::remove(to_string(level).c_str());
            level *= 2;
            file_exist = ifstream(to_string(level).c_str()).good();
        }
        std::rename(tmp_name, to_string(level).c_str());

        if (level > max_reached_level)
        {
            max_reached_level = level;
        }
    }

    // merge tail
    int prevLevel = 1;
    int level = 1;
    const char* file_name = nullptr;
    while ((level *= 2) < max_reached_level)
    {
        if(ifstream(to_string(level).c_str()).good())
        {
            if (file_name)
            {
                file_name = mergeFiles(to_string(level).c_str(),
                            level * _buffer_size,
                            file_name,
                            prevLevel * _buffer_size);
                prevLevel = prevLevel + level;
            } else
            {
                prevLevel = level;
                file_name = to_string(level).c_str();
            }
        }
    }

    file_name = mergeFiles(to_string(max_reached_level).c_str(),
                max_reached_level * _buffer_size,
                file_name,
                prevLevel * _buffer_size);

    // rename result file
    std::remove("RESULT");
    std::rename(file_name, "RESULT");

    cout << "max_reached_level = " << max_reached_level << endl;
    do // clear tmp files
    {
        std::remove(to_string(max_reached_level).c_str());
    } while ((max_reached_level /= 2) > 1);

    std::remove("tmp1");
    std::remove("tmp2");

    FileWrapper resultFile;
    resultFile.openFile("RESULT", READ);
    unsigned short* _data = resultFile.readFile(_data_size);

    // - - - - - - - - - - - - - - - - - - - - - - - - - -
    // check that file sorted
    for (int ix = 1; ix < _data_size; ++ix)
    {
        if (_data[ix] < _data[ix - 1])
        {
            cout << "NOT SORTED !!!" << endl;
            break;
        }
    }
    // - - - - - - - - - - - - - - - - - - - - - - - - - -

    cout << "FILES SORT DONE !!!" << endl;
}


#endif // FILEMERGE_H
