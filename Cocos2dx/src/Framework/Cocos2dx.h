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



class Application;
class InputSystem;
class SceneSystem;
class RenderSystem;



class Pass;
class ShadowPass;
class ForwardPass;

class SubPass;
class GeometrySubPass;
class SkyboxSubPass;
class TerrainSubPass;


#include "Framework/Common.h"





#include "Framework/IRuntimeModule.h"
#include "Framework/Application.h"
#include "Framework/InputSystem.h"
#include "Framework/RenderSystem.h"
#include "Framework/SceneObject.h"
#include "Framework/SceneSystem.h"
#include "Framework/Windows.h"

