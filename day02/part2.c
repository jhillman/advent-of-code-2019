/* Day 2, part 2 = 9074 */

#include <stdio.h>
#include "../intcode.h"

int main() {
    struct Program *program = readProgram("input.txt");

    if (program) {
        int targetOutput = 19690720;
        struct Program *testProgram = NULL;
        int outputFound = 0;

        for (int noun = 0; !outputFound && noun < 100; noun++) {
            for (int verb = 0; !outputFound && verb < 100; verb++) {
                freeProgram(testProgram);

                testProgram = copyProgram(program, NULL);

                initializeProgram(testProgram, noun, verb);

                runProgram(testProgram);

                if (*testProgram->data == targetOutput) {
                    outputFound = 1;
                }         
            }
        }

        printf("%d", 100 * programNoun(testProgram) + programVerb(testProgram));

        freeProgram(testProgram);
        freeProgram(program);
    }

    return 0;
}