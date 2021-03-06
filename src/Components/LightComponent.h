#pragma once
#include "Component.h"
#include "../Rendering/Light.h"

namespace glGame {

    class LightComponent : public Component {
    public:
        LightComponent();

        virtual std::string getName() const { return "Light"; }

		virtual void init() override;
		virtual void onRender() override;
        virtual void onDestroy() override;

    public:
        std::shared_ptr<Light> light;
        int lightId;

    private:
        PublicVariableEnum lightType;
    };

}