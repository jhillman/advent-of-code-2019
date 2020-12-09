/* Day 6, part 1 = 315757 */

#include <stdio.h>
#include "orbitmap.h"

int countOrbits(struct Object *object) {
    int count = 0;

    for (int i = 0; i < object->orbiterCount; i++) {
        count += countOrbits(&object->orbiters[i]);
    }

    struct Object *orbitee = object->orbitee;

    while (orbitee) {
        ++count;
        orbitee = orbitee->orbitee;
    }

    return count;
}

int main() {
    struct Object *orbitMap = readInput();

    if (orbitMap) {
        printf("%d", countOrbits(orbitMap));

        freeMap(orbitMap);
    }

    return 0;
}
