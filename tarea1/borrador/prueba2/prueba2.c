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

void f1(const char* archivo){
	printf("Hola mundo esta es la funcion 1 que analiza el %s",archivo);
}

void f2(const char *archivo){
	printf("hola mundo esta es la funcion 2 que analiza el %s",archivo);
}

void f3(const char *archivo){
	printf("hola mundo esta es la funcion 3 que analiza el %s",archivo);
}

void f4(const char *archivo){
	printf("hola mundo esta es la funcion 4 que analiza el %s",archivo);
}

void insertar_callback(struct t_node **Hijo,char *id){          
	struct t_node *Nodo=*Hijo;
	void (*p)(const char*);                                                 
	/*if(strcmp(id,"0")==0){
		p=f0;
		Nodo->callback=p;
	}*/
	
	if(strcmp(id,"1")==0)Nodo->callback=f1;                             
	else if(strcmp(id,"2")==0){
		p=f2;
		Nodo->callback=p;
	}
	else if(strcmp(id,"3")==0){
		p=f3;
		Nodo->callback=p;
	}
	else if(strcmp(id,"4")==0){
		p=f4;
		Nodo->callback=p;
	}
}

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

void clear(TOKEN **linea){
	TOKEN *aux;
	while(*linea){
		aux=*linea;
		free(aux->token);
		*linea=aux->sig;
		free(aux);
	}
}

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
	Raiz=(struct t_node*)malloc(sizeof(struct t_node));
	struct t_node *aux=Raiz;
	aux->children=NULL;
	aux->word=NULL;
	aux->callback=NULL;
	return Raiz;
}

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

struct t_node *def_comandos(){     //dudas en limpieza de memoria(memory leak)
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
		lista=split(c);
		add_tokens(lista,&Raiz);
		clear(&lista);
	}
	free(aux);
	return Raiz;
}

void recorrer_en_prof(struct t_node *ubicacion){
	struct l_node *aux=ubicacion->children;
	while(aux){
		printf("%s %p %p %p\n",aux->data->word,aux->data->word,aux->data->children,aux->data->callback);
		recorrer_en_prof(aux->data);
		aux=aux->next;
	}
}

struct t_node *recorrer_arbol_pet(struct t_node *ubicacion,char *token,TOKEN *antepenultimo){
	struct l_node *Nodo_L=ubicacion->children;
	struct l_node *aux=Nodo_L;
	char *ult_token=antepenultimo->token;
	const char *archivo=(const char*)antepenultimo->sig->token;
	printf("%s %s\n",ult_token,archivo);
	while(aux){
		if(strcmp(aux->data->word,token)==0){
			if(strcmp(aux->data->word,ult_token)==0){
				//printf("%s %p %p %p",aux->data->word,aux->data->word,aux->data->children,aux->data->callback);
				if(aux->data->callback){
					(aux->data->callback)(archivo);
					return NULL;
				}
				else{
					printf("No esta definido este comando\n");
					return NULL;
				}
			}
			return aux->data;
		}
		aux=aux->next;
	}
	printf("No esta definido este comando");
	return NULL;
}

void peticion_comandos(struct t_node *Raiz){
	struct t_node *ubicacion;
	TOKEN *lista,*lista_aux1,*lista_aux2;
	char *c,*aux;
	c=(char*)malloc(sizeof(char)*256);
	aux=c;
	while(1){
		printf("\n>");
		scanf(" %[^\n]s", c);
		lista=split(c);
		lista_aux1=lista;
		while(lista_aux1->sig->sig)lista_aux1=lista_aux1->sig;
		ubicacion=Raiz;
		lista_aux2=lista;
		while(lista_aux2&&ubicacion){
				ubicacion=recorrer_arbol_pet(ubicacion,lista_aux2->token,lista_aux1);
				lista_aux2=lista_aux2->sig;
		}
		clear(&lista);
	}
	free(aux);
}

int main(){
    //struct t_node *Raiz=ini_arbol();
    //printf("children:%p, word:%p, callback:%p",Raiz->children,Raiz->word,Raiz->callback);
    struct t_node *Raiz;
    Raiz=def_comandos();
    //recorrer_en_prof(Raiz);
    peticion_comandos(Raiz);
    return 0;
}

