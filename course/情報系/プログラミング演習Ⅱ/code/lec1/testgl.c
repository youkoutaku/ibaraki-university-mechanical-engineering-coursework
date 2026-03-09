//----------------------------------------------------------------------------
//														<testgl.c>
//
//													文字列の描画(タブ2）
//
//          gcc -o testgl testgl.c -lfreeglut -lglu32 -lopengl32
//                           または
//					gccgl -o testgl testgl.c
//--------------------------------------------------------------------------- 

#include <GL/freeglut.h>	//freeglutのヘッダファイルの読み込み

// 文字列を描画する関数 
void drawString2D( double x, double y, char *str )
{
  glRasterPos2d( x, y );   // 文字列の先頭の描画位置を(x,y)に設定

  while( *str != '\0' ) {  // 文字が終了コードでなければ
		 // 24ポイントのTimes Romanビットマップフォントで1文字ずつ描画
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *str ); 
    str++;  //ポインタを1文字分先に進める
  }
}

void display(void) {  // 画面描画関数
 
    glClearColor( 0, 0, 0, 1 );  		// ウィンドウの背景色を黒に設定
    glClear( GL_COLOR_BUFFER_BIT );	// カラーバッファをクリア（背景の塗りつぶし）    
		drawString2D(-0.7,  0.0, "Mechanical Systems Engineering" ); 
		drawString2D(-0.7, -0.1, "Programming Excercises II" );

    glFlush(); 					// 未実行の命令を全て実行
 
}

int main( int argc, char *argv[] ) {  

    glutInit(&argc, argv);						// GLUT環境の初期化
    glutInitDisplayMode(GLUT_RGBA);   // ディスプレイモードの設定
    glutInitWindowSize(500,500);      // ウィンドウサイズの設定（単位はpixel)
    glutInitWindowPosition(100,100);  // ウィンドウの位置（モニタ左上から(100,100)pixelの位置)
    glutCreateWindow(argv[0]); 				// ウィンドウ生成（ウィンドウのタイトル設定）

    glutDisplayFunc(display);       	// コールバック関数の登録（画面描画)
    
    glutMainLoop(); 									//イベント待ちの無限ループ

    return 0;
}

