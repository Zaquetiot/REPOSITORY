#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"
typedef struct tupla{
	char * token;
	char *linea_rest;
}TUPLA;

void ini_arbol(struct t_node ** Raiz){
	*Raiz=malloc(sizeof(struct t_node));
	struct t_node *aux=*Raiz;
	aux->children=NULL;
	aux->word=NULL;
	aux->callback=NULL;
}

/*void add_token(struct t_node ** Raiz,char *token,char *token_sig,char id){
	struct t_node Nodo=recorrer_arbol(Raiz,token)
}*/

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
	
TUPLA split(char * linea){
		TUPLA retorno;
		char * linea_rest;
		char *cond=strtok_r(linea," ",&linea_rest);
		retorno.linea_rest=linea_rest;
		if (cond==NULL){
			retorno.token=NULL;
			return retorno;
		}
		else{
			retorno.token=linea;
			return retorno;
		}
}
	

	
void def_commands(struct t_node ** Raiz){
	TUPLA tokens;
	char *c;
	c=malloc(sizeof(char)*256);
	int i,a;
	scanf("%d",&a);
	for (i = 0;i<a;i++){
		printf("\n>>");
		scanf(" %[^\n]s", c);
		do{
			tokens=split(c);
			if(tokens.token)printf("%s %s\n",tokens.token,tokens.linea_rest);
			c=tokens.linea_rest;
		}while(tokens.token);
		//arbol(Raiz,c,c[0]);
	}
}
		
int main(){
	struct t_node *Raiz=NULL;
	ini_arbol(&Raiz);
	def_commands(&Raiz);
	return 0;
}
