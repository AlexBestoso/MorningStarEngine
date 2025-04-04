
#include "../shader/shader.h"
class WindowCtrl : public Shader{
	private:
		GLFWwindow *window;
		std::string title;
		int screenWidth;
		int screenHeight;
		float soulColor[4];
		
		void fetchScreenDimensions(void);
		
	public:
		WindowCtrl(void);
		WindowCtrl(const char *title);
		void init(void);

		void setTitle(const char *title);
		GLFWwindow *getWindow(void);
		bool shouldClose(void);
		void alphaBlendFunc(void);
		void current(void);
		void depthTest(bool enabled);
		void blend(bool enabled); //If enabled, blend the computed fragment color values with the values in the color buffers. See glBlendFunc.
		void clipDistance(bool enabled, GLuint v); // If enabled, clip geometry against user-defined half space i.
		void colorLogic(bool enabled); // If enabled, apply the currently selected logical operation to the computed fragment color and color buffer values. See glLogicOp.
		void cullFace(bool enabled); // If enabled, cull polygons based on their winding in window coordinates. See glCullFace.
		void debugOutput(bool enabled); // If enabled, debug messages are produced by a debug context. When disabled, the debug message log is silenced. Note that in a non-debug context, very few, if any messages might be produced, even when GL_DEBUG_OUTPUT is enabled.
		void syncDebugOutput(bool enabled); // If enabled, debug messages are produced synchronously by a debug context. If disabled, debug messages may be produced asynchronously. In particular, they may be delayed relative to the execution of GL commands, and the debug callback function may be called from a thread other than that in which the commands are executed. See glDebugMessageCallback.
		void depthClamp(bool enabled); // If enabled, the −wc≤zc≤wc plane equation is ignored by view volume clipping (effectively, there is no near or far plane clipping). See glDepthRange.
		void dither(bool enabled); // If enabled, dither color components or indices before they are written to the color buffer.
		void framebufferSRGB(bool enabled); // If enabled and the value of GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING for the framebuffer attachment corresponding to the destination buffer is GL_SRGB, the R, G, and B destination color values (after conversion from fixed-point to floating-point) are considered to be encoded for the sRGB color space and hence are linearized prior to their use in blending.
		void lineSmooth(bool enabled); // If enabled, draw lines with correct filtering. Otherwise, draw aliased lines. See glLineWidth.
		void multiSample(bool enabled); // If enabled, use multiple fragment samples in computing the final color of a pixel. See glSampleCoverage.
		void polygonOffsetFill(bool enabled); // If enabled, and if the polygon is rendered in GL_FILL mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed. See glPolygonOffset.
		void polygonOffsetLine(bool enabled); // If enabled, and if the polygon is rendered in GL_LINE mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed. See glPolygonOffset.
		void polygonOffsetPoint(bool enabled); // If enabled, an offset is added to depth values of a polygon's fragments before the depth comparison is performed, if the polygon is rendered in GL_POINT mode. See glPolygonOffset.
		void ploygonSmooth(bool enabled); // If enabled, draw polygons with proper filtering. Otherwise, draw aliased polygons. For correct antialiased polygons, an alpha buffer is needed and the polygons must be sorted front to back.
		void primitiveRestart(bool enabled); // Enables primitive restarting. If enabled, any one of the draw commands which transfers a set of generic attribute array elements to the GL will restart the primitive when the index of the vertex is equal to the primitive restart index. See glPrimitiveRestartIndex.
		void primitiveResartFixedIndex(bool enabled); //  Enables primitive restarting with a fixed index. If enabled, any one of the draw commands which transfers a set of generic attribute array elements to the GL will restart the primitive when the index of the vertex is equal to the fixed primitive index for the specified index type. The fixed index is equal to 2n−1 where n is equal to 8 for GL_UNSIGNED_BYTE, 16 for GL_UNSIGNED_SHORT and 32 for GL_UNSIGNED_INT.
		void rasterizerDiscard(bool enabled); // If enabled, primitives are discarded after the optional transform feedback stage, but before rasterization. Furthermore, when enabled, glClear, glClearBufferData, glClearBufferSubData, glClearTexImage, and glClearTexSubImage are ignored.
		void sampleAlphaToCoverage(bool enabled); // If enabled, compute a temporary coverage value where each bit is determined by the alpha value at the corresponding sample location. The temporary coverage value is then ANDed with the fragment coverage value.
		void sampleAlphaToOne(bool enabled); // If enabled, each sample alpha value is replaced by the maximum representable alpha value.
		void sampleCoverage(bool enabled); // If enabled, the fragment's coverage is ANDed with the temporary coverage value. If GL_SAMPLE_COVERAGE_INVERT is set to GL_TRUE, invert the coverage value. See glSampleCoverage.
		void sampleShading(bool enabled); // If enabled, the active fragment shader is run once for each covered sample, or at fraction of this rate as determined by the current value of GL_MIN_SAMPLE_SHADING_VALUE. See glMinSampleShading.
		void sampleMask(bool enabled); // If enabled, the sample coverage mask generated for a fragment during rasterization will be ANDed with the value of GL_SAMPLE_MASK_VALUE before shading occurs. See glSampleMaski.
		void scissorTest(bool enabled); // If enabled, discard fragments that are outside the scissor rectangle. See glScissor.
		void stencilTest(bool enabled); // If enabled, do stencil testing and update the stencil buffer. See glStencilFunc and glStencilOp.
		void textureCubeMapSeamless(bool enabled); // If enabled, cubemap textures are sampled such that when linearly sampling from the border between two adjacent faces, texels from both faces are used to generate the final sample value. When disabled, texels from only a single face are used to construct the final sample value.
		void programPointSize(bool enabled); // If enabled and a vertex or geometry shader is active, then the derived point size is taken from the (potentially clipped) shader builtin gl_PointSize and clamped to the implementation-dependent point size range. 
		void setFrameResizeCallBack(void(*cb)(GLFWwindow*, int, int));
		void setKeyboardCallback(void (*callback)(GLFWwindow* window, int key, int scancode, int action, int mods));
		void setMouseClickCallback(void(*callback)(GLFWwindow*, int, int, int));
                void setMouseCursorPosCallback(void(*callback)(GLFWwindow*, double, double));
		void setWindowRefreshCb(void(*cb)(GLFWwindow*));
		void setErrorHandleCallback(void(*cb)(int, const char *));

		void drawClear(void);
		void drawTriangle(GLint first, GLsizei count);
		void poll(void);
		void kill(void);

		void generateVao(GLsizei n, GLuint *obj);
                // the same function is used to generate ebo
                void generateVbo(GLsizei n, GLuint *obj);
                void bindVao(GLuint obj);
                void bindVbo(GLuint obj);
                void bindVeo(GLuint obj);
		void unbindVao(void);
                void unbindVbo(void);
                void unbindVeo(void);
		
		void pushInputStatic(GLfloat *data, GLsizeiptr dataSize);
		void pushInputDynamic(GLfloat *data, GLsizeiptr dataSize);
		void defineInput(unsigned int i, int size, unsigned int stride, const void *offset);

};
