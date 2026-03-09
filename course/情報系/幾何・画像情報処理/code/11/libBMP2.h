//
// libBMP2.h
// C-based basic library for generating/reading BMP images
//
// Created by nobuyuki.umezu.cs@vc.ibaraki.ac.jp
// 2004-2023
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <assert.h>
#include <time.h>

#ifndef LIBBMP_H_INCLUDED
#define LIBBMP_H_INCLUDED

int BMP_font[] = { // 0x20 - 0x7E
  0X00000000, 0X00401084, 0X0000014A, 0X00AFABEA, 0X00FA7CBE, 
  0X01191131, 0X0126C8A2, 0X00000084, 0X00821088, 0X00221082, 
  0X015711D5, 0X00427C84, 0X00220000, 0X00007C00, 0X00400000, 
  0X00111110, 0X00E9D72E, 0X004210C4, 0X01F1322E, 0X00E8B22E, 
  0X008FA54C, 0X00F87C3F, 0X00E8BC2E, 0X0042223F, 0X00E8BA2E, 
  0X00E87A2E, 0X00020080, 0X00220080, 0X00820888, 0X000F83E0, 
  0X00222082, 0X0042222E, 0X00EAD72E, 0X011FC544, 0X00F8BE2F, 
  0X00E8862E, 0X00F8C62F, 0X01F0FC3F, 0X0010BC3F, 0X01E8E42E, 
  0X0118FE31, 0X00E2108E, 0X00E8C218, 0X01149D31, 0X01F08421, 
  0X0118D771, 0X011CD671, 0X00E8C62E, 0X0010BE2F, 0X01ECD62E, 
  0X0114BE2F, 0X00F8383E, 0X0042109F, 0X00E8C631, 0X00454631, 
  0X00AAD6B5, 0X01151151, 0X00421151, 0X01F1391F, 0X00E1084E, 
  0X01041041, 0X00E4210E, 0X00000144, 0X01F00000, 0X00000082, 
  0X0164A4C0, 0X00749C21, 0X00E085C0, 0X00E4B908, 0X0060BD26, 
  0X0042388C, 0X00C8724C, 0X00A51842, 0X00420080, 0X00621004, 
  0X00A32842, 0X00421086, 0X015AB800, 0X00949800, 0X0064A4C0, 
  0X0013A4C0, 0X008724C0, 0X00108DA0, 0X0064104C, 0X00C23880, 
  0X0164A520, 0X00452800, 0X00AAD400, 0X00A22800, 0X00111140, 
  0X00E221C0, 0X00C2088C, 0X00421084, 0X00622086, 0X000022A2,
};

enum color { BMP_B, BMP_G, BMP_R }; // color型
const int BMP_pixel_dim = 3; // R,G,B
const int BMP_width = 1280; // サイズ 16:9
const int BMP_height = 720;
int BMP_init = 0;

const int BMP_samples = 5;

// BMPクラス
struct BMP {
  unsigned char* body; // ピクセルデータ

  // BMPへッダの内容
  int file_size, offset, i_header_size, width, height;
  int comp_mode, body_size, x_reso, y_reso, palette, i_color;
  short int plane, bpp;

  // 統計
  unsigned int point_total;
  unsigned int point_outside;
  
};

struct BMP thisBMP;

void BMPnew( void ){
  thisBMP.body = malloc( BMP_width*BMP_height*BMP_pixel_dim );
  assert( thisBMP.body!=NULL );
  for(int i=0;i<BMP_width;i++){ // 黒で初期化
    for(int j=0;j<BMP_height;j++){
      thisBMP.body[ i*j*BMP_pixel_dim + BMP_B ] = 0;
      thisBMP.body[ i*j*BMP_pixel_dim + BMP_G ] = 0;
      thisBMP.body[ i*j*BMP_pixel_dim + BMP_R ] = 0;
    }
  }
  thisBMP.offset = 54;
  thisBMP.i_header_size=54;
  thisBMP.comp_mode = 0;
  thisBMP.x_reso = thisBMP.y_reso = 0;
  thisBMP.palette = 0;
  thisBMP.i_color = 0;
  thisBMP.plane = 1;
  thisBMP.bpp = 24;
  thisBMP.point_total = 0;
  thisBMP.point_outside = 0;
    
  BMP_init = 1;
}

