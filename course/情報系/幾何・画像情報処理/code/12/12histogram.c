#include "libBMP2.h"

int main( void ){
    int border = 120; // この値をいじる（0〜255）
    
    BMPread( 1 ); // 1番のサンプル画像
    int i, x, y, ave, max;
    int bar = 128;
    int count[256];
    char value[10];
    for( i=0; i<256; i++ ){ // 初期化
        count[ i ]  = 0;
    }
    for( x=0; x<BMP_width; x++ ){
        for( y=0; y<BMP_height; y++ ){
            ave = // 平均の値
                BMPpointGetR(x,y) +
                BMPpointGetG(x,y) +
                BMPpointGetB(x,y);
            ave /= 3;
            count[ ave ]++; // 数える
            if( ave < border ){  // 2値化
                BMPpoint( x, y, 0, 0, 0 );
            } else {
                BMPpoint( x, y, 255, 255, 255 );
            }
        }
    }
    max = 0;
    for( i=0; i<256; i++ ){ // 最大値を取り出す
        if( max<count[ i ] ){
            max = count[ i ];
        }
    }
    for( x=0; x<256; x++ ){ // ヒストグラムの描画
        for( y=0; y<bar; y++ ){
            if( bar*count[x]/max< y ){
                BMPpoint( x, bar-y, 0, 0, 0 );
            } else {
                BMPpoint( x, bar-y, 255, 0, 0 );
            }
        }
    }
    for( y=0; y<bar; y++ ){ // 境界値の図示
        BMPpoint( border, y, 255, 255, 255 );
    }
    sprintf( value, "%3d", border );
    BMPstr( border+5, bar+10, 255, 0, 0, value );
    
    BMPsave();
    return 0;
}
