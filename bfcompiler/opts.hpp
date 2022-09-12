#pragma once
#include"utils.hpp"

namespace bf {
	namespace opts {
		using Insts = std::vector<Instruction>;
		Insts offset_opt(Insts& insts);
	}
}