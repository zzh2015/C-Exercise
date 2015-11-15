/*******************************************************************************
FileName: Sort.h
*******************************************************************************/
#ifndef _SORT_H_
#define _SORT_H_

#include <iostream>
#include <math.h>

const int MAX = 10000000;

class Sort {
    public:
        static Sort &Instance () {
            static Sort SingletonSort;
            return SingletonSort;
        }
        Sort(const Sort &) = delete;
        Sort &operator=(const Sort &) = delete;
        //sort algorithms
        //insertion sort--O(n^2)
        template<typename T> void InsertionSort(T *, size_t);
        //merge sort--O(nlgn)--stability
        template<typename T> void MergeSort(T *, size_t, size_t);
    private:
        Sort() = default;
        ~Sort() = default;
        template<typename T> void Merge(T *, size_t, size_t, size_t);
};

template<typename T>
void Sort::Merge(T *arry, size_t p, size_t q, size_t r)
{
    T *leftArray = new T[q-p+2];
    T *rightArray = new T[r-q+1];

    for (auto i=1; i<=(q-p+1); ++i) {
        leftArray[i-1] = arry[p+i-1];
    }
    for (auto i=1; i<=(r-q); ++i) {
        rightArray[i-1] = arry[q+i];
    }
    leftArray[q-p+1] = MAX;
    rightArray[r-q] = MAX;

    for (int i=0,j=0,k=p; k<=r; ++k) {
        if (leftArray[i] <= rightArray[j]) {
            arry[k] = leftArray[i];
            ++i;
        } else {
            arry[k] = rightArray[j];
            ++j;
        }
    }
    delete [] leftArray;
    delete [] rightArray;
}

template<typename T>
void Sort::MergeSort(T *arry, size_t p, size_t r)
{
    if (p < r) {
        auto q = floor((p+r)/2);
        MergeSort(arry, p, q);
        MergeSort(arry, q+1, r);
        Merge(arry, p, q, r);
    }
}

template<typename T>
void Sort::InsertionSort(T *arry, size_t len)
{
    //when use i cmp with len,careful 'unsigned int','!='
    for (auto i=0, j=1; j!=len; ++j) {
        T key = arry[j];
        i = j-1;
        while ((i>=0) && (arry[i]>key)) {
            arry[i+1] = arry[i];
            --i;
        }
        arry[i+1] = key;
    }
}

#endif
