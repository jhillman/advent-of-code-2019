/* Day 7, part 1 = 116680 */

#include <stdio.h>
#include "phase.h"
#include "../intcode.h"

int main() {
    struct Program *program = readProgram("input.txt");

    struct Program *programA = copyProgram(program, "a");
    struct Program *programB = copyProgram(program, "b");
    struct Program *programC = copyProgram(program, "c");
    struct Program *programD = copyProgram(program, "e");
    struct Program *programE = copyProgram(program, "e");

    struct Program *programs[] = {
        programA,
        programB,
        programC,
        programD,
        programE
    };

    struct PhaseSequenceData data = getPhaseSequenceData(0, 4);

    for (int i = 0; i < data.phaseSequenceLength; i++) {
        pipe(programs[i]->input);
        pipe(programs[i]->output);
    }

    long maxSignal = 0;

    for (int i = 0; i < data.phaseSequenceCount; i++) {
        struct PhaseSequence phaseSequence = data.phaseSequences[i];

        long signal = 0;

        for (int j = 0; j < data.phaseSequenceLength; j++) {
            long phase = *((int *)&phaseSequence + j);

            write(programs[j]->input[WRITE], &phase, sizeof(phase));
            write(programs[j]->input[WRITE], &signal, sizeof(signal));

            runProgram(programs[j]);

            read(programs[j]->output[READ], &signal, sizeof(signal));

            resetProgram(programs[j], program->data);
        }

        if (signal > maxSignal) {
            maxSignal = signal;
        }
    }

    freeProgram(programA);
    freeProgram(programB);
    freeProgram(programC);
    freeProgram(programD);
    freeProgram(programE);

    free(data.phaseSequences);

    printf("%ld", maxSignal);

    return 0;
}
