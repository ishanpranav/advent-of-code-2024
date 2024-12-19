// day17a.c
// Copyright (c) 2024-2025 Ishan Pranav
// Licensed under the MIT license.

// Chronospatial Computer

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef DAY17
#define DAY17
#define BUFFER_SIZE 32
#define PROGRAM_SIZE 8
#define SAMPLE true
#endif

enum Opcode
{
    OPCODE_ADV = 0,
    OPCODE_BXL = 1,
    OPCODE_BST = 2,
    OPCODE_JNZ = 3,
    OPCODE_BXC = 4,
    OPCODE_OUT = 5,
    OPCODE_BDV = 6,
    OPCODE_CDV = 7
};

typedef enum Opcode Opcode;

enum Operand
{
    OPERAND_A = 4,
    OPERAND_B = 5,
    OPERAND_C = 6
};

typedef enum Operand Operand;

struct Word
{
    unsigned int literal : 3;
};

typedef struct Word Word;

struct Machine
{
    bool output;
    Word program[PROGRAM_SIZE];
    int a;
    int b;
    int c;
    unsigned int instructionPointer;
    unsigned int programSize;
};

typedef struct Machine Machine;

static int machine_evaluate(const Machine* instance, Word operand)
{
    if (operand.literal <= 3)
    {
        return operand.literal;
    }

    switch (operand.literal)
    {
    case OPERAND_A: return instance->a;
    case OPERAND_B: return instance->b;
    case OPERAND_C: return instance->c;
    }

    return 0;
}

int main()
{
    Machine machine;

    machine.output = false;
    machine.instructionPointer = 0;
    machine.programSize = 0;

    if (scanf("Register A: %d ", &machine.a) != 1)
    {
        machine.a = 0;
    }

    if (scanf("Register B: %d ", &machine.b) != 1)
    {
        machine.b = 0;
    }

    if (scanf("Register C: %d ", &machine.c) != 1)
    {
        machine.c = 0;
    }

    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, stdin))
    {
        int offset;

        sscanf(buffer, "Program: %n", &offset);

        for (char* p = strtok(buffer + offset, ","); p; p = strtok(NULL, ","))
        {
            machine.program[machine.programSize].literal = atoi(p);
            machine.programSize++;
        }
    }

#if SAMPLE
    printf("Output: ");
#endif

    while (machine.instructionPointer < machine.programSize)
    {
        Word opcode = machine.program[machine.instructionPointer];
        Word operand = machine.program[machine.instructionPointer + 1];

        switch (opcode.literal)
        {
        case OPCODE_ADV:
        {
            machine.a >>= machine_evaluate(&machine, operand);
        }
        break;

        case OPCODE_BXL:
        {
            machine.b ^= operand.literal;
        }
        break;

        case OPCODE_BST:
        {
            Word result;

            result.literal = machine_evaluate(&machine, operand);
            machine.b = result.literal;
        }
        break;

        case OPCODE_JNZ:
        {
            if (machine.a)
            {
                machine.instructionPointer = operand.literal;

                continue;
            }
        }
        break;

        case OPCODE_BXC:
        {
            machine.b ^= machine.c;
        }
        break;

        case OPCODE_OUT:
        {
            Word result;

            result.literal = machine_evaluate(&machine, operand);

            if (machine.output)
            {
                printf(",");
            }

            machine.output = true;

            printf("%d", result.literal);
        }
        break;

        case OPCODE_BDV:
        {
            machine.b = machine.a >> machine_evaluate(&machine, operand);
        }
        break;

        case OPCODE_CDV:
        {
            machine.c = machine.a >> machine_evaluate(&machine, operand);
        }
        break;
        }

        machine.instructionPointer += 2;
    }

#if SAMPLE
    printf(
        "\n\n"
        "Register A: %d\n"
        "Register B: %d\n"
        "Register C: %d\n" "\n"
        "Program: ",
        machine.a, machine.b, machine.c);

    if (machine.programSize)
    {
        printf("%d", machine.program[0].literal);

        for (unsigned int i = 1; i < machine.programSize; i++)
        {
            printf(",%d", machine.program[i].literal);
        }
    }
#endif

    printf("\n");

    return EXIT_SUCCESS;
}
