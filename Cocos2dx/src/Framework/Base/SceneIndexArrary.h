#pragma once
namespace Cocos {
	class SceneIndexArrary {
	public:
		const uint32_t* GetData() {
			return m_data;
		}
		const size_t& GetSize() {
			return m_size;
		}

	private:
		const uint32_t* m_data;
		const size_t m_size;
	};
}