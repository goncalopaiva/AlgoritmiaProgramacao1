//
// Created by Goncalo on 11/13/2020.
//

#include "alojamentos.h"

int main_projeto(){
    printf("start main_projeto()\n");


    LOTE_EDIFICIOS l1;
    strcpy(l1.nome, "Lote 1");

    read_edificos_csv(&l1, "edificios.csv");

    print_edificios(&l1);

    printf("end main_projeto()\n");
}


void insert_edificio(LOTE_EDIFICIOS *pl, int edificio, const char *nome, float longitude, float latitude, const char *morada, float preco_dia_m2){
    printf("opening insert_edificio()\n");

    EDIFICIOS *novo = (EDIFICIOS *) malloc (sizeof(EDIFICIOS));
    novo->edificio = edificio;
    strcpy(novo->nome, nome);
    novo->longitude = longitude;
    novo->latitude = latitude;
    strcpy(novo->morada, morada);
    novo->preco_dia_m2 = preco_dia_m2;
    novo->pnext = NULL;

    if (pl->pedificios == NULL || pl->nEdificios == 0) {
        pl->pedificios = novo;
        pl->nEdificios++;
        return;
    }
    EDIFICIOS *pcurrent = pl->pedificios, *pant = NULL;
    while (pcurrent != NULL && strcmp(nome, pcurrent->nome) > 0) {
        pant = pcurrent;
        pcurrent = pcurrent->pnext;
    }
    if (pcurrent == pl->pedificios) { //HEAD
        novo->pnext = pcurrent;
        pl->pedificios = novo;
        pl->nEdificios++;
        return;
    }
    //TAIL E MIDDLE
    pant->pnext = novo;
    novo->pnext = pcurrent;
    pl->nEdificios++;
    printf("closing insert_edificio()\n");
} //A funcionar

EDIFICIOS* find_edificios(LOTE_EDIFICIOS *lt, const char * nome_edificios) {
    printf("opening find_edificios()\n");
    EDIFICIOS *pp = lt->pedificios;
    while (pp != NULL) {
        if (strcmp(nome_edificios, pp->nome) == 0) {
            printf("find_edificios(): edificio encontrado\n");
            return pp;
        }
        pp=pp->pnext;
    }
    printf("closing find_edificios()\n");
    return NULL;
} //A funcionar

void read_edificos_csv (LOTE_EDIFICIOS *lt, char filename[]) {
    //edificio,nome,latitude,longitude,morada,preço_dia_m2
    printf("opening read_edificios_csv()\n");
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if ( (fp = fopen(filename, "r")) == NULL) {
        printf("read_edificios_csv(): Falha na abertura do ficheiro %s\n",filename);
        return;
    }

    int edificio;
    char nome[MAX200], morada[MAX200];
    float latitude, longitude, preco_dia_m2;

    char buff[1024];
    int row_count = 0;
    int field_count = 0;

    while(fgets(buff, 1024, fp)) {

        field_count = 0;
        row_count++;
        if (row_count == 1) {
            continue; // Não ler a primeira linha
        }

        char *field = strtok(buff, ",");
        while (field) {
            if (field_count == 0) {
                edificio = atoi(field);
            }
            if (field_count == 1) {
                strcpy(nome, field);
            }
            if (field_count == 2) {
                latitude = atof(field);
            }
            if (field_count == 3) {
                longitude = atof(field);
            }
            if (field_count == 4) {
                strcpy(morada, field);
            }
            if (field_count == 5) {
                preco_dia_m2 = atof(field);
            }
            field = strtok(NULL, ",");
            field_count++;
        }
        //printf("%d, %s, %f, %f, %s, %f \n",edificio, nome, longitude, latitude, morada, preco_dia_m2);
        insert_edificio(lt, edificio, nome, longitude, latitude, morada, preco_dia_m2);

    }

    fclose(fp);
    printf("closing read_edificios_csv()\n");
} //A funcionar

void print_edificios (LOTE_EDIFICIOS *lt) {
    printf("opening print_edificios()\n");
    EDIFICIOS *pp = NULL;
    pp = lt->pedificios;
    printf("EDIFICIO\tNOME\t\tLATITUDE\tLONGITUDE\tMORADA\t\tPRECO/DIA/M2\n");
    while (pp != NULL) {

        printf("%d\t\t%s\t\t%f\t%f\t%s\t\t%f\n", pp->edificio, pp->nome, pp->latitude, pp->longitude, pp->morada, pp->preco_dia_m2);
        pp = pp->pnext;
    }
    printf("closing print_edificios()\n");
} //A funcionar


