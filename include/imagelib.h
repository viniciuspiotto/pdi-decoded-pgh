#ifndef IMAGELIB_H
#define IMAGELIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

typedef struct s_image {
    int rowCount;
    int colCount;
    int maxIntensity;
    int *px;
} *image;

#define ERROR(x, y) \
    if (x)          \
    y
    
#define CREATOR "# CREATOR: Image Processing using C-Ansi - ByDu\n"

/**
 * @brief Exibe uma mensagem de erro formatada e finaliza o programa.
 * 
 * @param message Mensagem de erro no estilo printf.
 */
void error_msg(char *message, ...);

/**
 * @brief Cria uma imagem na memória
 * 
 * @param rowCount Número de linhas (altura) da imagem.
 * @param colCount Número de colunas (largura) da imagem.
 * @param maxIntensity Intensidade máxima de pixel.
 * @return image Ponteiro para a estrutura de imagem criada.
 */
image img_create(int rowCount, int colCount, int maxIntensity);

/**
 * @brief Libera a memória alocada para uma imagem.
 * 
 * @param img Imagem a ser liberada.
 */
void img_free(image img);

/**
 * @brief Gera os nomes de arquivo de entrada e saída com base no nome base e tipos.
 * 
 * @param baseName Nome base do arquivo.
 * @param inputFile Caminho para salvar o nome de arquivo de entrada gerado.
 * @param outputFile Caminho para salvar o nome de arquivo de saída gerado.
 * @param inputType Tipo de arquivo de entrada (1=PBM, 2=PGM, 3=PPM, 4=PGH).
 * @param outputType Tipo de arquivo de saída (1=PBM, 2=PGM, 3=PPM, 4=PGH).
 */
void img_name(char *baseName, char *inputFile, char *outputFile, int inputType, int outputType);

/**
 * @brief Escreve uma imagem no formato PGM (P2) em disco.
 * 
 * @param img Imagem a ser salva.
 * @param fileName Nome do arquivo de saída.
 */
void img_put(image img, char *fileName);

#endif