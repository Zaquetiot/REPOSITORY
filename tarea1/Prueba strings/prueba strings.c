#include <stdio.h>
#include <stdlib.h>

typedef struct frase{
	char caracter;
	char * sig;
}COMMAND;

void agregar_caracter(COMMAND **linea,char c){
	COMMAND *NewNodo,*aux;
	NewNodo=malloc(sizeof(COMMAND));
	NewNodo->caracter=c;
	NewNodo->sig=NULL;
	aux=*linea;
	if(aux==NULL){
		*linea=NewNodo;
	}
	else{
		for(;aux->sig!=NULL;aux=aux->sig)aux->sig=NewNodo;
	}
}

void clear(COMMAND **linea){
	COMMAND *aux;
	while(*linea){
		aux=*linea;
		*linea=*linea->sig;
		free(aux);
	}
}

void print(COMMAND * linea){
	while(linea->sig)putchar(linea->caracter);
}

COMMAND *read(){
	COMMAND *linea=NULL;
	char c;
	while((c=getchar())!='\n'){
		agregar_caracter(&linea,c);
	}
	return linea;
}
int main(){
	while(1){
		printf(">>");
		COMMAND *linea=read();
		/*poner en el arbol*/
		print(linea);
		clear(&linea);
	}
return 0;
}

