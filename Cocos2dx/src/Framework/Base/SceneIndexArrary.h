#pragma once
namespace Cocos {

	enum class IndexType {
		kIndexDataTypeInt8, kIndexDataTypeInt16, kIndexDataTypeInt32
	};

	class SceneIndexArrary {
	public:
		const uint32_t* GetData() {
			return m_data;
		}
		const size_t& GetSize() {
			return m_size;
		}

		IndexType& GetType() {
			return m_type;
		}

		const uint32_t GetCount() {
			return m_size;
		}

	private:
		const uint32_t* m_data;
		const size_t m_size;
		IndexType m_type;
	};
}