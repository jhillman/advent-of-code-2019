/* Day 2, part 1 = 2842648 */

#include <stdio.h>
#include "../intcode.h"

int main() {
    struct Program *program = readProgram("input.txt");

    if (program) {
        initializeProgram(program, 12, 2);

        runProgram(program);

        printf("%ld", *program->data);

        freeProgram(program);
    }

    return 0;
}