#ifndef FILEGENERATOR_H
#define FILEGENERATOR_H

#include <fstream>
#include <iostream>

using namespace std;

void generateFile(const char * _path_ptr, int _count_of_numbers)
{
    int count_of_bytes = _count_of_numbers * 2;
    ofstream file;
    file.open(_path_ptr);
    if (file)
    {
        cout << "generation started!" << endl;
        int count_of_done = 0;
        int percents = 0;
        char* _data_ptr = new char[count_of_bytes];
        for (int ix = 0; ix < count_of_bytes; ++ix)
        {
            _data_ptr[ix] = static_cast<char>(rand() % 0xff);
            ++count_of_done;
            if (count_of_done == count_of_bytes / 100)
            {
                cout << ++percents << "% of generating done" << endl;
                count_of_done = 0;
            }
        } cout << endl;

        count_of_done = 0;
        percents = 0;

        //int bytes_writed = 0;
        for (int ix = 0; ix < count_of_bytes; ++ix)
        {
            file << _data_ptr[ix];
            //++bytes_writed;
            //if (bytes_writed == 2)
            //{
            //    file << "\n";
            //    bytes_writed = 0;
            //}
            ++count_of_done;
            if (count_of_done == count_of_bytes / 100)
            {
                cout << ++percents << "% of writing done" << endl;
                count_of_done = 0;
            }
        }

        file.flush();
        file.close();

        cout << "DONE!" << endl;
    } else
    {
        cout << "can`t open file!" << endl;
    }
}

#endif // FILEGENERATOR_H
