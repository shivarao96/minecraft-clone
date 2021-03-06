#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "../../model/model.h"
#include "../../texture/textureHandler.h"
#include "../../shaders/basicShader/basicShader.h"

class Camera;
class QuadRenderer
{
public:
	QuadRenderer();
	void addAt(const glm::vec3& pos);
	void renderQuads(const Camera& cam);
private:
	std::vector<glm::vec3> m_quads;
	Model m_model;
	BasicShader m_basicShader;
	TextureHandler m_textureHandler;
};

