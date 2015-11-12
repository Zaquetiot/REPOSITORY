#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void f1(){
	printf("Hola mundo esta es la funcion 1");
}

void f2(){
	printf("hola mundo esta es la funcion 2"); 
}

void f3(){
	printf("hola mundo esta es la funcion 3");
}

void f4(){
	printf("hola mundo esta es la funcion 4");
}

void selecion_exec(char* id){       	//En el caso de la implementacion de 
	void(*p)();							//los callbacks, implementar en cada condicion una
	if(strcmp(id,"1")==0){				//una dereferenciacion del t_node a insertar
		p=f1;							//de tal modo de poder llegar al campo callback
		p();							//y hacer la asignacion correspondiente.
	}
	else if(strcmp(id,"2")==0){
		p=f2;
		p();
	}
	else if(strcmp(id,"3")==0){
		p=f3;
		p();
	}
	else if(strcmp(id,"4")==0){
		p=f4;
		p();
	}						
}								
	
int main(){
	char* id="1";
	printf("numero de funcion a llamar: ");
	selecion_exec(id);
	return 0;
}
