#include "iss.h"
#include "opcodes.h"
#include <string.h>
#include <assert.h>
#include <string>
#include <vector>

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

	bool debug = false;
	if (debug) std::cout << " PC: " << pc << " ";

	switch (op) {
		case Opcode::ADDI:
			if (debug) std::cout << "ADDI" << " regs[instr.rs1()]: " << regs[instr.rs1()] << " instr.I_imm(): " << instr.I_imm(); 
			
			regs[instr.rd()] = regs[instr.rs1()] + instr.I_imm();
			break;

		// TODO: Student task 1: Finalize 'I' Instrution set
		
		case Opcode::SLTI:
			if (debug) std::cout << "SLTI";

			if ((int32_t)regs[instr.rs1()] < (int32_t)instr.I_imm())
				regs[instr.rd()] = 1; 
			else 
				regs[instr.rd()] = 0; 
			break;
		
		case Opcode::SLTIU:
			if (debug) std::cout << "SLTIU";

			if ((uint32_t)regs[instr.rs1()] < (uint32_t)instr.I_imm())
				regs[instr.rd()] = 1; 
			else 
				regs[instr.rd()] = 0; 
			break;
		
		case Opcode::XORI:
			if (debug) std::cout << "XORI";

			regs[instr.rd()] = regs[instr.rs1()] ^ instr.I_imm();
			break;

		case Opcode::ORI:
			if (debug) std::cout << "ORI";

			regs[instr.rd()] = regs[instr.rs1()] | instr.I_imm();
			break;

		case Opcode::ANDI:
			if (debug) std::cout << "ANDI";

			regs[instr.rd()] = regs[instr.rs1()] & instr.I_imm();
			break;
		
		case Opcode::SLLI:
			if (debug) std::cout << "SLLI";

			regs[instr.rd()] = regs[instr.rs1()] << instr.I_imm();
			break;
		
		case Opcode::SRLI:
			if (debug) std::cout << "SRLI";

			regs[instr.rd()] = regs[instr.rs1()] >> instr.I_imm();
			break;

		case Opcode::SRAI:
			if (debug) std::cout << "SRAI";

			regs[instr.rd()] = regs[instr.rs1()] >> instr.I_imm();
			break;
		

		// Register operations

		case Opcode::ADD:
			if (debug) std::cout << "ADD";

			regs[instr.rd()] = regs[instr.rs1()] + regs[instr.rs2()];
			break;

		case Opcode::SUB:
			if (debug) std::cout << "SUB";

			regs[instr.rd()] = regs[instr.rs1()] - regs[instr.rs2()];
			break;

		case Opcode::SLT:
			if (debug) std::cout << "SLT";

			regs[instr.rd()] = regs[instr.rs1()] - regs[instr.rs2()];
			break;

		case Opcode::SLL:
			if (debug) std::cout << "SLL";

			regs[instr.rd()] = regs[instr.rs1()] << regs[instr.rs2()];
			break;
		
		case Opcode::SLTU:
			if (debug) std::cout << "SLTU";	

			if ((uint32_t)regs[instr.rs1()] < (uint32_t)regs[instr.rs2()])
				regs[instr.rd()] = 1; 
			else 
				regs[instr.rd()] = 0; 
			break;
		
		case Opcode::XOR:
			if (debug) std::cout << "XOR";

			regs[instr.rd()] = regs[instr.rs1()] ^ regs[instr.rs2()];
			break;

		case Opcode::SRL:
			if (debug) std::cout << "SRL";

			regs[instr.rd()] = regs[instr.rs1()] >> regs[instr.rs2()];
			break;
		
		case Opcode::SRA:
			if (debug) std::cout << "SRA";

			regs[instr.rd()] = regs[instr.rs1()] >> regs[instr.rs2()];
			break;

		case Opcode::OR:
			std::cout << "OR";

			regs[instr.rd()] = regs[instr.rs1()] | regs[instr.rs2()];
			break;

		case Opcode::AND:
			if (debug) std::cout << "AND";

			regs[instr.rd()] = regs[instr.rs1()] & regs[instr.rs2()];
			break;

		case Opcode::BGE:
			if (debug) std::cout << "BGE";

			if ((int32_t)regs[instr.rs1()] >= (int32_t)regs[instr.rs2()])
				pc = last_pc + instr.B_imm();
			break;

		//rd = PC+4; PC += imm
		case Opcode::JAL:
		{
			if (debug) std::cout << "JAL";
			// Changed to try to fix c code
			regs[instr.rd()] = pc; 
			pc = last_pc + instr.J_imm();
			break;
		}
		
		// PC+4; PC = rs1 + imm
		case Opcode::JALR:
		{
			if (debug) std::cout << "JALR";
			if (instr.rd() == RegFile::x0 && instr.rs1() == RegFile::x1) {
				if (debug) std::cout << " - RET ";
				pc = regs[RegFile::x1];
			}
			else {
				// Changed to try to fix c code
				regs[instr.rd()] = pc; 
				pc = (regs[instr.rs1()] + instr.I_imm()) & (~1);
			}
			break;
		}

		// rd = imm << 12
		case Opcode::LUI:
			if (debug) std::cout << "LUI";
			regs[(int32_t)instr.rd()] = instr.U_imm(); // Removed << 12 to try to fix c code
			break;
		
		// rd = PC + (imm << 12)
		case Opcode::AUIPC:
			if (debug) std::cout << "AUIPC";

			regs[instr.rd()] = pc + instr.U_imm();  // Removed << 12 to try to fix c code
			break;

		// END

		case Opcode::SW: {
			if (debug) std::cout << "SW";

			const uint32_t addr = regs[instr.rs1()] + instr.S_imm();
			bus->store_word(addr, regs[instr.rs2()]);
			}
			break;

		case Opcode::LW: {
			if (debug) std::cout << "LW";

			const uint32_t addr = regs[instr.rs1()] + instr.I_imm();
			regs[instr.rd()] = bus->load_word(addr);
			}
			break;

		case Opcode::BLT:
			if (debug) std::cout << "BLT";

			if (regs[instr.rs1()] < regs[instr.rs2()])
				pc = last_pc + instr.B_imm();
			break;

		case Opcode::BEQ:
			if (debug) std::cout << "BEQ";

			if (regs[instr.rs1()] == regs[instr.rs2()])
				pc = last_pc + instr.B_imm();
			break;

		case Opcode::BGEU:
			if (debug) std::cout << "BGEU";

			if ((uint32_t)regs[instr.rs1()] >= (uint32_t)regs[instr.rs2()])
				pc = last_pc + instr.B_imm();
			break;

		// TODO: Student task 3 'M' Set
		case Opcode::MUL:
			if (debug) std::cout << "MUL";

			regs[instr.rd()] = regs[instr.rs1()] * regs[instr.rs2()];
			break;

		case Opcode::MULH:
			if (debug) std::cout << "MULH";

			regs[instr.rd()] = (int64_t)regs[instr.rs1()] * (int64_t)regs[instr.rs2()];
			break;

		case Opcode::MULHSU:
			if (debug) std::cout << "MULHSU";

			regs[instr.rd()] = (uint64_t)regs[instr.rs1()] * (uint64_t)((uint32_t)regs[instr.rs2()]);
			break;

		case Opcode::MULHU:
			if (debug) std::cout << "MULHU";

			regs[instr.rd()] = (uint64_t)((uint32_t)regs[instr.rs1()]) * (uint64_t)((uint32_t)regs[instr.rs2()]);
			break;

		case Opcode::DIV: 
			{
				if (debug) std::cout << "DIV";

				if (regs[instr.rs2()] == 0) {
					regs[instr.rd()] = -1;
				} else {
					regs[instr.rd()] = regs[instr.rs1()] / regs[instr.rs2()];
				}
				break;
			}

		case Opcode::DIVU:
			{
				if (debug) std::cout << "DIVU";

				if (regs[instr.rs2()] == 0) {
					regs[instr.rd()] = -1;
				} else {
					regs[instr.rd()] = (uint32_t)regs[instr.rs1()] / (uint32_t)regs[instr.rs2()];
				}
				break;
			}

		case Opcode::REM:
			{
				if (debug) std::cout << "REM";

				if (regs[instr.rs2()] == 0) {
					regs[instr.rd()] = (uint32_t)regs[instr.rs1()];
				} else {
					regs[instr.rd()] = (uint32_t)regs[instr.rs1()] % (uint32_t)regs[instr.rs2()];
				}
				break;
			}

		case Opcode::REMU:
			{
				if (debug) std::cout << "REMU";

				if (regs[instr.rs2()] == 0) {
					regs[instr.rd()] = regs[instr.rs1()];
				} else {
					regs[instr.rd()] = regs[instr.rs1()] % regs[instr.rs2()];
				}
				break;
			}

		case Opcode::ECALL: {
			if (debug) std::cout << "ECALL ";
			
			auto syscall = regs[RegFile::a7];
			switch (syscall) {
				case Syscalls::SYS_exit:
					std::cout << "syscall exit(" << regs[RegFile::a0] << ")" << std::endl;
					shall_exit = true;
					break;
				// TODO: Student task 2 "other syscalls"

				case Syscalls::printInt:
					std::cout << regs[RegFile::a0];
					break;

				case Syscalls::printChar:
					std::cout << (char)regs[RegFile::a0];
					break;

				case Syscalls::printString:
				{
					if (debug) std::cout << std::endl;
		
					uint32_t adress = regs[RegFile::a0];

				
					std::vector<char> buf = {};
 
					for (uint32_t i = 0; i < 10; i++) {
						uint32_t x = bus->load_word(adress + (i * 4));

						if ((x & 255) == 0) {
							break;
						}
						buf.push_back(x);

						if (((x >> 8) & 255) == 0) {
							break;
						}
						buf.push_back(x >> 8);

						if (((x >> 16) & 255) == 0) {
							break;
						}
						buf.push_back(x >> 16);

						if (((x >> 24) & 255) == 0) {
							break;
						}
						buf.push_back(x >> 24);

						std::string str(buf.begin(), buf.end());
					}

					std::string str(buf.begin(), buf.end());
					std::cout << str;
					
					break;
				}
				// ------ End Task 2
				default:
					throw std::runtime_error("unknown syscall " + std::to_string(syscall));
			}
			break;
		}

		default:
			throw std::runtime_error("unknown (or unimplemented) opcode " + std::to_string(op));
	}

	if (debug) std::cout << std::endl;

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
