#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"
#include "funciones.h"

typedef struct tok{
	char *token;
	struct tok * sig;
}TOKEN;

//SECCION CALLBACKS
void insertar_callback(struct t_node **Hijo,char *id){          
	if(strcmp(id,"0")==0)(*Hijo)->callback=terminar_programa;
	if(strcmp(id,"1")==0)(*Hijo)->callback=insertar;                             
	if(strcmp(id,"2")==0)(*Hijo)->callback=eliminar_por_linea;
	if(strcmp(id,"3")==0)(*Hijo)->callback=eliminar_por_coincidencia;
	if(strcmp(id,"4")==0)(*Hijo)->callback=mostrar_por_linea;
	if(strcmp(id,"5")==0)(*Hijo)->callback=crear_archivo;
	if(strcmp(id,"6")==0)(*Hijo)->callback=eliminar_archivo;
	if(strcmp(id,"7")==0)(*Hijo)->callback=truncar_archivo;
}
//TERMINO SECCION CALLBACKS
//SECCION DE MANEJO DEL ARBOL
void elim_arbol(struct t_node **Raiz){
	struct l_node *aux;
	while((*Raiz)->children){
		aux=(*Raiz)->children;
		if((*Raiz)->children->data->children==NULL){
			free((*Raiz)->children->data->word);
			free((*Raiz)->children->data);
			(*Raiz)->children=aux->next;
			free(aux);
		}
		else{
			elim_arbol(&(aux->data));
		}
	}
}
//AGREGA LOS L_NODE
void agregar_l_node(struct l_node **lista,struct t_node *hijo){
	struct l_node *NewNodo,*aux;
	NewNodo=(struct l_node*)malloc(sizeof(struct l_node));
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
//AGREGA TOKENS A LA LISTA DE TOKENS
void agregar_token(TOKEN **linea,char *token){
	TOKEN *NewNodo,*aux;
	NewNodo=(TOKEN*)malloc(sizeof(TOKEN));
	NewNodo->token=(char*)malloc(sizeof(char)*256);
	strcpy(NewNodo->token,token);
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
//ELIMINA LA LISTA DE TOKENS
void clear(TOKEN **linea){
	TOKEN *aux;
	while(*linea){
		aux=*linea;
		free(aux->token);
		*linea=aux->sig;
		free(aux);
	}
}
//DIVIDE UN STRING EN TOKENS
TOKEN *split_tokens(char *linea){
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
//HACE LA RAIZ DEL ARBOL
struct t_node *ini_arbol(){
	struct t_node *Raiz;
	Raiz=(struct t_node*)malloc(sizeof(struct t_node));
	struct t_node *aux=Raiz;
	aux->children=NULL;
	aux->word=NULL;
	aux->callback=NULL;
	return Raiz;
}
//INSERTA UN HIJO A UN NODO
struct t_node *insertar_hijo(struct t_node **padre,char * token){
	struct t_node *Padre=*padre;
	struct t_node *Hijo=malloc(sizeof(struct t_node));
	Hijo->word=(char*)malloc(sizeof(char)*256);
	strcpy(Hijo->word,token);
	Hijo->children=NULL;
	Hijo->callback=NULL;
	agregar_l_node(&(Padre->children),Hijo);
	return Hijo;

}
//REOCORRE EL ARBOL EN BUSQUEDA DE TOKENS
struct t_node *recorrer_arbol_def(struct t_node **ubicacion,char *token,char *ult_token,char *id){
	struct t_node *Nodo_A=*ubicacion;
	struct l_node *Nodo_L=Nodo_A->children;
	struct l_node *aux=Nodo_L;
	while(aux){
		if(strcmp(aux->data->word,token)==0)return aux->data;
		aux=aux->next;
	}
	return insertar_hijo(ubicacion,token);
}
//AÑADE LOS TOKENS AL ARBOL
void add_tokens(TOKEN *lista,struct t_node **Raiz){
	struct t_node *ubicacion=*Raiz;
	char *id,*ult_token;
	TOKEN *aux=lista;
	while(aux->sig)aux=aux->sig;
	id=lista->token;
	ult_token=aux->token;
	lista=lista->sig;
	while(lista){
		ubicacion=recorrer_arbol_def(&ubicacion,lista->token,ult_token,id);
		if(strcmp(ubicacion->word,ult_token)==0)insertar_callback(&ubicacion,id);
		lista=lista->sig;
	}
}
//RECIBE LA RESPUESTA DEL USARIO Y LO ALMACENA
struct t_node *def_comandos(){
	TOKEN *lista;
	struct t_node *Raiz=ini_arbol();
	char *c,*aux;
	c=(char*)malloc(sizeof(char)*256);
	aux=c;
	int i,a;
	scanf("%d",&a);
	for (i = 0;i<a;i++){
		printf("\n>>");
		scanf(" %[^\n]s", c);
		lista=split_tokens(c);
		add_tokens(lista,&Raiz);
		clear(&lista);
	}
	free(aux);
	return Raiz;
}
//RECORRE EL ARBOL EN BUSQUEDA DE LOS CALLBACK EN BASE LOS TOKENS INGRESADOS AL ARBOL
struct t_node *recorrer_arbol_pet(struct t_node **Raiz,TOKEN **lista,char *linea,struct t_node *ubicacion,char *token,TOKEN *antepenultimo){
	struct l_node *Nodo_L=ubicacion->children;
	struct l_node *aux=Nodo_L;
	char *ult_token=antepenultimo->token;
	const char *archivo=(const char*)antepenultimo->sig->token;
	while(aux){
		if(strcmp(aux->data->word,token)==0){
			if(strcmp(aux->data->word,ult_token)==0){
				if(aux->data->callback){
					(aux->data->callback)(archivo);
					if((aux->data->callback)==terminar_programa){
						elim_arbol(Raiz);
						free(*Raiz);
						clear(lista);
						free(linea);
						exit(0);
					}
					return NULL;
				}
				else{
					printf(">>>No esta definido este comando\n");
					return NULL;
				}
			}
			return aux->data;
		}
		aux=aux->next;
	}
	printf(">>>No esta definido este comando\n");
	return NULL;
}
//ESPERA RESPUESTA DEL USUARIO PARA LLAMAR LOS CALLBACKS
void peticion_comandos(struct t_node **Raiz){
	struct t_node *ubicacion;
	TOKEN *lista,*lista_aux1,*lista_aux2;
	char *c,*aux;
	c=(char*)malloc(sizeof(char)*256);
	aux=c;
	while(1){
		printf("\n>");
		scanf(" %[^\n]s", c);
		lista=split_tokens(c);
		lista_aux1=lista;
		if(!lista->sig){
			printf(">>>No esta definido el comando, obs:como minimo debe haber dos tokens");
			continue;
		}
		while(lista_aux1->sig->sig)lista_aux1=lista_aux1->sig;
		ubicacion=*Raiz;
		lista_aux2=lista;
		while(lista_aux2&&ubicacion){
				ubicacion=recorrer_arbol_pet(Raiz,&lista,aux,ubicacion,lista_aux2->token,lista_aux1);
				lista_aux2=lista_aux2->sig;
		}
		clear(&lista);
	}
	free(aux);
}

void recorrer_en_prof(struct t_node *ubicacion){
	struct l_node *aux=ubicacion->children;
	while(aux){
		printf("%s %p %p %p\n",aux->data->word,aux->data->word,aux->data->children,aux->data->callback);
		recorrer_en_prof(aux->data);
		aux=aux->next;
	}
}

int main(){
    struct t_node *Raiz;
    Raiz=def_comandos();
    recorrer_en_prof(Raiz);
    peticion_comandos(&Raiz);
    return 0;
}
