//Projeto AED1 e LP1 - Ano Letivo 2020/2021
//Gonçalo Paiva (39807) e João Miranda (XXXXX)

//TODO: R1.
//TODO: R2.
//TODO: R3. Implementar uma API de funcoes de criacao/insercao, pesquisa, remocao e alteracao de eventos em cada agenda
// de cada estudio (ex. reservas, limpezas, manutencao, ...).
//TODO: R4.
//TODO: R5. Implementar uma API de funcoes de leitura e escrita de texto e binário para cada agenda, com os repetivos eventos registados.
//TODO: R6.
//TODO: R7. Implementar a geração de relatorios (em ecra e ficheiro) com a faturação por
// estudio, por edificio ou na totalidade do parque de edificios. Deverá ser possivel
// escolher o periodo do relatorio a gerar e a ordem de ordenacao (crescente ou decrescente).
//TODO: R8. Implementar a sincronização de uma agenda para a agenda principal (e da principal para
// restantes), aplicando estratégias de resolucao de conflitos existentes (sincronizacao e gestão de versões).
//TODO: R9.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "alojamentos.h"

int main() {
    printf("---------------------------------------------------\n");
    printf("---------------- GESTOR DE RESERVAS ---------------\n");
    printf("-------------------- Bem-Vindo --------------------\n");
    printf("---------------------------------------------------\n");

    printf("\n\n");

    printf("Escolha uma opcao: \n");
    printf("\t 1. Alojamentos\n");
    printf("\t 0. Sair\n");


    int op;
    printf("\nOpcao:  ");

    do {
        op=getchar();

        switch (op)
        {
            case 1: menu_alojamentos();
                break;
            case 2: adicionar_alojamentos();
                break;
            case 3: editar_alojamentos();
                break;
            case 0: break;

            default: printf("Opcao Invalida!\n");
        }
    } while (op!=0);
    return 0;

}

void linha() {
    printf("-----------------------------------------------------------------------------------------------------\n");
}

int sair() {
    char a;
    linha();
    printf("Deseja sair?\n");
    printf("S-Sim \t N-Nao");
    scanf("%c",&a);
    if (a=='S') {
        return 0;
    } else if (a=='N') {
        main();
    }
}
