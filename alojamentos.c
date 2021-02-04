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

    read_estudios_csv(&l1,"estudios.csv");
    print_estudios(&l1);

    read_eventos_csv(&l1, "eventos_novo.csv");

    print_eventos(&l1);

    relatorio_ecra(&l1);

    relatorio_ficheiro(&l1, "relatorio.csv");

    save_agenda_bin(l1, "agenda_eventos.bin");

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
    novo->estudios = calloc (MAXESTUDIOS, sizeof(ESTUDIOS));
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

void save_edificios_bin (LOTE_EDIFICIOS lt, char filename[]) {
    printf("opening save_edificios_bin()\n");
    FILE *fp = NULL;
    fp = fopen(filename, "wb");
    if ( (fp = fopen(filename, "wb")) == NULL) {
        printf("save_edificios_bin(): Erro na abertura do ficheiro %s\n", filename);
        return;
    }
    int size = strlen(lt.nome) + 1;
    fwrite(&size, sizeof(size), 1, fp);
    fwrite(lt.nome, sizeof (char), size, fp);
    fwrite(&lt.nEdificios, sizeof(int), 1, fp);
    EDIFICIOS *pe = lt.pedificios;
    for (int i=0; i<lt.nEdificios; i++) {
        //int edificio, char nome, float latitude, float longitude, char morada, float preco_dia_m2, int n_estudios
        fwrite(&pe->edificio, sizeof(int), 1, fp);
        size = strlen(pe->nome+1);
        fwrite(&size, sizeof(size), 1, fp);
        fwrite(pe->nome, sizeof(char), size, fp);
        fwrite(&pe->latitude, sizeof(float), 1, fp);
        fwrite(&pe->longitude, sizeof(float), 1, fp);
        size = strlen(pe->morada+1);
        fwrite(&size, sizeof(size), 1, fp);
        fwrite(pe->morada, sizeof(char), size, fp);
        fwrite(&pe->preco_dia_m2, sizeof(float), 1, fp);
        fwrite(&pe->n_estudios, sizeof(int), 1, fp);
        pe = pe->pnext;
    }
    fclose(fp);
    printf("closing save_edificios_bin()\n");
}

void read_edificios_bin(LOTE_EDIFICIOS *lt, char filename[]) {
    printf("opening read_edificios_bin()\n");
    FILE *fp = NULL;
    fp = fopen(filename, "rb");
    if ( (fp = fopen(filename, "rb")) == NULL) {
        printf("read_edificios_bin(): Erro na abertura do ficheiro %s\n", filename);
        return;
    }
    int size = 0, numeroEdificos = 0;
    fread(&size, sizeof(size), 1, fp);
    fread(lt->nome, sizeof(char), size, fp);
    fread(&numeroEdificos, sizeof(int), 1, fp);
    EDIFICIOS *pe = lt->pedificios;
    for (int i=0; i<numeroEdificos; i++) {
        int edificio;
        char nome [MAX200], morada[MAX200];
        float longitude, latitude, preco_dia_m2;
        fread(&edificio, sizeof(int), 1, fp);
        fread(&size, sizeof(size), 1, fp);
        if (size > MAX200) {
            printf("Erro\n");
            return;
        }
        fread(nome, sizeof(char), size, fp);
        fread(&latitude, sizeof(float), 1, fp);
        fread(&longitude, sizeof(float), 1, fp);
        fread(&size, sizeof(size), 1, fp);
        if (size > MAX200) {
            printf("Erro\n");
            return;
        }
        fread(morada, sizeof(char), size, fp);
        fread(&longitude, sizeof(float), 1, fp);
        fread(&preco_dia_m2, sizeof(int), 1, fp);
        insert_edificio(lt, edificio, nome, longitude, latitude, morada, preco_dia_m2);
    }
    fclose(fp);
    printf("closing read_edificios_bin()\n");
}

void edit_edificios(LOTE_EDIFICIOS *lt, int numeroEdificio, char nome[MAX200], float latitude, float longitude, char morada[MAX200], float preco_dia_m2) {
    EDIFICIOS *pe = find_edificios(lt, numeroEdificio);
    strcpy(pe->nome, nome);
    pe->latitude = latitude;
    pe->longitude = longitude;
    strcpy(pe->morada, morada);
    pe->preco_dia_m2 = preco_dia_m2;
}

