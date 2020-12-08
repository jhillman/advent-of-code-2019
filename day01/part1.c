/* Day 1, part 1 = 3465154 */

#include <stdio.h>

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        int mass;
        int totalFuel = 0;

        while (!feof(inputFile) && fscanf(inputFile, "%d", &mass)) {
            totalFuel += (mass / 3) - 2;
        }

        fclose(inputFile);

        printf("%d", totalFuel);
    }

    return 0;
}