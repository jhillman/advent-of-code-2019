#ifndef H_INTCODE
#define H_INTCODE

#include <stdio.h>
#include <stdlib.h>

struct Program {
    int *data;
    int length;
};

struct Program *readProgram(char *filename) {
    FILE *programFile = fopen("program.txt", "r");

    if (programFile) {
        char ch;
        int length = 0;

        while (!feof(programFile)) {
            ch = fgetc(programFile);

            if (ch == ',') {
                ++length;
            }
        }

        if (ch != ',' && length > 0) {
            ++length;
        }

        int *data = (int *)calloc(length, sizeof(int));
        int dataIndex = 0;

        fseek(programFile, 0, SEEK_SET);

        int input;

        while (dataIndex < length) {
            fscanf(programFile, "%d%c", &input, &ch);

            data[dataIndex++] = input;
        }

        fclose(programFile);

        struct Program *program = (struct Program *)calloc(1, sizeof(struct Program));

        program->data = data;
        program->length = length;

        return program;
    }

    return NULL;
}

struct Program *copyProgram(struct Program *program) {
    struct Program *programCopy = (struct Program *)calloc(1, sizeof(struct Program));
    programCopy->data = (int *)calloc(program->length, sizeof(int));

    for (int i = 0; i < program->length; i++) {
        programCopy->data[i] = program->data[i];
    }

    programCopy->length = program->length;

    return programCopy;
}

void initializeProgram(struct Program *program, int noun, int verb) {
    program->data[1] = noun;
    program->data[2] = verb;
}

int programNoun(struct Program *program) {
    return program->data[1];
}

int programVerb(struct Program *program) {
    return program->data[2];
}

void runProgram(struct Program *program) {
    int instructionOffset = 0;

    while (instructionOffset < program->length) {
        switch (program->data[instructionOffset]) {
            case 1:
                program->data[program->data[instructionOffset + 3]] = 
                    program->data[program->data[instructionOffset + 1]] + program->data[program->data[instructionOffset + 2]];

                instructionOffset += 4;
                break;
            case 2:
                program->data[program->data[instructionOffset + 3]] = 
                    program->data[program->data[instructionOffset + 1]] * program->data[program->data[instructionOffset + 2]];
        
                instructionOffset += 4;
                break;
            case 99:
                instructionOffset = program->length;    
        }
    }
}

void printProgram(struct Program *program) {
    for (int i = 0; i < program->length; i++) {
        printf("%d%s", program->data[i], i < program->length - 1 ? "," : "");
    }

    printf("\n");
}

void freeProgram(struct Program *program) {
    if (program) {
        free(program->data);
        free(program);
    }
}

#endif