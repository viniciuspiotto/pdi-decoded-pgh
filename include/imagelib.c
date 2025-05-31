#include "imagelib.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error_msg(char *message, ...) {
    char formattedMessage[255];
    va_list args;
    va_start(args, message);
    sprintf(formattedMessage, "ERROR: %s\n\n", message);
    vprintf(formattedMessage, args);
    va_end(args);
    exit(1);
}

image img_create(int rowCount, int colCount, int maxIntensity) {
    image img = (image)malloc(sizeof(struct s_image));
    img->px = (int *)malloc(rowCount * colCount * sizeof(int));
    img->rowCount = rowCount;
    img->colCount = colCount;
    img->maxIntensity = maxIntensity;
    return img;
}

void img_free(image img) {
    free(img->px);
    free(img);
}

void img_name(char *baseName, char *inputFile, char *outputFile, int inputType, int outputType) {
    char *extensions[4] = {".pbm", ".pgm", ".ppm", ".pgh"};
    char *extLocation = strstr(baseName, extensions[inputType - 1]);

    if (extLocation)
        *extLocation = '\0';

    sprintf(inputFile, "%s%s", baseName, extensions[inputType - 1]);
    sprintf(outputFile, "%s-result%s", baseName, extensions[outputType - 1]);
}

void img_put(image img, char *fileName) {
    int pixelCounter = 0;
    FILE *file;

    ERROR((file = fopen(fileName, "wt")) == NULL, error_msg("Image creation error: <%s>", fileName));

    fprintf(file, "P2\n");
    fputs(CREATOR, file);
    fprintf(file, "%d %d\n", img->colCount, img->rowCount); 
    fprintf(file, "%d\n", img->maxIntensity);

    for (int i = 0; i < img->rowCount * img->colCount; i++) {
        fprintf(file, "%d ", img->px[i]);
        pixelCounter++;

        if (pixelCounter == img->colCount) {
            fprintf(file, "\n");
            pixelCounter = 0;
        }
    }

    if (pixelCounter != 0) {
        fprintf(file, "\n");
    }

    fclose(file);
}