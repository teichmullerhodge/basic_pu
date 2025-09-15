#include "basic_pu/basic_pu.h"

int
main (int argc, char **argv)
{

    (void)argc;
    (void)argv;

    struct BPUInstruction instructions[7] = { { BPU_MOV, BPU_REGISTER_A, 10 },
                                              { BPU_MOV, BPU_REGISTER_B, 10 },
                                              { BPU_ADD, BPU_REGISTER_A, 10 },
                                              { BPU_ADD, BPU_REGISTER_B, 10 },
                                              { BPU_LOAD_PROC, 0x0, DISPLAY_REGISTERS },
                                              { BPU_PROC_CALL, 0x0, 0x0 },
                                              { BPU_EOP, 0x0, 0x0 }

    };

    struct basic_pu bpu = { 0x0, 0x0, 0x0 };

    run_program (instructions, &bpu);
    return 0;
}