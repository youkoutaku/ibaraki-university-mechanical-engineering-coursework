//----------------------------------------------------------------------------
//									         <RandomWalk.c>(タブ2）
//
//						□ 2次元等方的ランダムウォークのシミュレーション
//            □ 構造体配列に図形データをファイルから読み込む
//              
// (Windows マクロ無し）gcc -o RandomWalk RandomWalk.c -lfreeglut -lglu32 -lopengl32
// (Windows マクロ使用)	gccgl -o RandomWalk RandomWalk.c
// (Mac OS の場合)			gcc -o RandomWalk RandomWalk.c -framework OpenGL -framework GLUT -DGL_SILENCE_DEPRECATION
//--------------------------------------------------------------------------- 
#ifndef __APPLE__  				// OSがMacでない (Windowsの場合)
#include <GL/freeglut.h>	//freeglutのヘッダファイルの読み込み
#else
#include <GLUT/glut.h>  	// Macの場合のヘッダ
#endif

#include <stdio.h>							//printf()用
#include <stdlib.h>  						//exit(),rand()用
#include <math.h>								//数学関数
#include <time.h>								//time_t型を使用する
#define MAX 		4								//組み合わせる図形の数の上限
#define N 			36							//一つの部品の描画に使用できる最大頂点数
#define WIDTH 	500							//ウィンドウの横幅（デフォルト）
#define HEIGHT 	500							//ウィンドウの高さ（デフォルト）
#define TIME_INTERVAL	100
//--------------------------------------------------------------------------- 
// 構造体の宣言
//--------------------------------------------------------------------------- 
//図形情報用
typedef struct{
		GLenum mode;			//描画タイプ
		int			Vn;				//頂点数
		double 	color[3];	//色（RGB）
		double 	v[N][3];	//頂点座標（変換前）
		double 	vt[N][3];	//頂点座標（変換後）
} Vertex;

//--------------------------------------------------------------------------- 
// グローバル変数
//--------------------------------------------------------------------------- 
// 変換行列のパラメタ
double DEG=45;							//回転角度（度)のデフォルト
double THETA;								//回転角度（ラジアン）のデフォルト
double TX=0.1;							//X軸方向移動量のデフォルト
double TY=0.1;							//Y軸方向移動量のデフォルト
double Sx=0.5;							//X軸方向拡大率のデフォルト
double Sy=2.0;							//Y軸方向拡大率のデフォルト

// ウィンドウ内に設定される座標 
double xmin;							// 左端 
double xmax;							// 右端 
double ymin;							// 下端 
double ymax;							// 上端 

char	KEY;								//変換キー

double Ts[3][3]={0};		//変換行列（拡大・縮小）
double Tr[3][3]={0};		//変換行列（回転）
double Tt[3][3]={0};		//変換行列（平行移動）
double I[3][3]={0};			//変換行列（変換無）

Vertex 	part[MAX]={0};	//部品情報用配列			
int			part_num=0;			//部品数用のカウンタ

