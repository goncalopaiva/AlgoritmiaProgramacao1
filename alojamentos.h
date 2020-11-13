//
// Created by Goncalo on 11/13/2020.
//

#ifndef PROJETOLPIAEDI_ALOJAMENTOS_H
#define PROJETOLPIAEDI_ALOJAMENTOS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_VECTOR 20

//TODO: editar a estrutura ALOJAMENTO

typedef struct alojamentos {
    int num_alojamentos;
    char id[TAM_VECTOR];
    char nome[TAM_VECTOR];
    char categoria[TAM_VECTOR];
} ALOJAMENTO;

/**
 * Funcao que imprime as opçoes do menu de alojamentos.
 * @return
 */
int menu_alojamentos();

/**
 * Funcao que permite visualizar os alojamentos.
 * @return
 */
int ver_alojamentos();

/**
 * Funcao que permite adicionar alojamentos.
 * @return
 */
int adicionar_alojamentos();

/**
 * Funcao que permite editar os alojamentos.
 * @return
 */
int editar_alojamentos();


#endif //PROJETOLPIAEDI_ALOJAMENTOS_H
