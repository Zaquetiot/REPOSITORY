#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"

void ini_arbol(struct t_node ** Raiz){
	*Raiz=malloc(sizeof(struct t_node));
	struct t_node *aux=*Raiz;
	aux->children=NULL;
	aux->word=NULL;
	aux->callback=NULL;
}

void add_token(struct t_node ** Raiz,char *token,char *token_sig,char id){
	struct t_node Nodo=recorrer_arbol(Raiz,token)
}

void arbol(struct t_node ** Raiz,char *linea,char id){
	char *aux, *token_sig;
	
	if (strtok_r(linea," ", &token_sig) != NULL){
		if(strtok_r(token_sig, " ",&aux) ==NULL)token_sig=NULL;
		
		//add_token(linea,token_sig,id);
		//if(token_sig == NULL) printf("es un puntero");
		//if(token_sig == "hola") printf("es un string vacio");
		//printf("%s\n", token_sig);
		arbol(Raiz,aux,id);}
	else{
		return;}
	}
	

	
void def_commands(struct t_node ** Raiz){
	char c[256];
	int i,a;
	scanf("%d",&a);
	for (i = 0;i<a;i++){
		printf("\n>>");
		scanf(" %[^\n]s", c);
		
		arbol(Raiz,c,c[0]);

		
	}
}
		
int main(){
	struct t_node *Raiz=NULL;
	ini_arbol(&Raiz);
	def_commands(&Raiz);
	return 0;
}
