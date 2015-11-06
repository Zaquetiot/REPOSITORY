#include <stdio.h>
#include <stdlib.h>

void truncar_archivo(char *nombre_archivo){  //lista
	FILE *input, *aux;
	char s[255];
	input = fopen(nombre_archivo,"r");
	if (input != NULL){
		while (fscanf(input,"%s",s)==1){
			
			aux = fopen(s,"w");
			fclose(aux);
			}
		fclose(input);
		}
	else printf("ERROR: No existe el archivo especificado");
	return;
}

void eliminar_archivo(char *nombre_archivo){ //lista
	FILE *input;
	char s[255];
	int eliminado=1;
	input = fopen(nombre_archivo,"r");
	if (input != NULL){
		while (fscanf(input, "%s",  s) == 1){
			eliminado = remove(s);
			if (eliminado != 0) printf("El archivo %s no existe",s);}
		fclose(input);}
	else {
		printf("ERROR: No existe el archivo especificado");
		fclose(input);}
	return;
}


void crear_archivo(char *nombre_archivo){ //lista
	FILE *input;
	char s[255]; 
	input = fopen(nombre_archivo, "r");
	if (input != NULL){
		while (fgets(s,255,input) != NULL){
			fclose(fopen(s,"w"));}
		fclose(input);}
	else printf("ERROR, No existe el archivo especificado");
	
	return;
}

void mostrar_por_linea(char *nombre_archivo){ //lista
	FILE *input, *output;
	char c[255], archivo[255];
	int indice, contador = 0;
	input = fopen(nombre_archivo,"r");
	if (input!= NULL){
		while(fscanf(input, "%s %d",archivo, &indice) ==2){
			output = fopen(archivo, "r");
			while (fgets(c,255,output) != NULL){
				contador = contador + 1;
				if (contador == indice) printf ("%s", c);}
				if (contador < indice) printf("ERROR, no se encontro la linea especificada");
			fclose(output);}}
	else printf("ERROR, no existe el archivo especificado");
	return;
}
	
void eliminar_por_linea(char *nombre_archivo){ //falta borrar archivo output y renombrar el temporal
	FILE *input, *output, *aux;
	char c[255], d[255];
	int indice=1, contador = 0, eliminado = 1, archivo_existe = 1;
	input = fopen(nombre_archivo,"r");
	while (fscanf(input, "%s %d", c, &indice) == 2){
		output = fopen(c,"r");
		aux = fopen("temporal.txt", "w");
		while(fgets(d,255,output) != NULL){
			contador = contador + 1;
			if (indice < 0){
				fclose(aux);
				aux = fopen("temporal.txt","a");
				fputs(d,aux);
				//fputs("\n",aux);
				fclose(aux);}
				
			if (contador != indice){
				fputs(d,  aux);
				fputs("\n", aux);}
		}	
		fclose(output);
		fclose(aux);
		archivo_existe = remove(c);
		if (archivo_existe != 0) printf("el archivo no existia");
		eliminado = rename("temporal.txt",c);
		if (eliminado == 0) printf("se reemplazo bien"); 
		if (contador < indice) printf("Linea %d no existe en el archivo %s", indice, c);
		else printf("%s", d);
			
	}
	fclose(input);
	return;
}
			
		
/*void eliminar_por_coincidencia(char *nombre_archivo){
	FILE *input, *output, *aux;
	char c[255], d[255];
	int indice=0;
	while (fscanf(input,"%s %d [^\n]s",c, indice,d) !=NULL){
			while (fscanf(input, "%s %d", c, indice) == 2){*/