void remove_edificio(LOTE_EDIFICIOS *lt, int numeroEdificio) {
    EDIFICIOS *pant, *pcur, *pnext;
    pant = lt->pedificios;
    pcur = pant->pnext;
    pnext = pcur->pnext;

    if (pant->edificio == numeroEdificio) {
        lt->pedificios=pcur;
        lt->nEdificios = (lt->nEdificios)-1;
        return;
    }

    for (int i=0; i<lt->nEdificios; i++) {
        if (pcur->edificio == numeroEdificio) {
            pant->pnext = pnext;
            lt->nEdificios = (lt->nEdificios)-1;
            return;
        }
        pant = pcur;
        pcur = pnext;
        pnext = pnext->pnext;
    }
}

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
    pes->numAgendas = 0;
    pes->agendas = calloc (MAXAGENDAS, sizeof(AGENDAS));
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

void save_estudios_bin (LOTE_EDIFICIOS lt, char filename[]) {
    printf("opening save_estudios_bin()\n");
    FILE *fp = NULL;
    fp = fopen(filename, "wb");
    if ( (fp = fopen(filename, "wb")) == NULL) {
        printf("save_edificios_bin(): Erro na abertura do ficheiro %s\n", filename);
        return;
    }
    //int estudio, int numero, int edificio, char configuracao, int area
    EDIFICIOS *pe = lt.pedificios;
    for (int i=0; i<lt.nEdificios; i++) {
        int numeroEstudios = pe->n_estudios;
        for (int j=0; j<numeroEstudios; j++) {
            ESTUDIOS *pes = pe->estudios + j;
            fwrite(&pes->estudio, sizeof(int), 1, fp);
            fwrite(&pes->numero, sizeof(int), 1, fp);
            fwrite(&pes->edificio, sizeof(int), 1, fp);
            int size = strlen(pes->configuracao+1);
            fwrite(&size, sizeof(size), 1, fp);
            fwrite(pes->configuracao, sizeof(char), size, fp);
            fwrite(&pes->area, sizeof(int), 1, fp);
        }
        pe = pe->pnext;
    }
    fclose(fp);
    printf("closing read_estudios_bin()\n");
}

void edit_estudio (LOTE_EDIFICIOS *lt, int estudio, int numero, int edificio, char configurcao[MAX10], int area) {
    ESTUDIOS *pe = find_estudios(lt, estudio);
    pe->numero = numero;
    pe->edificio = edificio;
    strcpy(pe->configuracao, configurcao);
    pe->area = area;
}

void remove_estudio (LOTE_EDIFICIOS *lt, int numEstudio) {
    ESTUDIOS *pe = find_estudios(lt, numEstudio);
    EDIFICIOS *ped = find_edificios(lt, pe->edificio);
    for (int i=0; i<ped->n_estudios; i++) {
        ESTUDIOS *e = ped->estudios + i;
        if (e->estudio == numEstudio) {
            for (int j=i; j<ped->n_estudios; j++) {

                //estudio[j] = estudio[j+1];

            }
            ped->n_estudios--;
            return;
        }
    }
}

//------------ESTUDIO POLITICAS



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

POLITICAS* find_politicas(ESTUDIO_POLITICAS *ep, char politica[MAX200]) {
    POLITICAS *pp = ep->politica;
    int i=0;
    while (pp->politica + i != 0) {
        if ( strcmp(pp->politica, politica) ==0 ) {
            return pp;
        }
        i++;
    }
}

void remove_politicas() {


}

void edit_politicas() {


}

//--------------HOSPEDES
void insert_hospede (HOSPEDES *ph, int id, char nome[]) {
    printf("opening insert_hospede()\n");

    HOSPEDES *novo = (HOSPEDES *) malloc (sizeof (HOSPEDES));
    novo->id = id;
    strcpy(novo->nome, nome);
    novo->pnext = NULL;

    if (ph->numeroHospedes == 0) {
        ph = novo;
        ph->numeroHospedes++;
    }

    HOSPEDES *pcurrent = ph, *pant = NULL;
    while (pcurrent != NULL) {
        pant = pcurrent;
        pcurrent = pcurrent->pnext;
    }
    pant->pnext = novo;
    novo->pnext = pcurrent;
    ph->numeroHospedes++;
    printf("closing insert_hospede()\n");
}

HOSPEDES* find_hospede(HOSPEDES *ph, int idHospede) {
    printf("opening find_hospede()\n");
    while (ph != NULL) {
        if (ph->id == idHospede) {
            printf("find_hospede(): hospede encontrado\n");
            return ph;
        }
        ph = ph->pnext;
    }
    printf("closing find_hospede()\n");
    return NULL;
}

void edit_hospede(HOSPEDES *ph, int idHospede, char nome[MAX200]) {
    HOSPEDES *pe = find_hospede(ph, idHospede);
    strcpy(pe->nome, nome);
}

