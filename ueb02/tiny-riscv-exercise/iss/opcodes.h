#pragma once

#include <stdint.h>
#include "bit_range.h"


struct Instruction {
    Instruction(uint32_t instr)
            : instr(instr) {
    }

    inline uint32_t csr() {
        return BIT_RANGE(instr, 31, 20) >> 20;
    }

    inline uint32_t zimm() {
        return BIT_RANGE(instr, 19, 15) >> 15;
    }

    inline uint32_t shamt() {
        return (BIT_RANGE(instr, 24, 20) >> 20);
    }

    inline int32_t funct3() {
        return (BIT_RANGE(instr, 14, 12) >> 12);
    }

    inline int32_t funct12() {
        // cast to unsigned to avoid sign extension when shifting
        return (BIT_RANGE((uint32_t)instr, 31, 20) >> 20);
    }

    inline int32_t funct7() {
        // cast to unsigned to avoid sign extension when shifting
        return (BIT_RANGE((uint32_t)instr, 31, 25) >> 25);
    }

    inline int32_t funct5() {
        // cast to unsigned to avoid sign extension when shifting
        return (BIT_RANGE((uint32_t)instr, 31, 27) >> 27);
    }

    inline bool aq() {
        return BIT_SINGLE(instr, 26);
    }

    inline bool rl() {
        return BIT_SINGLE(instr, 25);
    }

    inline int32_t opcode() {
        return BIT_RANGE(instr, 6, 0);
    }


    inline int32_t J_imm() {
        return (BIT_SINGLE(instr,31) >> 11) | BIT_RANGE(instr,19,12) | (BIT_SINGLE(instr,20) >> 9) | (BIT_RANGE(instr,30,21) >> 20);
    }

    inline int32_t I_imm() {
        return BIT_RANGE(instr,31,20) >> 20;
    }

    inline int32_t S_imm() {
        return (BIT_RANGE(instr,31,25) >> 20) | (BIT_RANGE(instr,11,7) >> 7);
    }

    inline int32_t B_imm() {
        return (BIT_SINGLE(instr,31) >> 19) | (BIT_SINGLE(instr,7) << 4) | (BIT_RANGE(instr,30,25) >> 20) | (BIT_RANGE(instr,11,8) >> 7);
    }

    inline int32_t U_imm() {
        return BIT_RANGE(instr,31,12);
    }


    inline uint32_t rs1() {
        return (instr & (((1 << 5) - 1) << 15)) >> 15;
    }

    inline uint32_t rs2() {
        return (instr & (((1 << 5) - 1) << 20)) >> 20;
    }

    inline uint32_t rd() {
        return (instr & (((1 << 5) - 1) << 7)) >> 7;
    }

private:
    // use signed variable to have correct sign extension in immediates
    int32_t instr;
};

namespace Opcode {
    enum parts {
        OP_LUI    = 0b0110111,
        OP_AUIPC  = 0b0010111,
        OP_JAL    = 0b1101111,
        OP_JALR   = 0b1100111,
        F3_JALR   = 0b000,

        OP_LB     = 0b0000011,
        F3_LB     = 0b000,
        F3_LH     = 0b001,
        F3_LW     = 0b010,
        F3_LBU    = 0b100,
        F3_LHU    = 0b101,

        OP_SB     = 0b0100011,
        F3_SB     = 0b000,
        F3_SH     = 0b001,
        F3_SW     = 0b010,

        OP_BEQ    = 0b1100011,
        F3_BEQ    = 0b000,
        F3_BNE    = 0b001,
        F3_BLT    = 0b100,
        F3_BGE    = 0b101,
        F3_BLTU   = 0b110,
        F3_BGEU   = 0b111,

        OP_ADDI   = 0b0010011,
        F3_ADDI   = 0b000,
        F3_SLTI   = 0b010,
        F3_SLTIU  = 0b011,
        F3_XORI   = 0b100,
        F3_ORI    = 0b110,
        F3_ANDI   = 0b111,
        F3_SLLI   = 0b001,
        F3_SRLI   = 0b101,
        F7_SRLI   = 0b0000000,
        F7_SRAI   = 0b0100000,

