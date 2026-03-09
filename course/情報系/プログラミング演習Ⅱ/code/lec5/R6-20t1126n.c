//課題6 オリジナル図形データのファイル入出力
//20T1126N YANG GUANGZE(楊広沢)
//gccgl -o R6-20t1126n R6-20t1126n.c
	
#include <GL/freeglut.h>	
#include <stdio.h>							
#include <stdlib.h>  						
#include <math.h>								
#define MAX 	5		//組み合わせる図形の数の上限					
#define MN 		84		//図形全体の頂点数の上限				
#define WIDTH 	500		//ウィンドウの横幅（デフォルト）					
#define HEIGHT 	500		//ウィンドウの高さ（デフォルト）					

//--------------------------------------------------------------------------- 
//図形情報用配列と変数の宣言
//--------------------------------------------------------------------------- 
GLenum 	mode[MAX];			//描画タイプ
int		Vn[MAX];			//頂点数	
double 	color[MAX][3];		//色（RGB）
double 	v[MN][3];			//頂点座標（変換前）
double 	vt[MN][3];			//頂点座標（変換後）
int		part_num=0;			//部品数用のカウンタ
//--------------------------------------------------------------------------- 
// グローバル変数（変換行列、ウィンドウ）
//--------------------------------------------------------------------------- 
// 変換行列のパラメタ
double DEG=45;				//回転角度（度)のデフォルト
double THETA;				//回転角度（ラジアン）のデフォルト
double TX=0.3;				//X軸方向移動量のデフォルト
double TY=0.5;				//Y軸方向移動量のデフォルト
double Sx=0.5;				//X軸方向拡大率のデフォルト
double Sy=2.0;				//Y軸方向拡大率のデフォルト
// ウィンドウ内に設定される座標 
double xmin;				// 左端 
double xmax;				// 右端 
double ymin;				// 下端 
double ymax;				// 上端 

char	KEY;				//変換キー

double Ts[3][3]={0};		//変換行列（拡大・縮小）
double Tr[3][3]={0};		//変換行列（回転）
double Tt[3][3]={0};		//変換行列（平行移動）
double I[3][3]={0};			//変換行列（変換無）

