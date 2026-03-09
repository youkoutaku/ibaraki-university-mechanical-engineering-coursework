#include "libBMP2.h"
#include <math.h>

void bresenham( int x0, int y0, int x1, int y1 ){
    int x, y, dx, dy, err;
    dx = x1 - x0;
    dy = y1 - y0;
    y = y0;
    err = 2*dy - dx;
    for( x=x0; x<x1; x++ ){
        BMPpoint( x, y, 255, 0, 0 );
        if( err >= 0 ){
            err = err + 2*(dy-dx);
            y++;
        } else{
            err = err + 2*dy;
        }
    }
}

void DDA_AA( int x0, int y0, int x1, int y1 ){
    int x;
    double y = y0;
    double dy = (double)(y1-y0)/(x1-x0);
    double fraction;
    int value;
    for( x=x0; x<x1; x++ ){
        fraction = y-(int)y;
        value = (int)(255*(1.0-fraction))+BMPpointGetG(x,y);
        if( value > 255 ) value = 255;
        BMPpoint( x, (int)y, 0, value, 0 );
        value = (int)(255*fraction)+BMPpointGetG(x,y+1);
        if( value > 255 ) value = 255;
        BMPpoint( x, (int)y+1, 0, value, 0 );
        y += dy;
    }
}

int main( void ){
    BMPnew();
    int y;
    int offset = 400;
    
    for( y=100; y<=500; y+= 10 ){ // DDA
        bresenham( 40, 100, 440, y );
    }
    
    for( y=100; y<=500; y+= 10 ){ // DDA
        DDA_AA( 40+offset, 100, 440+offset, y );
    }

    BMPsave();
    return 0;
}
