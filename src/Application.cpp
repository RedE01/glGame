#include "Application.h"
#include <iostream>

namespace glGame {

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		s_Instance = this;

		std::string title = "glGame";
		int width = 1280, height = 720;
		m_viewportAspectRatio = width / (float)height;
		m_window = std::make_unique<Window>(title, width, height);
		m_window->setEventFunction(std::bind(&Application::onEvent, this, std::placeholders::_1));
		Input::m_window = m_window.get();

		renderer.init(); // Initializes glew, has to be called before any opengl code

		m_assetManager = std::make_unique<AssetManager>();

		m_sceneManager = std::make_unique<SceneManager>();
		m_sceneManager->initializeScene();

		#ifdef GL_GAME_EDITOR
		m_editor = std::make_unique<Editor>(std::bind(&Application::onEvent, this, std::placeholders::_1), m_window.get(), renderer.getEditorFrameTexture(), m_viewportAspectRatio);
		#endif
	}

	void Application::run() {
		#ifdef GL_GAME_EDITOR
		m_editor->setActiveScene(m_sceneManager->getActiveScene());
		m_editor->setAssetManager(m_assetManager.get());
		#endif

		m_time = std::make_unique<Time>();

		while(m_running) {
			m_sceneManager->initScene();

			float deltatime = m_time->getDeltatime();
			m_sceneManager->updateScene(deltatime);
			#ifndef GL_GAME_EDITOR
				physics.stepSimulation(deltatime);
			#else
				m_editor->update(deltatime, m_focused);
			#endif


			renderer.beginRender();
			renderer.render(m_sceneManager->getActiveScene());
			
			#ifdef GL_GAME_EDITOR
			renderer.renderGizmos(m_editor->getGizmoObjects());
			#endif
			renderer.endRender();

			#ifdef GL_GAME_EDITOR
			m_editor->renderEditor();
			#endif

			Input::Update();
			m_window->pollEvents();
			m_window->swapBuffers();
		}
	}

	void Application::onEvent(Event& e) {
		if(e.isInCategory(EventCategory::Input)) {
			Input::HandleEvent(&e);
		}

		else if(e.isInCategory(EventCategory::Application)) {
			if(e.getEventType() == EventType::WindowClose) {
				m_running = false;
			}
		}

		else if(e.isInCategory(EventCategory::Editor)) {
			if(e.getEventType() == EventType::SaveScene) {
				std::cout << "Scene saved" << std::endl;
				m_sceneManager->saveActiveScene();
			}
			else if(e.getEventType() == EventType::GameFocused) {
				m_focused = true;
			}
			else if(e.getEventType() == EventType::GameUnfocused) {
				m_focused = false;
			}
		}
	}
}