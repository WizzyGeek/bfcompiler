#include"opts.hpp"

// TODO: TEST
namespace bf {
	namespace opts {
		Insts offset_opt(const Insts& insts) {
			Insts ret = Insts(insts.size());
			size_t writer = 0;
			int last = -1;

			int lastmovs = 0;
			for (int k = 0; k < insts.size(); ++k) {
				Instruction i = insts[k];
				switch (i.type) {
					// failed, copy over
				case InstructionType::JMZ:
				case InstructionType::JNZ:
					if (last != -1) {
						auto temp2 = insts[last];
						ret.push_back(Instruction(temp2.type, temp2.data, lastmovs));
						ret.insert(ret.end(), insts.begin() + last + 1, insts.begin() + k + 1);
						last = -1;
					}
					break;
				case InstructionType::MOV:
					if (last < 0) {
						// Set last mov
						last = k;
						lastmovs = i.data;
					}
					else {
						auto linst = insts[last];
						auto lmovs = last;

						last = k; // Update last mov we leave after opt
						lastmovs = lastmovs + linst.data;

						for (int j = last + 1; j < k; j++) {
							auto temp = insts[j];
							temp.offset = lmovs;
							ret.push_back(temp);
						} // make and copy offset instruction
					}
				default:
					if (last < 0) {
						ret.push_back(i); // Not opting, just copy
					}
					break;
				}

				if (last != -1) { // copy left over
					auto temp2 = insts[last];
					ret.push_back(Instruction(temp2.type, temp2.data, lastmovs));
					ret.insert(ret.end(), insts.begin() + last + 1, insts.end());
				}
			}

			return ret;
		}
	}
}