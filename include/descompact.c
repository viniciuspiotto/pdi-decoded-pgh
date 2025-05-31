#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "descompact.h"
#include "huffman.h"

image read_pgh(char *fileName) {
    char lineBuffer[100];
    int rowCount, colCount, maxIntensity;
    image img;
    FILE *file;

    ERROR((file = fopen(fileName, "r")) == NULL, error_msg("File open error: <%s>", fileName));
    
    fgets(lineBuffer, 80, file);
    ERROR((lineBuffer[0] != 'P' || lineBuffer[1] != 'H'), error_msg("File type image error: <%s>", fileName));

    fgets(lineBuffer, 80, file);
    while (strchr(lineBuffer, '#'))
        fgets(lineBuffer, 80, file);

    sscanf(lineBuffer, "%d %d", &colCount, &rowCount);
    ERROR(colCount == 0 || rowCount == 0, error_msg("Image dimensions error: <%s>", fileName));

    fscanf(file, "%d", &maxIntensity);
    ERROR(maxIntensity == 0, error_msg("Image max intensity error: <%s>", fileName));
    int ch;
    while ((ch = fgetc(file)) != '\n' && ch != EOF);

    img = img_create(rowCount, colCount, maxIntensity);
    ERROR(!img, error_msg("Image allocation error: %s\n\n", fileName));

    long hexSize;
    unsigned char *hexData = scan_hex_data(file, &hexSize);

    long histogramSize = (long)(maxIntensity + 1) * sizeof(int);
    int *histogram = create_histogram(hexData, maxIntensity);

    unsigned char *huffmanBytes = hexData + histogramSize;
    long remainingSize = hexSize - histogramSize;

    char *bitSequence = bytes_to_bits(huffmanBytes, remainingSize);

    int huffmanRoot = build_tree(histogram, maxIntensity);

    long bitSequenceLength = remainingSize * 8;

    decode_image(img, bitSequence, bitSequenceLength, huffmanRoot);
    
    free(histogram);
    free(bitSequence);
    free(hexData);
    fclose(file);
    return img;
}

unsigned char *scan_hex_data(FILE *file, long *outSize) {
    long currentPos = ftell(file);
    fseek(file, 0, SEEK_END);
    long endPos = ftell(file);
    fseek(file, currentPos, SEEK_SET);
    long dataSize = endPos - currentPos;

    unsigned char *data = (unsigned char *)malloc(dataSize);
    fread(data, sizeof(unsigned char), dataSize, file);

    *outSize = dataSize;
    return data;
}

int *create_histogram(unsigned char *hexData, int maxIntensity) {
    int *histogram = (int *)malloc((maxIntensity + 1) * sizeof(int));

    for (int i = 0; i <= maxIntensity; i++) {
        long offset = (long)i * sizeof(int);

        uint32_t value = (uint32_t)hexData[offset] |
                         ((uint32_t)hexData[offset + 1] << 8) |
                         ((uint32_t)hexData[offset + 2] << 16) |
                         ((uint32_t)hexData[offset + 3] << 24);

        histogram[i] = (int)value;
    }

    return histogram;
}

char *bytes_to_bits(unsigned char *bytes, long bytesLength) {
    long totalBits = bytesLength * 8;
    char *bits = (char *)malloc(totalBits + 1);

    long bitIndex = 0;
    for (long i = 0; i < bytesLength; i++) {
        unsigned char byte = bytes[i];
        for (int bitPos = 7; bitPos >= 0; bitPos--) {
            bits[bitIndex++] = ((byte >> bitPos) & 1) ? '1' : '0';
        }
    }
    bits[bitIndex] = '\0';

    return bits;
}