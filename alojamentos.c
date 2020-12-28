//
// Created by Goncalo on 11/13/2020.
//

#include "alojamentos.h"

struct EDIFICIOS* head;

int main_projeto(){

}

LOTE_EDIFICIOS create_lote (const char *pnomes[], int size) {
    LOTE_EDIFICIOS l = {NULL};
    for (int i=0; i<size; i++) {
        insert_edificio(&l, pnomes[i]);
    }
    return l;
}

void insert_edificio(LOTE_EDIFICIOS *pl, int edificio, const char *nome, float longitude, float latitude, const char *morada, float preco_dia_m2){
    EDIFICIOS *pp = (EDIFICIOS *) malloc (sizeof (EDIFICIOS));
    pp->edificio = edificio;
    pp->nome = (char *) malloc (strlen (nome));
    strcpy(pp->nome, nome);
    pp->longitude = longitude;
    pp->latitude = latitude;
    pp->morada = (char *) malloc (strlen (morada));
    strcpy(pp->nome, morada);
    pp->preco_dia_m2 = preco_dia_m2;

    pp->pnext = NULL;

    if (pl->pedificios == NULL) {
        pl->pedificios = pp;
        return;
    }

    EDIFICIOS *pcurrent = pl->pedificios;
    EDIFICIOS *pprev = NULL;

    while (pcurrent != NULL) {
        pprev = pcurrent;
        pcurrent = pcurrent->pnext;
    }
    pp->pnext = pcurrent;
    pprev->pnext = pp;

}

EDIFICIOS* find_edificios(LOTE_EDIFICIOS *lt, const char * nome_edificios) {
    EDIFICIOS *pp = lt->pedificios;
    while (pp != NULL) {
        if (strcmp(nome_edificios, pp->nome) == 0) {
            return pp;
        }
        pp=pp->pnext;
    }
    return NULL;
}

//função que altera/remove edificios


void insert_estudio(LOTE_EDIFICIOS *lt, char edificio[MAX200] ,int estudio, int numero, int edificio, char configuracao[MAX10], int area, POLITICAS politicas) {

    EDIFICIOS *ped = find_edificios(lt,edificio);

    ESTUDIOS *pes = (...);

    pes->estudio = estudio;
    pes->numero = numero;
    pes->edificio=edificio;
    strcpy(pes->configuracao, configuracao);
    pes->area=area;
    pes->politicas=politicas;

}



//funcao que insere estudios
//funcao que procura estudios
//funcao que altera/remove estudios

//funcao que insere hospede
//funcao que procura hospede
//funcao que altera/remove hospede

//funcao que insere politica preços
//funcao que procura politicas de preco
//funcao que altera/remove politicas preco

//funcao que insere/cria evento
//funcao que procura evento
//funcao que altera/remove evento



void print_edificios (EDIFICIOS *pedificio, int size) { //Otimização: sem o size
    printf("----->start print_edificios()\n");
    for (int i=0; i<size; i++) {
        printf("%d, %s, %f, %f, %s, %f\n", pedificio->edificio, pedificio->nome, pedificio->latitude, pedificio->longitude, pedificio->morada, pedificio->preco_dia_m2);
        pedificio=pedificio->pnext;
    }
    printf("end print_edificios()\n");
}



void print_estudios (ESTUDIOS *pestudios, int size) {
    printf("start print_estudios()\n");
    for (int i=0; i<size; i++) {
        printf("%d, %d, %d, %s, %d\n", pestudios->estudio, pestudios->numero, pestudios->edificio, pestudios->configuracao, pestudios->area);
    }
    printf("end print_estudios()\n");
}