//--------------------------------------------------------------------------- 
// 関数のプロトタイプ宣言
//--------------------------------------------------------------------------- 
void affine(void);
void init(void);
void set_vertices(double T[][3], double v[][3], double vt[][3], int n);
void load_data(void);
void draw_axis(void);
void save_data(void);
//--------------------------------------------------------------------------- 
// 変換行列の設定
//--------------------------------------------------------------------------- 
void affine(void){
	THETA=2*M_PI*DEG/360;		//回転角度の設定
	//scaling
	Ts[0][0]=Sx;	Ts[0][1]=0.0;	Ts[0][2]=0.0;
    Ts[1][0]=0.0;	Ts[1][1]=Sy;	Ts[1][2]=0.0;
    Ts[2][0]=0.0;	Ts[2][1]=0.0;	Ts[2][2]=1.0;

	//rotation
	Tr[0][0]=cos(THETA); 	Tr[0][1]=-sin(THETA);	Tr[0][2]=0.0;
    Tr[1][0]=sin(THETA);	Tr[1][1]=cos(THETA);	Tr[1][2]=0.0;
    Tr[2][0]=0.0;			Tr[2][1]=0.0;			Tr[2][2]=1.0;

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
// 頂点設定関数
// 		T:変換行列用配列へのポインタ, 
// 		v:頂点座標配列（変換前）へのポインタ
// 		vt:頂点座標配列（変換後）へのポインタ
//		n:頂点数
//--------------------------------------------------------------------------- 
void set_vertices(double T[][3], double v[][3], double vt[][3], int n){
	int i,j,k;

	//N角形の頂点を指定(k番目の頂点の計算）
	for(k=0;k<n;k++){
		for(i=0;i<3;i++){
			vt[k][i]=0.0;
			for(j=0;j<3;j++)	vt[k][i]+=T[i][j]*v[k][j];
		}
	}
}
//--------------------------------------------------------------------------- 
// 初期化
//--------------------------------------------------------------------------- 
void init(void){
	affine();	//set affine transformation matrices	

	load_data(); //	ファイルから頂点座標と色情報の読み込み
}

//--------------------------------------------------------------------------- 
// ファイルからの図形データ読み込み
//--------------------------------------------------------------------------- 
void load_data(void){
	FILE 	*fp; 								
	char 	fname[]="R6-20t1126n_in.csv",
				ss[256],							
				md;										
	double	dt1,dt2,dt3,dt4;		
	int		vsum=0;							
 
	fp = fopen(fname, "r"); 		
	if(fp == NULL) {
			printf("Can't open %s!\n", fname);
			exit(1);
	}
	
	while(fgets(ss, 256, fp) != NULL){
		printf("%s",ss);
		sscanf(ss, "%c,%lf,%lf,%lf,%lf", &md, &dt1, &dt2, &dt3, &dt4);
		if( md=='p'||md=='l'||md=='L'||md=='s'||md=='t'||
        	md=='T'||md=='f'||md=='q'||md=='Q'||md=='P' ){
	
			switch(md){
				case 'p':	mode[part_num]=0x0000;	break;	//GL_POINTS
				case 'l':	mode[part_num]=0x0001;	break;	//GL_LINES
				case 'L':	mode[part_num]=0x0002;	break;	//GL_LINE_LOOP
				case 's':	mode[part_num]=0x0003;	break;	//GL_LINE_STRIP
				case 't':	mode[part_num]=0x0004;	break;	//GL_TRIANGLES
				case 'T':	mode[part_num]=0x0005;	break;	//GL_TRIANGLE_STRIP
				case 'f':	mode[part_num]=0x0006;	break;	//GL_TRIANGLE_FAN
				case 'q':	mode[part_num]=0x0007;	break;	//GL_QUADS
				case 'Q':	mode[part_num]=0x0008;	break;	//GL_QUAD_STRIP
				case 'P':	mode[part_num]=0x0009;	break;	//GL_POLYGON
				default: printf("Can't discriminate the mode(primitive)."); exit(0);
			}
		
		Vn[part_num]=dt1;				
		color[part_num][0]=dt2;	
		color[part_num][1]=dt3;	
		color[part_num][2]=dt4;	
		part_num++;			
		}else if(md=='v'){ 
			v[vsum][0]=dt1;	
			v[vsum][1]=dt2;	
			v[vsum][2]=dt3;	
			vsum++;					
		}else{
			printf("Can't discriminate the mode."); exit(0);
		}
	} 
	printf("\nloaded vertex data(part_num=%d vsum=%d)\n",part_num, vsum);	
}
//--------------------------------------------------------------------------- 
// 座標とグリッド線の描画
//--------------------------------------------------------------------------- 
void draw_axis(void){
	double gd;
	glBegin(GL_LINES);
		glColor3d(0.75, 0.75, 0.75);	
		for(gd=ymin; gd<=ymax; gd+=0.1){ 
			glVertex2d( xmin, gd );
			glVertex2d( xmax, gd );
		}
		for(gd=xmin; gd<=xmax; gd+=0.1){ 
			glVertex2d( gd, ymin );
			glVertex2d( gd, ymax );
		}
		glColor3d(0.0, 0.0, 0.0);
		glVertex2d( xmin, 0.0);		glVertex2d( xmax, 0.0 );	
		glVertex2d( 0.0, ymin );	glVertex2d( 0.0, ymax );	
		glEnd();
}
//--------------------------------------------------------------------------- 
// 画面表示関数（描画関数）
//--------------------------------------------------------------------------- 
void display(void) {
	int	i,k,n;		
				
    glClearColor( 0, 0, 0, 1 );  		
    glClear( GL_COLOR_BUFFER_BIT );		
	draw_axis();	

	int	vsum=0;
	for(n=0;n<part_num;n++)	vsum+=Vn[n];

	if(KEY=='s' || KEY=='S') 						
    	set_vertices(Ts, v, vt, vsum);
	else if(KEY=='r' || KEY=='R')			
		set_vertices(Tr, v, vt, vsum);
	else if(KEY=='t' || KEY=='T')						
		set_vertices(Tt, v, vt, vsum);
	else	set_vertices(I, v, vt, vsum);	

	int ksum=0;
	for(n=0;n<part_num;n++){
		glColor3d(color[n][0], color[n][1], color[n][2]);
		glBegin( mode[n] );  		
		for(k=ksum;k<ksum+Vn[n];k++) glVertex2d( vt[k][0], vt[k][1] );
		ksum=k;	
  		glEnd();  						
	}

	for(k=0;k<vsum;k++){
			for(i=0;i<3;i++)	v[k][i]=vt[k][i];
	}

	glFlush(); 

	KEY='x';	
}
//--------------------------------------------------------------------------- 
// ウィンドウサイズ変更時
//--------------------------------------------------------------------------- 
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	xmin=-1.0*w/WIDTH; xmax=1.0*w/WIDTH; ymin=-1.0*h/HEIGHT; ymax=1.0*h/HEIGHT;
	gluOrtho2D(xmin, xmax, ymin, ymax);
}
//--------------------------------------------------------------------------- 
// キーボードイベントコールバック関数
//--------------------------------------------------------------------------- 
void keyboard(unsigned char key, int x, int y){
  	switch (key) {
		case 'r':	case 'R':
			KEY=key;
			glutPostRedisplay();		
			break;
		case 's':	case 'S':
			KEY=key;
			glutPostRedisplay();		
			break;
		case 't':	case 'T':
			KEY=key;
			glutPostRedisplay();		
			break;
		case 'f': case 'F':
			save_data();
			break;
  		case 'q':	case 'Q':	case '\033':   
			exit(0);
  		default:
    		break;
  	}
}
void save_data(void){
    FILE *fp;
	char fname[]="R6-20t1126n_out.csv";
    fp =fopen(fname,"w");
    int ksum=0,n=0;
	char md[MAX]={0};
    for(n=0; n<part_num;n++){
		if (mode[n]==0x0000){
			md[n]='p';
		}else if(mode[n]== 0x0001){
			md[n]='l';
		}else if(mode[n]== 0x0002){
			md[n]='L';
		}else if(mode[n]== 0x0003){
			md[n]='s';
		}else if(mode[n]== 0x0004){
			md[n]='t';
		}else if(mode[n]== 0x0005){
			md[n]='T';
		}else if(mode[n]== 0x0006){
			md[n]='f';
		}else if(mode[n]== 0x0007){
			md[n]='q';
		}else if(mode[n]== 0x0008){
			md[n]='Q';
		}else if(mode[n]== 0x0009){
			md[n]='P';
		}else{
			printf("描画タイプの出力に失敗しました");
		}
		fprintf(fp,"%c,%d,%lf,%lf,%lf\n", md[n], Vn[n], color[n][0], color[n][1], color[n][2]);

		for(ksum=0; ksum<Vn[n]; ksum++){
				fprintf(fp,"v,%lf,%lf,%lf,0\n", v[ksum][0], v[ksum][1], v[ksum][2]);
		}
	}

	if(fp == NULL){
		printf("出力ファイルに失敗しました");
    	exit(1);
    }

	printf("saved data to %s\n",fname);

	fclose(fp);
}
//--------------------------------------------------------------------------- 
// メイン関数
//--------------------------------------------------------------------------- 
int main( int argc, char *argv[] ) {  

    glutInit(&argc, argv);					
    glutInitDisplayMode(GLUT_RGBA);   
    glutInitWindowSize(WIDTH,HEIGHT);     
    glutInitWindowPosition(100,100);  
    glutCreateWindow(argv[0]); 		

	init();		

    glutDisplayFunc(display);       

	glutReshapeFunc(reshape);		

    glutKeyboardFunc(keyboard); 	
			
    glutMainLoop(); 									

    return 0;
}

