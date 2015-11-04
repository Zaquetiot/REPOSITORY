#include <stdio.h>
#include <stdlib.h>

void truncar_archivo(char *nombre_archivo){  //probar
	FILE *input;
	char s[255];
	input = fopen(nombre_archivo,"r");
	if (input != NULL){
		while (fgets(s, 255, input)!=NULL){
			fclose(fopen(s,"w"));}
		fclose(input);}
	else printf("ERROR: No existe el archivo especificado");
	return;
}

void eliminar_archivo(char *nombre_archivo){ //probar 
	FILE *input;
	char s[255];
	int eliminado=0;
	input = fopen(nombre_archivo,"r");
	if (input != NULL){
		while (fgets(s,255,input) != NULL){
			eliminado = remove(s);
			if (eliminado != 0) printf("El archivo %s no existe",s);}
		fclose(input);}
	else printf("ERROR: No existe el archivo especificado");

	return;
}

void crear_archivo(char *nombre_archivo){ //probar
	FILE *input, *output;
	char s[255]; 
	input = fopen(nombre_archivo, "r");
	if (input != NULL){
		while (fgets(s,255,input) != NULL){
			output = fclose(fopen(s,"w"));}
		fclose(input);}
	else printf("ERROR, No existe el archivo especificado");
	
	return;
}

void mostrar_por_linea(char *nombre_archivo){ //probar
	FILE *input, *output;
	char c[255], *archivo;
	int indice, contador = 0;
	input = fopen(nombre_archivo,"r");
	if (input!= NULL){
		while(fscanf(input, "%s %d",archivo, &indice) !=NULL){
			output = fopen(archivo, "r");
			while (fgets(c,255,output) != NULL){
				contador = contador + 1;
				if (contador == indice) printf ("%s", c);}
			printf("ERROR, no se encontro la linea especificada");
			fclose(output);}}
	else printf("ERROR, no existe el archivo especificado");
	return;
}
	
void eliminar_por_linea(char *nombre_archivo){
	FILE *input, *output, *aux;
	char c[255], d[255];
	int indice, contador = 0;
	input = fopen(nombre_archivo,"r");
	while (fscanf(input, "%s %d", c, indice) == 2){
		output = fopen(c,"r");
		aux = fopen("temporal.txt", "w");
		while(fgets(d,255,output) != NULL){
			contador = contador + 1;
			if (contador != indice){
				fputs(d,  aux);
				fputs("\n", aux);}
		}	
		fclose(output);
		if (contador < indice) printf("Linea %d no existe en el archivo %s", indice, c);
		else printf("%s", d);
	}
	fclose(input);
	return;
}			
		

