#include "context.h"
#include <GL/glew.h>

Context::Context() {
	sf::ContextSettings setting;
	setting.antialiasingLevel = 4;
	setting.majorVersion = 3;
	setting.minorVersion = 3;
	setting.depthBits = 24;
	setting.stencilBits = 8;
	
	m_window.create(
		{ 1280, 768 },
		"MineCraft Clone",
		sf::Style::Close,
		setting
	);
	glewInit();
	glewExperimental = GL_TRUE;
	glViewport(
		0,
		0,
		1280,
		768
	);
	glCullFace(GL_BACK);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//m_window.setFramerateLimit(144);
	//m_window.setVerticalSyncEnabled(true); //!!!: this vertical sync causing frame rate drop
}