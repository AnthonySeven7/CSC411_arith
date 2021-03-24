#include "array.h"
#include "mem.h"
#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED
#define T UArray2_T
typedef struct T *T;

struct UArray2_T{
    int width, height, size;
    Array_T _array;
};

T UArray2_new(int x, int y, int size);
void* UArray2_at(int x, int y, T pointer); // Return a specific element based on its x and y position in the array (pointer is 2d array)
void UArray2_free(T uarray2);
int UArray2_width(T uarray2);
int UArray2_height(T uarray2);
int UArray2_size(T uarray2);
void UArray2_map_row_major(T uarray2, void* apply(const void* element, int x, int y, void* cl), void* cl); // Iterate through each element in the earray
    // For each element, call the 'apply' function
    // If out of bounds return error message
    // *Column indices vary more rapidly than row indicies*
void UArray2_map_col_major(T uarray2, void* apply(const void* element, int x, int y, void* cl), void* cl); // Iterate through each element in the array
    // For each element, call the 'apply' function
    // If out of bounds return error message
    // *Row indicies vary more rapidly than column indicies*
#undef T
#endif