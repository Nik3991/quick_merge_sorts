#include <iostream>
#include <string>

#include <countingSort.h>
#include <fileGenerator.h>
#include <fileMerge.h>
#include <FileWrapper.h>
#include <merge1.h>
#include <merge2.h>
#include <quickSort.h>
#include <Timer.h>

using namespace std;

int main()
{
    int data_size = 100000;

    // - - - - - - - - MERGE SORT FILES - - - - - - -
    {
        Timer timer(Timer::micros);
        sortFileData("E:/billion_2byte_elements.txt",
                     "E:/sorted_1.txt",
                     "E:/sorted_2.txt",
                     data_size,
                     data_size / 10);

    }
    // - - - - - - - - - - - - - - - - - - - - - - - -

    auto checkSort = [](unsigned short* _data, int _data_size, const char* _name)
    {
        bool sorted = true;
        // check that data sorted
        for (int ix = 1; ix < _data_size; ++ix)
        {
            if (_data[ix] < _data[ix - 1])
            {
                cout << _data[ix] << " " << _data[ix - 1]  << " " << ix << endl;
                sorted = false;
                break;
            }
        }
        if (sorted)
        {
            cout << _name << " DONE !!!" << endl;
        } else
        {
            cout << _name << " NOT DONE !!!" << endl;
        }
    };

    // - - - - - - - - QUICK SORT - - - - - - - - - -
    {
        FileWrapper dataFile;
        dataFile.openFile("E:/billion_2byte_elements.txt", READ);
        unsigned short* _data_ptr = dataFile.readFile(data_size);
        dataFile.closeFile();

        if (_data_ptr)
        {
            cout << endl;
            Timer* timer_ptr = new Timer(Timer::micros);
            quickSort(_data_ptr, data_size);
            delete timer_ptr;
            checkSort(_data_ptr, data_size, "QUICK SORT");
        } else
        {
            cout << " data not readed !!! " << endl;
        }
        delete[] _data_ptr;
    }

    // - - - - - - - - MERGE SORT - - - - - - - - - -
    {
        FileWrapper dataFile;
        dataFile.openFile("E:/billion_2byte_elements.txt", READ);
        unsigned short* _data_ptr = dataFile.readFile(data_size);
        dataFile.closeFile();

        unsigned short* result_ptr = new unsigned short[data_size];

        if (_data_ptr)
        {
            cout << endl;
            Timer* timer_ptr = new Timer(Timer::micros);
            mergeSort(_data_ptr, data_size, result_ptr);
            delete timer_ptr;

            checkSort(result_ptr, data_size, "MERGE SORT");
        } else
        {
            cout << " data not readed !!! " << endl;
        }
        delete[] _data_ptr;
        delete[] result_ptr;
    }

    // - - - - - - - - MERGE 2 SORT - - - - - - - - - -
    {
        FileWrapper dataFile;
        dataFile.openFile("E:/billion_2byte_elements.txt", READ);
        unsigned short* _data_ptr = dataFile.readFile(data_size);
        dataFile.closeFile();

        if (_data_ptr)
        {
            cout << endl;
            Timer* timer_ptr = new Timer(Timer::micros);
            mergeSort2(_data_ptr, data_size);
            delete timer_ptr;

            checkSort(_data_ptr, data_size, "MERGE 2 SORT");
        } else
        {
            cout << " data not readed !!! " << endl;
        }
        delete[] _data_ptr;
    }

    //- - - - - - - - - - COUNTING SORT - - - - - - - - - - -
    {
        FileWrapper dataFile;
        dataFile.openFile("E:/billion_2byte_elements.txt", READ);
        unsigned short* _data_ptr = dataFile.readFile(data_size);
        dataFile.closeFile();

        if (_data_ptr)
        {
            cout << endl;
            Timer* timer_ptr = new Timer(Timer::micros);
            countingSort(_data_ptr, data_size, 0xFFFF);
            delete timer_ptr;
            checkSort(_data_ptr, data_size, "COUNTING SORT");
        } else
        {
            cout << " data not readed !!! " << endl;
        }
        delete[] _data_ptr;
    }

    //- - - - - - - - - - OBJECTS COUNTING SORT - - - - - - - - - - -
    {
        FileWrapper dataFile;
        dataFile.openFile("E:/billion_2byte_elements.txt", READ);
        unsigned short* _data_ptr = dataFile.readFile(data_size);
        dataFile.closeFile();

        if (_data_ptr)
        {
            cout << endl;
            Timer* timer_ptr = new Timer(Timer::micros);
            unsigned short* result_ptr = objectsCountingSort(_data_ptr, data_size, 0xFFFF);
            delete timer_ptr;
            checkSort(result_ptr, data_size, "OBJECT COUNTING SORT");
            delete[] result_ptr;
        } else
        {
            cout << " data not readed !!! " << endl;
        }
        delete[] _data_ptr;
    }
    cout << endl;

    return 0;
}
