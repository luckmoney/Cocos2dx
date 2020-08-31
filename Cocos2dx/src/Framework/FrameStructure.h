#pragma once
#include <stdint.h>


namespace Cocos {
	struct PerBatchConstants{};

	struct DrawBatchContext :PerBatchConstants {
		int32_t batchIndex{ 0 };
	};
}

