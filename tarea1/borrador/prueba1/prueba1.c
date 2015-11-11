#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tok{
	char *token;
	struct tok * sig;
}TOKEN;

struct l_node;

struct t_node
{
    struct l_node *children;
    char *word;
    void (*callback)(const char *);
};

struct l_node
{
    struct t_node *data;
    struct l_node *next;
};

void agregar_token(TOKEN **linea,char *token){
	TOKEN *NewNodo,*aux;
	NewNodo=malloc(sizeof(TOKEN));
	NewNodo->token=token;
	NewNodo->sig=NULL;
	aux=*linea;
	if(aux==NULL){
		*linea=NewNodo;
	}
	else{
		while(aux->sig)aux=aux->sig;
		aux->sig=NewNodo;
	}
}

void clear(TOKEN **linea){
	TOKEN *aux;
	while(*linea){
		aux=*linea;
		*linea=aux->sig;
		free(aux);
	}
}

/*typedef struct tupla{
	char * token;
	char *linea_rest;
}TUPLA;

TUPLA split(char * linea){
		TUPLA retorno;
		char *linea_rest;
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
}*/

TOKEN *split(char *linea){
   TOKEN *lista=NULL;
   char *token;
   
   /* get the first token */
   token = strtok(linea," ");
   
   /* walk through other tokens */
   while( token != NULL ){
		agregar_token(&lista,token);
		token = strtok(NULL," ");
	}
   return lista;
}

void recorre(TOKEN *linea){
	while(linea){
		printf("%s\n",linea->token);
		linea=linea->sig;
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
/*char *ult_token(char *linea){
	TUPLA tokens;
	tokens.linea_rest=linea;
	char *comp;
	comp="";
	while(1){
		tokens=split(tokens.linea_rest);
		if(strcmp(tokens.linea_rest,comp)==0)return tokens.token;
	}
	
}*/
/*void descomponer(char *linea,char *prim_token){
 * 
	TUPLA tokens;
	char *ult_token="";
	while(1){
			tokens=split(linea);
			if(tokens.token)printf("%s %s\n",tokens.token,tokens.linea_rest);
			printf("%p %p\n",tokens.token,tokens.linea_rest);
			linea=tokens.linea_rest;
			if(strcmp(tokens.linea_rest,ult_token)==0){
			ult_token=tokens.token;
			}
			if(tokens.token==NULL)break;
		}
		printf("%s %s\n",prim_token,ult_token);
}
*/

struct t_node *add_tokens(TOKEN *lista){
	struct t_node *Raiz=ini_raiz();
	struct t_node *ubicacion=Raiz;
	while(lista){
		ubicacion=recorrer_arbol(&ubicacion,lista->token,);
		lista->sig;
	}
}

void def_commands(){     //dudas en limpieza de memoria(memory leak)
	char *c,*aux;
	c=malloc(sizeof(char)*256);
	aux=c;
	int i,a;
	scanf("%d",&a);
	for (i = 0;i<a;i++){
		printf("\n>>");
		scanf(" %[^\n]s", c);
		TOKEN *lista=split(c);
		struct t_node *Raiz=add_tokens(lista);
		recorre(lista);
		clear(&lista);
		//ultimo_token=ult_token(c);
		//printf("%s\n",ultimo_token);
		
		
		/*do{
			tokens=split(c);
			if(tokens.token)printf("%s %s\n",tokens.token,tokens.linea_rest);
			printf("%p %p\n",tokens.token,tokens.linea_rest);
			c=tokens.linea_rest;
			free(tokens.token);
			free(tokens.linea_rest)
		}while(tokens.token);*/
	}
	free(aux);
}

int main(){
    //struct t_node *Raiz=ini_arbol();
    //printf("children:%p, word:%p, callback:%p",Raiz->children,Raiz->word,Raiz->callback);
    def_commands();
    return 0;
}
