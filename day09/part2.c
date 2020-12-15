/* Day 9, part 2 = 87221 */

#include "../intcode.h"

int main() {
    struct Program *program = readProgram("input.txt");

    if (program) {
        pipe(program->input);
        pipe(program->output);

        int input = 2;
        write(program->input[WRITE], &input, sizeof(input));

        runProgram(program);

        long output;
        while (read(program->output[READ], &output, sizeof(output)) && output == 0);

        freeProgram(program);

        printf("%ld", output);
    }

    return 0;
}
