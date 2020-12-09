/* Day 5, part 1 = 6761139 */

#include "../intcode.h"

int main() {
    struct Program *program = readProgram("input.txt");

    if (program) {
        runProgram(program);

        freeProgram(program);
    }

    return 0;
}
