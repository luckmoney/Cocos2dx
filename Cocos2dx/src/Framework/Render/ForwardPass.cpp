#include "Cocos2dx.h"

namespace Cocos {

	ForwardPass::~ForwardPass() {

	}

	void ForwardPass::Init() {
		GeometrySubPass *geo = new GeometrySubPass();
		m_subpasses.push_back(geo);

		SkyboxSubPass *sky = new SkyboxSubPass();
		m_subpasses.push_back(sky);

		TerrainSubPass *terr = new TerrainSubPass();
		m_subpasses.push_back(terr);
	}


	void ForwardPass::Draw() {
		auto iter = m_subpasses.begin();
		while (iter != m_subpasses.end())
		{
			(*iter)->Draw();
			++iter;
		}
	}
}