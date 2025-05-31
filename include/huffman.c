#include "huffman.h"

nodetype node[MAX_NODES];

void decode_image(image img, char *huffmanCode, long huffmanBitsLength, int rootNodeIndex) {
    int currentNodeIndex = rootNodeIndex;
    long currentPixelIndex = 0;
    long imageSize = (long)img->rowCount * img->colCount;
    
    for (long i = 0; i < huffmanBitsLength && currentPixelIndex < imageSize; i++) {
        char bit = huffmanCode[i];

        if (bit == '0') {
            currentNodeIndex = node[currentNodeIndex].left;
        } else if (bit == '1') {
            currentNodeIndex = node[currentNodeIndex].right;
        }

        if (node[currentNodeIndex].left == -1 && node[currentNodeIndex].right == -1) {
            img->px[currentPixelIndex] = currentNodeIndex;
            currentPixelIndex++;
            currentNodeIndex = rootNodeIndex;
        }
    }
}

int remove_freq(int *rootNodes) {
    int nodeIndex = *rootNodes;
    *rootNodes = node[*rootNodes].father;
    return nodeIndex;
}

void insert_freq(int *rootNodes, int nodeIndex) {
    int previous = -1, current = *rootNodes;

    while (current != -1 && node[current].freq <= node[nodeIndex].freq) {
        previous = current;
        current = node[current].father;
    }

    if (previous == -1) {
        node[nodeIndex].father = *rootNodes;
        *rootNodes = nodeIndex;
    } else {
        node[nodeIndex].father = node[previous].father;
        node[previous].father = nodeIndex;
    }
}

int build_tree(int *histogram, int maxIntensity) {
    int i, newNodeIndex, leftNode, rightNode;
    int rootNodes = -1;

    for (i = 0; i <= maxIntensity; i++) {
        node[i].freq = histogram[i];
        node[i].left = -1;
        node[i].right = -1;
        insert_freq(&rootNodes, i);
    }

    for (newNodeIndex = maxIntensity + 1; newNodeIndex < 2 * (maxIntensity + 1) - 1; newNodeIndex++) {
        leftNode = remove_freq(&rootNodes);
        rightNode = remove_freq(&rootNodes);

        node[leftNode].father = newNodeIndex;
        node[rightNode].father = newNodeIndex;

        node[newNodeIndex].freq = node[leftNode].freq + node[rightNode].freq;
        node[newNodeIndex].left = leftNode;
        node[newNodeIndex].right = rightNode;

        insert_freq(&rootNodes, newNodeIndex);
    }

    return remove_freq(&rootNodes);
}