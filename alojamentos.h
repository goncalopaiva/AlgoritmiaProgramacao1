//
// Created by Goncalo on 11/13/2020.
//

#ifndef PROJETOLPIAEDI_ALOJAMENTOS_H
#define PROJETOLPIAEDI_ALOJAMENTOS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXEDIFICIOS 20
#define MAXESTUDIOS 200
#define MAXAGENDAS 200
#define MAXEVENTOS 500
#define MAXDIAS 100

#define MAX200 200
#define MAX10 12

typedef struct hospede {
    int id;
    char nome[MAX200];
    int numeroHospedes;
    struct hospede *pnext;
} HOSPEDES;

typedef struct politica {
    char politica[MAX200];
    char plataforma[MAX200];
    char regras[MAX200];
} POLITICAS;

typedef struct estudio_politica {
    int estudio;
    POLITICAS *politica;
    char *regras;
} ESTUDIO_POLITICAS;

typedef struct evento {
    int id;
    char tipo[MAX200];
    char data_inicio[MAX10];
    char data_fim[MAX10];
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
    int numDias;
    DIAS *dia;
} AGENDAS;

typedef struct estudio {
    int estudio;
    int numero;
    int edificio;
    char configuracao[MAX10];
    int area;
    int numAgendas;
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

/**
 * Função que guarda num ficheiro binario a informacao sobre os edificios de lote de edificios.
 * @param lt - lote de edificios
 * @param filename - nome do ficheiro
 */
void save_edificios_bin (LOTE_EDIFICIOS lt, char filename[]);

/**
 * Função que le um ficheiro binario de edificios e guarda num lote de edificios.
 * @param lt - lote de edificios
 * @param filename - nome do ficheiro
 */
void read_edificios_bin(LOTE_EDIFICIOS *lt, char filename[]);

/**
 * Função que edita um edificio
 * @param lt - lote edificios
 * @param numeroEdificio - numero do edificio
 * @param nome - novo nome do edificio
 * @param latitude - nova latitude do eficio
 * @param longitude - nova longitude do edificio
 * @param morada - nova morada do edificio
 * @param preco_dia_m2 - novo preco/dia/m2 do edificio
 */
void edit_edificios(LOTE_EDIFICIOS *lt, int numeroEdificio, char nome[MAX200], float latitude, float longitude, char morada[MAX200], float preco_dia_m2);

/**
 * Função que remove um edificio
 * @param lt - lote de edificio
 * @param numeroEdificio - numero do edificio
 */
void remove_edificio(LOTE_EDIFICIOS *lt, int numeroEdificio);

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
 * Função que lê um ficheiro csv de estudio
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

/**
 * Função que guarda num ficheiro binario a informacao sobre os edificios de lote de edificios.
 * @param lt - lote de edificios
 * @param filename - nome do ficheiro
 */
void save_estudios_bin (LOTE_EDIFICIOS lt, char filename[]);

//-----------------------AGENDA----------------------------------------------------------

/**
 * Função que insere uma nova agenda
 * @param lt - lote edificio
 * @param idEstudio - id do novo estudio
 * @param nomeAgenda - nome da nova agenda
 */
void insert_agenda (LOTE_EDIFICIOS *lt, int idEstudio, char nomeAgenda[]);

/**
 * Função que procura uma agenda
 * @param lt - lote de edificios
 * @param idEstudio - id do estudio a procurar
 * @param nomeAgenda - nome da agenda a procurar
 * @return AGENDAS
 */
AGENDAS* find_agenda (LOTE_EDIFICIOS *lt, int idEstudio, char nomeAgenda[]);

/**
 * Função que lê um ficheiro de agenda em binario
 * @param lt - lote de edificios
 * @param filename - nome do ficheiro a ler
 */
void read_agenda_bin (LOTE_EDIFICIOS *lt, char filename[]);

/**
 * Função que guarda um ficheiro de agendas em binario
 * @param lt - lote de edificios
 * @param idEstudio - id do estudio
 * @param filename - nome do ficheiro
 */
void save_agenda_bin (LOTE_EDIFICIOS lt, char filename[]);
//-------------------------DIA----------------------------------------------------------

/**
 * Função que procura um dia
 * @param pa - pointer agenda
 * @param dia - dia a procurar
 * @return DIAS
 */
DIAS* find_dia (AGENDAS *pa, char dia[MAX10]);

//-----------------------EVENTOS---------------------------------------------------------

/**
 * Função que lê um ficheiro csv de eventos
 * @param dt - pointer dias
 * @param filename - nome do ficheiro
 */
void read_eventos_csv (LOTE_EDIFICIOS *lt, char filename[]);

/**
 *
 * @param lt
 * @param id
 * @param tipo
 * @param data_inicio
 * @param data_fim
 * @param hospede
 * @param estudio
 * @param plataforma
 */
void insert_evento(LOTE_EDIFICIOS *lt, int id, char tipo[], char data_inicio[], char data_fim[], int hospede, int estudio, char plataforma[]);
/**
 * Função que imprime no ecra os eventos de um dia
 * @param d - pointer dia
 */
void print_eventos (LOTE_EDIFICIOS *lt);

/**
 * Função que procura um evento num determinado dia
 * @param pd - pointer dia
 * @param idEvento - id do evento a procurar
 * @return EVENTOS
 */
EVENTOS * find_evento (DIAS *pd, int idEvento);

/**
 * Função para editar um evento
 * @param pd - pointer dia
 * @param idEvento - id do evento a editar
 * @param tipo - novo tipo do evento
 * @param data_inicio - nova data incio
 * @param data_fim - nova data fim
 * @param hospede
 * @param estudio
 * @param plataforma
 */
void edit_evento (DIAS *pd, int idEvento, char tipo[MAX200], char data_inicio[], char data_fim[], int hospede, int estudio, char plataforma[]);

/**
 * Função que remove um evento
 * @param pd - pointer dia
 * @param idEvento - id do evento a remover
 */
void remove_evento (DIAS *pd, int idEvento);

//-------------------POLITICAS-----------------------------------------------------------

/**
 * Função que insere politicas
 * @param ep - pointer ESTUDIO_POLTICAS
 * @param politica - politica a adicionar
 * @param plataforma - plataforma a adicionar
 * @param regras - regras a adicionar
 */
void insert_politicas (ESTUDIO_POLITICAS *ep, char politica[], char plataforma[], char regras[]);


//---------------------HOSPEDES----------------------------------------------------------

/**
 * Função que insere um hospede novo
 * @param ph - lista ligada de hospedes
 * @param id - id do hospede a adicionar
 * @param nome - nome do hospede a adicionar
 */
void insert_hospede (HOSPEDES *ph, int id, char nome[]);

/**
 * Função que procura um hospede por id
 * @param ph - lista ligada de hospedes
 * @param idHospede - id do hospede a procurar
 * @return hospede encontrado
 */
HOSPEDES* find_hospede(HOSPEDES *ph, int idHospede);

/**
 * Função para editar hospedes
 * @param ph - pointer da lista ligada de hospedes
 * @param idHospede - id do hospede a editar
 * @param nome - novo nome hospede
 */
void edit_hospede(HOSPEDES *ph, int idHospede, char nome[MAX200]);

/**
 * Função que remove um hospede
 * @param ph - pointer da lista ligada de hospedes
 * @param idHospede - id do hospede a eliminar
 */
void remove_hospede(HOSPEDES *ph, int idHospede);




void insert_dia (AGENDAS *pa, char dia[MAX10]);

//--------------------

void relatorio_ecra(LOTE_EDIFICIOS *lt);

void relatorio_ficheiro(LOTE_EDIFICIOS *lt, char filename[]);

#endif //PROJETOLPIAEDI_ALOJAMENTOS_H