void insert_evento(DIAS *d, int id, const char *tipo, const char *data_inicio, const char *data_fim, int hospede, int estudio, const char *plataforma) {
    printf("opening insert_evento()\n");

    EVENTOS *novo = (EVENTOS *) malloc (sizeof(EVENTOS));
    novo->id = id;
    strcpy(novo->tipo, tipo);
    strcpy(novo->data_inicio, data_inicio);
    strcpy(novo->data_fim, data_fim);
    novo->hospede = hospede;
    novo->estudio = estudio;
    strcpy(novo->plataforma, plataforma);
    novo->nextEvento = NULL;

    if (d->evento == NULL || d->nEventos == 0) {
        d->evento = novo;
        d->nEventos++;
    }
    EVENTOS *pcurrent = d->evento, *pant = NULL;
    while (pcurrent != NULL) {
        pant = pcurrent;
        pcurrent = pcurrent->nextEvento;
    }
    if (pcurrent == d->evento) {
        novo->nextEvento = pcurrent;
        d->evento = novo;
        d->nEventos++;
        return;
    }
    pant->nextEvento = novo;
    novo->nextEvento = pcurrent;
    d->nEventos++;
    printf("closing insert_evento()");
} //Verificar se funciona


void read_estudios_csv (LOTE_EDIFICIOS lt, char filename[]) {
    //estudio,numero,edificio,configuracao,area
    printf("opening read_estudios_csv()\n");
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if ( (fp = fopen(filename, "r")) == NULL) {
        printf("read_estudios_csv(): Falha na abertura do ficheiro %s\n",filename);
        return;
    }

    int estudio, numero, edificio, area;
    char configuracao[MAX10];

    char buff[1024];
    int row_count = 0;
    int field_count = 0;

    while(fgets(buff, 1024, fp)) {

        field_count = 0;
        row_count++;
        if (row_count == 1) {
            continue; // Não ler a primeira linha
        }

        char *field = strtok(buff, ",");
        while (field) {
            if (field_count == 0) {
                estudio = atoi(field);
            }
            if (field_count == 1) {
                numero = atoi(field);
            }
            if (field_count == 2) {
                edificio = atoi(field);
            }
            if (field_count == 3) {
                strcpy(configuracao, field);
            }
            if (field_count == 4) {
                area  = atoi(field);
            }
            field = strtok(NULL, ",");
            field_count++;
        }
        printf("%d, %d, %d, %s, %d \n",estudio, numero, edificio, configuracao, area);
        //insert_estudio();
    }

    fclose(fp);
    printf("closing read_estudios_csv()\n");

} //Terminar

void read_eventos_csv (char filename[]) {
    //id,tipo,data_inicio,data_fim,hospede,estudio,plataforma
    printf("opening read_eventos_csv()\n");
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if ( (fp = fopen(filename, "r")) == NULL) {
        printf("read_eventos_csv(): Falha na abertura do ficheiro %s\n",filename);
        return;
    }

    int id, hospede, estudio;
    char tipo[MAX200], data_inicio[MAX200], data_fim[MAX200], plataforma[MAX200];

    char buff[1024];
    int row_count = 0;
    int field_count = 0;

    while(fgets(buff, 1024, fp)) {

        field_count = 0;
        row_count++;
        if (row_count == 1) {
            continue; // Não ler a primeira linha
        }

        char *field = strtok(buff, ",");
        while (field) {
            if (field_count == 0) {
                id = atoi(field);
            }
            if (field_count == 1) {
                strcpy(tipo, field);
            }
            if (field_count == 2) {
                strcpy(data_inicio, field);
            }
            if (field_count == 3) {
                strcpy(data_fim, field);
            }
            if (field_count == 4) {
                hospede = atoi(field);
            }
            if (field_count == 5) {
                estudio = atoi(field);
            }
            if (field_count == 6) {
                strcpy(plataforma, field);
            }
            field = strtok(NULL, ",");
            field_count++;
        }
        printf("%d, %s, %s, %s, %d, %d, %s \n",id, tipo, data_inicio, data_fim, hospede, estudio, plataforma);
        //insert_evento();
    }

    fclose(fp);
    printf("closing read_eventos_csv()\n");
} //Terminar




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






void print_estudios (EDIFICIOS pedificio, int size) {
    printf("start print_estudios()\n");
    printf("ESTUDIO\tNUMERO\tEDIFICIO\tCONFIGURACAO\tAREA\n");
    ESTUDIOS *pp = NULL;
    pp = pedificio.estudios;
    for (int i=0; i<size; i++) {
        printf("%d\t\t%d\t\t%d\t\t%s\t\t%d\n", pp[i].estudio, pp[i].numero, pp[i].edificio, pp[i].configuracao, pp[i].area);
    }
    printf("end print_estudios()\n");
}

