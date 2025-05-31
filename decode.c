/*=============================================================
* UNIFAL = Universidade Federal de Alfenas. 
* BACHARELADO EM CIENCIA DA COMPUTAÇÃO.
* Trabalho   : Decodificador do formato PGH 5 
* Professor  : Luiz Eduardo da Silva
* Aluno      : Vinícius Henrique Piotto Boiago 
* Data       : 26/05/2025 
*=============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/imagelib.h"
#include "./include/huffman.h"
#include "./include/descompact.h"

void msg(char *s) {
    printf("\nEdecoding files in PGH format");
    printf("\n-------------------------");
    printf("\nUsage: %s image-name[.pgh]\n\n", s);
    printf("\n image-name[.pgh] is file in pgh format\n\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    char nameIn[100], nameOut[100], cmd[110];
    image In;

    if (argc < 2 ) {
     msg(argv[0]);
    }

    img_name(argv[1], nameIn, nameOut, 4, 2);

    In = read_pgh(nameIn);

    img_put(In, nameOut);

    sprintf(cmd, "eog %s &", nameOut);
    puts(cmd);
    system(cmd);
    img_free(In);
    return 0;
}