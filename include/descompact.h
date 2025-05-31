#ifndef DESCOMPACT_H
#define DESCOMPACT_H

#include "imagelib.h"

/**
 * @brief Lê uma imagem codificada no formato personalizado PGH
 * 
 * @param fileName Nome do arquivo da imagem.
 * @return image Imagem com os pixels decodificados.
 */
image read_pgh(char *fileName);

/**
 * @brief Converte um vetor de bytes em uma sequência de bits (como string).
 * 
 * @param bytes Vetor de bytes.
 * @param bytesLength Tamanho do vetor de bytes.
 * @return char* String de bits ('0' e '1').
 */
char *bytes_to_bits(unsigned char *bytes, long bytesLength);

/**
 * @brief Cria um histograma a partir dos bytes.
 * 
 * @param hexData Vetor de bytes contendo os dados do histograma.
 * @param maxIntensity Valor máximo de intensidade da imagem.
 * @return int* Vetor de inteiros representando o histograma.
 */
int *create_histogram(unsigned char *hexData, int maxIntensity);

/**
 * @brief Lê os dados binários restantes do arquivo a partir da posição atual.
 * 
 * @param file Arquivo da imagem aberta posteriormente.
 * @param outSize Tamanho dos dados lidos.
 * @return unsigned char* Vetor com os dados lidos.
 */
unsigned char *scan_hex_data(FILE *file, long *outSize);

#endif