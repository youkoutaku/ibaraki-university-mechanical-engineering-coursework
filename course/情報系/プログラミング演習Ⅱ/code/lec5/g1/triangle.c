//----------------------------------------------------------------------------
//									         <triangle.c>
//
//													三角形の描画(タブ2）
//
// (Windows マクロ無し）gcc -o triangle triangle.c -lfreeglut -lglu32 -lopengl32
// (Windows マクロ使用)	gccgl -o triangle triangle.c
// (Mac OS の場合)			gcc -o triangle triangle.c -framework OpenGL -framework GLUT -DGL_SILENCE_DEPRECATION
//--------------------------------------------------------------------------- 

#ifndef __APPLE__  				// OSがMacでない (Windowsの場合)
#include <GL/freeglut.h>	//freeglutのヘッダファイルの読み込み
#else
#include <GLUT/glut.h>  	// Macの場合のヘッダ
#endif

void display(void) {  // 画面表示関数
 
    glClearColor( 0, 0, 0, 1 );  		// ウィンドウの背景色を黒に設定
    glClear( GL_COLOR_BUFFER_BIT );	// カラーバッファをクリア（背景の塗りつぶし）
    
		/* ここに線の太さの設定を記述 */
		glColor3d( 1, 0, 0 ); 			// 色の設定(赤)
		glBegin( GL_TRIANGLES ); 		// 図形描画タイプの設定開始: 三角形(塗りつぶし) 
    	//三角形の3頂点を指定 
    	glVertex2d( -0.8, -0.8 );
    	glVertex2d(  0.8, -0.8 );
    	glVertex2d(  0.0,  0.8 );
  	glEnd( );  									// 図形描画タイプの設定終了

		/* ここに2番目の三角形の描画を記述 */

    glFlush(); 					        // 未実行の命令を全て実行
 
}

int main( int argc, char *argv[] ) {  

    glutInit(&argc, argv);						// GLUT環境の初期化
    glutInitDisplayMode(GLUT_RGBA);   // ディスプレイモードの設定
    glutInitWindowSize(500,500);      // ウィンドウサイズの設定（単位はpixel)
    glutInitWindowPosition(100,100);  // ウィンドウの位置（モニタ左上から(100,100)pixelの位置)
    glutCreateWindow(argv[0]); 				// ウィンドウ生成（ウィンドウのタイトル設定）

    glutDisplayFunc(display);       	// コールバック関数の登録（画面表示)
    
    glutMainLoop(); 									//イベント待ちの無限ループ

    return 0;
}

