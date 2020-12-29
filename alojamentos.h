//
// Created by Goncalo on 11/13/2020.
//

#ifndef PROJETOLPIAEDI_ALOJAMENTOS_H
#define PROJETOLPIAEDI_ALOJAMENTOS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX200 200
#define MAX10 10
#define BUFFER_SIZE 1024


typedef struct politica {
    char politica[MAX200];
    char plataforma[MAX200];
    char regras[MAX200];
} POLITICAS;

typedef struct estudio_politica {
    int estudio;
    POLITICAS politica;
    char *regras[];
} ESTUDIO_POLITICAS;

//Rever estruturas politica e estudo_politica

typedef struct evento {
    int id;
    char tipo[MAX200];
    char data_inicio[MAX10]; //Mudar para data idk
    char data_fim[MAX10]; //Mudar para data idk
    int hospede;
    int estudio;
    char plataforma[MAX200];
    struct evento *nextEvento;
} EVENTOS;

typedef struct dia {
    char dia[MAX10];
    EVENTOS evento;
} DIAS;

typedef struct agendas {
    char agenda[MAX200];
    DIAS dia;
} AGENDAS;

typedef struct estudio {
    int estudio;
    int numero;
    int edificio;
    char configuracao[MAX10];
    int area;
    POLITICAS politicas;
} ESTUDIOS;

typedef struct edificio {
    int edificio;
    char nome[MAX200];
    float latitude;
    float longitude;
    char morada[MAX200];
    float preco_dia_m2; //Preco diario por m^2. Preço diario estudio=(preco_dia_m2 do edifico) x (area do estudio)
    struct edificio *pnext;
    ESTUDIOS estudios[];
} EDIFICIOS;

typedef struct lote_edificios {
    EDIFICIOS *pedificios;
} LOTE_EDIFICIOS;







int main_projeto();

/**
 * Dado um array de nomes de edificios, cria e inicia uma lista ligada de edificios.
 * @param pnomes - array de nomes de edificios
 * @param size - numero de edificios a serem inseridos
 * @return cópia do lote de edificios criado
 */
//LOTE_EDIFICIOS create_lote (const char *pnomes[], int size);

/**
 * Insere um novo edificio no lote de edificios já inicializado.
 * @param pl - pointer para o lote de edificios ja inicializado
 * @param edificio -
 * @param nome - nome do edificio a adicionar
 * @param longitude - longitude do edificio a adicionar
 * @param latitude - latitude do edificio a adicionar
 * @param morada - morada do edificio a adicionar
 * @param preco_dia_m2 - preco por dia por m^2 do edificio a adicionar
 */
void insert_edificio(LOTE_EDIFICIOS *pl, int edificio, const char *nome, float longitude, float latitude, const char *morada, float preco_dia_m2);

void read_edificos_csv (LOTE_EDIFICIOS lt, char filename[]);

void read_estudios_csv (LOTE_EDIFICIOS lt, char filename[]);

void read_eventos_csv (char filename[]);


EDIFICIOS* find_edificios(LOTE_EDIFICIOS *lt, const char * nome_edificios);

//void insert_estudio(LOTE_EDIFICIOS *lt, char edificio[MAX200] ,int estudio, int numero, int edificio, char configuracao[MAX10], int area, POLITICAS politicas);

void print_edificios (LOTE_EDIFICIOS *lt);

void print_estudios (EDIFICIOS pedificio, int size);


#endif //PROJETOLPIAEDI_ALOJAMENTOS_H
