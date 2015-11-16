#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "split.h"
//FUNCIONES PARA EL MANEJO DE ARCHIVOS
void truncar_archivo(const char *nombre_archivo){  
	FILE *input, *aux;
	char s[255], db[255] = "db/";
	input = fopen(nombre_archivo,"r");
	if (input != NULL){
		while (fscanf(input,"%s",s)==1){
			strcat(db,s);
			aux = fopen(db,"w");
			fclose(aux);
			strcpy(db,"db/");
			}
		fclose(input);
		}
	else printf(">>>ERROR: No existe el archivo especificado");
	return;
}

void eliminar_archivo(const char *nombre_archivo){ 
	FILE *input;
	char s[255], db[255] = "db/";
	int eliminado=1;
	input = fopen(nombre_archivo,"r");
	if (input != NULL){
		while (fscanf(input, "%s",  s) == 1){
			strcat(db,s);
			eliminado = remove(db);
			strcpy(db,"db/");
			if (eliminado != 0) printf(">>>El archivo %s no existe",s);}
		fclose(input);}
	else {
		printf(">>>ERROR: No existe el archivo especificado");
		fclose(input);}
	return;
}

void crear_archivo(const char *nombre_archivo){ 
	FILE *input;
	char s[255], db[255] = "db/"; 
	input = fopen(nombre_archivo, "r");
	if (input != NULL){
		while (fgets(s,255,input) != NULL){
			strcat(db,s);
			fclose(fopen(db,"w"));
			strcpy(db,"db/");}
		fclose(input);}
	else printf(">>>ERROR, No existe el archivo especificado");
	return;
}

void mostrar_por_linea(const char *nombre_archivo){ 
	FILE *input, *output;
	char c[255], archivo[255],db[255] = "db/";
	int indice, contador = 0;
	input = fopen(nombre_archivo,"r");
	if (input!= NULL){
		while(fscanf(input, "%s %d",archivo, &indice) ==2){
			strcat(db,archivo);
			output = fopen(db, "r");
			contador = 0;
			strcpy(db,"db/");
			while (fgets(c,255,output) != NULL){
				contador = contador + 1;
				if (contador == indice) printf (">>>%s", c);}
				if (contador < indice) printf(">>>ERROR, no se encontro la linea especificada");
			fclose(output);}}
	else printf(">>>ERROR, no existe el archivo especificado");
	fclose(input);
	return;
}
	
void eliminar_por_linea(const char *nombre_archivo){ 
	FILE *input, *output, *aux;
	char c[255], d[255],db[255] = "db/";
	int indice=1, contador = 0, total = 0;
	input = fopen(nombre_archivo,"r");
	while (fscanf(input, "%s %d", c, &indice) == 2){
		strcat(db,c);
		output = fopen(db,"r");
		aux = fopen("db/temporal.txt","w");
		contador = 0;
		total = 0;
		while(fgets(d,255,output) != NULL) total = total + 1;
		fclose(output);
		output = fopen(db,"r");
		while(fgets(d,255,output) != NULL){
			contador = contador + 1;
			if ((indice > 0) && (contador != indice)) fputs(d,aux);
			if (indice < 0){
				if (contador != total) fputs(d,aux);
			}
			if (indice == contador) printf(">>>%s",d); 
		}
		if (contador < indice) printf(">>>Linea %d no existe en archivo %s", indice, c);
		fclose(output);
		fclose(aux);
		remove(db);
		rename("db/temporal.txt",db);
		strcpy(db,"db/");
	}
	fclose(input);
	return ;
}

void eliminar_por_coincidencia(const char *nombre_archivo){
	FILE *input, *output, *aux;
	char c[255], keyword[255],d[255],e[255], **sueltas, db[255] = "db/";
	size_t *num_tokens = malloc(sizeof(size_t));
	int indice = 0, largo = 0, i = 0, total_palabras = 0;
	input = fopen(nombre_archivo,"r");
	while (fscanf(input,"%s %d %s", c, &indice, keyword) == 3){
		strcat(db,c);
		output = fopen(db,"r");
		aux = fopen("db/temporal.txt", "w");
		while(fgets(d,255,output) != NULL){
			largo = strlen(d);
			strcpy(e,d);
			total_palabras = 1;
			for (i = 0; i<= largo; i++){
				 if (d[i] == ' ') total_palabras = total_palabras + 1;} 
			sueltas = split(d,largo,' ',num_tokens);
			printf("total palabras: %d || indice: %d\n", total_palabras, indice);
			if (indice > total_palabras){
				printf(">>>No existe el indice indicado\n");
				break;}
			if ((sueltas[indice] != NULL) && (strcmp(sueltas[indice],keyword) == 0)) continue;
			fputs(e,aux);
		}
		fclose(aux);
		fclose(output);
		remove(db);
		rename("db/temporal.txt",db);
		strcpy(db,"db/");
	}
	fclose(input);
	return;
}		
		
void insertar(const char *nombre_archivo){
	FILE *input, *output, *aux;
	char c[255], d[255], e[255],db[255] = "db/";
	int indice=1, contador = 0;
	float porcentaje = 0, agregados = 0, total_inputs = 0;
	input = fopen(nombre_archivo,"r");
	while (fscanf(input, "%s %d %[^\n]s", c, &indice, d) == 3){
		strcat(db,c);
		output = fopen(db,"r");
		contador = 0;
		total_inputs = total_inputs + 1;
		if (output == NULL) {	
			printf(">>>No existe el archivo %s \n",c);
			strcpy(db,"db/");
			continue;}
		else{	
		aux = fopen("db/temporal.txt","a");
		while (fgets(e,255,output) != NULL){
			contador = contador + 1;
			if (contador == indice) {
				fputs(d, aux);
				fputs("\n",aux);
				agregados = agregados + 1;}
			fputs(e,aux);
		}
		fclose(aux);
		fclose(output);
		remove(db);
		rename("db/temporal.txt",db);
		if (indice < 0){
			aux = fopen(db,"a");
			fputs(d,aux);
			fclose(aux);
			strcpy(db,"db/");
			agregados = agregados + 1;}
		strcpy(db,"db/");
	}
}
	fclose(input);
	porcentaje = (agregados / total_inputs) * 100;
	printf(">>>Se han insertado %d de %d registros (%.2f%%) satisfactoriamente", (int)agregados, (int)total_inputs, porcentaje);
	return ;
}

void terminar_programa(const char *nombre_archivo){
	FILE *input;
	char c[255];
	if (strcmp(nombre_archivo, "noargs") != 0){ 
		input = fopen(nombre_archivo,"r");
		while(fscanf(input," %[^\n]s", c) == 1) printf(">>>%s\n", c);
		fclose(input);
	}
	return;	
}
//HASTA AQUI LAS FUNCIONES DE MANEJO DE ARCHIVO.
