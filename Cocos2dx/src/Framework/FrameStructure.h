#pragma once
#include <stdint.h>
#include <vector>

namespace Cocos {
	struct PerBatchConstants{};

	struct DrawBatchContext :PerBatchConstants {
		int32_t batchIndex{ 0 };
		unsigned int vao;
		unsigned int mode;
		unsigned int type;
		unsigned int count;
	};

	struct Frame {
		std::vector<DrawBatchContext> m_batchContext;
	};
}