//ランダムウォーカー
int sim_time	;					//シミュレーション時間
double x;								//ウォーカーの x 座標
double y;								//ウォーカーの y 座標
char	move;							//ウォーカーの移動方向
//--------------------------------------------------------------------------- 
// 関数のプロトタイプ宣言
//--------------------------------------------------------------------------- 
void affine(void);
void init(void);
void set_vertices(double T[][3], Vertex *part);
void load_data(void);
void draw_axis(void);
double uniform_random(void);
void timer(int value);
//--------------------------------------------------------------------------- 
//  文字列を描画する関数
//--------------------------------------------------------------------------- 
void drawString2D( double x, double y, char *str )
{
  glRasterPos2d( x, y );   //文字列の先頭の描画位置を(x,y)に設定

  while( *str != '\0' ) {  //文字が終了コードでなければ
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, *str );  //12ポイントのHelveticaビットマップフォントで1文字ずつ描画
    str++;  							//1文字分先に進める
  }
}
//--------------------------------------------------------------------------- 
//  一様乱数[0,1]を返す
//--------------------------------------------------------------------------- 
double uniform_random(void){

  return  (double)rand()/RAND_MAX;

}
//--------------------------------------------------------------------------- 
// 変換行列の設定
//--------------------------------------------------------------------------- 
void affine(void)
{
	THETA=2*M_PI*DEG/360;		//回転角度の設定
	//scaling
	Ts[0][0]=Sx;	Ts[0][1]=0.0;	Ts[0][2]=0.0;
  Ts[1][0]=0.0;	Ts[1][1]=Sy;	Ts[1][2]=0.0;
  Ts[2][0]=0.0;	Ts[2][1]=0.0;	Ts[2][2]=1.0;

	//rotation
	Tr[0][0]=cos(THETA); 	Tr[0][1]=-sin(THETA);	Tr[0][2]=0.0;
  Tr[1][0]=sin(THETA);	Tr[1][1]=cos(THETA);	Tr[1][2]=0.0;
  Tr[2][0]=0.0;					Tr[2][1]=0.0;					Tr[2][2]=1.0;

	//translation
	Tt[0][0]=1.0;	Tt[0][1]=0.0;	Tt[0][2]=TX;
  Tt[1][0]=0.0;	Tt[1][1]=1.0;	Tt[1][2]=TY;
  Tt[2][0]=0.0;	Tt[2][1]=0.0;	Tt[2][2]=1.0;

	//変換無（単位行列）
	I[0][0]=1.0;	I[0][1]=0.0;	I[0][2]=0.0;
  I[1][0]=0.0;	I[1][1]=1.0;	I[1][2]=0.0;
  I[2][0]=0.0;	I[2][1]=0.0;	I[2][2]=1.0;
}
//--------------------------------------------------------------------------- 
// 座標変換後の頂点設定関数
// 		T:変換行列用配列へのポインタ, 
// 		part:図形情報配列（Vertex型）へのポインタ
//--------------------------------------------------------------------------- 
void set_vertices(double T[][3], Vertex *part)
{
	int i,j,k,n;

	for(n=0;n<part_num;n++){ //n番目の部品の座標変換
		for(k=0;k<part[n].Vn;k++){ //n番目の部品のk番目の頂点の計算
			for(i=0;i<3;i++){
				part[n].vt[k][i]=0.0;
				for(j=0;j<3;j++)	part[n].vt[k][i]+=T[i][j]*part[n].v[k][j];
			}
		}
	}
}
//--------------------------------------------------------------------------- 
// 初期化
//--------------------------------------------------------------------------- 
void init(void)
{
		affine();			//set affine transformation matrices

		load_data(); 	//ファイルから頂点座標と色情報の読み込み

		sim_time=0;		//シミュレーション時間の初期化

		x=0; y=0;			//ウォーカの位置の初期化

  	srand((unsigned)time(NULL)); //現在時刻を乱数の初期値に設定
}

