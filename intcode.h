#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

enum { READ, WRITE };

struct Program {
    char *identifier;
    
    int *data;
    int length;

    int input[2];
    int output[2];
};

struct Program *readProgram(char *filename) {
    FILE *programFile = fopen(filename, "r");

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

struct Program *copyProgram(struct Program *program, char *identifier) {
    struct Program *programCopy = (struct Program *)calloc(1, sizeof(struct Program));

    programCopy->identifier = identifier;
    programCopy->data = (int *)calloc(program->length, sizeof(int));

    for (int i = 0; i < program->length; i++) {
        programCopy->data[i] = program->data[i];
    }

    programCopy->length = program->length;

    return programCopy;
}

void resetProgram(struct Program *program, int *data) {
    for (int i = 0; i < program->length; i++) {
        program->data[i] = data[i];
    }
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

void printProgram(struct Program *program) {
    for (int i = 0; i < program->length; i++) {
        printf("%d%s", program->data[i], i < program->length - 1 ? "," : "");
    }

    printf("\n");
}

int programParameter(struct Program *program, int mode, int offset) {
    return mode == 0 ? program->data[program->data[offset]] : program->data[offset];
}

void runProgram(struct Program *program) {
    int offset = 0;

    while (offset < program->length) {
        int instruction = program->data[offset];

        int opcode = instruction % 100;
        instruction = instruction / 100;

        int mode1 = instruction % 10;
        instruction /= 10;

        int mode2 = instruction % 10;
        instruction /= 10;

        int mode3 = instruction;

        int parameter1;
        int parameter2;

        switch (opcode) {
            case 1:
                parameter1 = programParameter(program, mode1, offset + 1);
                parameter2 = programParameter(program, mode2, offset + 2);

                program->data[program->data[offset + 3]] = parameter1 + parameter2;

                offset += 4;
                break;
            case 2:
                parameter1 = programParameter(program, mode1, offset + 1);
                parameter2 = programParameter(program, mode2, offset + 2);

                program->data[program->data[offset + 3]] = parameter1 * parameter2;
        
                offset += 4;
                break;
            case 3:
                if (program->input[READ]) {
                    while(!read(program->input[READ], &parameter1, sizeof(parameter1)));
                } else {
                    scanf("%d", &parameter1);
                }

                program->data[program->data[offset + 1]] = parameter1;

                offset += 2;
                break;
            case 4:
                parameter1 = programParameter(program, mode1, offset + 1);

                if (program->output[WRITE]) {
                    write(program->output[WRITE], &parameter1, sizeof(int));
                } else {
                    printf("%d\n", parameter1);
                }

                offset += 2;
                break;
            case 5:
                parameter1 = programParameter(program, mode1, offset + 1);
                parameter2 = programParameter(program, mode2, offset + 2);

                if (parameter1) {
                    offset = parameter2;
                } else {
                    offset += 3;
                }
                break;
            case 6:
                parameter1 = programParameter(program, mode1, offset + 1);
                parameter2 = programParameter(program, mode2, offset + 2);

                if (!parameter1) {
                    offset = parameter2;
                } else {
                    offset += 3;
                }
                break;
            case 7:
                parameter1 = programParameter(program, mode1, offset + 1);
                parameter2 = programParameter(program, mode2, offset + 2);

                program->data[program->data[offset + 3]] = parameter1 < parameter2 ? 1 : 0;

                offset += 4;
                break;
            case 8:
                parameter1 = programParameter(program, mode1, offset + 1);
                parameter2 = programParameter(program, mode2, offset + 2);

                program->data[program->data[offset + 3]] = parameter1 == parameter2 ? 1 : 0;

                offset += 4;
                break;
            case 99:
                offset = program->length;    
        }
    }
}

void freeProgram(struct Program *program) {
    if (program) {
        free(program->data);

        if (program->input[READ]) {
            close(program->input[READ]);
        }
        if (program->input[WRITE]) {
            close(program->input[WRITE]);
        }

        if (program->output[READ]) {
            close(program->output[READ]);
        }
        if (program->output[WRITE]) {
            close(program->output[WRITE]);
        }

        free(program);
    }
}