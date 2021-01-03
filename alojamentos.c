//
// Created by Goncalo on 11/13/2020.
//

#include "alojamentos.h"

//Edificio > Estudio > Agenda > Dia > Evento

int main_projeto(){
    printf("start main_projeto()\n");


    LOTE_EDIFICIOS l1 = {"Lote 1", NULL, 0};

    read_edificos_csv(&l1, "edificios.csv");
    print_edificios(&l1);

    read_estudios_csv(&l1, "estudios.csv");
    insert_estudio(&l1, 2, 1, 1, "AA", 10);
    print_estudios(&l1);

    ESTUDIOS *e1 = find_estudios(&l1, 8);

    printf("Estudio procurado: Estudio: %d Numero: %d Edificio: %d Configuracao: %s\n",e1->estudio, e1->numero, e1->edificio, e1->configuracao);

    printf("end main_projeto()\n");
}

//------------EDIFICIOS

EDIFICIOS* find_edificios(LOTE_EDIFICIOS *lt, int numeroEdificio) {
    //printf("opening find_edificios()\n");
    EDIFICIOS *pp = lt->pedificios;
        while (pp != NULL) {
        if (pp->edificio == numeroEdificio) {
            //printf("find_edificios(): edificio encontrado\n");
            //printf("closing find_edificios()\n");
            return pp;
        }
        pp=pp->pnext;
    }
    //printf("closing find_edificios()\n");
    return NULL;
} //A funcionar

void insert_edificio(LOTE_EDIFICIOS *pl, int edificio, const char *nome, float longitude, float latitude, const char *morada, float preco_dia_m2){
    printf("opening insert_edificio()\n");

    EDIFICIOS *novo = (EDIFICIOS *) malloc (sizeof(EDIFICIOS));
    novo->edificio = edificio;
    strcpy(novo->nome, nome);
    novo->longitude = longitude;
    novo->latitude = latitude;
    strcpy(novo->morada, morada);
    novo->preco_dia_m2 = preco_dia_m2;
    novo->n_estudios=0;
    novo->estudios = calloc (1, sizeof(ESTUDIOS));
    novo->pnext = NULL;

    if (pl->pedificios == NULL || pl->nEdificios == 0) {
        pl->pedificios = novo;
        (pl->nEdificios++);
        return;
    }
    EDIFICIOS *pcurrent = pl->pedificios, *pant = NULL;
    while (pcurrent != NULL /*&& strcmp(nome, pcurrent->nome) > 0*/) {
        pant = pcurrent;
        pcurrent = pcurrent->pnext;
    }
    if (pcurrent == pl->pedificios) { //HEAD
        novo->pnext = pcurrent;
        pl->pedificios = novo;
        (pl->nEdificios)++;
        return;
    }
    //TAIL E MIDDLE
    pant->pnext = novo;
    novo->pnext = pcurrent;
    pl->nEdificios++;
    printf("closing insert_edificio()\n");
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
    int field_count;

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
        printf("%d, %s, %f, %f, %s, %f \n",edificio, nome, longitude, latitude, morada, preco_dia_m2);
        insert_edificio(lt, edificio, nome, longitude, latitude, morada, preco_dia_m2);
        printf("%d\n", lt->nEdificios);
    }

    fclose(fp);
    printf("closing read_edificios_csv()\n");
} //A funcionar

void print_edificios (LOTE_EDIFICIOS *lt) {
    printf("opening print_edificios()\n");
    EDIFICIOS *pp = NULL;
    pp = lt->pedificios;
    printf("EDF.\t%-20s\tLATITUDE\tLONGITUDE\t%-20s\tPRECO/DIA/M2\n","NOME","MORADA");
    while (pp != NULL) {

        printf("%d\t%-20s\t%f\t%f\t%-20s\t%.2f\n", pp->edificio, pp->nome, pp->latitude, pp->longitude, pp->morada, pp->preco_dia_m2);
        //print_estudios(pp);
        pp = pp->pnext;
    }
    printf("closing print_edificios()\n");
} //A funcionar

//-------------ESTUDIOS

ESTUDIOS* find_estudios(LOTE_EDIFICIOS *lt, int numeroEstudio) {
    printf("opening find_estudios():\n");
    EDIFICIOS *pp = lt->pedificios;
    ESTUDIOS *pe = pp->estudios;
    while (pp != NULL) {
        for (int i = 0; i<pp->n_estudios; i++) {
            ESTUDIOS *pr = pe+i;
            if (pr->estudio == numeroEstudio) {
                printf("find_estudio(): estudio encontrado\n");
                printf("closing find_estudio()\n");
                return pr;
            }
        }
        pp = pp->pnext;
    }
    printf("closing find_estudios()\n");
    return NULL;
} //A funcionar

