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
		//	Instruction* next = NULL;
		Instruction(InstructionType t, int d) : type(t), data(d) {};
		bool is_dead();
	};

	int get_tenative_data(InstructionType type, const char i);
	InstructionType classify(const char t);
	std::vector<Instruction> make_instructions(std::fstream& fp);
	void brainfuck(const std::vector<Instruction>& is, unsigned int len);
}
