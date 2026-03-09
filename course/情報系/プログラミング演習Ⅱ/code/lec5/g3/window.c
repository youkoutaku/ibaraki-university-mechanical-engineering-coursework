//----------------------------------------------------------------------------
//									         <window.c>(タブ2）
//
//						□ 2次元の座標変換（同次座標を用いたアフィン変換）
//						□ N角形の描画（POLYGON)
//						□ ウィンドウサイズ変更時の座標軸の再設定
//
// (Windows マクロ無し）gcc -o window window.c -lfreeglut -lglu32 -lopengl32
// (Windows マクロ使用)	gccgl -o window window.c
// (Mac OS の場合)			gcc -o window window.c -framework OpenGL -framework GLUT -DGL_SILENCE_DEPRECATION
//--------------------------------------------------------------------------- 
#ifndef __APPLE__  				// OSがMacでない (Windowsの場合)
#include <GL/freeglut.h>	//freeglutのヘッダファイルの読み込み
#else
#include <GLUT/glut.h>  	// Macの場合のヘッダ
#endif

#include <math.h>								//数学関数
#define N 4											//頂点の数
#define DEG 60									//回転角度（度)
#define THETA (2*M_PI*DEG/360)	//回転角度（ラジアン）
#define TX 0.4									//X軸方向移動量
#define TY 0.3									//Y軸方向移動量
#define Sx 5.0									//X軸方向拡大率
#define Sy 2.0									//Y軸方向拡大率
#define WIDTH 	500							//ウィンドウの横幅（デフォルト）
#define HEIGHT 	500							//ウィンドウの高さ（デフォルト）
//--------------------------------------------------------------------------- 
// グローバル変数
//--------------------------------------------------------------------------- 
// ウィンドウ内に設定される座標 
double xmin;					// 左端 
double xmax;					// 右端 
double ymin;					// 下端 
double ymax;					// 上端 
//変換行列（拡大・縮小）
double Ts[3][3]={{Sx,  0.0, 0.0},
								 {0.0, Sy,  0.0},
								 {0.0, 0.0, 1.0}};
//変換行列（回転）
double Tr[3][3]={{cos(THETA), -sin(THETA), 0.0},
								 {sin(THETA),  cos(THETA), 0.0},
								 {0.0,				 0.0, 			 1.0}};
//変換行列（平行移動）
double Tt[3][3]={{1.0, 0.0, TX },
								 {0.0, 1.0, TY },
								 {0.0, 0.0, 1.0}};
//--------------------------------------------------------------------------- 
// 画面表示関数（描画関数）
//--------------------------------------------------------------------------- 
void display(void) {

		int	i,j,k;		//	カウンタ

 		//頂点座標(変換前）
		double	v[N][3]={{ 0.0,  0.0, 1.0},
										 { 0.3,  0.0, 1.0},
										 { 0.3,  0.3, 1.0},
										 { 0.0,  0.3, 1.0}};
		double 	vt[N][3]={0};	//頂点座標（変換後）

    glClearColor( 1, 1, 1, 1 );  		// ウィンドウの背景色を白に設定
    glClear( GL_COLOR_BUFFER_BIT );	// カラーバッファをクリア（背景の塗りつぶし）

		//座標とグリッド線の描画（座標軸の再設定対応）
		double gd;
		glBegin(GL_LINES);
			glColor3d(0.75, 0.75, 0.75);	//グレー
			for(gd=ymin; gd<=ymax; gd+=0.1){ //横グリッド線
				glVertex2d( xmin, gd );
				glVertex2d( xmax, gd );
			}
			for(gd=xmin; gd<=xmax; gd+=0.1){ //縦グリッド線
				glVertex2d( gd, ymin );
				glVertex2d( gd, ymax );
			}
			glColor3d(0.0, 0.0, 0.0);			//黒
			//x軸
			glVertex2d( xmin, 0.0);
			glVertex2d( xmax, 0.0 );
			//y軸
			glVertex2d( 0.0, ymin );
			glVertex2d( 0.0, ymax );
		glEnd();
    
#if 1
    //アフィン変換（拡大・縮小）
		for(k=0;k<N;k++){
			for(i=0;i<3;i++){
				vt[k][i]=0.0;
				for(j=0;j<3;j++)	vt[k][i]+=Ts[i][j]*v[k][j];
			}
		}
#endif

#if 0
		//アフィン変換（回転）
		for(k=0;k<N;k++){
			for(i=0;i<3;i++){
				vt[k][i]=0.0;
				for(j=0;j<3;j++)	vt[k][i]+=Tr[i][j]*v[k][j];
			}
		}
#endif

#if 0
		//アフィン変換（平行移動）
		for(k=0;k<N;k++){
			for(i=0;i<3;i++){
				vt[k][i]=0.0;
				for(j=0;j<3;j++)	vt[k][i]+=Tt[i][j]*v[k][j];
			}
		}
#endif

		glColor3d( 0, 0, 1 ); 		// 色の設定(青)
		glBegin( GL_POLYGON ); 		// 図形描画タイプの設定開始: N角形(塗りつぶし) 		
			for(k=0;k<N;k++)	glVertex2d( vt[k][0], vt[k][1] );
  	glEnd( );  								// 図形描画タイプの設定終了

    glFlush(); 					      // 未実行の命令を全て実行
 
}
//--------------------------------------------------------------------------- 
// ウィンドウサイズ変更時
//--------------------------------------------------------------------------- 
void reshape(int w, int h) {
    // リサイズ後のウィンドウの全面を表示領域に設定
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

		//座標軸を(xmin, ymin)～(xmax, ymax)に設定
		xmin=-1.0*w/WIDTH; xmax=1.0*w/WIDTH; ymin=-1.0*h/HEIGHT; ymax=1.0*h/HEIGHT;
		gluOrtho2D(xmin, xmax, ymin, ymax);
}

//--------------------------------------------------------------------------- 
// メイン関数
//--------------------------------------------------------------------------- 
int main( int argc, char *argv[] ) {  

    glutInit(&argc, argv);						// GLUT環境の初期化
    glutInitDisplayMode(GLUT_RGBA);   // ディスプレイモードの設定
    glutInitWindowSize(WIDTH,HEIGHT); // ウィンドウサイズの設定（単位はpixel)
    glutInitWindowPosition(100,100);  // ウィンドウの位置（モニタ左上から(100,100)pixelの位置)
    glutCreateWindow(argv[0]); 				// ウィンドウ生成（ウィンドウのタイトル設定）

    glutDisplayFunc(display);       	// コールバック関数の登録（画面表示)
		glutReshapeFunc(reshape);					// コールバック関数の登録（ウィンドウのサイズ変更）
    
    glutMainLoop(); 									//イベント待ちの無限ループ

    return 0;
}

