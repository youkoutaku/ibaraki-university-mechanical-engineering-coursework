#include "libBMP2.h"
#include <math.h>

#define ELEM_SWAP(a,b) { register int t=(a);(a)=(b);(b)=t; }

/*
 *  This Quickselect routine is based on the algorithm described in
 *  "Numerical recipes in C", Second Edition,
 *  Cambridge University Press, 1992, Section 8.5, ISBN 0-521-43108-5
 *  This code by Nicolas Devillard - 1998. Public domain.
 */
int quick_select( int arr[], int n ){ // メディアンを見つける関数
    int low, high ;
    int median;
    int middle, ll, hh;
    
    low = 0 ; high = n-1 ; median = (low + high) / 2;
    for (;;) {
        if (high <= low) /* One element only */
            return arr[median] ;
        
        if (high == low + 1) {  /* Two elements only */
            if (arr[low] > arr[high])
                ELEM_SWAP(arr[low], arr[high]) ;
            return arr[median] ;
        }
        
        /* Find median of low, middle and high items; swap into position low */
        middle = (low + high) / 2;
        if (arr[middle] > arr[high])    ELEM_SWAP(arr[middle], arr[high]) ;
        if (arr[low] > arr[high])       ELEM_SWAP(arr[low], arr[high]) ;
        if (arr[middle] > arr[low])     ELEM_SWAP(arr[middle], arr[low]) ;
        
        /* Swap low item (now in position middle) into position (low+1) */
        ELEM_SWAP(arr[middle], arr[low+1]) ;
        
        /* Nibble from each end towards middle, swapping items when stuck */
        ll = low + 1;
        hh = high;
        for (;;) {
            do ll++; while (arr[low] > arr[ll]) ;
            do hh--; while (arr[hh]  > arr[low]) ;
            
            if (hh < ll)
                break;
            
            ELEM_SWAP(arr[ll], arr[hh]) ;
        }
        
        /* Swap middle item (in position low) back into correct position */
        ELEM_SWAP(arr[low], arr[hh]) ;
        
        /* Re-set active partition */
        if (hh <= median)
            low = ll;
        if (hh >= median)
            high = hh - 1;
    }
}

#undef ELEM_SWAP

int main( void ){
    BMPread( 1 );
    int x, y, i, j, ave, data, index;
    int array[9];
    
    for( x=0; x<BMP_width; x++ ){ // グレイスケール化
        for( y=0; y<BMP_height; y++ ){
            ave = // 平均の値
            BMPpointGetR(x,y) +
            BMPpointGetG(x,y) +
            BMPpointGetB(x,y);
            ave /= 3;
            BMPpoint( x, y, ave, ave, ave );
        }
    }
    
    for( i=0; i<1000; i++ ){ // 白と黒のノイズをばらまく
        BMPpoint( rand()%BMP_width, rand()%BMP_height, 255, 255, 255 );
        BMPpoint( rand()%BMP_width, rand()%BMP_height, 0, 0, 0 );
    }
    
    // 平滑化（3x3）
    for( x=0; x<BMP_width/3; x++ ){ // 画像の左1/3
        for( y=0; y<BMP_height; y++ ){
            data = 0;
            for( i=-1; i<2; i++ ){
                for( j=-1; j<2; j++ ){
                    data += BMPpointGetR( x+i, y+j );
                }
            }
            data /= 9;
            BMPpoint( x, y, BMPpointGetR(x,y), data, data );
        }
    }
    
    // メディアンフィルタ
    for( x=2*BMP_width/3; x<BMP_width; x++ ){ // 画像の右1/3
        for( y=0; y<BMP_height; y++ ){
            index = 0;
            for( i=-1; i<2; i++ ){ // 3x3の範囲を配列にコピー
                for( j=-1; j<2; j++ ){
                    array[index] = BMPpointGetR( x+i, y+j );
                    index++;
                }
            }
            data = quick_select( array, 9 ); // メディアンを取得
            BMPpoint( x, y, BMPpointGetR(x,y), data, data );
        }
    }
    
    for( x=0; x<BMP_width; x++ ){ // 計算結果の確定
        for( y=0; y<BMP_height; y++ ){
            data = BMPpointGetG(x,y);
            BMPpoint( x, y, data, data, data );
        }
    }
    
    BMPsave();
}
