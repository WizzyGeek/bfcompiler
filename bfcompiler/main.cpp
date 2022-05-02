#include<iostream>
#include<fstream>
#include<string>

#include"utils.hpp"

using std::cout;
 
int main(int argc, char* argv[]) {
	unsigned int len = 10000;
	if (argc == 1) {
		cout << "Specify source file!\n";
		return 0;
	}
	else if (argc > 2) {
		try {
			len = std::stoi(argv[2]);
		}
		catch (...) {
			len = 10000;
		}
	}

	std::fstream fp;
	try {
		fp.open(argv[1]);
		//.open("C:/.dev/bfcompiler/examples/mandelbrot.bf");
	}
	catch (const std::fstream::failure er) {
		std::cerr << "Failed to open file: " << argv[1] << '\n';
		std::cerr << "Error message: " << er.what() << '\n';
		std::cerr << "Error code: " << er.code() << '\n';
		return 1;
	}
	if (!fp.is_open()) {
		std::cerr << "Failed to open specified file" << "\n";
		return 1;
	}

	try {
		std::vector<Instruction> ins = make_instructions(fp);
		brainfuck(ins, len);
		cout << "\n=== Program End ===";
		return 0;
	}
	catch (const std::invalid_argument er) {
		std::cerr << er.what() << '\n';
		return 1;
	}
	catch (const std::exception er) {
		std::cerr << er.what() << '\n';
		return 1;
	}
}