void remove_hospede(HOSPEDES *ph, int idHospede) {
    HOSPEDES *pant, *pcur, *pnext;
    pant = ph;
    pcur = pant->pnext;
    pnext = pcur->pnext;

    if (pant->id == idHospede) {
        ph = pcur;
        ph->numeroHospedes--;
        return;
    }

    for (int i=0; i<ph->numeroHospedes; i++) {
        if (pcur->id == idHospede) {

            ph->numeroHospedes--;
            return;
        }
        pant = pcur;
        pcur = pnext;
        pnext = pnext->pnext;
    }

}

//-------------AGENDA
void insert_agenda (LOTE_EDIFICIOS *lt, int idEstudio, char nomeAgenda[]) {
    printf("opening insert_agenda()\n");
    ESTUDIOS *pe = NULL;
    pe = find_estudios(lt, idEstudio);
    AGENDAS *pa = (pe->agendas) + pe->numAgendas;
    strcpy(pa->agenda, nomeAgenda);
    pa->numDias=0;
    pa->dia = calloc (MAXDIAS, sizeof(DIAS));
    (pe->numAgendas)++;
    printf("closing insert_agenda()\n");
}

AGENDAS * find_agenda (LOTE_EDIFICIOS *lt, int idEstudio, char nomeAgenda[]) {
    ESTUDIOS *pe = find_estudios(lt, idEstudio);
    for (int i=0; i<pe->numAgendas; i++) {
        AGENDAS *pa = (pe->agendas)+i;
        if (strcmp(pa->agenda, nomeAgenda) == 0) {
            return pa;
        }
    }
    printf("find_agenda(): Agenda nao encontrada\n");
    return NULL;
}

void read_agenda_bin (LOTE_EDIFICIOS *lt, char filename[]) {
    printf("opening read_agenda_bin()\n");
    FILE *fp = NULL;
    fp = fopen(filename, "wb");
    if ( (fp = fopen(filename, "wb")) == NULL) {
        printf("save_agenda_bin(): Erro na abertura do ficheiro %s\n", filename);
        return;
    }



    printf("closing read_agenda_bin()\n");
}

void save_agenda_bin (LOTE_EDIFICIOS lt, char filename[]) {
    printf("opening save_agenda_bin()\n");
    FILE *fp = NULL;
    fp = fopen(filename, "wb");
    if ( (fp = fopen(filename, "wb")) == NULL) {
        printf("save_agenda_bin(): Erro na abertura do ficheiro %s\n", filename);
        return;
    }

    EDIFICIOS *pedificios = lt.pedificios;
    while (pedificios != NULL) {
        for (int i=0; i<pedificios->n_estudios; i++) {
            ESTUDIOS *pestudios = pedificios->estudios+i;
            for (int j=0; j<pestudios->numAgendas; j++) {
                AGENDAS *pagendas = pestudios->agendas+j;
                for (int k=0; k<pagendas->numDias; k++) {
                    DIAS *pdias = pagendas->dia+k;
                    EVENTOS *pevento = pdias->evento;
                    while (pevento != NULL) {

                        fwrite(&pevento->id, sizeof(int), 1, fp);

                        int size = strlen(pevento->tipo+1);
                        fwrite(&size, sizeof(size), 1, fp);
                        fwrite(pevento->tipo, sizeof(char), size, fp);

                        size = strlen(pevento->data_inicio+1);
                        fwrite(&size, sizeof(size), 1, fp);
                        fwrite(pevento->data_inicio, sizeof(char), size, fp);

                        size = strlen(pevento->data_fim+1);
                        fwrite(&size, sizeof(size), 1, fp);
                        fwrite(pevento->data_fim, sizeof(char), size, fp);

                        fwrite(&pevento->hospede, sizeof(int), 1, fp);
                        fwrite(&pevento->estudio, sizeof(int), 1, fp);

                        size = strlen(pevento->plataforma+1);
                        fwrite(&size, sizeof(size), 1, fp);
                        fwrite(pevento->plataforma, sizeof(char), size, fp);

                        pevento=pevento->nextEvento;
                    }
                }
            }
        }

        pedificios=pedificios->pnext;
    }

    fclose(fp);

    printf("closing save_agenda_bin()\n");
}

//-------------DIA

void insert_dia (AGENDAS *pa, char dia[MAX10]) {
    DIAS *pd = pa->dia + pa->numDias;
    strcpy(pd->dia, dia);
    //pd->evento = (EVENTOS *) malloc (sizeof(EVENTOS));
    pd->evento = calloc (MAXEVENTOS, sizeof(EVENTOS));
    pd->nEventos=0;
    (pa->numDias)++;
}

