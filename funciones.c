#include "complex.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void init(){
    countMemory = 0;
    *complex_dynamic_memory = NULL;

    for(int i=0; i<10; i++){
        for(int j=0; j<2; j++){
            complex_static_memory[i][j]=0.0f;
        }
    }

}

/**
 * @brief reserva memoria para la parte dinamica de almacenamiento
 * 
 * @param n número de localidades a reservar
 * @return memory el apuntador a la zona de memoria reservada
 */
float **create_memory(int n){
    float** memory;
    memory = (float**)malloc(n*sizeof(float*));
    for(int i = 0; i<2; i++)
        memory[i] = (float*)malloc(2*sizeof(float));
    return memory;
}

/**
 * @brief sirve para cambiar el tamaño de la memorua dinamica
 * 
 * @param n número de elementos a incrementar o reducir
 * @return apuntador a la zona de memoria reservada
 */
float **resize(int n){
    int tam = countMemory-10 + n;
    float **memory;
    memory = (float**)realloc(complex_dynamic_memory, 2*tam*sizeof(float));
}

void delete_memory(float **mem){
    int tam = countMemory-10;
    for(int i = 0; i<tam; i++)
        free(mem[i]);
    free(mem);
}

void open_in_file(char *filename){
    in_file = fopen(filename, "r+");
    if(!in_file){
        print("No tienes permisos suficientes para abrir %s\n", filename);
    }
}

void open_out_file(char *filename){
    out_file = fopen(filename, "w");
    if(!out_file){
        printf("No tienes permisos para abrir %s\n", filename);
    }
}

void close_file(FILE *f){
    fclose(f);
}

void complex_read(float c[2]){
    if(in_file){
        fscanf(in_file, "%f\t%f", &c[0], &c[1]);
    } else{
        printf("NO hay archivo abierto\n");
    }
}

void complex_write(float c[2]){
    if(out_file){
        fprintf(out_file, "%f\t%f\n", c[0], c[1]);
    }else 
        printf("No hay archivo abierto\n");
}

void complex_scan(float c[2], float c2[2]){
    for(int i=0; i<2; i++){
        scanf("%f", &c[i]);
    }
    for(int j=0; j<2; j++){
        scanf("%f", &c2[j]);
    }
}

void complex_print(float c[2]){
    (c[1]>=0.0)?
        printf("%f+%fi\n", c[0], c[1]):
        printf("%f-%fi\n", c[0], c[1]);
}

float *complex_add(float c[2], float c2[2]){
    int cRes[2];
    complex_scan(c,c2);
    cRes[0]=c[0]+c2[0];
    cRes[1]=c[1]+c2[1];
    complex_print(cRes);
}

float *complex_sub(float c[2], float c2[2]){
    int cRes[2];
    complex_scan(c,c2);
    cRes[0]=c[0]-c2[0];
    cRes[1]=c[1]-c2[1];
    complex_print(cRes);
}

float *complex_con(float c[2], float c2[2]){
    int cRes[2];
    int cRes2[2];
    complex_scan(c,c2);
    cRes[0]=c[0];
    cRes[1]=c[1]*(-1);
    cRes2[0]=c2[0];
    cRes2[1]=c2[1]*(-1);
    complex_print(cRes);
    complex_print(cRes2);
}

float *complex_mul(float c[2], float c2[2]){
    int cRes[2];
    complex_scan(c,c2);
    cRes[0]=(c[0]*c2[0])-(c[1]*c2[1]);
    cRes[1]=(c[0]*c2[1])+(c[1]*c2[0]);
    complex_print(cRes);
}

float *complex_div(float c[2], float c2[2]){
    float cRes[2];
    complex_scan(c,c2);
    cRes[0]=((c[0]*c2[0])+(c[1]*c2[1]))/(pow(c2[1],2)+pow(c2[1],2));
    cRes[1]=((c[1]*c2[0])-(c[0]*c2[1]))/(pow(c2[1],2)+pow(c2[1],2));
    complex_print(cRes);
}
