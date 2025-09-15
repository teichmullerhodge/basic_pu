#include "basic_pu.h"

#include <stdio.h>

bool
is_valid_u8 (long long any_integer)
{
    return any_integer >= 0 && any_integer <= 255;
}

int
run_program (struct BPUInstruction *instructions, struct basic_pu *bpu)
{
    if (bpu == NULL)
        {
            perror ("bpu is null at run_program.\n");
            return -1;
        }

    if (instructions == NULL)
        {
            perror ("instructions is null at run_program.\n");
            return -1;
        }

    size_t instruction_index = 0;
    enum BPUInstructionSet instruction = instructions[instruction_index].single_instruction;

    while (instruction != BPU_EOP)
        {
            const enum BPURegister _register
                = instructions[instruction_index].at_register; // register is a reserved keyword.
            const int value = instructions[instruction_index].value;

            switch (instruction)
                {
                case BPU_MOV:
                    {
                        if (_register == BPU_REGISTER_A)
                            {
                                bpu->register_A = value;
                                break;
                            }
                        if (_register == BPU_REGISTER_B)
                            {
                                bpu->register_B = value;
                                break;
                            }
                        if (_register == BPU_PROC_REGISTER && is_valid_u8 (value))
                            {
                                bpu->procedure_register = value;
                                break;
                            }

                        break;
                    }
                case BPU_ADD:
                    {
                        if (_register == BPU_REGISTER_A)
                            {
                                bpu->register_A += value;
                                break;
                            }
                        if (_register == BPU_REGISTER_B)
                            {
                                bpu->register_B += value;
                                break;
                            }
                        if (_register == BPU_PROC_REGISTER
                            && is_valid_u8 (bpu->procedure_register + value))
                            {
                                bpu->procedure_register += value;
                                break;
                            }

                        break;
                    }

                case BPU_SUB:
                    {
                        if (_register == BPU_REGISTER_A)
                            {
                                bpu->register_A -= value;
                                break;
                            }
                        if (_register == BPU_REGISTER_B)
                            {
                                bpu->register_B -= value;
                                break;
                            }
                        if (_register == BPU_PROC_REGISTER
                            && is_valid_u8 (bpu->procedure_register - value))
                            {
                                bpu->procedure_register -= value;
                                break;
                            }

                        break;
                    }
                case BPU_MUL:
                    {
                        if (_register == BPU_REGISTER_A)
                            {
                                bpu->register_A *= value;
                                break;
                            }
                        if (_register == BPU_REGISTER_B)
                            {
                                bpu->register_B *= value;
                                break;
                            }
                        if (_register == BPU_PROC_REGISTER)
                            {
                                const int result = bpu->procedure_register * value;
                                if (is_valid_u8 (result))
                                    bpu->procedure_register = result;

                                break;
                            }

                        break;
                    }
                case BPU_SWITCH:
                    {
                        if (_register == BPU_REGISTER_A)
                            {

                                bpu->register_A = bpu->register_B;
                                break;
                            }
                        if (_register == BPU_REGISTER_B)
                            {

                                bpu->register_B = bpu->register_A;
                                break;
                            }
                        if (_register == BPU_PROC_REGISTER)
                            {

                                break;
                            }
                        break;
                    }
                case BPU_LOAD_PROC:
                    {
                        if (is_valid_u8 (value))
                            bpu->procedure_register = value;
                        break;
                    }
                case BPU_PROC_CALL:
                    {
                        if (bpu->procedure_register == DISPLAY_REGISTER_A)
                            {
                                printf ("register_A: %ld\n", bpu->register_A);
                                break;
                            }
                        if (bpu->procedure_register == DISPLAY_REGISTER_B)
                            {
                                printf ("register_B: %ld\n", bpu->register_B);
                                break;
                            }
                        if (bpu->procedure_register == DISPLAY_REGISTERS)
                            {
                                printf ("register_A: %ld - register_B: %ld\n", bpu->register_A,
                                        bpu->register_B);
                                break;
                            }
                        if (bpu->procedure_register == RESET_REGISTERS)
                            {
                                bpu->register_A = 0x0;
                                bpu->register_B = 0x0;
                                bpu->procedure_register = 0x0;
                                break;
                            }
                        break;
                    }
                case BPU_EOP:
                    {
                        break;
                    }
                }

            instruction_index++;
            instruction = instructions[instruction_index].single_instruction;
        }

    return 0;
}