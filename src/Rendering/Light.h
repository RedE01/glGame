#pragma once
#include <glm/glm.hpp>
#include "../Math/Vector.h"

#include <memory>

namespace glGame {

    class FrameBuffer;
    class Renderer;

    enum LightType {
        Point = 0, Directional = 1
    };

    class Light {
    public:
        Light(const LightType& lightType);
        Light(const LightType& lightType, const Vector3& position);
        Light(const LightType& lightType, const Vector3& position, const float& intensity);
        ~Light();

        int getId() { return m_lightId; }
        void updateLight();
        
    public:
        Vector3 position;
        float intensity;
        LightType lightType;
        bool castShadows = false;
        Vector3 direction;
        Vector2i shadowmapSize = Vector2i(1024, 1024);
        Vector2 shadowSize;
        float shadowNearPlane, shadowFarPlane;

    private:
        int m_lightId = -1, m_shadowmapId = -1;
        glm::mat4 m_lightSpaceMatrix;
        std::unique_ptr<FrameBuffer> m_shadowmapFramebuffer;

        friend class LightManager;
        friend class Renderer;
    };

}