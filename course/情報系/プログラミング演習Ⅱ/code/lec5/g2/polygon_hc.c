//----------------------------------------------------------------------------
//									         <polygon_hc.c>
//
//													N角形(POLYGON)の描画(タブ2）
//													同次座標(homogeneous coordinates)
//
// (Windows マクロ無し）gcc -o polygon_hc polygon_hc.c -lfreeglut -lglu32 -lopengl32
// (Windows マクロ使用)	gccgl -o polygon_hc polygon_hc.c
// (Mac OS の場合)			gcc -o polygon_hc polygon_hc.c -framework OpenGL -framework GLUT -DGL_SILENCE_DEPRECATION
//--------------------------------------------------------------------------- 
#ifndef __APPLE__  				// OSがMacでない (Windowsの場合)
#include <GL/freeglut.h>	//freeglutのヘッダファイルの読み込み
#else
#include <GLUT/glut.h>  	// Macの場合のヘッダ
#endif

#define N 4
//--------------------------------------------------------------------------- 
// 画面表示関数（描画関数）
//--------------------------------------------------------------------------- 
void display(void) {

		int	i,j,k;		//	カウンタ

 		//頂点座標（同次座標）
		double	v[N][3]={{ 0.0,  0.0, 1.0 },
										 { 0.3,  0.0, 1.0 },
										 { 0.3,  0.3, 1.0 },
										 { 0.0,  0.3, 1.0 }};

    glClearColor( 1, 1, 1, 1 );  		// ウィンドウの背景色を白に設定
    glClear( GL_COLOR_BUFFER_BIT );	// カラーバッファをクリア（背景の塗りつぶし）
    
		//座標とグリッド線の描画
		glBegin(GL_LINES);
			for(i=-9;i<=9;i++){ //X軸と横グリッド線
				if(i==0) 	glColor3d(0.0, 0.0, 0.0);			//黒
				else			glColor3d(0.75, 0.75, 0.75);	//グレー
				glVertex2d( -1.0, i*0.1 );
				glVertex2d(  1.0, i*0.1 );
			}
			for(i=-9;i<=9;i++){ //Y軸と縦グリッド線
				if(i==0) 	glColor3d(0.0, 0.0, 0.0);			//黒
				else			glColor3d(0.75, 0.75, 0.75);	//グレー
				glVertex2d( i*0.1, -1.0 );
				glVertex2d( i*0.1,  1.0 );
			}
		glEnd();
    
		glColor3d( 0, 0, 1 ); 		// 色の設定(青)
		glBegin( GL_POLYGON ); 		// 図形描画タイプの設定開始: N角形(塗りつぶし) 	
			for(k=0; k<N; k++)	glVertex2d( v[k][0], v[k][1] );
  	glEnd( );  								// 図形描画タイプの設定終了

    glFlush(); 					       // 未実行の命令を全て実行
}
//--------------------------------------------------------------------------- 
// メイン関数
//--------------------------------------------------------------------------- 
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

