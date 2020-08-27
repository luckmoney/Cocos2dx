#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <ostream>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



namespace Cocos {
	class InputSystem;
	class SceneSystem;
	class RenderSystem;
	class RednerAble;
	class Cube;
	class Pass;
	class ShadowPass;
	class ForwardPass;
	class SkyboxSubPass;
}



#include "Framework/Common.h"


#include "Framework/Render/Pass.h"
#include "Framework/Render/ForwardPass.h"
#include "Framework/Render/GeometrySubPass.h"
#include "Framework/Render/Material.h"
#include "Framework/Render/Shader.h"
#include "Framework/Render/SkyboxSubPass.h"
#include "Framework/Render/SubPass.h"
#include "Framework/Render/TerrainSubPass.h"
#include "Framework/Render/Texture.h"
#include "Framework/Render/ShadowPass.h"



#include "Framework/IRuntimeModule.h"
#include "Framework/Application.h"
#include "Framework/InputSystem.h"
#include "Framework/RenderSystem.h"
#include "Framework/SceneObject.h"
#include "Framework/SceneSystem.h"
#include "Framework/Windows.h"

#include "Framework/RenderAble.h"
#include "Framework/Cube.h"




