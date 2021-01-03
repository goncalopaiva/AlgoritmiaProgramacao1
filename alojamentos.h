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

typedef struct politica {
    char politica[MAX200];
    char plataforma[MAX200];
    char regras[MAX200];
} POLITICAS;

typedef struct estudio_politica {
    int estudio;
    POLITICAS *politica;
    char *regras[];
} ESTUDIO_POLITICAS;


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
    EVENTOS *evento;
    int nEventos;
} DIAS;

typedef struct agendas {
    char agenda[MAX200];
    DIAS *dia;
} AGENDAS;

typedef struct estudio {
    int estudio;
    int numero;
    int edificio;
    char configuracao[MAX10];
    int area;
    AGENDAS *agendas;
    ESTUDIO_POLITICAS *estudo_politicas;
} ESTUDIOS;

typedef struct edificio {
    int edificio;
    char nome[MAX200];
    float latitude;
    float longitude;
    char morada[MAX200];
    float preco_dia_m2; //Preco diario por m^2. Preço diario estudio=(preco_dia_m2 do edifico) x (area do estudio)
    int n_estudios;
    ESTUDIOS *estudios;
    struct edificio *pnext;
} EDIFICIOS;

typedef struct lote_edificios {
    char nome[MAX200];
    EDIFICIOS *pedificios;
    int nEdificios;
} LOTE_EDIFICIOS;



int main_projeto();


//----------------------EDIFICIOS--------------------------------------------------

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

/**
 * Função que lê um ficheiro csv de edificios.
 * @param lt - lote de edificios
 * @param filename - nome do ficheiro a ler
 */
void read_edificos_csv (LOTE_EDIFICIOS *lt, char filename[]);

/**
 * Função para encontrar um edificio num lote de edificios.
 * @param lt - lote de edificios
 * @param numeroEdificio - numero do edificio a encontrar
 * @return
 */
EDIFICIOS* find_edificios(LOTE_EDIFICIOS *lt, int numeroEdificio);

/**
 * Função que imprime para o ecrã os edificios de um lote de edificios.
 * @param lt - lote de edificios
 */
void print_edificios (LOTE_EDIFICIOS *lt);

//--------------------------ESTUDIOS--------------------------------------------------

/**
 * Função que insere um novo estudio.
 * @param lt - lote de edificios
 * @param edificio - edificio ao qual o estudio pertence
 * @param estudio - id do estudio
 * @param numero - numero do estudio
 * @param configuracao - configuração do estudio
 * @param area - area do estudio
 */
void insert_estudio(LOTE_EDIFICIOS *lt, int edificio, int estudio, int numero, char configuracao[], int area);

/**
 * Função que lê um ficheiro csv de estudios
 * @param lt - lote de edificios
 * @param filename - nome do ficheiro
 */
void read_estudios_csv (LOTE_EDIFICIOS *lt, char filename[]);

/**
 * Função para encontrar um estudio num lote de edificios
 * @param lt - lote de edificios
 * @param numeroEstudio - numero do estudio a encontrar
 * @return estudio procurado
 */
ESTUDIOS* find_estudios(LOTE_EDIFICIOS *lt, int numeroEstudio);

/**
 * Função que imprime para o ecrã os estudios de um lote de edificios
 * @param lt - lote de edificios
 */
void print_estudios (LOTE_EDIFICIOS *lt);

//-----------------------AGENDA----------------------------------------------------------


//-------------------------DIA----------------------------------------------------------


//-----------------------EVENTOS---------------------------------------------------------

void read_eventos_csv (DIAS *dt, char filename[]);

void insert_evento(DIAS *d, int id, const char *tipo, const char *data_inicio, const char *data_fim, int hospede, int estudio, const char *plataforma);

void print_eventos (DIAS *d);

//-------------------POLITICAS-----------------------------------------------------------


void insert_politicas (ESTUDIO_POLITICAS *ep, char politica[], char plataforma[], char regras[]);





#endif //PROJETOLPIAEDI_ALOJAMENTOS_H
