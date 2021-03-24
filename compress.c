#include "compress.h"
#include "pnmrdr.h"
#include "uarray2.h"

typedef struct image_rgb { unsigned int red; unsigned int blue; unsigned int green; } image_rgb;
typedef struct image_ypp { unsigned int y; unsigned int pb; unsigned int pr; } image_ypp;
//typedef struct image_dct {?} image_dct;

void compress(FILE* input) {
    Pnmrdr_T r = Pnmrdr_new(input);
    Pnmrdr_mapdata data = Pnmrdr_data(r);
    unsigned int width = data.width;
    unsigned int height = data.height;
    // Check dimensions of image for trimming
    if(data.width%2 != 0){
        //Trim
        width-=1;
    }
    if(data.height%2 != 0){
        //Trim
        height-=1;
    }
    UArray2_T image = UArray2_new(width, height, sizeof(image_rgb));
    for(unsigned int i=0; i < height; i++){
        for(unsigned int j=0; j < width*3; j+=3){
            image_rgb pixel = {(float)Pnmrdr_get(r)/data.denominator,(float)Pnmrdr_get(r)/data.denominator,(float)Pnmrdr_get(r)/data.denominator};
            image_rgb* tmp = UArray2_at(i,j/3,image);
            *tmp = pixel;
        }
    }
    
}

void decompress(FILE* input) {
    (void)input;
}