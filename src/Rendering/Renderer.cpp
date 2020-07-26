#include "Renderer.h"
#include "../Resources/Scene.h"
#include "../Components/Camera.h"
#include "../Components/MeshRenderer.h"
#include "../Components/Transform.h"
#include "Cubemap.h"
#include "Material.h"
#include "Light.h"
#include "UniformBuffer.h"

#include <iostream>

namespace glGame {

	void Renderer::init() {
		initGLEW();

		#ifdef GL_GAME_EDITOR
		m_editorFramebuffer = std::make_unique<FrameBuffer>();
		#endif

		m_cameraUniformBuffer = std::make_unique<UniformBuffer>(128);
		m_cameraUniformBuffer->addData(64, NULL);
		m_cameraUniformBuffer->addData(64, NULL);
		m_cameraUniformBuffer->bindingPoint(0);
	}

	void Renderer::submit(Model* model, const glm::mat4& modelMatrix) {
		m_objectRenderData = ObjectRenderData(model->getVertexArray(), model->getVerticiesCount(), m_objectRenderData.material, modelMatrix);
	}

	void Renderer::submit(VertexArray* vertexArray, const unsigned int& verticies, const glm::mat4& modelMatrix) {
		m_objectRenderData = ObjectRenderData(vertexArray, verticies, m_objectRenderData.material, modelMatrix);
	}

	void Renderer::submit(Cubemap* cubemap, Shader* shader) {
		m_skyboxRenderData = SkyboxRenderData(cubemap, shader);
	}

	void Renderer::submit(Light* light) {
		// Todo global uniform for lights
	}

	void Renderer::setMaterial(Material* material) {
		m_objectRenderData.material = material;
	}

	void Renderer::beginRender() {
		clearScreen();

		#ifdef GL_GAME_EDITOR
		//Render to frame texture
		m_editorFramebuffer->bind();
		#endif

		clearScreen();
	}

	void Renderer::render(Scene* scene) {
		if(scene->activeCamera.expired()) return;

		const glm::mat4& projectionMatrix = scene->activeCamera.lock()->getProjectionMatrix();
		const glm::mat4& viewMatrix = scene->activeCamera.lock()->getViewMatrix();

		m_cameraUniformBuffer->setData(0, (void*)&(projectionMatrix[0][0]));
		m_cameraUniformBuffer->setData(1, (void*)&(viewMatrix[0][0]));
		
		//Render scene
		unsigned int lightCountLastFrame = m_lightCount;
		m_lightCount = 0;
		std::vector<ObjectRenderData> frameRenderData;
		for(int i = 0; i < scene->getGameObjectCount(); ++i) {
			GameObject* gameObject = scene->getGameObject(i);

			m_objectRenderData.vao = nullptr;
			m_objectRenderData.material = nullptr;
			for(int j = 0; j < gameObject->getComponentSize(); ++j) {
				gameObject->getComponent(j)->onRender();
			}

			processRenderData(frameRenderData);
		}

		
		for(ObjectRenderData& objRenderData : frameRenderData) {
			if(objRenderData.vao) {
				if(objRenderData.material && !objRenderData.material->texture.expired() && !objRenderData.material->shader.expired()) {
					objRenderData.material->shader->useShader();

					objRenderData.material->texture->bind();
					
					objRenderData.vao->bind();
					objRenderData.material->shader->setUniformMat4("u_model", &(objRenderData.modelMatrix[0][0]));
					glDrawArrays(GL_TRIANGLES, 0, objRenderData.verticies);
				}

			}
		}

		if(m_skyboxRenderData.cubemap && m_skyboxRenderData.shader) {
			glDepthMask(GL_FALSE);
			glDepthFunc(GL_LEQUAL);
			
			m_skyboxRenderData.shader->useShader();
			m_skyboxRenderData.shader->setUniformMat4("u_projection", &(projectionMatrix[0][0]));
			m_skyboxRenderData.shader->setUniformMat4("u_view", &(viewMatrix[0][0]));
			m_skyboxRenderData.cubemap->bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);

			m_skyboxRenderData = SkyboxRenderData();
			glDepthMask(GL_TRUE);
			glDepthFunc(GL_LESS);
		}
	}

	void Renderer::renderGizmos(const std::vector<GameObject*>& gizmoObjects) {
		glClear(GL_DEPTH_BUFFER_BIT);
		for(GameObject* go : gizmoObjects) {
			go->onRender();
		}
	}

	void Renderer::endRender() {
		#ifdef GL_GAME_EDITOR
		m_editorFramebuffer->unbind();
		#endif
	}

	void Renderer::initGLEW() {
		if (glewInit() != GLEW_OK) {
			std::cout << "Could not initialize GLEW" << std::endl;
			return;
		}

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::processRenderData(std::vector<ObjectRenderData>& frameRenderData) {
		frameRenderData.push_back(m_objectRenderData);
	}

	void Renderer::clearScreen() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
}
