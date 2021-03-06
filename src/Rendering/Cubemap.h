#pragma once
#include "../Resources/TextureAsset.h"

#include <memory>
#include <string>
#include <array>

namespace glGame {

    class VertexArray;

    class Cubemap {
    public:
        Cubemap(Asset<Texture> textureAssets[6]);
        ~Cubemap();

        void bind();
        void unbind();

        static VertexArray* getVertexArray();
    private:

    private:
        unsigned int m_textureId = 0;
        int m_imageWidth, m_imageHeight, m_channels;

        static float s_cubemapVertices[];
        static std::unique_ptr<VertexArray> s_cubemapVAO;
    };

}