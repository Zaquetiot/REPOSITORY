#include <stdio.h>

void console(char *linea){
	printf(">> ");
	scanf("%[^\n]",linea);
	/*printf("%s\n",linea);*/
}

int main(){
	char linea[256];
	for(int i=0;i<3;i++){
		console(linea);
		
	}
	return 0;
}
