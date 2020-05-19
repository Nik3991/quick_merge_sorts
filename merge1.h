#ifndef MERGE1_H
#define MERGE1_H

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template <typename T>
void merge(T* _data_ptr1, int _size1, T *_data_ptr2, int _size2, T *_result_ptr)
{
    int index1 = 0, index2 = 0, resultIndex = 0;

    while (index1 < _size1 && index2 < _size2)
    {
        if (_data_ptr1[index1] <= _data_ptr2[index2])
        {
            _result_ptr[resultIndex++] = _data_ptr1[index1++];
        } else if (_data_ptr2[index2] <= _data_ptr1[index1])
        {
            _result_ptr[resultIndex++] = _data_ptr2[index2++];
        }
    }

    while (index1 < _size1)
    {
        _result_ptr[resultIndex++] = _data_ptr1[index1++];
    }

    while (index2 < _size2)
    {
        _result_ptr[resultIndex++] = _data_ptr2[index2++];
    }
}

template <typename T>
T* mergeSort(T* _data_ptr, int _size, T* _result_ptr)
{
    if (_size < 2)
    {
        return _data_ptr;
    }
    T* local_ptr = new T[_size];
    int halfSize = _size / 2;
    merge( mergeSort(_data_ptr, halfSize, local_ptr), halfSize,
           mergeSort(_data_ptr + halfSize, _size - halfSize, local_ptr + halfSize), _size - halfSize,
           _result_ptr);
    delete[] local_ptr;
    return _result_ptr;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#endif // MERGE1_H
