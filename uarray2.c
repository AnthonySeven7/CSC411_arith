#include "uarray2.h"
#include "assert.h"
#include <stdlib.h>
#define T UArray2_T

T UArray2_new(int x, int y, int size){
    T array2 = malloc(sizeof(T));
    array2->width = x;
    array2->height = y;
    array2->size = size;
    array2->_array = Array_new(x*y, size);
    return array2;
}

void* UArray2_at(int x, int y, UArray2_T pointer){ // Return a specific element based on its x and y position in the array (pointer is 2d array)
    assert(pointer);
    assert(x >= 0 && x < pointer->width);
    assert(y >= 0 && y < pointer->height);
    return Array_get(pointer->_array,x*pointer->width+y);
}

void UArray2_free(UArray2_T uarray2){
    Array_free(&((*uarray2)._array));
    free(uarray2);
    return;
}

int UArray2_width(UArray2_T uarray2){
    return uarray2->width;
}

int UArray2_height(UArray2_T uarray2){
    return uarray2->height;
}

int UArray2_size(UArray2_T uarray2){
    return uarray2->size;
}

void UArray2_map_row_major(UArray2_T uarray2, void* apply(const void* element, int x, int y, void* cl), void* cl){ // Iterate through each element in the earray
    // For each element, call the 'apply' function
    // If out of bounds return error message
    // *Column indices vary more rapidly than row indicies*
    for(int i = 0; i < uarray2->width; i++) {
        for(int j = 0; j < uarray2->height; j++) {
            apply(UArray2_at(i,j,uarray2), i, j, cl);
        }
    }

}

void UArray2_map_col_major(UArray2_T uarray2, void* apply(const void* element, int x, int y, void* cl), void* cl){ // Iterate through each element in the array
    // For each element, call the 'apply' function
    // If out of bounds return error message
    // *Row indicies vary more rapidly than column indicies*
    for(int i = 0; i < uarray2->height; i++) {
        for(int j = 0; j < uarray2->width; j++) {
            apply(UArray2_at(i,j,uarray2), i, j, cl);
        }
    }
}
#undef T