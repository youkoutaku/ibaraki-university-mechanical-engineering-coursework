//-----------------------------//
//          <ex7-1.c>          //
//	再起処理の簡単なプログラム //
//-----------------------------//
#include <stdio.h>

void func(int i);

int main(void)
{
	func(0);
	
	return 0;
}

void func(int i)
{
	if(i<3){
		printf("%d ",i);
		func(i+1);	//再起コール
	}
}