DIAS * find_dia (AGENDAS *pa, char dia[MAX10]) {
    for (int i=0; i<pa->numDias; i++) {
        DIAS *pd = (pa->dia)+i;
        if (strcmp(dia, pd->dia) == 0) {
            return pd;
        }
    }
    return NULL;
}

//-------------EVENTO

void insert_evento(LOTE_EDIFICIOS *lt, int id, char tipo[], char data_inicio[], char data_fim[], int hospede, int estudio, char plataforma[]) {
    printf("opening insert_evento()\n");

    AGENDAS *pa = find_agenda(lt,estudio,plataforma);
    if (pa == NULL) {
        insert_agenda(lt, estudio, plataforma);
        pa = find_agenda(lt, estudio, plataforma);
    }
    DIAS *pd = find_dia(pa,data_inicio);
    if (pd == NULL) {
        insert_dia(pa,data_inicio);
        pd = find_dia(pa,data_inicio);
    }

    EVENTOS *novo = (EVENTOS *) malloc (sizeof(EVENTOS));
    novo->id = id;
    strcpy(novo->tipo, tipo);
    strcpy(novo->data_inicio, data_inicio);
    strcpy(novo->data_fim, data_fim);
    novo->hospede = hospede;
    novo->estudio = estudio;
    strcpy(novo->plataforma, plataforma);
    novo->nextEvento = NULL;

    if (pd->evento == NULL || pd->nEventos == 0) {
        pd->evento = novo;
        pd->nEventos++;
    }
    EVENTOS *pcurrent = pd->evento, *pant = NULL;
    while (pcurrent != NULL) {
        pant = pcurrent;
        pcurrent = pcurrent->nextEvento;
    }
    if (pcurrent == pd->evento) {
        novo->nextEvento = pcurrent;
        pd->evento = novo;
        pd->nEventos++;
        return;
    }
    pant->nextEvento = novo;
    novo->nextEvento = pcurrent;
    pd->nEventos++;
    printf("closing insert_evento()\n");
} //Verificar se funciona

void read_eventos_csv (LOTE_EDIFICIOS *lt, char filename[]) {
    //id,tipo,data_inicio,data_fim,hospede,estudio,plataforma
    printf("opening read_eventos_csv()\n");
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("read_eventos_csv(): Falha na abertura do ficheiro %s\n", filename);
        return;
    }

    int id, hospede, estudio;
    char tipo[MAX200], data_inicio[MAX10], data_fim[MAX10], plataforma[MAX200];

    char buff[1024];
    int row_count = 0;
    int field_count = 0;

    while (fgets(buff, 1024, fp)) {

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
        printf("%d, %s, %s, %s, %d, %d, %s \n", id, tipo, data_inicio, data_fim, hospede, estudio, plataforma);
        insert_evento(lt, id, tipo, data_inicio, data_fim, hospede, estudio, plataforma);
    }

    fclose(fp);
    printf("closing read_eventos_csv()\n");
}

void print_eventos (LOTE_EDIFICIOS *lt) {
    printf("opening print_eventos()\n");

    printf("ID\tTIPO\t\tDATA INICIO\tDATA FIM\tHOSPEDE\t\tESTUDIO\t\tPLATAFORMA\n");

    EDIFICIOS *pe = lt->pedificios;
    while (pe != NULL) {
        for (int i=0; i<pe->n_estudios; i++) {
            ESTUDIOS *pestudio = (pe->estudios)+i;
            for (int j=0; j<pestudio->numAgendas; j++) {
                AGENDAS *pa = (pestudio->agendas)+j;
                for (int k=0; k<pa->numDias; k++) {
                    DIAS *pd = pa->dia+k;
                    EVENTOS *pev = pd->evento;
                    while (pev != NULL) {
                        printf("%d\t%s\t\t%s\t%s\t%d\t\t%d\t\t%s",pev->id, pev->tipo, pev->data_inicio, pev->data_fim, pev->hospede, pev->estudio, pev->plataforma);
                        pev = pev->nextEvento;
                    }
                }
            }
        }
        pe = pe->pnext;
    }

    printf("\n");
}

EVENTOS * find_evento (DIAS *pd, int idEvento) {
    EVENTOS *pe = pd->evento;
    while (pe != NULL) {
        if (idEvento == pe->id) {
            return pe;
        }
        pe = pe->nextEvento;
    }
    return NULL;
}

void edit_evento (DIAS *pd, int idEvento, char tipo[MAX200], char data_inicio[], char data_fim[], int hospede, int estudio, char plataforma[]) {
    EVENTOS *pe = find_evento(pd, idEvento);
    if (pe == NULL) {
        return;
    }
    strcpy(pe->tipo, tipo);
    strcpy(pe->data_inicio, data_inicio);
    strcpy(pe->data_fim, data_fim);
    pe->hospede = hospede;
    pe->estudio = estudio;
    strcpy(pe->plataforma, plataforma);
}

