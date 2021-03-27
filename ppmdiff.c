#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "pnm.h"
#include "assert.h"
#include "uarray2.h"
#include "a2methods.h"
#include "a2plain.h"

void compare(FILE* image1, FILE* image2);

int main(int argc, char *argv[]) {
    // Ensure parameter number
    if(argc == 3) {
        // Ensure at most one standard input
        if(argv[1] == argv[2] && *argv[1] == '-'){
            fprintf(stderr,"%s: both inputs cannot be from stdinput\n",argv[0]);
            exit(1);
        }
        else{
            FILE *fp1, *fp2;
            if(*argv[1] == '-'){
                fp2 = fopen(argv[2],"r");
                assert(fp2);
                compare(stdin,fp2);
                fclose(fp2);
            }
            if(*argv[2] == '-'){
                fp1 = fopen(argv[1],"r");
                assert(fp1);
                compare(fp1,stdin);
                fclose(fp1);
            }
            else{
                fp1 = fopen(argv[1],"r");
                fp2 = fopen(argv[2],"r");
                assert(fp1);
                assert(fp2);
                compare(fp1, fp2);
                fclose(fp1);
                fclose(fp2);
            }
        }
    }
    else
    {
        fprintf(stderr,"Usage: %s {image1} {image2}\n",argv[0]);
        exit(1);
    }
}

void compare(FILE* input1, FILE* input2) {
    A2Methods_T methods = array2_methods_plain;
    Pnm_ppm image1, image2;
    TRY
        image1 = Pnm_ppmread(input1, methods);
    EXCEPT(Pnm_Badformat)
        fprintf(stderr, "Not valid file format\n");
        exit(1);
    END_TRY;
    TRY
        image2 = Pnm_ppmread(input2, methods);
    EXCEPT(Pnm_Badformat)
        fprintf(stderr, "Not valid file format\n");
        exit(1);
    END_TRY;
    float e; // root mean square difference
    unsigned int w, h;
    float sum = 0;
    Pnm_rgb pixel1, pixel2;
    if((abs((int)image1->height - (int)image2->height) > 1) || (abs((int)image1->width - (int)image2->width) > 1)){
        fprintf(stderr, "Image dimensions are too different\n");
        printf("1.0\n");
        exit(1);
    }
    if(image1->width < image2->width) w = image1->width;
    else w = image2->width;
    if(image1->height < image2->height) h = image1->height;
    else h = image2->height;
    for(unsigned int i=0; i<w; i++){
        for(unsigned int j=0; j<h; j++){
            pixel1 = methods->at(image1->pixels,i,j);
            pixel2 = methods->at(image2->pixels,i,j);
            sum += (pow((((float)pixel1->red)/image1->denominator)-(((float)pixel2->red)/image2->denominator),2)+
                pow((((float)pixel1->green)/image1->denominator)-(((float)pixel2->green)/image2->denominator),2)+
                pow((((float)pixel1->blue)/image1->denominator)-(((float)pixel2->blue)/image2->denominator),2));
        }
    }
    e = sum/(3*w*h);
    e = sqrt(e);
    printf("%.4f\n",e);
}