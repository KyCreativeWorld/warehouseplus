#include "insertion_sort_warehouse.h"

// FIXME: Needs to take ikeaData wh and the field it is sorting by.
//        Then, it needs to do the same operations to all fields.
void insertionSort(int wh[], int n = -1) {
    if (n == -1) n = sizeof(wh);
    
    for (int i = 1; i < n; ++i) {
        int key = wh[i];
        int j = i - 1;

        while (j >= 0 && wh[j] > key) {
            wh[j + 1] = wh[j];
            j = j - 1;
        }

        wh[j + 1] = key;
    }
}

void insertionSort(std::string wh[], int n = -1) {
    if (n == -1) n = sizeof(wh);
    
    for (int i = 1; i < n; ++i) {
        std::string key = wh[i];
        int j = i - 1;

        while (j >= 0 && wh[j] > key) {
            wh[j + 1] = wh[j];
            j = j - 1;
        }

        wh[j + 1] = key;
    }
}

void insertionSort(double wh[], int n = -1) {
    if (n == -1) n = sizeof(wh);
    
    for (int i = 1; i < n; ++i) {
        double key = wh[i];
        int j = i - 1;

        while (j >= 0 && wh[j] > key) {
            wh[j + 1] = wh[j];
            j = j - 1;
        }

        wh[j + 1] = key;
    }
}