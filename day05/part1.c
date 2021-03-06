/* Day 5, part 1 = 6761139 */

#include "../intcode.h"

int main() {
    struct Program *program = readProgram("input.txt");

    if (program) {
        pipe(program->input);
        pipe(program->output);

        int input = 1;
        write(program->input[WRITE], &input, sizeof(input));

        runProgram(program);

        int output;
        while (read(program->output[READ], &output, sizeof(output)) && output == 0);

        freeProgram(program);

        printf("%d", output);
    }

    return 0;
}
