#pragma once

namespace Cocos {
	enum class VertexType{Float1,Float2,Float3,Float4};

	class SceneVertexArrary {
	public:
		SceneVertexArrary(float *data,size_t size,VertexType type)
		:m_data(data)
		,m_size(size)
		,m_type(type){

		}


		const float* GetData() {
			return m_data;
		};

		const size_t& GetSize() {
			return m_size;
		};

		VertexType& GetDataType() { return m_type; }

	private:
		const float *m_data;
		const size_t m_size;
		VertexType m_type;
	};
}