void read_estudios_csv (LOTE_EDIFICIOS *lt, char filename[]) {
    //estudio,numero,edificio,configuracao,area
    //printf("opening read_estudios_csv()\n");
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if ( (fp = fopen(filename, "r")) == NULL) {
        printf("read_estudios_csv(): Falha na abertura do ficheiro %s\n",filename);
        return;
    }

    int estudio, numero, edificio, area;
    char configuracao[3];

    char buff[1024];
    int row_count = 0;
    int field_count;

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
        //printf("%d, %d, %d, %s, %d \n",estudio, numero, edificio, configuracao, area);
        insert_estudio(lt, edificio, estudio, numero, configuracao, area);
    }

    fclose(fp);
    //printf("closing read_estudios_csv()\n");

} //A funcionar

void insert_estudio(LOTE_EDIFICIOS *lt, int edificio, int estudio, int numero, char configuracao[], int area) {
    //printf("opening insert_estudio()\n");

    EDIFICIOS *pp = find_edificios(lt, edificio); //Edificio em que vamos inserir o estudio

    if (pp == NULL) {
        printf("insert_estudio(): Erro. Edificio nao encontrado\n");
        return;
    }

    ESTUDIOS *pes = (pp->estudios) + pp->n_estudios;
    pes->estudio=estudio;
    pes->edificio=edificio;
    pes->numero=numero;
    strcpy(pes->configuracao, configuracao);
    pes->area = area;
    pes->estudo_politicas = NULL;
    pes->agendas = NULL;
    (pp->n_estudios)++;

    //printf("closing insert_estudio()\n");
} //A funcionar

void print_estudios (LOTE_EDIFICIOS *lt) {
    printf("start print_estudios()\n");
    EDIFICIOS *pe = lt->pedificios;
    printf("ESTUDIO\t\tNUMERO\t\tEDIFICIO\tCONFIGURACAO\tAREA\n");
    for (int i=0; i<lt->nEdificios; i++) {
        for (int j=0; j<pe->n_estudios; j++) {
            ESTUDIOS *pes = pe->estudios + j;
            printf("%d\t\t%d\t\t%d\t\t%s\t\t%d\n", pes->estudio, pes->numero, pes->edificio, pes->configuracao, pes->area);
        }
        pe=pe->pnext;
    }
    printf("end print_estudios()\n");
} //A funcionar

//------------POLITICAS

void read_politicas_csv(ESTUDIO_POLITICAS *pl, char filename[]) {
    //politca,plataforma,regras
    printf("opening read_politicas_csv()\n");
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if ( (fp = fopen(filename, "r")) == NULL) {
        printf("read_politicas_csv(): Falha na abertura do ficheiro %s\n",filename);
        return;
    }

    char politica[MAX200], plataforma[MAX200], regras[MAX200];

    char buff[1024];
    int row_count = 0;
    int field_count;

    while(fgets(buff, 1024, fp)) {

        field_count = 0;
        row_count++;
        if (row_count == 1) {
            continue; // Não ler a primeira linha
        }

        char *field = strtok(buff, ",");
        while (field) {
            if (field_count == 0) {
                strcpy(politica, field);
            }
            if (field_count == 1) {
                strcpy(plataforma, field);
            }
            if (field_count == 2) {
                strcpy(regras, field);
            }
            field = strtok(NULL, ",");
            field_count++;
        }
        //printf("%s, %s, %s\n",politica, plataforma, regras);
        insert_politicas(pl, politica, plataforma, regras);
    }

    fclose(fp);
    printf("closing read_politicas_csv()\n");

}

void insert_politicas (ESTUDIO_POLITICAS *ep, char politica[], char plataforma[], char regras[]) {
    printf("opening insert_politicas()\n");
    POLITICAS *pp = ep->politica;

    strcpy(pp->politica, politica);
    strcpy(pp->plataforma, plataforma);
    strcpy(pp->regras, regras);

    printf("closing insert_politicas()\n");
}


//-------------AGENDA



//-------------DIA



//-------------EVENTO

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

void read_eventos_csv (DIAS *dt, char filename[]) {
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
        insert_evento(dt, id, tipo, data_inicio, data_fim, hospede, estudio, plataforma);
    }

    fclose(fp);
    printf("closing read_eventos_csv()\n");
} //Terminar. Receber DIA ou entao mudar insert_eventos

void print_eventos (DIAS *d) {
    printf("opening print_eventos()\n");
    EVENTOS *ev = NULL;
    ev = d->evento;
    printf("ID\t\tTIPO\t\tDATA INICIO\t\tDATA FIM\t\tHOSPEDE\t\tESTUDIO\t\tPLATAFORMA\n");
    while (ev != NULL) {
        printf("%d\t\t%s\t\t%s\t\t%s\t\t%d\t\t%f\t\t%s\n");
        ev = ev->nextEvento;
    }
    printf("closing print_eventos()\n");
}

