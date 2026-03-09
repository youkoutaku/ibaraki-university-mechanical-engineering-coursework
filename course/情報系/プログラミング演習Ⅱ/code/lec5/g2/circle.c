//----------------------------------------------------------------------------
//									         <circle.c>
//
//						2次元の座標変換（同次座標を用いたアフィン変換）
//													円の描画（POLYGON)(タブ2）
//
// (Windows マクロ無し）gcc -o circle circle.c -lfreeglut -lglu32 -lopengl32
// (Windows マクロ使用)	gccgl -o circle circle.c
// (Mac OS の場合)			gcc -o circle circle.c -framework OpenGL -framework GLUT -DGL_SILENCE_DEPRECATION
//--------------------------------------------------------------------------- 
#ifndef __APPLE__  				// OSがMacでない (Windowsの場合)
#include <GL/freeglut.h>	//freeglutのヘッダファイルの読み込み
#else
#include <GLUT/glut.h>  	// Macの場合のヘッダ
#endif

#include <math.h>								//数学関数
#define N 360										//頂点の数
#define DEG 45									//回転角度（度)
#define THETA (2*M_PI*DEG/360)	//回転角度（ラジアン）
#define TX 0.3									//X軸方向移動量
#define TY 0.5									//Y軸方向移動量
#define Sx 0.5									//X軸方向拡大率
#define Sy 2.0									//Y軸方向拡大率
//--------------------------------------------------------------------------- 
// グローバル変数
//--------------------------------------------------------------------------- 
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
//変換行列（無変換）
double I[3][3]={{1.0, 0.0, 0.0 },
								 {0.0, 1.0, 0.0 },
								 {0.0, 0.0, 1.0}};
//--------------------------------------------------------------------------- 
// 円の頂点設定関数:中心( xc, yc ), 半径rの円
//--------------------------------------------------------------------------- 
void set_circle_vertices(double xc, double yc, double r, double v[][3])
{
		int i;
		//頂点座標の設定
		for( i = 0; i < N; i++ ) {  // 円周上の頂点を360/N度刻みでN個設定 
      	v[i][0] = xc + r * cos( 2.0 * M_PI * i / N ); // 頂点のx座標 
      	v[i][1] = yc + r * sin( 2.0 * M_PI * i / N ); // 頂点のy座標 
				v[i][2] = 1.0;
    }
}
//--------------------------------------------------------------------------- 
// 画面表示関数（描画関数）
//--------------------------------------------------------------------------- 
void display(void) {

		int	i,j,k;		//	カウンタ

 		//頂点座標(変換前）
		double	v[N][3];
		double 	vt[N][3]={0};	//頂点座標（変換後）
				
		set_circle_vertices(0.5, 0.0, 0.3, v); //円の頂点座標の設定

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

#if 0
		//アフィン変換（無変換）
		for(k=0;k<N;k++){
			for(i=0;i<3;i++){
				vt[k][i]=0.0;
				for(j=0;j<3;j++)	vt[k][i]+=I[i][j]*v[k][j];
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