//--------------------------------------------------------------------------- 
// ファイルからの図形データ読み込み
//--------------------------------------------------------------------------- 
void load_data(void)
{
	FILE 	*fp; 									//ファイルポインタ
	char 	fname[]="walker.csv",//読み込みファイル名
				ss[256],							//読み込み文字列格納用
				mode;									//図形のタイプ(v（頂点座標）,p,l,L,s,t,T,f,q,Q,P)
	double	dt1,dt2,dt3,dt4;		//読み込みデータ一時格納用変数
	int		n,										//カウンタ
				vsum;									//読み込んだ頂点データの数
 
	fp = fopen(fname, "r"); 		//ファイルオープン
	if(fp == NULL) {
			printf("Can't open %s!\n", fname);
			exit(1);
	}
	
	while(fgets(ss, 256, fp) != NULL){
			printf("%s",ss);
			sscanf(ss, "%c,%lf,%lf,%lf,%lf", &mode, &dt1, &dt2, &dt3, &dt4);

			if( mode=='p'||mode=='l'||mode=='L'||mode=='s'||mode=='t'||
          mode=='T'||mode=='f'||mode=='q'||mode=='Q'||mode=='P' ){
				
					switch(mode){
						case 'p':	part[part_num].mode=0x0000;	break;	//GL_POINTS
						case 'l':	part[part_num].mode=0x0001;	break;	//GL_LINES
						case 'L':	part[part_num].mode=0x0002;	break;	//GL_LINE_LOOP
						case 's':	part[part_num].mode=0x0003;	break;	//GL_LINE_STRIP
						case 't':	part[part_num].mode=0x0004;	break;	//GL_TRIANGLES
						case 'T':	part[part_num].mode=0x0005;	break;	//GL_TRIANGLE_STRIP
						case 'f':	part[part_num].mode=0x0006;	break;	//GL_TRIANGLE_FAN
						case 'q':	part[part_num].mode=0x0007;	break;	//GL_QUADS
						case 'Q':	part[part_num].mode=0x0008;	break;	//GL_QUAD_STRIP
						case 'P':	part[part_num].mode=0x0009;	break;	//GL_POLYGON
						default: printf("Can't discriminate the mode(primitive)."); exit(0);
					}

					part[part_num].Vn=dt1;						//頂点数
					part[part_num].color[0]=dt2;			//R
					part[part_num].color[1]=dt3;			//G
					part[part_num].color[2]=dt4;			//B
					part_num++;			//入力した部品の数のカウント
					vsum=0;			 		//読み込んだ頂点データの数用のカウンタを0にセット
			}
			else if(mode=='v'){ //頂点座標データ
					part[part_num-1].v[vsum][0]=dt1;	//x座標
					part[part_num-1].v[vsum][1]=dt2;	//y座標
					part[part_num-1].v[vsum][2]=dt3;	//1
					vsum++;					//入力した頂点データの数のカウント
			}
			else{
					printf("Can't discriminate the mode."); exit(0);
			}
	}
	vsum=0;
	for(n=0;n<part_num;n++) vsum+=part[n].Vn;
	//読み込んだ部品の数と頂点総数の出力
	printf("loaded vertex data(part_num=%d vsum=%d)\n",part_num, vsum);
}
//--------------------------------------------------------------------------- 
// 座標とグリッド線の描画
//--------------------------------------------------------------------------- 
void draw_axis(void)
{
		double gd;
		//座標とグリッド線の描画
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
			glVertex2d( xmin, 0.0);		glVertex2d( xmax, 0.0 );	//x軸
			glVertex2d( 0.0, ymin );	glVertex2d( 0.0, ymax );	//y軸
		glEnd();
}
//--------------------------------------------------------------------------- 
// 画面表示関数（描画関数）
//--------------------------------------------------------------------------- 
void display(void) {

		int	i,k,n;			//カウンタ
		char str[100];	//シミュレーション時間とウォーカーの位置表示用
				
    glClearColor( 1, 1, 1, 1 );  		// ウィンドウの背景色を白に設定
    glClear( GL_COLOR_BUFFER_BIT );	// カラーバッファをクリア（背景の塗りつぶし）
		draw_axis();	//座標とグリッド線の描画

		//ウォーカーの移動
		if(move=='L'){ 			//平行移動（左）
			x-=TX;
			if(x<xmin)	x=xmin;							//移動しない
    	else{
				Tt[0][2]=-TX; Tt[1][2]=0.0;
				set_vertices(Tt, part);				//移動する
			}
		}
		else if(move=='R'){	//平行移動（右）
			x+=TX;
			if(x>xmax)	x=xmax;						//移動しない
    	else{
				Tt[0][2]=TX; Tt[1][2]=0.0;
				set_vertices(Tt, part);			//移動する
			}
		}
		else if(move=='U'){	//平行移動（上）
			y+=TY;
			if(y>ymax)	y=ymax; 				//移動しない
			else{
				Tt[0][2]=0.0; Tt[1][2]=TY;
 				set_vertices(Tt, part);		//移動する
			}
		}
		else if(move=='D'){	//平行移動（下）
			y-=TY;
			if(y<ymin)	y=ymin;					//移動しない
    	else{
					Tt[0][2]=0.0; Tt[1][2]=-TY;
					set_vertices(Tt, part);	//移動する
			}
		}
		else	set_vertices(I, part);	//変換無

		//ウォーカーの描画
		for(n=0;n<part_num;n++){
			glColor3d(part[n].color[0], part[n].color[1], part[n].color[2]);//色の設定
			glBegin( part[n].mode ); 	// 図形描画タイプの設定開始 		
				for(k=0;k<part[n].Vn;k++) glVertex2d( part[n].vt[k][0], part[n].vt[k][1] );
  		glEnd();  							// 図形描画タイプの設定終了
		}

		//part[n].v(n=0, ..., part_num-1)に変換後の頂点座標を設定
		for(n=0;n<part_num;n++){
			for(k=0;k<part[n].Vn;k++){
				for(i=0;i<3;i++) part[n].v[k][i]=part[n].vt[k][i];
			}
		}

		//フォーマットに従って文字配列strに格納 
		sprintf(str,"Simulation time = %d   Position=( %.1f , %.1f )", sim_time, x, y);

  	// 文字列strを(xmini+10, ymax-10)の位置に描画 
		glColor3d(0, 0, 1.0);
		drawString2D(xmin+0.1, ymax-0.1, str ); 

		glutSwapBuffers();		//画面の更新
}

