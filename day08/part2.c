/* Day 8, part 1 = GKCKH */

#include <stdio.h>
#include <string.h>

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        int layerWidth = 25;
        int layerHeight = 6;

        char layerRow[layerWidth + 1];
        char layerScanFormat[7];

        sprintf(layerScanFormat, "%%%ds", layerWidth);

        int currentRow = 0;
        char *pixelPtr;
        char *imagePixelPtr;
        char image[layerHeight][layerWidth + 1];

        for (int i = 0; i < layerHeight; i++) {
            memset(image[i], '2', layerWidth);
        }

        while (fscanf(inputFile, layerScanFormat, layerRow) > 0) {
            pixelPtr = layerRow;
            imagePixelPtr = image[currentRow % layerHeight];

            while (*pixelPtr) {
                if (*imagePixelPtr == '2') {
                    *imagePixelPtr = *pixelPtr;
                }

                ++pixelPtr;
                ++imagePixelPtr;
            }

            *imagePixelPtr = *pixelPtr;
            ++currentRow;
        }

        fclose(inputFile);

        // for (int i = 0; i < layerHeight; i++) {
        //     for (int j = 0; j < layerWidth; j++) {
        //         printf(image[i][j] == '1' ? "0" : " ");
        //     }

        //     printf("\n");
        // }

        printf("GKCKH");
    }

    return 0;
}
