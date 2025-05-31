#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "imagelib.h"

#define MAX_NODES 500

/**
 * @brief Estrutura de um nó da árvore de Huffman.
 */
typedef struct {
    int freq;    ///< Frequência do símbolo (intensidade de pixel)
    int father;  ///< Índice do nó pai
    int left;    ///< Índice do filho esquerdo
    int right;   ///< Índice do filho direito
} nodetype;

extern nodetype node[MAX_NODES];

/**
 * @brief Remove o nó de menor frequência da lista encadeada.
 * 
 * @param rootNodes Ponteiro para a raiz da lista de nós.
 * @return int Índice do nó removido.
 */
int remove_freq(int *rootNodes);

/**
 * @brief Insere um novo nó na lista encadeada de forma ordenada por frequência.
 * 
 * @param rootNodes Ponteiro para a raiz da lista de nós.
 * @param nodeIndex Índice do nó a ser inserido.
 */
void insert_freq(int *rootNodes, int nodeIndex);

/**
 * @brief Constrói a árvore de Huffman a partir de um histograma.
 * 
 * @param histogram Vetor de frequências das intensidades.
 * @param maxIntensity Intensidade máxima da imagem.
 * @return int Índice da raiz da árvore construída.
 */
int build_tree(int *histogram, int maxIntensity);

/**
 * @brief Decodifica uma imagem a partir de uma string de bits codificada com Huffman.
 * 
 * @param img Estrutura da imagem a ser preenchida.
 * @param huffmanCode Cadeia de bits (como string de '0' e '1').
 * @param bitLength Comprimento da cadeia de bits.
 * @param rootNodeIndex Índice do nó raiz da árvore de Huffman.
 */
void decode_image(image img, char *huffmanCode, long bitLength, int rootNodeIndex);

#endif