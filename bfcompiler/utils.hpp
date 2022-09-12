#pragma once
#include<iostream>
#include<vector>

namespace bf {
	enum struct InstructionType : char {
		INC, MOV, JMZ, JNZ, IN, OUT, COMMENT
	};

	struct Instruction {
		InstructionType type;
		int data;
		short int offset;

		//	Instruction* next = NULL;
		Instruction(InstructionType t, size_t d);

		Instruction(InstructionType t, int d, int s) : type(t), data(d), offset(s) {};
		Instruction(InstructionType t, int d) : type(t), data(d), offset(0) {};
		Instruction(const Instruction& cp) {
			type = cp.type;
			data = cp.data;
			offset = cp.offset;
		};

		bool is_dead();
	};

	int get_tenative_data(InstructionType type, const char i);
	InstructionType classify(const char t);
	std::vector<Instruction> make_instructions(std::fstream& fp);
	void brainfuck(const std::vector<Instruction>& is, unsigned int len);
}
