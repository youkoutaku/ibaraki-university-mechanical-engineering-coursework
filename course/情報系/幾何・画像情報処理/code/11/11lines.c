#include "libBMP2.h"
#include <math.h>
void line( int x0, int y0, int x1, int y1 ){
    int i;
    double x, y;
    double dx = x1 - x0;
    double dy = y1 - y0;
    int step = BMP_width*2;
    dx /= step;
    dy /= step;
    x = x0;
    y = y0;
    for( i=0; i<step; i++ ){
        BMPpoint( (int)x, (int)y, 255, 0, 0 );
        x += dx;
        y += dy;
    }
}

void DDA( int x0, int y0, int x1, int y1 ){
    int x;
    double y = y0;
    double dy = (double)(y1-y0)/(x1-x0);
    for( x=x0; x<x1; x++ ){
        BMPpoint( x, (int)y, 0, 255, 0 );
        y += dy;
    }
}

void bresenham( int x0, int y0, int x1, int y1 ){
    int x, y, dx, dy, err;
    dx = x1 - x0;
    dy = y1 - y0;
    y = y0;
    err = 2*dy - dx;
    for( x=x0; x<x1; x++ ){
        BMPpoint( x, y, 0, 0, 255 );
        if( err >= 0 ){
            err = err + 2*(dy-dx);
            y++;
        } else{
            err = err + 2*dy;
        }
    }
}

int main( void ){
    BMPnew();
    int tmp;
    int y;
    int offset = 0;//400
    
    BMPstr( 40, 80, 255, 255, 255, "SIMPLE" );
    for( y=100; y<=500; y+= 10 ){ // simple line
        line( 40, 100, 440, y );
    }
    printf( "simple: %d\n", thisBMP.point_total );
    tmp = thisBMP.point_total;

    BMPstr( 40+offset, 80, 255, 255, 255, "DDA" );
    for( y=100; y<=500; y+= 10 ){ // DDA
        DDA( 40+offset, 100, 440+offset, y );
    }
    printf( "DDA: %d\n", thisBMP.point_total-tmp );
    tmp = thisBMP.point_total;

    BMPstr( 40+offset*2, 80, 255, 255, 255, "BRESEHAM" );
    for( y=100; y<=500; y+= 10 ){ // Bresenham
        bresenham( 40+offset*2, 100, 440+offset*2, y );
    }
    printf( "Bresenham: %d\n", thisBMP.point_total-tmp );

    BMPsave();
    return 0;
}
