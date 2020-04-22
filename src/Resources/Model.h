#pragma once
#include "Asset.h"
#include "../Rendering/VertexArray.h"
#include "../Rendering/VertexBuffer.h"

#include <memory>

namespace glGame {

	class Model : public Asset {
	public:
		Model(const char* fileName);

		virtual const char* getAssetTypeString() { return "Model"; }
        virtual AssetType getAssetType() { return AssetType::Model; }

		void bind();
		void unbind();

		inline int getVerticiesCount() const { return m_verticies; }

	private:
		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<VertexBuffer> m_vbo;

		int m_verticies;
	};

}