void BMPpoint( int x, int y, unsigned char r, // 点をセット
		  unsigned char g, unsigned char b ){ 
  if( BMP_init != 1 ){
    printf( "call BMPnew() before BMPpoint().\n" );
    return;
  }
  if( x<0 || y<0 || BMP_width-1<x || BMP_height-1<y ){ // 範囲外
    thisBMP.point_outside++;
    return;
  }
  thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_R ] = r;
  thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_G ] = g;
  thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_B ] = b;
  thisBMP.point_total++;
}

void BMPpointXOR( int x, int y, unsigned char r,
		     unsigned char g, unsigned char b ){ // 点をXORでセット
  if( BMP_init != 1 ){
    printf( "call BMPnew() before BMPpointXOR().\n" );
    return;
  }
  if( x<0 || y<0 || BMP_width-1<x || BMP_height-1<y ){ // 範囲外
    thisBMP.point_outside++;
    return;
  }
  thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_R ] ^= r;
  thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_G ] ^= g;
  thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_B ] ^= b;
  // thisBMP.point_total++;
}

void BMPstr( int x, int y, unsigned char r, unsigned char g,
		unsigned char b, char* str ){ // 文字列描画
  if( BMP_init != 1 ){
    printf( "call BMPnew() before BMPstr().\n" );
    return;
  }
  int strMax = 128;
  int index = 0;
  while( str[index] != 0 && index<strMax ){
    int bits = BMP_font[ str[index]-' ' ];
    for( int i=0; i<5; i++ ){
      for( int j=0; j<5; j++ ){
	if( bits & 0x01 ){ // 左端のピクセル
	  BMPpoint( x+index*6+j, y+i, r, g, b );
	}
	bits = bits >> 1; // 右に1ピクセルずらす
      }
    }
    index++;
  }
}

void BMPsave( void ){

  if( BMP_init != 1 ){
    printf( "call BMPnew() before BMPsave().\n" );
    return;
  }
  int tmp;
  short int tmp2;
  char name[256];
  char stamp[32];
  int baseX = BMP_width-10-6*20;
  int baseY = BMP_height-20;

  time_t now = time(NULL);
  struct tm* local = localtime( &now );
  sprintf( name, "%4d%02d%02d-%02d%02d%02d.bmp",
	   local->tm_year+1900,
	   local->tm_mon+1,
	   local->tm_mday,
	   local->tm_hour,
	   local->tm_min,
	   local->tm_sec );
  
  FILE* fp = fopen( name, "wb"); // ファイルを開く
  assert( fp!=NULL );

  sprintf( stamp, "%4d-%02d-%02d %02d:%02d:%02d",
	   local->tm_year+1900,
	   local->tm_mon+1,
	   local->tm_mday,
	   local->tm_hour,
	   local->tm_min,
	   local->tm_sec );
  int index = 0;
  while( stamp[index] != 0 ){
    int bits = BMP_font[ stamp[index]-' ' ];
    for( int i=0; i<5; i++ ){
      for( int j=0; j<5; j++ ){
	if( bits & 1 ){
	  BMPpointXOR( baseX+index*6+j, baseY+i, 255, 255, 255 );
	}
	bits >>= 1;
      }
    }
    index++;
  }

  fprintf( fp, "BM" ); // 識別子
  tmp = BMP_width*BMP_height*BMP_pixel_dim + 54;
  fwrite(&tmp,4,1,fp); // ファイルサイズ
  tmp = 0;
  fwrite(&tmp,4,1,fp); // 予約
  tmp = 54;
  fwrite(&tmp,4,1,fp); // 画像本体へのオフセット
  tmp = 40;
  fwrite(&tmp,4,1,fp); // へッダの大きさ
  fwrite(&BMP_width,4,1,fp); // Xサイズ
  fwrite(&BMP_height,4,1,fp); // Yサイズ
  tmp2 = 1;
  fwrite(&tmp2,2,1,fp); // プレーン数
  tmp2 = 24;
  fwrite(&tmp2,2,1,fp); // BPP
  tmp = 0;
  fwrite(&tmp,4,1,fp); // モード(無圧縮)
  tmp = BMP_width*BMP_height*BMP_pixel_dim;
  fwrite(&tmp,4,1,fp); // 画像本体の長さ
  tmp = 0;
  fwrite(&tmp,4,1,fp); // pixel per meter, x
  tmp = 0;
  fwrite(&tmp,4,1,fp); // pixel per meter, y
  tmp = 0;
  fwrite(&tmp,4,1,fp); // パレット数
  tmp = 0;
  fwrite(&tmp,4,1,fp); // 重要なパレット数(無視)

  fwrite( thisBMP.body, 1, BMP_width*BMP_height*BMP_pixel_dim, fp ); //本体の書き出し

  fclose( fp );
  printf( "Saved as \"%s\"\n", name );
  printf( "Total points drawn: %d ", thisBMP.point_total );
  printf( "(outside: %d)\n", thisBMP.point_outside );
  
}

