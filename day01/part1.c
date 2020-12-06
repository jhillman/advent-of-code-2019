/* Day 1, part 1 = 3465154 */

#include <stdio.h>

int main() {
    FILE *modulesFile = fopen("modules.txt", "r");

    if (modulesFile) {
        int mass;
        int totalFuel = 0;

        while (!feof(modulesFile) && fscanf(modulesFile, "%d", &mass)) {
            totalFuel += (mass / 3) - 2;
        }

        fclose(modulesFile);

        printf("%d", totalFuel);
    }

    return 0;
}