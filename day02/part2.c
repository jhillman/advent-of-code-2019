/* Day 2, part 2 = 9074 */

#include <stdio.h>
#include "../intcode.h"

int main() {
    struct Program *program = readProgram("program.txt");

    if (program) {
        int targetOutput = 19690720;
        struct Program *testProgram = NULL;
        int outputFound = 0;

        for (int verb = 0; !outputFound && verb < 100; verb++) {
            for (int noun = 0; !outputFound && noun < 100; noun++) {
                if (testProgram) {
                    freeProgram(testProgram);
                }

                testProgram = copyProgram(program);

                initializeProgram(testProgram, verb, noun);

                runProgram(testProgram);

                if (*testProgram->data == targetOutput) {
                    outputFound = 1;
                }         
            }
        }

        printf("%d", 100 * programVerb(testProgram) + programNoun(testProgram));

        freeProgram(testProgram);
        freeProgram(program);
    }

    return 0;
}