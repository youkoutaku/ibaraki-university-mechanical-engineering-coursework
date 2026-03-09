//‰Û‘è2 ‚¶‚á‚ñ‚¯‚ñƒvƒƒOƒ‰ƒ€
//20T1126N YANG GUANGZE(—kL‘ò)

#include <stdio.h>
#include <time.h>

void text(int a, int b){
    if(a == 0){
        printf("Cumputer=");
    }else{
        printf("You=");
    }
    switch (b)
        {
        case 0:
            printf("rock");
            break;
        case 1:
            printf("Scissors");
            break;
        case 2:
            printf("Paper");
            break;
        default:
            break;
        }
    printf("\t");
}

int main(void){
    int i = 0;
    int u_hand;

    do{
        srand( time(0) );
        int c_hand = rand()%3;
        printf("Your hand ( 0:Rock / 1:Scissors / 2:Paper ) ? ");
        scanf("%d",&u_hand);
        text( 0,c_hand );
        text( 1,u_hand );
        printf("\n");

        if( ( u_hand+1 ) % 3 == c_hand ){
            i = 1;
        }else{
            i = -1;
        }
        if( u_hand == c_hand ){
            i=0;
            printf("Draw\n");
        }
        
    }while(i == 0);
    if(i == 1){
        printf("You Win.\n");
    }else{
        printf("You lose.\n");
    }
    return 0;
}