//
// Created by Goncalo on 11/13/2020.
//

#include "alojamentos.h"
#include "main.h"

int menu_alojamentos() {

    int op =0;

    printf("----------------------------------\n");
    printf("-------- MENU ALOJAMENTOS --------\n");
    printf("----------------------------------\n");

    printf("\n\n");

    printf("Escolha uma opcao: \n");
    printf("\t 1. Ver alojamentos\n");
    printf("\t 2. Adicionar alojamentos\n");
    printf("\t 3. Editar alojamentos\n");
    printf("\t 4. (...)\n");
    printf("\t 0. Voltar ao menu principal\n");

    do {
        scanf("%d",&op);

        switch (op)
        {
            case 1: ver_alojamentos();
                break;
            case 2: adicionar_alojamentos();
                break;
            case 3: editar_alojamentos();
                break;
            case 0: main();

            default: printf("Opcao Invalida!\n");
        }
    } while (op!=0);
    return 0;
}

int ver_alojamentos() {
    //Ver todos os alojamentos ou só 1?
    //Se todos -> imprimir todos os alojamentos.
    //Se só 1 -> introduza o codigo do alojamento.

    linha();
    printf("----> Lista de todos os alojamentos:\n\n");


}

int adicionar_alojamentos() {
    //Pedir informacao do alojamento (morada, preco, ...)
    //Código do alojamento -> proximo elemento.

    linha();
    printf("----> Adicionar novo alojamento:\n\n");

}

int editar_alojamentos() {
    //Mostrar todos os alojamentos
    //Pedir codigo do alojamento que quer editar.
    //Pedir campo que quer editar.
    //Guardar novas informacao no alojamento.

    linha();
    printf("----> Editar alojamento:\n\n");


}