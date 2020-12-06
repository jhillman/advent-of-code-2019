/* Day 1, part 2 = 5194864 */

#include <stdio.h>

int main() {
    FILE *modulesFile = fopen("modules.txt", "r");

    if (modulesFile) {
        int mass;
        int totalFuel = 0;

        while (!feof(modulesFile) && fscanf(modulesFile, "%d", &mass)) {
            int fuel = (mass / 3) - 2;

            while (fuel > 0) {
                totalFuel += fuel;
                
                fuel = (fuel / 3) - 2;
            }
        }

        fclose(modulesFile);

        printf("%d", totalFuel);
    }

    return 0;
}