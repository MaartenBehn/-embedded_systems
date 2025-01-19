#include "iss.h"
#include "opcodes.h"
#include <string.h>
#include <assert.h>

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "bus.h"



void ISS::run_step() {
	number_of_steps_executed++;
	auto mem_word = bus->load_word(pc);
	Instruction instr(mem_word);
	auto op = decode(instr);
	pc += sizeof(uint32_t);

	switch (op) {
		case Opcode::ADDI:
			regs[instr.rd()] = regs[instr.rs1()] + instr.I_imm();
			break;

		// TODO: Student task 1: Finalize 'I' Instrution set
		
		case Opcode::SLTI:
			if ((int32_t)regs[instr.rs1()] < (int32_t)instr.I_imm())
				regs[instr.rd()] = 1; 
			else 
				regs[instr.rd()] = 0; 
			break;
		
		case Opcode::SLTIU:
			if ((uint32_t)regs[instr.rs1()] < (uint32_t)instr.I_imm())
				regs[instr.rd()] = 1; 
			else 
				regs[instr.rd()] = 0; 
			break;
		
		case Opcode::XORI:
			regs[instr.rd()] = regs[instr.rs1()] ^ instr.I_imm();
			break;

		case Opcode::ORI:
			regs[instr.rd()] = regs[instr.rs1()] | instr.I_imm();
			break;

		case Opcode::ANDI:
			regs[instr.rd()] = regs[instr.rs1()] & instr.I_imm();
			break;
		
		case Opcode::SLLI:
			regs[instr.rd()] = regs[instr.rs1()] << instr.I_imm();
			break;
		
		case Opcode::SRLI:
			regs[instr.rd()] = regs[instr.rs1()] >> instr.I_imm();
			break;

		case Opcode::SRAI:
			regs[instr.rd()] = regs[instr.rs1()] >> instr.I_imm();
			break;
		

		// Register operations

		case Opcode::ADD:
			regs[instr.rd()] = regs[instr.rs1()] + regs[instr.rs2()];
			break;

		case Opcode::SUB:
			regs[instr.rd()] = regs[instr.rs1()] - regs[instr.rs2()];
			break;

		case Opcode::SLT:
			regs[instr.rd()] = regs[instr.rs1()] - regs[instr.rs2()];
			break;

		case Opcode::SLL:
			regs[instr.rd()] = regs[instr.rs1()] << regs[instr.rs2()];
			break;
		
		case Opcode::SLTU:
			if ((uint32_t)regs[instr.rs1()] < (uint32_t)regs[instr.rs2()])
				regs[instr.rd()] = 1; 
			else 
				regs[instr.rd()] = 0; 
			break;
		
		case Opcode::XOR:
			regs[instr.rd()] = regs[instr.rs1()] ^ regs[instr.rs2()];
			break;

		case Opcode::SRL:
			regs[instr.rd()] = regs[instr.rs1()] >> regs[instr.rs2()];
			break;
		
		case Opcode::SRA:
			regs[instr.rd()] = regs[instr.rs1()] >> regs[instr.rs2()];
			break;

		case Opcode::OR:
			regs[instr.rd()] = regs[instr.rs1()] | regs[instr.rs2()];
			break;

		case Opcode::AND:
			regs[instr.rd()] = regs[instr.rs1()] & regs[instr.rs2()];
			break;

		case Opcode::BGE:
			if ((int32_t)regs[instr.rs1()] >= (int32_t)regs[instr.rs2()])
				pc = last_pc + instr.B_imm();
			break;

		//rd = PC+4; PC += imm
		case Opcode::JAL:
			regs[instr.rd()] = pc + 4; 
			pc = last_pc + instr.J_imm();
			break;

		// PC+4; PC = rs1 + imm
		case Opcode::JALR:
			regs[instr.rd()] = pc + 4; 
			pc = regs[instr.rs1()] + instr.J_imm();
			break;

		// rd = imm << 12
		case Opcode::LUI:
			regs[(int32_t)instr.rd()] = instr.U_imm() << 12;
			break;
		
		// rd = PC + (imm << 12)
		case Opcode::AUIPC:
			regs[instr.rd()] = pc + (instr.U_imm() << 12);
			break;

		// END

		case Opcode::SW: {
			const uint32_t addr = regs[instr.rs1()] + instr.S_imm();
			bus->store_word(addr, regs[instr.rs2()]);
			}
			break;

		case Opcode::LW: {
			const uint32_t addr = regs[instr.rs1()] + instr.I_imm();
			regs[instr.rd()] = bus->load_word(addr);
			}
			break;

		case Opcode::BLT:
			if (regs[instr.rs1()] < regs[instr.rs2()])
				pc = last_pc + instr.B_imm();
			break;

		case Opcode::BEQ:
			if (regs[instr.rs1()] == regs[instr.rs2()])
				pc = last_pc + instr.B_imm();
			break;

		case Opcode::BGEU:
			if ((uint32_t)regs[instr.rs1()] >= (uint32_t)regs[instr.rs2()])
				pc = last_pc + instr.B_imm();
			break;

		// TODO: Student task 2 'M' Set

		// TODO: Student Task 4 FLT and FLTZ

		case Opcode::ECALL: {
			auto syscall = regs[RegFile::a7];
			switch (syscall) {
				case Syscalls::SYS_exit:
					std::cout << "syscall exit(" << regs[RegFile::a0] << ")" << std::endl;
					shall_exit = true;
					break;
				// TODO: Student task 3 "other syscalls"
				// ------ End Task 2
				default:
					throw std::runtime_error("unknown syscall " + std::to_string(syscall));
			}
			break;
		}

		default:
			throw std::runtime_error("unknown (or unimplemented) opcode " + std::to_string(op));
	}

	// zero register is hardwired to zero value
	regs[RegFile::zero] = 0;
}


void ISS::init(Bus *bus, Address entrypoint, Address stackpointer) {
	this->bus = bus;
	regs[RegFile::sp] = stackpointer;
	pc = entrypoint;
}

void ISS::run() {
	assert(bus); // check that bus has been provided

	do {
		last_pc = pc;
		run_step();
	} while (!shall_exit);
}

void ISS::show() {
	regs.show();
	std::cout << "pc = 0x" << std::hex << pc << std::dec << std::endl;
	std::cout << "Number of steps executed: " << number_of_steps_executed << std::endl;
}
