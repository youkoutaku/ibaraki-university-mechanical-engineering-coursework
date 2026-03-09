//2~N‚Ì’†‚©‚ç‘f”‚ğE‚¢o‚·
//¬‚³‚È‘f”‚©‚ç‡‚É‚»‚Ì”{”‚ğu‚Ó‚é‚¢v‚©‚çˆêŠ‡‚Å—‚Æ‚·B

#include <stdio.h>
#include <math.h>

#define Num 1000

int main (void){
    int prinme[Num+1];
    int i, j, Limit;

    for(i=2; i <= Num; i++ ){
        prinme[i] = 1;
    }

    Limit = (int)sqrt( (double)Num );
     for(i = 2; i <= Limit; i++){
        if(prinme[i] == 1){
            for(j = 2*i; j<= Num; j+=i){
                if(j%i == 0){
                    prinme[j]=0;
                }
            }
        }
    }

    printf("\n‹‚ß‚ç‚ê‚½‘f”\n");
    for (i = 0; i <= Num; i++){
        if(prinme[i] == 1){
            printf("%5d", i);
        }
    }
    printf("\n");

}
    
    

