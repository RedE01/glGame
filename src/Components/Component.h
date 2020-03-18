#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <string.h>

namespace glGame {

	class GameObject;

	enum class PublicVariableType {
		Int=0, Float, Double, Char, String, GameObject, Component, Vec2, Vec3, Asset, Color
	};

	struct PublicVariable {
		void* data;
		PublicVariableType variableType;
		std::string name;
		float editor_sliderSpeed;

		PublicVariable(void* data, PublicVariableType variableType, std::string name) : data(data), variableType(variableType), name(name), editor_sliderSpeed(1.0f) {}
		PublicVariable(void* data, PublicVariableType variableType, std::string name, float sliderSpeed) : data(data), variableType(variableType), name(name), editor_sliderSpeed(sliderSpeed) {}
	};

	class Component {
	public:
		Component() {}
		virtual ~Component() {}

		virtual std::string getName() const = 0;
		virtual void init() {}
		virtual void update() = 0;
		virtual void onRender() {}

		inline const int getPublicVariableCount() const {
			return m_publicVariables.size();
		}

		inline const PublicVariable& getPublicVariable(int index) const {
			return m_publicVariables[index];
		}

		inline PublicVariable* const getPublicVariable(const std::string& name) {
			for(PublicVariable& pVar : m_publicVariables) {
				if(name == pVar.name) return &pVar;
			}

			return nullptr;
		}

	protected:
		inline void addPublicVariable(void* variable, PublicVariableType varType, std::string name) {
			m_publicVariables.push_back(PublicVariable(variable, varType, name));
		}

		inline void addPublicVariable(void* variable, PublicVariableType varType, const char* name, float sliderSpeed) {
			m_publicVariables.push_back(PublicVariable(variable, varType, name, sliderSpeed));
		}

		GameObject* gameObject = nullptr;

	private:
		inline void setParentGameObject(GameObject* parent) {
			gameObject = parent;
		}
		friend class GameObject;

	private:
		std::vector<PublicVariable> m_publicVariables;
		
	};

}