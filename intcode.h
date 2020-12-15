#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

enum { READ, WRITE };

struct Program {
    char *identifier;
    
    long *data;
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

        struct Program *program = (struct Program *)calloc(1, sizeof(struct Program));

        program->data = (long *)calloc(length * 2, sizeof(long));
        program->length = length;

        int dataIndex = 0;

        fseek(programFile, 0, SEEK_SET);

        long input;

        while (dataIndex < length) {
            fscanf(programFile, "%ld%c", &input, &ch);

            program->data[dataIndex++] = input;
        }

        fclose(programFile);

        return program;
    }

    return NULL;
}

struct Program *copyProgram(struct Program *program, char *identifier) {
    struct Program *programCopy = (struct Program *)calloc(1, sizeof(struct Program));

    programCopy->identifier = identifier;
    programCopy->data = (long *)calloc(program->length, sizeof(long));

    for (int i = 0; i < program->length; i++) {
        programCopy->data[i] = program->data[i];
    }

    programCopy->length = program->length;

    return programCopy;
}

void resetProgram(struct Program *program, long *data) {
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
        printf("%ld%s", program->data[i], i < program->length - 1 ? "," : "");
    }

    printf("\n");
}

long readParameter(struct Program *program, int mode, int offset, int relativeBase) {
    switch (mode) {
        case 1:
            return program->data[offset];
        case 2:
            return program->data[relativeBase + program->data[offset]];
        default:
            return program->data[program->data[offset]];
    }
}

void writeData(struct Program *program, int mode, int offset, int relativeBase, long data) {
    switch (mode) {
        case 1:
            program->data[offset] = data;
            break;
        case 2:
            program->data[relativeBase + program->data[offset]] = data;
            break;
        default:
            program->data[program->data[offset]] = data;
            break;
    }
}

void runProgram(struct Program *program) {
    int offset = 0;
    int relativeBase = 0;

    while (offset < program->length) {
        int instruction = program->data[offset];

        int opcode = instruction % 100;
        instruction = instruction / 100;

        int mode1 = instruction % 10;
        instruction /= 10;

        int mode2 = instruction % 10;
        instruction /= 10;

        int mode3 = instruction;

        long parameter1;
        long parameter2;

        switch (opcode) {
            case 1:
                parameter1 = readParameter(program, mode1, offset + 1, relativeBase);
                parameter2 = readParameter(program, mode2, offset + 2, relativeBase);

                writeData(program, mode3, offset + 3, relativeBase, parameter1 + parameter2);

                offset += 4;
                break;
            case 2:
                parameter1 = readParameter(program, mode1, offset + 1, relativeBase);
                parameter2 = readParameter(program, mode2, offset + 2, relativeBase);

                writeData(program, mode3, offset + 3, relativeBase, parameter1 * parameter2);
        
                offset += 4;
                break;
            case 3:
                if (program->input[READ]) {
                    while(!read(program->input[READ], &parameter1, sizeof(parameter1)));
                } else {
                    scanf("%ld", &parameter1);
                }

                writeData(program, mode1, offset + 1, relativeBase, parameter1);

                offset += 2;
                break;
            case 4:
                parameter1 = readParameter(program, mode1, offset + 1, relativeBase);

                if (program->output[WRITE]) {
                    write(program->output[WRITE], &parameter1, sizeof(parameter1));
                } else {
                    printf("%ld\n", parameter1);
                }

                offset += 2;
                break;
            case 5:
                parameter1 = readParameter(program, mode1, offset + 1, relativeBase);
                parameter2 = readParameter(program, mode2, offset + 2, relativeBase);

                if (parameter1) {
                    offset = parameter2;
                } else {
                    offset += 3;
                }
                break;
            case 6:
                parameter1 = readParameter(program, mode1, offset + 1, relativeBase);
                parameter2 = readParameter(program, mode2, offset + 2, relativeBase);

                if (!parameter1) {
                    offset = parameter2;
                } else {
                    offset += 3;
                }
                break;
            case 7:
                parameter1 = readParameter(program, mode1, offset + 1, relativeBase);
                parameter2 = readParameter(program, mode2, offset + 2, relativeBase);

                writeData(program, mode3, offset + 3, relativeBase, parameter1 < parameter2 ? 1 : 0);

                offset += 4;
                break;
            case 8:
                parameter1 = readParameter(program, mode1, offset + 1, relativeBase);
                parameter2 = readParameter(program, mode2, offset + 2, relativeBase);

                writeData(program, mode3, offset + 3, relativeBase, parameter1 == parameter2 ? 1 : 0);

                offset += 4;
                break;
            case 9:
                parameter1 = readParameter(program, mode1, offset + 1, relativeBase);
                
                relativeBase += parameter1;

                offset += 2;
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