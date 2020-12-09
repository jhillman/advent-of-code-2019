/* Day 6, part 2 = 481 */

#include <stdio.h>
#include "orbitmap.h"

int main() {
    struct Object *orbitMap = readInput();

    if (orbitMap) {
        struct Object *you = findObject(orbitMap, "YOU");
        struct Object *santa = findObject(orbitMap, "SAN");

        if (you && santa) {
            int youTransferCount = 0;
            int santaTransferCount = 0;
            int commonObjectFound = 0;

            struct Object *youObject = you->orbitee;

            while (youObject && !commonObjectFound) {
                struct Object *santaObject = santa->orbitee;
                santaTransferCount = 0;

                while (santaObject) {
                    if (strcmp(youObject->name, santaObject->name) == 0) {
                        commonObjectFound = 1;
                        break;
                    }

                    santaObject = santaObject->orbitee;
                    ++santaTransferCount;
                }

                if (!commonObjectFound) {
                    youObject = youObject->orbitee;
                    ++youTransferCount;
                }
            }

            printf("%d", youTransferCount + santaTransferCount);
        }

        freeMap(orbitMap);
    }

    return 0;
}
