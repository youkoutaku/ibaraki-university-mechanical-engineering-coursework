#include <stdio.h>

int main( void )
{
  int a;

  for (a=1; a<=5; a++)  {
    printf("------- %d\n", a);
    switch (a)  {
      case 1:   /* a==1 ‚Ì‚Æ‚« */
        printf("a=1‚¾‚æ\n");
        break;
      case 3:   /* a==3 ‚Ì‚Æ‚« */
        printf("a=3‚¾‚æ\n");
        break;
      case 5:   /* a==5 ‚Ì‚Æ‚« */
        printf("a=5‚¾‚æ\n");
        break;
      default:   /* ‚»‚êˆÈŠO */
        printf("‚»‚Ì‘¼\n");
    }
  }

  return 0;
}

