/* Day 5, part 2 = 9217546 */

#include "../intcode.h"

int main() {
    struct Program *program = readProgram("input.txt");

    if (program) {
        runProgram(program);

        freeProgram(program);
    }

    return 0;
}
