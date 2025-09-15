/**
 * @file basic_pu.h
 * @brief Header file for the Basic Processing Unit (BPU) interface.
 *
 * Defines enums, structures, and function prototypes for a simple processing unit
 * supporting basic arithmetic and procedure operations. The BPU features general-purpose
 * registers and a procedure register, and executes instructions defined by the BPUInstructionSet.
 *
 * Enums:
 * - BPUProcedures: Supported procedure operations (display, reset).
 * - BPUInstructionSet: Supported instruction types (MOV, ADD, SUB, MUL, SWITCH, LOAD_PROC,
 * PROC_CALL, EOP).
 * - BPURegister: Supported registers (A, B, procedure).
 *
 * Structures:
 * - BPUInstruction: Represents a single instruction, including type, target register, and value.
 * - basic_pu: Represents the BPU's registers.
 *
 * Functions:
 * - is_valid_u8: Checks if a value fits in an unsigned 8-bit integer.
 * - run_program: Executes a sequence of instructions on a BPU instance.
 */

#ifndef BASIC_PU_H
#define BASIC_PU_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Enum defining procedure operations for the BPU.
 *  DISPLAY_REGISTER_A - Display the value in register A
 *  DISPLAY_REGISTER_B - Display the value in register B
 *  DISPLAY_REGISTERS - Display values in both registers A and B
 *  RESET_REGISTERS - Reset both registers A and B to zero, and clear the procedure register
 */
enum BPUProcedures
{
    DISPLAY_REGISTER_A, // 0x00
    DISPLAY_REGISTER_B, // 0x01
    DISPLAY_REGISTERS,  // 0x02
    RESET_REGISTERS     // 0x03

};
/**
 * @brief Enum defining the instruction set for the BPU.
 *  BPU_MOV - Move value to register
 *  BPU_ADD - Add value to register
 *  BPU_SUB - Subtract value from register
 *  BPU_MUL - Multiply register by value
 *  BPU_SWITCH - Switch values between registers
 *  BPU_LOAD_PROC - Load procedure into procedure register
 *  BPU_PROC_CALL - Call procedure based on procedure register
 *  BPU_EOP - End of program
 */
enum BPUInstructionSet
{
    BPU_MOV,       // 0x00
    BPU_ADD,       // 0x01
    BPU_SUB,       // 0x02
    BPU_MUL,       // 0x03
    BPU_SWITCH,    // 0x04
    BPU_LOAD_PROC, // 0x05
    BPU_PROC_CALL, // 0x06
    BPU_EOP,       // 0x07

};

/**
 * @brief BPU registers enumeration.
 *  BPU_REGISTER_A - General-purpose register A
 *  BPU_REGISTER_B - General-purpose register B
 *  BPU_PROC_REGISTER - Procedure register for controlling procedure calls
 */
enum BPURegister
{
    BPU_REGISTER_A,
    BPU_REGISTER_B,
    BPU_PROC_REGISTER
};

/**
 * @brief Structure representing a basic processing unit (BPU) instruction.
 *
 * Contains the instruction type, associated register, and an integer value.
 *
 * @var single_instruction The instruction from the BPUInstructionSet enum.
 * @var at_register The register from the BPURegister enum.
 * @var value The value associated with the instruction or register.
 */
struct BPUInstruction
{
    enum BPUInstructionSet single_instruction;
    enum BPURegister at_register;
    int value;
};

/**
 * @brief Structure representing basic processor unit registers.
 *
 * Contains the following members:
 * - procedure_register: Fast unsigned 8-bit register for procedure control.
 * - register_A: Fast signed 64-bit general-purpose register A.
 * - register_B: Fast signed 64-bit general-purpose register B.
 */
struct basic_pu
{
    uint_fast8_t procedure_register;
    int_fast64_t register_A;
    int_fast64_t register_B;
};

/**
 * @brief Checks if a given integer value can be represented as an unsigned 8-bit integer (uint8_t).
 *
 * This function verifies whether the input integer falls within the valid range for an unsigned
 * 8-bit integer, which is [0, 255] inclusive.
 *
 * @param any_integer The integer value to check.
 * @return true if the value is within the range of uint8_t, false otherwise.
 */
bool is_valid_u8 (long long any_integer);

/**
 * @brief Executes a sequence of BPU instructions on the provided basic_pu instance.
 *
 * This function processes the array of instructions using the specified
 * basic_pu structure, performing the operations defined by each instruction.
 *
 * @param instructions Pointer to an array of BPUInstruction structures to execute.
 * @param bpu Pointer to the basic_pu instance on which instructions will be run.
 * @return int Status code indicating success or failure of execution.
 */
int run_program (struct BPUInstruction *instructions, struct basic_pu *bpu);

#endif