        // TODO: Task 1
        // ADD,..., Register - Register Operations
        OP_ADD  = 0b0110011,
        F3_ADD  = 0b000,
        // F3_SUB  = 0b000,
        F3_SLTU = 0b011,
        F3_XOR  = 0b100,
        F3_OR   = 0b110,
        F3_AND  = 0b111,
        F3_SLL  = 0b001,
        F3_SRL  = 0b101,
        F3_SLT  = 0b010,
        // F3_SRA  = 0b101,
        F7_ADD = 0b0000000,
        F7_SUB = 0b0100000,
        F7_SLTU = 0b0000000,
        F7_XOR = 0b0000000,
        F7_OR = 0b0000000,
        F7_AND = 0b0000000,
        F7_SLL = 0b0000000,
        F7_SRL = 0b0000000,
        F7_SLT = 0b0000000,
        F7_SRA = 0b0100000,
        // End Task 1

        // TODO: Task 3 M-Extension
        // OP_MUL    = 0b0110011,
        // F3_MUL    = 0b000,
        // F3_MULH   = 0b001,
        // F3_MULHSU = 0b010,
        // F3_MULHU  = 0b011,
        // F3_DIV    = 0b100,
        // F3_DIVU   = 0b101,
        // F3_REM    = 0b110,
        // F3_REMU   = 0b111,
        F7_MUL    = 0b0000001,
        F7_MULH   = 0b0000001,
        F7_MULHSU = 0b0000001,
        F7_MULHU  = 0b0000001,
        F7_DIV    = 0b0000001,
        F7_DIVU   = 0b0000001,
        F7_REM    = 0b0000001,
        F7_REMU   = 0b0000001,
        // End Task 3

        OP_ECALL   = 0b1110011,
        F3_SYS     = 0b000,
        F12_ECALL  = 0b000000000000,
        F12_EBREAK = 0b000000000001,
        //begin:privileged-instructions
        F12_URET   = 0b000000000010,
        F12_SRET   = 0b000100000010,
        F12_MRET   = 0b001100000010,
        F12_WFI    = 0b000100000101,
        F7_SFENCE_VMA = 0b0001001,
        //end:privileged-instructions
        F3_CSRRW   = 0b001,
        F3_CSRRS   = 0b010,
        F3_CSRRC   = 0b011,
        F3_CSRRWI  = 0b101,
        F3_CSRRSI  = 0b110,
        F3_CSRRCI  = 0b111,

        OP_AMO        = 0b0101111,
        F5_LR_W       = 0b00010,
        F5_SC_W       = 0b00011,
        F5_AMOSWAP_W  = 0b00001,
        F5_AMOADD_W   = 0b00000,
        F5_AMOXOR_W   = 0b00100,
        F5_AMOAND_W   = 0b01100,
        F5_AMOOR_W    = 0b01000,
        F5_AMOMIN_W   = 0b10000,
        F5_AMOMAX_W   = 0b10100,
        F5_AMOMINU_W  = 0b11000,
        F5_AMOMAXU_W  = 0b11100,
        
        // TODO: Task 4 "Custom Instruction"
        OP_FOR   = 0b0001011,
        F3_FLT   = 0b000,
        F3_FNEQZ = 0b001,
		// End Task 4
    };

    enum mapping {
        UNDEF = 0,

        // RV32I Base Instruction Set
        LUI = 1,
        AUIPC,
        JAL,
        JALR,
        BEQ,
        BNE,
        BLT,
        BGE,
        BLTU,
        BGEU,
        LB,
        LH,
        LW,
        LBU,
        LHU,
        SB,
        SH,
        SW,
        ADDI,
        SLTI,
        SLTIU,
        XORI,
        ORI,
        ANDI,
        SLLI,
        SRLI,
        SRAI,
        ADD,
        SUB,
        SLL,
        SLT,
        SLTU,
        XOR,
        SRL,
        SRA,
        OR,
        AND,
        ECALL,
        EBREAK,
        CSRRW,
        CSRRS,
        CSRRC,
        CSRRWI,
        CSRRSI,
        CSRRCI,

        // RV32M Standard Extension
        MUL,
        MULH,
        MULHSU,
        MULHU,
        DIV,
        DIVU,
        REM,
        REMU,
        
        // Operations for Student Task 4
        FLT,
        FNEQZ,
    };
}

