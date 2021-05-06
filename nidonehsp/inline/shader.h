
#define N2I_GL_SHADER_VERSION()		"#version 300 es\n"

#define N2I_GL_SHADER_PRECISION()	"precision mediump float;\n"

#define N2I_GL_SHADER_HEADER() \
	N2I_GL_SHADER_VERSION() \
	N2I_GL_SHADER_PRECISION()

#define N2I_GL_SHADER_UNIFORM_TEXTURE() \
	"#define N2_DECLARE_UNIFORM_TEXTURE() \\\n" \
	"	uniform sampler2D uTexture\n" \
	"#define N2_UTEXTURE uTexture\n" \

#define N2I_GL_SHADER_DEF_UNIFORM_TEXTURE() \
	N2I_GL_SHADER_UNIFORM_TEXTURE() \
	"N2_DECLARE_UNIFORM_TEXTURE();\n"

#define N2I_GL_SHADER_UNIFORM_TRANSCOLOR() \
	"#define N2_DECLARE_UNIFORM_TRANSCOLOR() \\\n" \
	"	uniform vec4 uTransColor\n" \
	"#define N2_UTRANSCOLOR (uTransColor)\n" \

#define N2I_GL_SHADER_DEF_UNIFORM_TRANS_COLOR() \
	N2I_GL_SHADER_UNIFORM_TRANSCOLOR() \
	"N2_DECLARE_UNIFORM_TRANSCOLOR();\n"

#define N2I_GL_SHADER_UB_DRAWENV() \
	"#define N2_DECLARE_UB_DRAWENV() \\\n" \
	"	layout(std140) uniform ubDrawEnv { \\\n" \
	"		mat4 uViewMatrix; \\\n" \
	"		mat4 uProjMatrix; \\\n" \
	"		mat4 uProjViewMatrix; \\\n" \
	"		vec4 uScreenParam; \\\n" \
	"	}\n" \
	"#define N2_VMTX (uViewMatrix)\n" \
	"#define N2_PMTX (uProjMatrix)\n" \
	"#define N2_PVMTX (uProjViewMatrix)\n" \
	"#define N2_SCREEN_WIDTH (uScreenParam.x)\n" \
	"#define N2_SCREEN_HEIGHT (uScreenParam.y)\n" \
	"#define N2_SCREEN_WIDTH_INV (uScreenParam.z)\n" \
	"#define N2_SCREEN_HEIGHT_INV (uScreenParam.w)\n" \

#define N2I_GL_SHADER_DEF_UB_DRAWENV() \
	N2I_GL_SHADER_UB_DRAWENV() \
	"N2_DECLARE_UB_DRAWENV();\n"

#define N2I_GL_SHADER_UB_D3MODEL() \
	"#define N2_DECLARE_UB_D3MODEL() \\\n" \
	"	layout(std140) uniform ubD3Model{ \\\n" \
	"		mat4 uWorldMatrix; \\\n" \
	"		vec4 uModelColor; \\\n" \
	"	}\n" \
	"#define N2_WMTX (uWorldMatrix)\n" \
	"#define N2_MODEL_COLOR (uModelColor)\n" \

#define N2I_GL_SHADER_DEF_UB_D3MODEL() \
	N2I_GL_SHADER_UB_D3MODEL() \
	"N2_DECLARE_UB_D3MODEL();\n"

#define N2I_GL_SHADER_ATTR_POSITION() \
	"#define N2_DECLARE_ATTR_POSITION() \\\n" \
	"	in vec3 aPosition\n" \
	"#define N2_ATTR_POSITION (aPosition)\n" \

#define N2I_GL_SHADER_DEF_ATTR_POSITION() \
	N2I_GL_SHADER_ATTR_POSITION() \
	"N2_DECLARE_ATTR_POSITION();\n"

#define N2I_GL_SHADER_ATTR_TEXCOORD() \
	"#define N2_DECLARE_ATTR_TEXCOORD() \\\n" \
	"	in vec2 aTexCoord\n" \
	"#define N2_ATTR_TEXCOORD (aTexCoord)\n" \

#define N2I_GL_SHADER_DEF_ATTR_TEXCOORD() \
	N2I_GL_SHADER_ATTR_TEXCOORD() \
	"N2_DECLARE_ATTR_TEXCOORD();\n"

#define N2I_GL_SHADER_ATTR_COLOR() \
	"#define N2_DECLARE_ATTR_COLOR() \\\n" \
	"	in vec4 aColor\n" \
	"#define N2_ATTR_COLOR (aColor)\n" \

#define N2I_GL_SHADER_DEF_ATTR_COLOR() \
	N2I_GL_SHADER_ATTR_COLOR() \
	"N2_DECLARE_ATTR_COLOR();\n"

#define N2I_GL_SHADER_ATTR_TEXCOORD_CLAMP() \
	"#define N2_DECLARE_ATTR_TEXCOORD_CLAMP() \\\n" \
	"	in vec4 aTexCoordClamp\n" \
	"#define N2_ATTR_TEXCOORD_CLAMP (aTexCoordClamp)\n" \

#define N2I_GL_SHADER_DEF_ATTR_TEXCOORD_CLAMP() \
	N2I_GL_SHADER_ATTR_TEXCOORD_CLAMP() \
	"N2_DECLARE_ATTR_TEXCOORD_CLAMP();\n"