// for BMP2 functions

void BMPread( int ID ){
    // ID check
    if( ID<0 || BMP_samples<ID ){
        printf( "call BMPread() with a number between 1 and %d.\n", BMP_samples );
        exit( 1 );
    }
    
    char name[256];
    sprintf( name, "%02d.bmp", ID );
    FILE* fp = fopen( name, "rb" ); // ファイルを開く
    if( fp == NULL ){ // オープン失敗
        printf( "BMPread() cannot find the file: %s in your directory.\n", name );
        printf( "check your files and location and try again.\n" );
    }
    assert( fp!=NULL );
    
    BMPnew(); // BMP初期化

    size_t done;
    unsigned char header[54];
    unsigned char* headerPtr = header;
    
    // ヘッダ部の読み込み
    done = fread( headerPtr, 1, 54, fp );
    if( done < 54 ){
        printf( "The file %s is too small. Check your BMP file.\n", name );
        exit( 1 );
    }
    
    // ヘッダの内容確認
    if( headerPtr[0]!='B' || headerPtr[1]!='M' ){
        printf( "The file %s is not a BMP image. Check it again.\n", name );
        exit( 1 );
    }
    headerPtr += 2;
    if( *(int*)headerPtr != BMP_width*BMP_height*BMP_pixel_dim+54 ){
        printf( "%s has a non-suppoerted file size (%d). Check it again.\n", name, *(int*)headerPtr );
        exit( 1 );
    }
    headerPtr += 4;
    if( *(int*)headerPtr != 0 ){
        printf( "%s has a non-suppoerted header element (%d). Check it again.\n", name, *(int*)headerPtr );
        exit( 1 );
    }
    headerPtr += 4;
    if( *(int*)headerPtr != 54 ){
        printf( "%s has a non-suppoerted offset to pixel body (%d). Check it again.\n", name, *(int*)headerPtr );
        exit( 1 );
    }
    headerPtr += 4;
    if( *(int*)headerPtr != 40 ){
        printf( "%s has a non-suppoerted header size (%d). Check it again.\n", name, *(int*)headerPtr );
        exit( 1 );
    }
    headerPtr += 4;

    if( *(int*)headerPtr != BMP_width ){
        printf( "%s has a non-suppoerted width (%d). Check it again.\n", name, *(int*)headerPtr );
//        exit( 1 );
    }
    headerPtr += 4;
    if( *(int*)headerPtr != BMP_height ){
        printf( "%s has a non-suppoerted height (%d). Check it again.\n", name, *(int*)headerPtr );
//        exit( 1 );
    }
    headerPtr += 4;

    if( *(short int*)headerPtr != 1 ){
        printf( "%s has a non-suppoerted number of planes (%d). Check it again.\n", name, *(int*)headerPtr );
        exit( 1 );
    }
    headerPtr += 2;

    if( *(short int*)headerPtr != 24 ){
        printf( "%s has a non-suppoerted bits per pixels(BPP) (%d). Check it again.\n", name, *(int*)headerPtr );
        exit( 1 );
    }
    headerPtr += 2;

    if( *(int*)headerPtr != 0 ){
        printf( "%s has a non-suppoerted compression mode (%d). Check it again.\n", name, *(int*)headerPtr );
        exit( 1 );
    }
    headerPtr += 4;
    if( *(int*)headerPtr != BMP_width*BMP_height*BMP_pixel_dim ){
        printf( "%s has a non-suppoerted body length (%d). Check it again.\n", name, *(int*)headerPtr );
        exit( 1 );
    }
    headerPtr += 4;
    if( *(int*)headerPtr != 0 ){
//        printf( "%s has an X resolution (%d), ignored.\n", name, *(int*)headerPtr );
    }
    headerPtr += 4;
    if( *(int*)headerPtr != 0 ){
//        printf( "%s has a Y resolution (%d), ignored.\n", name, *(int*)headerPtr );
    }
    headerPtr += 4;
    if( *(int*)headerPtr != 0 ){
        printf( "%s has a non-suppoerted number of palettes (%d). Check it again.\n", name, *(int*)headerPtr );
        exit( 1 );
    }
    headerPtr += 4;
    if( *(int*)headerPtr != 0 ){
        printf( "%s has a non-suppoerted number of important palettes (%d). Check it again.\n", name, *(int*)headerPtr );
        exit( 1 );
    }
    headerPtr += 4;
    printf( "The size of the header read is %d.\n", (int)(headerPtr-header) );
    
    thisBMP.i_header_size=54;
    thisBMP.comp_mode = 0;
    thisBMP.x_reso = thisBMP.y_reso = 0;
    thisBMP.palette = 0;
    thisBMP.i_color = 0;
    thisBMP.plane = 1;
    thisBMP.bpp = 24;
    thisBMP.point_total = 0;
    thisBMP.point_outside = 0;
    
    fseek( fp, 54, 0 ); // ヘッダ読み飛ばし
    done = fread( thisBMP.body, 1, BMP_width*BMP_height*BMP_pixel_dim, fp ); // ピクセル値読み出し
    if( done < BMP_width*BMP_height*BMP_pixel_dim ){ // データ不足
        printf( "The number of pixels is insufficient. Check your BMP file." );
        exit( 1 );
    }
    printf( "Image file \"%s\" loading completed.\n", name );
    
}
void BMPpointAlpha( int x, int y, // 点をセット
                  unsigned char r, unsigned char g, unsigned char b, unsigned char a ){
    if( BMP_init != 1 ){
        printf( "call BMPnew() before BMPpoint().\n" );
        return;
    }
    if( x<0 || y<0 || BMP_width-1<x || BMP_height-1<y ){ // 範囲外
        thisBMP.point_outside++;
        return;
    }
    /*
    double alpha = a/255.0;
    double oldR = thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_R ];
    double oldG = thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_G ];
    double oldB = thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_B ];

    double newR, newG, newB;
    newR = (oldR*(1-alpha) + r*alpha)/255.0;
    newG = (oldG*(1-alpha) + g*alpha)/255.0;
    newB = (oldB*(1-alpha) + b*alpha)/255.0;
    
    thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_R ] = (unsigned char)newR;
    thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_G ] = (unsigned char)newG;
    thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_B ] = (unsigned char)newB;
     */
    
    int newR = (thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_R ]*(255-a) + r*a )/255;
    thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_R ] = (unsigned char)newR;
    int newG = (thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_G ]*(255-a) + g*a )/255;
    thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_G ] = (unsigned char)newG;
    int newB = (thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_B ]*(255-a) + b*a )/255;
    thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_B ] = (unsigned char)newB;

    thisBMP.point_total++;
}

unsigned char BMPpointGetR( int x, int y ){
    if( BMP_init != 1 ){
        printf( "call BMPnew() before BMPpoint().\n" );
        exit( 1 );
    }
    if( x<0 || y<0 || BMP_width-1<x || BMP_height-1<y ){ // 範囲外
        thisBMP.point_outside++;
        return 0;
    }
    return thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_R ];
}

unsigned char BMPpointGetG( int x, int y ){
    if( BMP_init != 1 ){
        printf( "call BMPnew() before BMPpoint().\n" );
        exit( 1 );
    }
    if( x<0 || y<0 || BMP_width-1<x || BMP_height-1<y ){ // 範囲外
        thisBMP.point_outside++;
        return 0;
    }
    return thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_G ];
}

unsigned char BMPpointGetB( int x, int y ){
    if( BMP_init != 1 ){
        printf( "call BMPnew() before BMPpoint().\n" );
        exit( 1 );
    }
    if( x<0 || y<0 || BMP_width-1<x || BMP_height-1<y ){ // 範囲外
        thisBMP.point_outside++;
        return 0;
    }
    return thisBMP.body[ (BMP_width*(BMP_height-1-y) + x)*BMP_pixel_dim + BMP_B ];
}



#endif
