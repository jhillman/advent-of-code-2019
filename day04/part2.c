/* Day 4, part 2 = 1145 */

#include <stdio.h>

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        int rangeMin;
        char dash;
        int rangeMax;

        fscanf(inputFile, "%d%c%d", &rangeMin, &dash, &rangeMax);

        fclose(inputFile);

        char password[7];        
        int passwordCount = 0;

        for (int passwordNumber = rangeMin; passwordNumber <= rangeMax; passwordNumber++) {
            sprintf(password, "%d", passwordNumber);

            int increasing = 1;
            int twoAdjacent = 0;

            for (int i = 1; increasing && i < 6; i++) {
                int diff = password[i] - password[i - 1];
                increasing = diff >= 0;

                if (diff == 0 && !twoAdjacent) {
                    twoAdjacent = 1;

                    if (i > 1 && password[i - 2] == password[i]) {
                        twoAdjacent = 0;
                    } else if (i < 5 && password[i + 1] == password[i]) {
                        twoAdjacent = 0;
                    }
                }
            }

            if (increasing && twoAdjacent) {
                ++passwordCount;
            }
        }

        printf("%d", passwordCount);
    }

    return 0;
}