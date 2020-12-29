//
// Created by Goncalo on 11/13/2020.
//

#include "alojamentos.h"

int main_projeto(){
    printf("start main_projeto()\n");


    EDIFICIOS e1 = {1, "PF Boavista", 41.162392, -8.655714, "Avenida da Boavista", 1.5};
    EDIFICIOS e2 = {2,"PF Riberia",41.140416,-8.612434,"Cais da Ribeira",1.8};
    EDIFICIOS e3 = {3,"PF Norte",41.15,-8.61024,"Rua do Norte",1.3};
    EDIFICIOS e4 = {4,"PF Santa Catarina",41.14638,-8.60705,"Rua Santa Catarina",1.7};
    e1.pnext = &e2;
    e2.pnext = &e3;
    e3.pnext = &e4;
    LOTE_EDIFICIOS l1 = {&e1};
    //print_edificios(&l1);



    printf("end main_projeto()\n");
}

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

void read_edificos_csv (LOTE_EDIFICIOS lt, char filename[]) {
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
        insert_edificio(&lt, edificio, nome, longitude, latitude, morada, preco_dia_m2);

    }

    fclose(fp);
    printf("closing read_edificios_csv()\n");
} //A funcionar

void print_edificios (LOTE_EDIFICIOS *lt) {
    printf("----->start print_edificios()\n");
    EDIFICIOS *pp = NULL;
    pp = lt->pedificios;
    printf("EDIFICIO\tNOME\t\t\tLATITUDE\tLONGITUDE\tMORADA\t\t\tPRECO/DIA/M2\n");
    while (pp != NULL) {

        printf("%d\t\t%s\t\t%f\t%f\t%s\t\t%f\n", pp->edificio, pp->nome, pp->latitude, pp->longitude, pp->morada, pp->preco_dia_m2);
        pp = pp->pnext;
    }
    printf("end print_edificios()\n");
} //A funcionar






void insert_edificio(LOTE_EDIFICIOS *pl, int edificio, const char *nome, float longitude, float latitude, const char *morada, float preco_dia_m2){
    printf("opening insert_edificio()\n");
    EDIFICIOS *pp = (EDIFICIOS *) malloc (sizeof (EDIFICIOS));
    printf("criado edicios pp\n");
    pp->edificio = edificio;
    strcpy(pp->nome, nome);
    pp->longitude = longitude;
    pp->latitude = latitude;
    strcpy(pp->nome, morada);
    pp->preco_dia_m2 = preco_dia_m2;
    printf("atribuidos os valores dados a pp\n");
    ESTUDIOS e = {0,0,0,"",0,"","",""};
    printf("criados o estudio e com valores 0\n");
    //pp->estudios = e;
    pp->pnext = NULL;
    printf("pp->estudios = e \n pp->pnext = NULL \n");
    if (pl->pedificios == NULL) {
        pl->pedificios = pp;
        return;
        printf("if (pl->pedificios == NULL \n\t pl->edificios = pp\n");
    }

    EDIFICIOS *pcurrent = pl->pedificios;
    printf("EDIFICIOS *pcurrent = pl->pedificios\n");
    EDIFICIOS *pprev = NULL;
    printf("EDIFICIOS *pprev = NULL;\n");
    while (pcurrent != NULL) {
        pprev = pcurrent;
        pcurrent = pcurrent->pnext;
        printf("While (pcurrent != NULL) \n\t pprev=pcurrent \n\t pcurrent = pcurrent->pnext\n");
    }
    pp->pnext = pcurrent;
    printf("pp->pnext = pcurrent\n");
    pprev->pnext = pp;
    printf("pprev->pnext = pp\n");
    printf("closing insert_edificio()\n");
}


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




//função que altera/remove edificios



/*

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
 */


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