void remove_evento (DIAS *pd, int idEvento) {
    EVENTOS *pant, *pcur, *pnext;
    pant = pd->evento;
    pcur = pant->nextEvento;
    pnext = pcur->nextEvento;

    if (pant->id == idEvento) {
        pd->evento=pcur;
        pd->nEventos--;
        return;
    }

    for (int i=0; i<pd->nEventos; i++) {
        if (pcur->id == idEvento) {
            pant->nextEvento = pnext;
            pd->nEventos--;
            return;
        }
        pant = pcur;
        pcur = pnext;
        pnext = pnext->nextEvento;
    }
}

//---------------RELATÓRIOS

void relatorio_ecra(LOTE_EDIFICIOS *lt) {
   printf("******************** RELATORIO ********************\n");

    EDIFICIOS *pedificios = lt->pedificios;
    while (pedificios != NULL) {
        printf("\n\t* EDIFICIO %d - %s\n",pedificios->edificio, pedificios->nome);
        printf("\t* %s (%f, %f)\n", pedificios->morada, pedificios->latitude, pedificios->longitude);
        printf("\t* %0.2f EUR/dia/m^2 com %d estudios\n", pedificios->preco_dia_m2, pedificios->n_estudios);
        for (int i=0; i<pedificios->n_estudios; i++) {
            ESTUDIOS *pestudios = pedificios->estudios+i;
            int numeroEventos=0;
            printf("\t\t** ESTUDIO: %d - N.%d - %s - %d m^2\n", pestudios->estudio, pestudios->numero, pestudios->configuracao, pestudios->area);
            for (int j=0; j<pestudios->numAgendas; j++) {
                AGENDAS *pagenda = pestudios->agendas+j;
                for (int k=0; k<pagenda->numDias; k++) {
                    DIAS *pdias = pagenda->dia+k;
                    printf("\t\t*** %d evento(s)\n", pdias->nEventos-1);
                    EVENTOS *peventos = pdias->evento;
                    while (peventos != NULL) {
                        printf("\t\t\t**** ID: %d - TIPO: %s\tDE %s A %s\tHOSPEDE: %d\tPLAT.: %s\n",peventos->id, peventos->tipo, peventos->data_inicio, peventos->data_fim, peventos->hospede, strtok(peventos->plataforma,"\n"));
                        numeroEventos++;
                        peventos=peventos->nextEvento;
                    }
                }
            }
        }
        pedificios = pedificios->pnext;
    }
}

void relatorio_ficheiro(LOTE_EDIFICIOS *lt, char filename[]) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Impossivel abrir o ficheiro.\n");
        return;
    }

    EDIFICIOS *pedificios = lt->pedificios;
    while (pedificios != NULL) {
        fprintf(fp,"\n\t* EDIFICIO %d - %s\n",pedificios->edificio, pedificios->nome);
        fprintf(fp,"\t* %s (%f, %f)\n", pedificios->morada, pedificios->latitude, pedificios->longitude);
        fprintf(fp,"\t* %0.2f EUR/dia/m^2 com %d estudios\n", pedificios->preco_dia_m2, pedificios->n_estudios);
        for (int i=0; i<pedificios->n_estudios; i++) {
            ESTUDIOS *pestudios = pedificios->estudios+i;
            int numeroEventos=0;
            fprintf(fp,"\t\t** ESTUDIO: %d - N.%d - %s - %d m^2\n", pestudios->estudio, pestudios->numero, pestudios->configuracao, pestudios->area);
            for (int j=0; j<pestudios->numAgendas; j++) {
                AGENDAS *pagenda = pestudios->agendas+j;
                for (int k=0; k<pagenda->numDias; k++) {
                    DIAS *pdias = pagenda->dia+k;
                    fprintf(fp,"\t\t*** %d evento(s)\n", pdias->nEventos-1);
                    EVENTOS *peventos = pdias->evento;
                    while (peventos != NULL) {
                        fprintf(fp,"\t\t\t**** ID: %d - TIPO: %s\tDE %s A %s\tHOSPEDE: %d\tPLAT.: %s\n",peventos->id, peventos->tipo, peventos->data_inicio, peventos->data_fim, peventos->hospede, strtok(peventos->plataforma,"\n"));
                        numeroEventos++;
                        peventos=peventos->nextEvento;
                    }
                }
            }
        }
        pedificios = pedificios->pnext;
    }

    fclose(fp);


}