//--------------------------------------------------------------------------- 
// ウィンドウサイズ変更時
//--------------------------------------------------------------------------- 
void reshape(int w, int h) {
    // ウィンドウの描画範囲が[0, w] x [0, h]となるように設定
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

		//座標軸を(xmin, ymin)～(xmax, ymax)に設定
		xmin=-1.0*w/WIDTH; xmax=1.0*w/WIDTH; ymin=-1.0*h/HEIGHT; ymax=1.0*h/HEIGHT;
		gluOrtho2D(xmin, xmax, ymin, ymax);
}
//--------------------------------------------------------------------------- 
// キーボードイベントコールバック関数
//--------------------------------------------------------------------------- 
void keyboard(unsigned char key, int x, int y)
{
  	switch (key) {
			case 'a':	case 'A':	
				glutTimerFunc(TIME_INTERVAL, timer, 0);//TIME_INTERVAL(ミリ秒)後にコールバック関数timerを実行
				break;
			case 'q':	case 'Q':	case '\033':  // '\033' は ESC の ASCII コード 
				exit(0);
  		default:
    		break;
  	}
}
//--------------------------------------------------------------------------- 
// タイマーコールバック関数
//--------------------------------------------------------------------------- 
void timer(int value)
{
		double r;	//乱数代入用
	
		sim_time++;	//シミュレーション時間（呼び出し回数）のカウント

		r=uniform_random();
		if(r<0.25)				move='L';	//左
		else if(r<0.5)		move='R';	//右
		else if(r<0.75)		move='U';	//上（前方）
		else							move='D';	//下（後方）

		glutPostRedisplay();		//ディスプレイコールバックの呼び出し

		//TIME_INTERVAL（ミリ秒）後にtimer関数を呼び出す
		glutTimerFunc(TIME_INTERVAL , timer , 0);		
}
//--------------------------------------------------------------------------- 
// メイン関数
//--------------------------------------------------------------------------- 
int main( int argc, char *argv[] ) {  

    glutInit(&argc, argv);						// GLUT環境の初期化
		// ディスプレイモードの設定(RGB カラー/ ダブルバッファリングを使う)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );   
    glutInitWindowSize(WIDTH,HEIGHT); // ウィンドウサイズの設定（単位はpixel)
    glutInitWindowPosition(100,100);  // ウィンドウの位置（モニタ左上から(100,100)pixelの位置)
    glutCreateWindow(argv[0]); 				// ウィンドウ生成（ウィンドウのタイトル設定）

		init();		//initialization

    glutDisplayFunc(display);       	// コールバック関数の登録（画面表示)

		glutReshapeFunc(reshape);					//ウィンドウサイズ変更時

    glutKeyboardFunc(keyboard); 			//キーボードイベントコールバック関数

    glutMainLoop(); 									//イベント待ちの無限ループ

    return 0;
}

