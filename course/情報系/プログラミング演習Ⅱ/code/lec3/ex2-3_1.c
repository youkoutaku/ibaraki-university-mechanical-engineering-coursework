#include <stdio.h>
int main( void ){
    int i,j,k;
    double A[2][3] = {{3.0, 0.0, 1.0}, {0.0, 2.0, 4.0}};
    double B[3][2] = {{2.0, 1.0}, {0.0, 3.0}, {-1.0, 4.0}};
    double C[2][2] ={0};
  
    for(i=0; i<2; i++){
        for(j=0; j<2; j++){
            // C[i][j]=0.0;
            for(k=0; k<3; k++){
                C[i][j] += A[i][k]*B[k][j];
            }
            printf("C[%d][%d]=%f", i, j, C[i][j]);
        }
        printf("\n");
    }

  return 0;
}