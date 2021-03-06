#include "quadRenderer.h"
#include "../../entity/camera/camera.h"
#include <iostream>
#include "../../math/Matrix.h"
#include "../../glActions/glFunctions.h"

QuadRenderer::QuadRenderer() {
	m_textureHandler.loadFromFile("test");
    m_model.addData({
        {
           -0.5,  0.5, 0,
            0.5,  0.5, 0,
            0.5, -0.5, 0,
           -0.5, -0.5, 0,
        },
        {
            0, 1,
            1, 1,
            1, 0,
            0, 0,
        },
        {
            0, 2, 1,
            2, 0, 3,
        }
    });
}
void QuadRenderer::addAt(const glm::vec3& pos) {
    m_quads.push_back(pos);
}
void QuadRenderer::renderQuads(const Camera& cam) {
    if (m_quads.empty()) return;
    m_basicShader.useShader();
    m_textureHandler.bindTexture();
    m_model.bindVAO();
    m_basicShader.setInt("texSampler", 0);
    glActiveTexture(GL_TEXTURE0);
    m_basicShader.loadProjectionMatrix(cam.getProjectionMatrix());
    m_basicShader.loadViewMatrix(cam.getViewMatrix());

    for (auto& quad : m_quads) {
        m_basicShader.loadModelMatrix(
            makeModelMatrix({quad, glm::vec3(0,0,0) })
        );
        GlFunctions::drawElements(m_model.getIndicesCount());
    }
    m_quads.clear();
}