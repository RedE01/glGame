#pragma once
#include <vector>
#include <memory>

#include "Scene.h"

namespace glGame {

	class SceneManager {
	public:
		SceneManager();

		void initScene();
		void updateScene(float deltatime);
		void callSceneOnRender();
		void addScene();
		void setActiveScene(int index);
		Scene* getActiveScene() const { return m_activeScene; };

		void initializeScene();
		void saveActiveScene();

	private:
		void loadScene(const char* fileName);

		Component* addComponent(std::string& component, GameObject* gameObject);

	private:
		std::vector<std::unique_ptr<Scene>> m_scenes;
		Scene* m_activeScene = nullptr;
	};

}