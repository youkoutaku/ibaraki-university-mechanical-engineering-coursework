#include "libBMP2.h"

int main( void ){
    BMPread( 1 );
    int x, y;
    int data;
    for( x=0; x<BMP_width; x++ ){
        for( y=0; y<BMP_height; y++ ){
            data = BMPpointGetG(x,y);
            BMPpoint( x, y, data, data, data );
        }
    }
    BMPsave();
}
