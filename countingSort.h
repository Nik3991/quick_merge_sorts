#ifndef COUNTINGSORT_H
#define COUNTINGSORT_H

template <typename T>
void countingSort(T* _data_ptr, int _data_size, int _max_value)
{
    int *array_ptr = new int[_max_value + 1];
    for (int ix = 0; ix <= _max_value; ++ix)
    {
        array_ptr[ix] = 0;
    }

    for (int ix = 0; ix < _data_size; ++ix)
    {
        ++array_ptr[_data_ptr[ix]];
    }

    int index = 0;
    for (T ix = 0; ix <= _max_value; ++ix)
    {
        for (int iy = 0; iy < array_ptr[ix]; ++iy)
        {
            _data_ptr[index++] = ix;
        }
        if (ix == _max_value)
        {
            break;
        }
    }
    delete[] array_ptr;
}

template <typename T>
T* objectsCountingSort(T* _data_ptr, int _data_size, int _max_value)
{
    int *array_ptr = new int[_max_value + 1];
    T* result_ptr = new T[_data_size];

    for (int ix = 0; ix <= _max_value; ++ix)
    {
        array_ptr[ix] = 0;
    }

    for (int ix = 0; ix < _data_size; ++ix)
    {
        ++array_ptr[_data_ptr[ix]];
    }

    for (int ix = 1; ix <= _max_value; ++ix)
    {
        array_ptr[ix] += array_ptr[ix - 1];
    }

    for (int ix = _data_size - 1; ix >= 0; --ix)
    {
        result_ptr[--array_ptr[_data_ptr[ix]]] = _data_ptr[ix];
    }
    delete[] array_ptr;
    return result_ptr;
}

#endif // COUNTINGSORT_H
