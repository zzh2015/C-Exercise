/*******************************************************************************
FileName: main.cpp
*******************************************************************************/
#include "Sort.h"

using namespace std;

int main(int argc, char *argv[])
{
    int arry_i[8] = {12, 0, 11, 3, 6, 2, 1, 5}; 
    double arry_d[8] = {3.14, 1.68, 0.0, 1.12, 1.44, 2.25, 10.10, 6.28};

    Sort &st = Sort::Instance();
    cout << "get sort ok!" << endl;
    //st.InsertionSort(arry_i, 8);
    st.MergeSort(arry_i, 0, 8);
    cout << "int ok!" << endl;
    st.InsertionSort(arry_d, 8);

    cout << "After Insertion Sort(int):" << endl;
    for (auto i=0u; i!=8; ++i) {
        cout << arry_i[i] << " " << endl;
    }
    cout << endl;
    cout << "After Insertion Sort(double):" << endl;
    for (auto i=0u; i!=8; ++i) {
        cout << arry_d[i] << " " << endl;
    }
    cout << endl;

    return 0;
}

