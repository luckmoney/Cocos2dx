#pragma  once
#include "Framework/Cocos2dx.h"
namespace Cocos {


	class SceneMesh  {
	public:
		void AddVertexArrary(SceneVertexArrary&& data) {
			m_vertexArr.push_back(std::forward<SceneVertexArrary>(data));
		};
		void AddIndexArrary(SceneIndexArrary&&data) {
			m_indexArr.push_back(std::forward<SceneIndexArrary>(data));
		};

		std::vector<SceneVertexArrary>& GetSceneVertexArrary() {
			return m_vertexArr;
		};

		std::vector<SceneIndexArrary>& GetSceneIndexArrary() {
			return m_indexArr;
		}

	private:
		std::vector<SceneVertexArrary> m_vertexArr;
		std::vector<SceneIndexArrary> m_indexArr;
	};
}