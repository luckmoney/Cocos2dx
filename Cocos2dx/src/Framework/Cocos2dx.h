#pragma once


#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <ostream>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Application;
class InputSystem;
class SceneSystem;
class RenderSystem;

class PipelineStateManager;
class AssetsManager;


class Pass;
class ShadowPass;
class ForwardPass;

class SubPass;
class GeometrySubPass;
class SkyboxSubPass;
class TerrainSubPass;

class OpenglRender;

class PipelineState;




#include "Framework/IRuntimeModule.h"
#include "Framework/Common.h"
#include "Framework/FrameStructure.h"

#include "Framework/Base/SceneObject.h"
#include "Framework/Base/SceneObjectSkyBox.h"
#include "Framework/Base/SceneVertexArrary.h"
#include "Framework/Base/SceneIndexArrary.h"
#include "Framework/Base/SceneObjectLight.h"
#include "Framework/Base/SceneObjectTexture.h"
#include "Framework/Base/SceneMesh.h"
#include "Framework/Base/ParameterValueMap.h"
#include "Framework/Base/SceneObjectMaterial.h"



#include "Framework/Render/Pass.h"
#include "Framework/Render/SubPass.h"
#include "Framework/Render/ForwardPass.h"
#include "Framework/Render/GeometrySubPass.h"

#include "Framework/Render/Shader.h"
#include "Framework/Render/ShadowPass.h"
#include "Framework/Render/SkyboxSubPass.h"
#include "Framework/Render/TerrainSubPass.h"
#include "Framework/Render/Texture.h"



#include "Framework/Application.h"
#include "Framework/InputSystem.h"
#include "Framework/RenderSystem.h"

#include "Framework/SceneSystem.h"
#include "Framework/Windows.h"
#include "Framework/PipelineStateManager.h"
#include "Framework/AssetsManager.h"
#include "Framework/PipelineStateManager.h"