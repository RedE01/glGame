#pragma once

namespace glGame {

	class FrameBuffer {

	public:
		FrameBuffer();
		~FrameBuffer();

		void bind();

	private:
		void genFramebuffer();
		unsigned int genTexture(int width, int height);
		unsigned int genRenderBuffer(int width, int height);

	private:
		unsigned int m_frameBuffer;
		unsigned int m_frameTexture;
		unsigned int m_renderBuffer;

	};

}