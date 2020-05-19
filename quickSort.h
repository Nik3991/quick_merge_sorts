#ifndef QUICKSORT_H
#define QUICKSORT_H

template <typename T>
void quickSort(T *_data_ptr, int _size)
{
    int i = -1;
    int j = 0;

    if (_size < 2)
    {
        return;
    }

    while (j != _size)
    {
        if (_data_ptr[j] <= _data_ptr[_size - 1])
        {
            swap(_data_ptr[++i], _data_ptr[j]);
        }
        ++j;
    }

    quickSort(_data_ptr, i);
    quickSort(_data_ptr + i, _size - i);
}

#endif // QUICKSORT_H
