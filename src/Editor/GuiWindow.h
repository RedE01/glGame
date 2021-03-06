#pragma once
#include <memory>
#include <vector>
#include <functional>
#include "../Events/EditorEvent.h"
#include "../Math/Vector.h"

namespace glGame {

	class Scene;
	class PublicVariable;
	class AssetManager;
	class GameObject;
	class Editor;
	class Texture;
	namespace assetInternal { class AssetT; }

	class GuiWindow {
	public:
		GuiWindow() = default;

		virtual const char* getWindowName() = 0;
		virtual void renderWindow() = 0;

		inline void setEventFunction(std::function<void(Event&)>& eventFunction) { m_eventFunction = &eventFunction; }
		void setEditor(Editor* editor) { m_editor = editor; }

	public:
		bool isOpen = true;
		std::function<void(Event&)>* m_eventFunction = nullptr;
		int windowFlags = 0;

	protected:
		Editor* m_editor;
	};

	class ViewportWindow : public GuiWindow {
	public:
		ViewportWindow(Vector2i viewportSize);
		~ViewportWindow();

		void setTexture(std::shared_ptr<Texture> texture);

		inline virtual const char* getWindowName() { return "Viewport"; }
		virtual void renderWindow() override;

	public:
		float viewportX, viewportY, viewportWidth, viewportHeight;

	private:
		std::shared_ptr<Texture> m_viewportTexture;
		Vector2i m_viewportSize;
		bool m_focused;
	};

	class SceneWindow : public GuiWindow {
	public:
		SceneWindow(Scene* scene);
		SceneWindow();

		inline void setScene(Scene* scene) { m_scene = scene; }

		inline virtual const char* getWindowName() { return "Scene"; }
		virtual void renderWindow() override;

	private:
		Scene* m_scene;
	};

	class PropertiesWindow : public GuiWindow {
	public:
		PropertiesWindow(Scene* scene);
		PropertiesWindow();

		void setScene(Scene* scene);

		inline virtual const char* getWindowName() { return "Properties"; }
		virtual void renderWindow() override;

	private:
		void drawGameObjectPropertiesWindow(std::shared_ptr<GameObject> selectedObj);
		void drawAssetPropertiesWindow(std::shared_ptr<assetInternal::AssetT> selectedAsset);
		void drawComponentVariableGui(const PublicVariable* editorVariable);
		template<class T>void drawAssetVariableGui(const PublicVariable* editorVariable, const char* payloadTarget);

	private:
		Scene* m_scene;
	};

	class AssetWindow : public GuiWindow {
	public:
		AssetWindow(AssetManager* assetManger);
		AssetWindow();

		inline void setAssetManger(AssetManager* assetManger) { m_assetManager = assetManger; }

		inline virtual const char* getWindowName() { return "Assets"; }
		virtual void renderWindow() override;

	private:
		AssetManager* m_assetManager;
	};

}