static Opcode::mapping decode(Instruction &instr) {
    using namespace Opcode;

    switch (instr.opcode()) {
        case OP_LUI:
            return Opcode::LUI;

        case OP_AUIPC:
            return Opcode::AUIPC;

        case OP_JAL:
            return Opcode::JAL;

        case OP_JALR: {
            assert (instr.funct3() == F3_JALR);
            return Opcode::JALR;
        }

        case OP_BEQ: {
            switch (instr.funct3()) {
                case F3_BEQ:
                    return BEQ;
                case F3_BNE:
                    return BNE;
                case F3_BLT:
                    return BLT;
                case F3_BGE:
                    return BGE;
                case F3_BLTU:
                    return BLTU;
                case F3_BGEU:
                    return BGEU;
            }
            break;
        }

        case OP_LB: {
            switch (instr.funct3()) {
                case F3_LB:
                    return LB;
                case F3_LH:
                    return LH;
                case F3_LW:
                    return LW;
                case F3_LBU:
                    return LBU;
                case F3_LHU:
                    return LHU;
            }
            break;
        }

        case OP_SB: {
            switch (instr.funct3()) {
                case F3_SB:
                    return SB;
                case F3_SH:
                    return SH;
                case F3_SW:
                    return SW;
            }
            break;
        }

        // TODO Student Task 1 & 3:
        case OP_ADD: // 0110011 also OP_MUL
        {
            switch (instr.funct3()) {
                case F3_ADD: // 0x0
                {
                    switch (instr.funct7())
                    {
                    case F7_ADD: // 0x00
                        return ADD;

                    case F7_SUB: // 0x20
                        return SUB;
                    
                    case F7_MUL: // 0x01
                        return MUL;
                    }
                    break;
                }

                case F3_XOR: // 0x4
                {
                    switch (instr.funct7())
                    {
                    case F7_XOR: // 0x00
                        return XOR;

                    case F7_DIV: // 0x01
                        return DIV;
                    }
                    break;
                }

                case F3_OR:   // 0x6
                {
                    switch (instr.funct7())
                    {
                    case F7_OR: // 0x00
                        return OR;

                    case F7_REM: // 0x01
                        return REM;
                    }
                    break;
                }

                case F3_AND:  // 0x7
                {
                    switch (instr.funct7())
                    {
                    case F7_AND: // 0x00
                        return OR;

                    case F7_REMU: // 0x01
                        return REMU;
                    }
                    break;
                }

                case F3_SLL: // 0x1
                {
                    switch (instr.funct7())
                    {
                    case F7_SLL: // 0x00
                        return SLL;

                    case F7_MULH: // 0x01
                        return MULH;
                    }
                    break;
                }
                case F3_SRL:  // 0x5
                {
                    switch (instr.funct7())
                    {
                    case F7_SRL: // 0x00
                        return SRL;

                    case F7_SRA: // 0x20
                        return SRA;
                    
                    case F7_DIVU: // 0x01
                        return DIVU;
                    }
                    break;
                }

                case F3_SLT:  // 0x2
                {
                    switch (instr.funct7())
                    {
                    case F7_SLT: // 0x00
                        return SLT;

                    case F7_MULHSU: // 0x01
                        return MULHSU;
                    }
                    break;
                }

                case F3_SLTU: // 0x3
                {
                    switch (instr.funct7())
                    {
                    case F7_SLTU: // 0x00
                        return SLTU;

                    case F7_MULHU: // 0x01
                        return MULHU;
                    }
                    break;
                }
                break;
            }
        }


        case OP_ADDI:
        {
            switch (instr.funct3()) {
                case F3_ADDI:
                    return ADDI;

                case F3_SLTI:
                    return SLTI;
        
                case F3_SLTIU:
                    return SLTIU;

                case F3_XORI:
                    return XORI;

                case F3_ORI:
                    return ORI;

                case F3_ANDI:
                    return ANDI;

                case F3_SLLI:
                    return SLLI;

                case F3_SRLI: {
                    switch (instr.funct7())
                    {
                    case F7_SRLI:
                        return SRLI;

                    case F7_SRAI:
                        return SRAI;
                    }
                }
            }
            
            break;
        }

        case OP_ECALL: {
            switch (instr.funct3()) {
                case F3_SYS: {
                    switch (instr.funct12()) {
                        case F12_ECALL:
                            return ECALL;
                        case F12_EBREAK:
                            return EBREAK;
                    }
                    break;
                }
                case F3_CSRRW:
                    return CSRRW;
                case F3_CSRRS:
                    return CSRRS;
                case F3_CSRRC:
                    return CSRRC;
                case F3_CSRRWI:
                    return CSRRWI;
                case F3_CSRRSI:
                    return CSRRSI;
                case F3_CSRRCI:
                    return CSRRCI;
            }
            break;
        }

        // TODO: Student Task 4
        // Decode FLZ FLTZ

        case OP_FOR: {
            switch (instr.funct3()) {
                case F3_FLT:
                    return FLT;
                case F3_FNEQZ:
                    return FNEQZ;
            }
            break;
        }
    }

    throw std::runtime_error("unknown instruction " + std::to_string(instr.opcode()) );
}
