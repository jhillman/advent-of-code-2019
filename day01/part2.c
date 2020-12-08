/* Day 1, part 2 = 5194864 */

#include <stdio.h>

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        int mass;
        int totalFuel = 0;

        while (!feof(inputFile) && fscanf(inputFile, "%d", &mass)) {
            int fuel = (mass / 3) - 2;

            while (fuel > 0) {
                totalFuel += fuel;
                
                fuel = (fuel / 3) - 2;
            }
        }

        fclose(inputFile);

        printf("%d", totalFuel);
    }

    return 0;
}