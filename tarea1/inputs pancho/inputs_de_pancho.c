#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"

typedef struct tupla{
	char * token;
	char *linea_rest;
}TUPLA;

void add_node_list(struct l_node **lista,struct t_node *hijo){
	struct l_node *NewNodo,*aux;
	NewNodo=malloc(sizeof(struct l_node));
	NewNodo->data=hijo;
	NewNodo->next=NULL;
	aux=*lista;
	if(aux==NULL){
		*lista=NewNodo;
	}
	else{
		while(aux->next)aux=aux->next;
		aux->next=NewNodo;
	}
}

struct t_node *ini_arbol(){
	struct t_node *Raiz;
	Raiz=malloc(sizeof(struct t_node));
	struct t_node *aux=Raiz;
	aux->children=NULL;
	aux->word=NULL;
	aux->callback=NULL;
	return Raiz;
}

struct t_node *insertar_hijo(struct t_node **padre,char * token){
	struct t_node *Padre=*padre;
	struct t_node *Hijo=malloc(sizeof(struct t_node));
	Hijo->word=token;
	Hijo->children=NULL;
	Hijo->callback=NULL;
	add_node_list(&(Padre->children),Hijo);
	return Hijo;
	
}

struct t_node *recorrer_arbol(struct t_node** Raiz,char * token){
	struct t_node *Nodo_A=*Raiz;
	struct l_node *Nodo_L=Nodo_A->children;
	struct l_node *aux=Nodo_L;
	while(Nodo_L||aux){
		if(strcmp(aux->data->word,token)==0)return aux->data;
		aux=aux->next;
	}
	return insertar_hijo(&Nodo_A,token);//insertar hijos al Nodo_A, 
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

void add_token(char * linea,char id,char *ult_token){
	TUPLA tokens;
	tokens.token=NULL;
	tokens.linea_rest=linea;
	struct t_node *Raiz=ini_arbol();
	struct t_node *ubicacion=Raiz;
	do{
		tokens=split(tokens.linea_rest);
		ubicacion=recorrer_arbol(&ubicacion,tokens.token);
	}while(tokens.token);
}

void arbol(struct t_node ** Raiz,char *linea,char id){
	char *aux, *token_sig;
	
	if (strtok_r(linea," ", &token_sig) != NULL){
		if(strtok_r(token_sig, " ",&aux) ==NULL)token_sig=NULL;
		
		//add_token(linea,token_sig,id);
		//if(token_sig == NULL) printf("es un puntero");
		//if(token_sig == "hola") printf("es un string vacio");
		//printf("%s\n", token_sig);
		arbol(Raiz,aux,id);
	}
	else{
		return;}
}
	
void def_commands(struct t_node ** Raiz){
	TUPLA tokens;
	char *c,*aux;
	c=malloc(sizeof(char)*256);
	aux=c;
	int i,a;
	scanf("%d",&a);
	for (i = 0;i<a;i++){
		printf("\n>>");
		scanf(" %[^\n]s", c);
		do{
			tokens=split(c);
			/*aqui insertar token en el arbol*/
			if(tokens.token)printf("%s %s\n",tokens.token,tokens.linea_rest);
			c=tokens.linea_rest;
		}while(tokens.token);
		//arbol(Raiz,c,c[0]);
	}
	free(aux);
}
		
int main(){
	struct t_node *Raiz=NULL;
	def_commands(&Raiz);
	return 0;
}
