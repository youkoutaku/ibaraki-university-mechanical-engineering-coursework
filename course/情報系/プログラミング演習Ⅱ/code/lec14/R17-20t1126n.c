//課題17 関数マクロを定義するプログラム
//20t1126n YANG GUANGZE
//gcc -Wall -o R17-20t1126n R17-20t1126n.c

#include <stdio.h>
#include <stdlib.h>

#define N 3
#define Kioku(pt)   {\
                        if( (pt) == NULL){\
                            exit(1);\
                        }else{\
                            printf(""#pt"の記憶領域の確保に成功しました\n");\
                        }\
                    }
#define Kaihou(pt)  {\
                        free( (pt) );\
                        (pt) =NULL;\
                    }

int main (){
    int i, j, k,
        m, l;
    double (*A)[N], (*B)[N];

    printf("次元数(m) :");
    scanf("%d",&m);
    printf("次元数(l) :");
    scanf("%d",&l);

    A=(double (*)[N])calloc(m*N, sizeof(double));	

    B=(double (*)[N])calloc(l*N, sizeof(double));	

    double (*C)[l]=(double (*)[l])calloc(m*l, sizeof(double));	

    Kioku(A); 
    Kioku(B);
    Kioku(C);

    printf("----------データの入力----------\n");

    for(i=0; i<m; i++){
        for(j=0; j<N; j++){
            printf("A[%d][%d]=", i, j);
            scanf("%lf",&A[i][j]);
        }
    }

    for(i=0; i<N; i++){
        for(j=0; j<l; j++){
            printf("B'[%d][%d]=", j, i);
            scanf("%lf",&B[j][i]);
        }
    }

    printf("----------A x B の結果----------\n");

    printf("C=\n");   

    for(i=0; i<m; i++){
        for(j=0; j<l; j++){
            for (k=0; k<N; k++){
                C[i][j] += A[i][k] * B[j][k];
            }
            printf("\t%.1lf",C[i][j]);    
        }
        printf("\n");
    }

    Kaihou(A); 
    Kaihou(B); 
    Kaihou(C);

    return 0;
}