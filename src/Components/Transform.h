#pragma once
#include "../Math/Vector.h"
#include "Component.h"

namespace glGame {

	class Transform : public Component {
	public:
		Transform();

		virtual std::string getName() const { return "Transform"; }

		void move(const Vector3& vector);
		void move(const float& x, const float& y, const float& z);
		void rotate(const Vector3& vector);
		void rotate(const float& x, const float& y, const float& z);

	public:
		Vector3 position, scale, rotation;
	};

}
