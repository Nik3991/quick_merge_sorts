#ifndef MERGE2_H
#define MERGE2_H

template <typename T>
void merge2(T* _data1_ptr, int _size1, T* _data2_ptr, int _size2)
{
   int index1 = 0, index2 = 0, resultIndex = 0;

   T* result_ptr = new T[_size1 + _size2];

   while (index1 < _size1 && index2 < _size2)
   {
       if (_data1_ptr[index1] <= _data2_ptr[index2])
       {
           result_ptr[resultIndex++] = _data1_ptr[index1++];
       } else if (_data2_ptr[index2] <= _data1_ptr[index1])
       {
           result_ptr[resultIndex++] = _data2_ptr[index2++];
       }
   }

   while (index1 < _size1)
   {
       result_ptr[resultIndex++] = _data1_ptr[index1++];
   }

   while (index2 < _size2)
   {
       result_ptr[resultIndex++] = _data2_ptr[index2++];
   }

   for (int ix = 0; ix < _size1 + _size2; ++ix)
   {
        _data1_ptr[ix] = result_ptr[ix];
   }

   delete[] result_ptr;
}

template <typename T>
T* mergeSort2(T* _data_ptr, int _size)
{
    if (_size < 2)
    {
        return _data_ptr;
    }
    int half = _size / 2;
    merge2( mergeSort2(_data_ptr, half), half,
            mergeSort2(_data_ptr + half, _size - half), _size - half);

    return _data_ptr;
}

#endif // MERGE2_H
