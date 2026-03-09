#include "libBMP2.h"

// 参考 https://codezine.jp/article/detail/98
// (c) T. Ishidate
int thinImage( int x, int y, int start ){
    int p[8];
    int product, sum;
    int count = 0;
    
    p[0] = BMPpointGetR( x-1, y-1 );
    p[1] = BMPpointGetR( x-1, y   );
    p[2] = BMPpointGetR( x-1, y+1 );
    p[3] = BMPpointGetR( x  , y+1 );
    p[4] = BMPpointGetR( x+1, y+1 );
    p[5] = BMPpointGetR( x+1, y   );
    p[6] = BMPpointGetR( x+1, y-1 );
    p[7] = BMPpointGetR( x  , y-1 );
    
    int k;
    for( k=start; k<start+3; k++ ){
        product = 0;
        if( (p[k%8]==0) && (p[(k+1)%8]==0) && (p[(k+2)%8]==0) ) product = 1;
        sum = 0;
        if( (p[(k+4)%8]==255) && (p[(k+5)%8]==255) && (p[(k+6)%8]==255) ) sum = 1;
        if( product==1 && sum==1 ){
            BMPpoint( x, y, BMPpointGetR( x, y ), 0, BMPpointGetB( x, y ) ); // その画素を除去
            count++;
        }
    }
    return( count );
}

void copyImage( void ){
    int x, y, g;
    for( x=0; x<BMP_width; x++ ){ // Gの値をRにコピー
        for( y=0; y<BMP_height; y++ ){
            g = BMPpointGetG(x,y);
            BMPpoint( x, y, g, g, BMPpointGetB( x, y ) );
        }
    }
}

int main( void ){
    BMPread( 1 );
    int x, y, ave;
    int changeCount, loopCount = 0;
    char value[32];
    
    for( x=0; x<BMP_width; x++ ){ // RGBの平均で2値化
        for( y=0; y<BMP_height; y++ ){
            ave = // 平均の値
            BMPpointGetR(x,y) +
            BMPpointGetG(x,y) +
            BMPpointGetB(x,y);
            ave /= 3;
            if( ave >127 ){
                BMPpoint( x, y, 255, 255,255 );
            } else {
                BMPpoint( x, y, 0, 0, 0 );
            }
        }
    }
    printf("binarization done\n");
    
    // 細線化
    do{
        loopCount++;
        changeCount = 0;

        copyImage();
        for( y=1; y<BMP_height-1; y++ ){ // 左上から
            for( x=1; x<BMP_height-1; x++ ){
                if( BMPpointGetR( x, y ) == 255 ) {
                    changeCount += thinImage( x, y, 0 );
                }
            }
        }
        
        copyImage();
        for( y=BMP_height-2; y>0; y-- ){ // 右下から
            for( x=BMP_width-2; x>0; x-- ){
                if( BMPpointGetR( x, y ) == 255 ) {
                    changeCount += thinImage( x, y, 4 );
                }
            }
        }
        
        copyImage();
        for( y=1; y<BMP_height-1; y++ ){ // 右上から
            for( x=BMP_width-2; x>0; x-- ){
                if( BMPpointGetR( x, y ) == 255 ) {
                    changeCount += thinImage( x, y, 6 );
                }
            }
        }
        
        copyImage();
        for( y=BMP_height-2; y>0; y-- ){ // 左下から
            for( x=1; x<BMP_width-1; x++ ){
                if( BMPpointGetR( x, y ) == 255 ) {
                    changeCount += thinImage( x, y, 2 );
                }
            }
        }
         
       printf("%3d: removed %d pixels\n", loopCount, changeCount );
            
    } while( changeCount > 0 );

    sprintf( value, "loop count: %5d", loopCount );
    BMPstr( 10, 10, 255, 255, 255, value );
    
    BMPsave();
}
