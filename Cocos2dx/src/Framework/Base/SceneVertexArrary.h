#pragma once

namespace Cocos {
	enum class VertexType{Float1,Float2,Float3,Float4};

	class SceneVertexArrary {
	public:
		const uint32_t* GetData() {
			return m_data;
		};

		const size_t& GetSize() {
			return m_size;
		};

		VertexType& GetDataType() { return m_type; }

	private:
		const uint32_t *m_data;
		const size_t m_size;
		VertexType& m_type;
	};
}