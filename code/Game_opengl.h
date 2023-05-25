//----------
GLuint VBO;
GLuint VAO;
GLuint FXAAVBO;
GLuint FXAAVAO;
GLuint ProgramID;
GLuint HUDProgramID;
GLuint FXAAProgramID;
GLuint FrameBuffer;
GLuint FrameTexture;
GLuint depthrenderbuffer;
//----------
#define GL_ARRAY_BUFFER                   0x8892
#define GL_STATIC_DRAW                    0x88E4
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_STREAM_DRAW                    0x88E0
#define GL_VERTEX_SHADER                  0x8B31
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_LINK_STATUS                    0x8B82
#define GL_COMPILE_STATUS                 0x8B81
#define GL_VALIDATE_STATUS                0x8B83
#define GL_ATTACHED_SHADERS               0x8B85
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_MIRRORED_REPEAT                0x8370
#define GL_BGRA                           0x80E1
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_TEXTURE_2D_ARRAY               0x8C1A
#define GL_MAJOR_VERSION                  0x821B
#define GL_MINOR_VERSION                  0x821C
#define GL_SRGB8_ALPHA8                   0x8C43
#define GL_FRAMEBUFFER_SRGB               0x8DB9
#define GL_MAP_WRITE_BIT                  0x0002
#define GL_MAP_UNSYNCHRONIZED_BIT         0x0020
#define GL_MULTISAMPLE                    0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define GL_SAMPLE_ALPHA_TO_ONE            0x809F
#define GL_TEXTURE_2D_MULTISAMPLE         0x9100
#define GL_FRAMEBUFFER                    0x8D40
#define GL_RENDERBUFFER                   0x8D41
#define GL_COLOR_ATTACHMENT0              0x8CE0
#define GL_FRAMEBUFFER_COMPLETE           0x8CD5
#define GL_DRAW_FRAMEBUFFER               0x8CA9
#define GL_READ_FRAMEBUFFER               0x8CA8
#define GL_DEPTH_COMPONENT16              0x81A5
#define GL_DEPTH_COMPONENT24              0x81A6
#define GL_DEPTH_COMPONENT32              0x81A7
#define GL_DEPTH_ATTACHMENT               0x8D00
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_DRAW_FRAMEBUFFER_BINDING       0x8CA6
#define TEXTURE_MAX_ANISOTROPY_EXT        0x84FE
#define MAX_TEXTURE_MAX_ANISOTROPY_EXT    0x84FF
#define GL_CURRENT_PROGRAM                0x8B8D
#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB       0x2093
#define WGL_CONTEXT_FLAGS_ARB             0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB      0x9126
#define WGL_DRAW_TO_WINDOW_ARB            0x2001
#define WGL_SUPPORT_OPENGL_ARB            0x2010
#define WGL_DOUBLE_BUFFER_ARB             0x2011
#define WGL_PIXEL_TYPE_ARB                0x2013
#define WGL_TYPE_RGBA_ARB                 0x202B
#define WGL_COLOR_BITS_ARB                0x2014
#define WGL_DEPTH_BITS_ARB                0x2022
#define WGL_STENCIL_BITS_ARB              0x2023
#define WGL_CONTEXT_DEBUG_BIT_ARB                  0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB     0x0002
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB           0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB  0x00000002
#define GL_DEBUG_OUTPUT_SYNCHRONOUS       0x8242
//----------
#define OpenGLFunction(Name) global_variable wgl_##Name *Name;
#define GetOpenGLFunction(Name) Name = (wgl_##Name *)wglGetProcAddress(#Name)
//----------
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
typedef char GLchar;

//----------function pointers

typedef void wgl_glGenBuffers(GLsizei n, GLuint * buffers);
typedef void wgl_glBindBuffer(GLenum target, GLuint buffer);
typedef void wgl_glBufferData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage);
typedef GLuint wgl_glCreateShader(GLenum shaderType);
typedef void wgl_glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void wgl_glCompileShader(GLuint shader);
typedef GLuint wgl_glCreateProgram(void);
typedef void wgl_glAttachShader(GLuint program,
                                GLuint shader);
typedef void wgl_glLinkProgram(GLuint program);
typedef void wgl_glDeleteShader(GLuint shader);
typedef void wgl_glValidateProgram(GLuint program);
typedef void wgl_glGetProgramiv(GLuint program, GLenum pname, GLint *params);
typedef void wgl_glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void wgl_glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void wgl_glUseProgram(GLuint program);
typedef void wgl_glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
typedef void wgl_glEnableVertexAttribArray(GLuint index);
typedef void wgl_glGenVertexArrays(GLsizei n, GLuint *arrays);
typedef void wgl_glBindVertexArray(GLuint array);
typedef void wgl_glGenerateMipmap(GLenum target);
typedef GLint wgl_glGetUniformLocation(GLuint program, const GLchar *name);
typedef void wgl_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void wgl_glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
typedef void wgl_glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void wgl_glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef HGLRC wgl_wglCreateContextAttribsARB(HDC hDC, HGLRC hshareContext, const int *attribList);
typedef void* wgl_glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef GLboolean wgl_glUnmapBuffer(GLenum target);
typedef void wgl_glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void wgl_glGenFramebuffers(GLsizei n, GLuint *framebuffers);
typedef void wgl_glBindFramebuffer(GLenum target, GLuint framebuffer);
typedef void wgl_glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef GLenum wgl_glCheckFramebufferStatus(GLenum target);
typedef void wgl_glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void wgl_glGetShaderiv(GLuint shader, GLenum pname, GLint *params);
typedef void wgl_glUniform1i(GLint location, GLint v0);
typedef void wgl_glActiveTexture(GLenum texture);
typedef void wgl_glGenRenderbuffers(GLsizei n, GLuint *renderbuffers);
typedef void wgl_glBindRenderbuffer(GLenum target, GLuint renderbuffer);
typedef void wgl_glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void wgl_glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void wgl_glUniform2f(GLint location, GLfloat v0, GLfloat v1);

//----------function prototypes

#define GL_DEBUG_CALLBACK(Name) void Name(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam)
typedef GL_DEBUG_CALLBACK(GLDEBUGPROC);
typedef void wgl_glDebugMessageCallbackARB(GLDEBUGPROC* callback, const void *userParam);

//----------function pointers

OpenGLFunction(glGenBuffers);
OpenGLFunction(glBindBuffer);
OpenGLFunction(glBufferData);
OpenGLFunction(glCreateShader);
OpenGLFunction(glShaderSource);
OpenGLFunction(glCompileShader);
OpenGLFunction(glCreateProgram);
OpenGLFunction(glAttachShader);
OpenGLFunction(glLinkProgram);
OpenGLFunction(glDeleteShader);
OpenGLFunction(glValidateProgram);
OpenGLFunction(glGetProgramiv);
OpenGLFunction(glGetShaderInfoLog);
OpenGLFunction(glGetProgramInfoLog);
OpenGLFunction(glUseProgram);
OpenGLFunction(glVertexAttribPointer);
OpenGLFunction(glEnableVertexAttribArray);
OpenGLFunction(glGenVertexArrays);
OpenGLFunction(glBindVertexArray);
OpenGLFunction(glGenerateMipmap);
OpenGLFunction(glGetUniformLocation);
OpenGLFunction(glUniformMatrix4fv);
OpenGLFunction(glBufferSubData);
OpenGLFunction(glTexImage3D);
OpenGLFunction(glTexSubImage3D);
OpenGLFunction(wglCreateContextAttribsARB);
OpenGLFunction(glDebugMessageCallbackARB);
OpenGLFunction(glMapBufferRange);
OpenGLFunction(glUnmapBuffer);
OpenGLFunction(glTexImage2DMultisample);
OpenGLFunction(glGenFramebuffers);
OpenGLFunction(glBindFramebuffer);
OpenGLFunction(glFramebufferTexture2D);
OpenGLFunction(glCheckFramebufferStatus);
OpenGLFunction(glBlitFramebuffer);
OpenGLFunction(glGetShaderiv);
OpenGLFunction(glUniform1i);
OpenGLFunction(glActiveTexture);
OpenGLFunction(glGenRenderbuffers);
OpenGLFunction(glBindRenderbuffer);
OpenGLFunction(glRenderbufferStorage);
OpenGLFunction(glFramebufferRenderbuffer);
OpenGLFunction(glUniform2f);

//------------------------------shader header

char* ShaderHeader =
R"FOO(
#version 330 core
#extension GL_EXT_texture_array : enable
#extension GL_EXT_texture_filter_anisotropic : enable
)FOO";

//------------------------------vertex shader

char* ShaderVertex = 
R"FOO(
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 texCoord;
out vec3 TexCoord;
out vec4 FragmentPosition;
uniform mat4 ProjectionMatrix;
void main()
{
    gl_Position = ProjectionMatrix * vec4(position, 1.0);
    FragmentPosition = gl_Position;
    TexCoord = texCoord;
}
)FOO";

//------------------------------fragment shader

char* ShaderFragment =
R"FOO(
in vec3 TexCoord;
in vec4 FragmentPosition;
out vec4 color;
uniform mat4 DitherMatrix;
uniform sampler2DArray ourTexture;
void main()
{
    vec4 texColor = texture2DArray(ourTexture, TexCoord);
    float MatIndexX = mod(gl_FragCoord.x,4);
    float MatIndexY = mod(gl_FragCoord.y,4);
    if (texColor.a < (DitherMatrix[int(MatIndexX)][int(MatIndexY)]))
    {
        discard;
    }
    color = mix(texColor,vec4(0.7,0.7,0.7,0.0),(FragmentPosition.z / 60.0f));
    color.a = dot(color.rgb, vec3(0.299, 0.587, 0.114)); //FXAA Luma
} 
)FOO";

//------------------------------HUD vertex shader (no projection)

char* HUDShaderVertex = 
R"FOO(
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 texCoord;
out vec3 TexCoord;
void main()
{
    gl_Position = vec4(position, 1.0);
    TexCoord = texCoord;
}
)FOO";

//------------------------------HUD fragment shader (no distance fade)

char* HUDShaderFragment =
R"FOO(
in vec3 TexCoord;
out vec4 color;
uniform mat4 DitherMatrix;
uniform sampler2DArray ourTexture;
void main()
{
    vec4 texColor = texture2DArray(ourTexture, TexCoord);
    float MatIndexX = mod(gl_FragCoord.x,4);
    float MatIndexY = mod(gl_FragCoord.y,4);
    if (texColor.a < (DitherMatrix[int(MatIndexX)][int(MatIndexY)]))
    {
        discard;
    }
    color = texColor;
} 
)FOO";

//------------------------------FXAA vertex shader

char* FXAAShaderVertex =
R"FOO(
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
out vec2 TexCoord;
void main()
{
gl_Position = vec4(position,0.0,1.0);
TexCoord = texCoord;
}
)FOO";

//------------------------------FXAA fragment shader
// Copyright (c) 2014-2015, NVIDIA CORPORATION. All rights reserved. Thanks Tim.
char* FXAAShaderFragment =
R"FOO(
in vec2 TexCoord;
out vec4 color;
uniform sampler2D tex0;
uniform vec2 PixelSize;
#define FXAA_QUALITY__PS 5
#define FXAA_QUALITY__P0 1.0
#define FXAA_QUALITY__P1 1.5
#define FXAA_QUALITY__P2 2.0
#define FXAA_QUALITY__P3 4.0
#define FXAA_QUALITY__P4 12.0
#define FxaaBool bool
#define FxaaDiscard discard
#define FxaaFloat float
#define FxaaFloat2 vec2
#define FxaaFloat3 vec3
#define FxaaFloat4 vec4
#define FxaaHalf float
#define FxaaHalf2 vec2
#define FxaaHalf3 vec3
#define FxaaHalf4 vec4
#define FxaaInt2 ivec2
#define FxaaSat(x) clamp(x, 0.0, 1.0)
#define FxaaTex sampler2D
#define FxaaTexTop(t, p) textureLod(t, p, 0.0)
#define FxaaTexOff(t, p, o, r) textureLodOffset(t, p, 0.0, o)
FxaaFloat FxaaLuma(FxaaFloat4 rgba) { return rgba.w; }

FxaaFloat4 FxaaPixelShader(FxaaFloat2 pos,FxaaTex tex,FxaaFloat2 fxaaQualityRcpFrame,FxaaFloat fxaaQualitySubpix,FxaaFloat fxaaQualityEdgeThreshold,FxaaFloat fxaaQualityEdgeThresholdMin)
 {
    FxaaFloat2 posM;
    posM.x = pos.x;
    posM.y = pos.y;
    FxaaFloat4 rgbyM = FxaaTexTop(tex, posM);
    #define lumaM rgbyM.w
    FxaaFloat lumaS = FxaaLuma(FxaaTexOff(tex, posM, FxaaInt2( 0, 1), fxaaQualityRcpFrame.xy));
    FxaaFloat lumaE = FxaaLuma(FxaaTexOff(tex, posM, FxaaInt2( 1, 0), fxaaQualityRcpFrame.xy));
    FxaaFloat lumaN = FxaaLuma(FxaaTexOff(tex, posM, FxaaInt2( 0,-1), fxaaQualityRcpFrame.xy));
    FxaaFloat lumaW = FxaaLuma(FxaaTexOff(tex, posM, FxaaInt2(-1, 0), fxaaQualityRcpFrame.xy));
    FxaaFloat maxSM = max(lumaS, lumaM);
    FxaaFloat minSM = min(lumaS, lumaM);
    FxaaFloat maxESM = max(lumaE, maxSM);
    FxaaFloat minESM = min(lumaE, minSM);
    FxaaFloat maxWN = max(lumaN, lumaW);
    FxaaFloat minWN = min(lumaN, lumaW);
    FxaaFloat rangeMax = max(maxWN, maxESM);
    FxaaFloat rangeMin = min(minWN, minESM);
    FxaaFloat rangeMaxScaled = rangeMax * fxaaQualityEdgeThreshold;
    FxaaFloat range = rangeMax - rangeMin;
    FxaaFloat rangeMaxClamped = max(fxaaQualityEdgeThresholdMin, rangeMaxScaled);
    FxaaBool earlyExit = range < rangeMaxClamped;
    if(earlyExit)
        return rgbyM;
    FxaaFloat lumaNW = FxaaLuma(FxaaTexOff(tex, posM, FxaaInt2(-1,-1), fxaaQualityRcpFrame.xy));
        FxaaFloat lumaSE = FxaaLuma(FxaaTexOff(tex, posM, FxaaInt2( 1, 1), fxaaQualityRcpFrame.xy));
        FxaaFloat lumaNE = FxaaLuma(FxaaTexOff(tex, posM, FxaaInt2( 1,-1), fxaaQualityRcpFrame.xy));
        FxaaFloat lumaSW = FxaaLuma(FxaaTexOff(tex, posM, FxaaInt2(-1, 1), fxaaQualityRcpFrame.xy));
    FxaaFloat lumaNS = lumaN + lumaS;
    FxaaFloat lumaWE = lumaW + lumaE;
    FxaaFloat subpixRcpRange = 1.0/range;
    FxaaFloat subpixNSWE = lumaNS + lumaWE;
    FxaaFloat edgeHorz1 = (-2.0 * lumaM) + lumaNS;
    FxaaFloat edgeVert1 = (-2.0 * lumaM) + lumaWE;
    FxaaFloat lumaNESE = lumaNE + lumaSE;
    FxaaFloat lumaNWNE = lumaNW + lumaNE;
    FxaaFloat edgeHorz2 = (-2.0 * lumaE) + lumaNESE;
    FxaaFloat edgeVert2 = (-2.0 * lumaN) + lumaNWNE;
    FxaaFloat lumaNWSW = lumaNW + lumaSW;
    FxaaFloat lumaSWSE = lumaSW + lumaSE;
    FxaaFloat edgeHorz4 = (abs(edgeHorz1) * 2.0) + abs(edgeHorz2);
    FxaaFloat edgeVert4 = (abs(edgeVert1) * 2.0) + abs(edgeVert2);
    FxaaFloat edgeHorz3 = (-2.0 * lumaW) + lumaNWSW;
    FxaaFloat edgeVert3 = (-2.0 * lumaS) + lumaSWSE;
    FxaaFloat edgeHorz = abs(edgeHorz3) + edgeHorz4;
    FxaaFloat edgeVert = abs(edgeVert3) + edgeVert4;
    FxaaFloat subpixNWSWNESE = lumaNWSW + lumaNESE;
    FxaaFloat lengthSign = fxaaQualityRcpFrame.x;
    FxaaBool horzSpan = edgeHorz >= edgeVert;
    FxaaFloat subpixA = subpixNSWE * 2.0 + subpixNWSWNESE;
    if(!horzSpan) lumaN = lumaW;
    if(!horzSpan) lumaS = lumaE;
    if(horzSpan) lengthSign = fxaaQualityRcpFrame.y;
    FxaaFloat subpixB = (subpixA * (1.0/12.0)) - lumaM;
    FxaaFloat gradientN = lumaN - lumaM;
    FxaaFloat gradientS = lumaS - lumaM;
    FxaaFloat lumaNN = lumaN + lumaM;
    FxaaFloat lumaSS = lumaS + lumaM;
    FxaaBool pairN = abs(gradientN) >= abs(gradientS);
    FxaaFloat gradient = max(abs(gradientN), abs(gradientS));
    if(pairN) lengthSign = -lengthSign;
    FxaaFloat subpixC = FxaaSat(abs(subpixB) * subpixRcpRange);
    FxaaFloat2 posB;
    posB.x = posM.x;
    posB.y = posM.y;
    FxaaFloat2 offNP;
    offNP.x = (!horzSpan) ? 0.0 : fxaaQualityRcpFrame.x;
    offNP.y = ( horzSpan) ? 0.0 : fxaaQualityRcpFrame.y;
    if(!horzSpan) posB.x += lengthSign * 0.5;
    if( horzSpan) posB.y += lengthSign * 0.5;
    FxaaFloat2 posN;
    posN.x = posB.x - offNP.x * FXAA_QUALITY__P0;
    posN.y = posB.y - offNP.y * FXAA_QUALITY__P0;
    FxaaFloat2 posP;
    posP.x = posB.x + offNP.x * FXAA_QUALITY__P0;
    posP.y = posB.y + offNP.y * FXAA_QUALITY__P0;
    FxaaFloat subpixD = ((-2.0)*subpixC) + 3.0;
    FxaaFloat lumaEndN = FxaaLuma(FxaaTexTop(tex, posN));
    FxaaFloat subpixE = subpixC * subpixC;
    FxaaFloat lumaEndP = FxaaLuma(FxaaTexTop(tex, posP));
    if(!pairN) lumaNN = lumaSS;
    FxaaFloat gradientScaled = gradient * 1.0/4.0;
    FxaaFloat lumaMM = lumaM - lumaNN * 0.5;
    FxaaFloat subpixF = subpixD * subpixE;
    FxaaBool lumaMLTZero = lumaMM < 0.0;
    lumaEndN -= lumaNN * 0.5;
    lumaEndP -= lumaNN * 0.5;
    FxaaBool doneN = abs(lumaEndN) >= gradientScaled;
    FxaaBool doneP = abs(lumaEndP) >= gradientScaled;
    if(!doneN) posN.x -= offNP.x * FXAA_QUALITY__P1;
    if(!doneN) posN.y -= offNP.y * FXAA_QUALITY__P1;
    FxaaBool doneNP = (!doneN) || (!doneP);
    if(!doneP) posP.x += offNP.x * FXAA_QUALITY__P1;
    if(!doneP) posP.y += offNP.y * FXAA_QUALITY__P1;
    if(doneNP) {
        if(!doneN) lumaEndN = FxaaLuma(FxaaTexTop(tex, posN.xy));
        if(!doneP) lumaEndP = FxaaLuma(FxaaTexTop(tex, posP.xy));
        if(!doneN) lumaEndN = lumaEndN - lumaNN * 0.5;
        if(!doneP) lumaEndP = lumaEndP - lumaNN * 0.5;
        doneN = abs(lumaEndN) >= gradientScaled;
        doneP = abs(lumaEndP) >= gradientScaled;
        if(!doneN) posN.x -= offNP.x * FXAA_QUALITY__P2;
        if(!doneN) posN.y -= offNP.y * FXAA_QUALITY__P2;
        doneNP = (!doneN) || (!doneP);
        if(!doneP) posP.x += offNP.x * FXAA_QUALITY__P2;
        if(!doneP) posP.y += offNP.y * FXAA_QUALITY__P2;       
        if(doneNP) {
            if(!doneN) lumaEndN = FxaaLuma(FxaaTexTop(tex, posN.xy));
            if(!doneP) lumaEndP = FxaaLuma(FxaaTexTop(tex, posP.xy));
            if(!doneN) lumaEndN = lumaEndN - lumaNN * 0.5;
            if(!doneP) lumaEndP = lumaEndP - lumaNN * 0.5;
            doneN = abs(lumaEndN) >= gradientScaled;
            doneP = abs(lumaEndP) >= gradientScaled;
            if(!doneN) posN.x -= offNP.x * FXAA_QUALITY__P3;
            if(!doneN) posN.y -= offNP.y * FXAA_QUALITY__P3;
            doneNP = (!doneN) || (!doneP);
            if(!doneP) posP.x += offNP.x * FXAA_QUALITY__P3;
            if(!doneP) posP.y += offNP.y * FXAA_QUALITY__P3;            
            if(doneNP) {
                if(!doneN) lumaEndN = FxaaLuma(FxaaTexTop(tex, posN.xy));
                if(!doneP) lumaEndP = FxaaLuma(FxaaTexTop(tex, posP.xy));
                if(!doneN) lumaEndN = lumaEndN - lumaNN * 0.5;
                if(!doneP) lumaEndP = lumaEndP - lumaNN * 0.5;
                doneN = abs(lumaEndN) >= gradientScaled;
                doneP = abs(lumaEndP) >= gradientScaled;
                if(!doneN) posN.x -= offNP.x * FXAA_QUALITY__P4;
                if(!doneN) posN.y -= offNP.y * FXAA_QUALITY__P4;
                doneNP = (!doneN) || (!doneP);
                if(!doneP) posP.x += offNP.x * FXAA_QUALITY__P4;
                if(!doneP) posP.y += offNP.y * FXAA_QUALITY__P4;
            }
        }
    }
    FxaaFloat dstN = posM.x - posN.x;
    FxaaFloat dstP = posP.x - posM.x;
    if(!horzSpan) dstN = posM.y - posN.y;
    if(!horzSpan) dstP = posP.y - posM.y;
    FxaaBool goodSpanN = (lumaEndN < 0.0) != lumaMLTZero;
    FxaaFloat spanLength = (dstP + dstN);
    FxaaBool goodSpanP = (lumaEndP < 0.0) != lumaMLTZero;
    FxaaFloat spanLengthRcp = 1.0/spanLength;
    FxaaBool directionN = dstN < dstP;
    FxaaFloat dst = min(dstN, dstP);
    FxaaBool goodSpan = directionN ? goodSpanN : goodSpanP;
    FxaaFloat subpixG = subpixF * subpixF;
    FxaaFloat pixelOffset = (dst * (-spanLengthRcp)) + 0.5;
    FxaaFloat subpixH = subpixG * fxaaQualitySubpix;
    FxaaFloat pixelOffsetGood = goodSpan ? pixelOffset : 0.0;
    FxaaFloat pixelOffsetSubpix = max(pixelOffsetGood, subpixH);
    if(!horzSpan) posM.x += pixelOffsetSubpix * lengthSign;
    if( horzSpan) posM.y += pixelOffsetSubpix * lengthSign;
    return FxaaFloat4(FxaaTexTop(tex, posM).xyz, lumaM);
}

void main()
{
vec2 posPos = (TexCoord) + (PixelSize*0.5);
  color = FxaaPixelShader(posPos,tex0,PixelSize,1.00,0.166,0.0833);
}
)FOO";

//------------------------------

internal void OpenGLCreatePrograms(char* HeaderCode, char* VertexCode, char* HUDVertexCode, char* FXAAVertexCode, char* FragmentCode, char* HUDFragmentCode,char* FXAAFragmentCode)
{
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLchar* VertexShaderCode[] = 
    {
        HeaderCode,
        VertexCode
    };
    glShaderSource(VertexShaderID,ArrayCount(VertexShaderCode),VertexShaderCode,NULL);
    glCompileShader(VertexShaderID);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    GLchar* FragmentShaderCode[] = 
    {
        HeaderCode,
        FragmentCode
    };
    glShaderSource(FragmentShaderID,ArrayCount(FragmentShaderCode),FragmentShaderCode,NULL);
    glCompileShader(FragmentShaderID);
    ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    glValidateProgram(ProgramID);
    GLint Validated = 0;
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Validated);
    if(!Validated)
    {
        GLsizei NotUsed;
        char VertexErrors[4096];
        char FragmentErrors[4096];
        char ProgramErrors[4096];
        glGetShaderInfoLog(VertexShaderID,sizeof(VertexErrors),&NotUsed,VertexErrors);
        glGetShaderInfoLog(FragmentShaderID,sizeof(FragmentErrors),&NotUsed,FragmentErrors);
        glGetProgramInfoLog(ProgramID,sizeof(ProgramErrors),&NotUsed,ProgramErrors);
        Assert(!"Messed Up Shader");
    }
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
    
    //----------
    GLuint HUDVertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLchar* HUDVertexShaderCode[] = 
    {
        HeaderCode,
        HUDVertexCode
    };
    glShaderSource(HUDVertexShaderID,ArrayCount(HUDVertexShaderCode),HUDVertexShaderCode,NULL);
    glCompileShader(HUDVertexShaderID);
    GLuint HUDFragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    GLchar* HUDFragmentShaderCode[] = 
    {
        HeaderCode,
        HUDFragmentCode
    };
    glShaderSource(HUDFragmentShaderID,ArrayCount(HUDFragmentShaderCode),HUDFragmentShaderCode,NULL);
    glCompileShader(HUDFragmentShaderID);
    HUDProgramID = glCreateProgram();
    glAttachShader(HUDProgramID, HUDVertexShaderID);
    glAttachShader(HUDProgramID, HUDFragmentShaderID);
    glLinkProgram(HUDProgramID);
    glValidateProgram(HUDProgramID);
    Validated = 0;
    glGetProgramiv(HUDProgramID, GL_LINK_STATUS, &Validated);
    if(!Validated)
    {
        GLsizei NotUsed;
        char VertexErrors[4096];
        char FragmentErrors[4096];
        char ProgramErrors[4096];
        glGetShaderInfoLog(HUDVertexShaderID,sizeof(VertexErrors),&NotUsed,VertexErrors);
        glGetShaderInfoLog(HUDFragmentShaderID,sizeof(FragmentErrors),&NotUsed,FragmentErrors);
        glGetProgramInfoLog(HUDProgramID,sizeof(ProgramErrors),&NotUsed,ProgramErrors);
        Assert(!"Messed Up Shader");
    }
    glDeleteShader(HUDVertexShaderID);
    glDeleteShader(HUDFragmentShaderID);
    
    //----------
    GLuint FXAAVertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLchar* FXAAVertexShaderCode[] = 
    {
        HeaderCode,
        FXAAVertexCode
    };
    glShaderSource(FXAAVertexShaderID,ArrayCount(FXAAVertexShaderCode),FXAAVertexShaderCode,NULL);
    glCompileShader(FXAAVertexShaderID);
    GLuint FXAAFragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    GLchar* FXAAFragmentShaderCode[] = 
    {
        HeaderCode,
        FXAAFragmentCode
    };
    glShaderSource(FXAAFragmentShaderID,ArrayCount(FXAAFragmentShaderCode),FXAAFragmentShaderCode,NULL);
    glCompileShader(FXAAFragmentShaderID);
    FXAAProgramID = glCreateProgram();
    glAttachShader(FXAAProgramID, FXAAVertexShaderID);
    glAttachShader(FXAAProgramID, FXAAFragmentShaderID);
    glLinkProgram(FXAAProgramID);
    glValidateProgram(FXAAProgramID);
    Validated = 0;
    glGetProgramiv(FXAAProgramID, GL_LINK_STATUS, &Validated);
    if(!Validated)
    {
        GLsizei NotUsed;
        char VertexErrors[4096];
        char FragmentErrors[4096];
        char ProgramErrors[4096];
        glGetShaderInfoLog(FXAAVertexShaderID,sizeof(VertexErrors),&NotUsed,VertexErrors);
        glGetShaderInfoLog(FXAAFragmentShaderID,sizeof(FragmentErrors),&NotUsed,FragmentErrors);
        glGetProgramInfoLog(FXAAProgramID,sizeof(ProgramErrors),&NotUsed,ProgramErrors);
        Assert(!"Messed Up Shader");
    }
    glDeleteShader(FXAAVertexShaderID);
    glDeleteShader(FXAAFragmentShaderID);
}

//----------

#if GPUDEBUG
GL_DEBUG_CALLBACK(OpenGLDebugCallback)
{
    char* ErrorMessage = (char*)message;
    Assert(!"OpenGL Error");
}
#endif

//------------------------------

internal void
LoadTexture(char* TextureName,uint8 TextureSlot)
{
    uint8* TextureData = (uint8*)ScratchMemoryBuffer;
    PlatformLoadTexture(TextureName,TextureData);
    loaded_bitmap* Texture = (loaded_bitmap*)TextureData;
    TextureData += Texture->BitmapOffset;
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
                    0,                // Mipmap number
                    0, 0, TextureSlot,          // xoffset, yoffset, zoffset
                    128, 128, 1, // width, height, depth
                    GL_BGRA,          // format
                    GL_UNSIGNED_BYTE, // type
                    TextureData);           // pointer to data
}

//------------------------------

internal void
OpenGLStartup(game_memory* GameMemory,game_state* GameState)
{
#if GPUDEBUG
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallbackARB(OpenGLDebugCallback, 0);
#endif
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_DITHER);
    glDisable(GL_MULTISAMPLE);
    glClearColor(0.7f, 0.7f, 0.7f, 0.0f);
    
    //----------
    OpenGLCreatePrograms(ShaderHeader,ShaderVertex,HUDShaderVertex,FXAAShaderVertex,ShaderFragment,HUDShaderFragment,FXAAShaderFragment);
    
    //----------
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,((1800000 + 180000)*4), 0, GL_DYNAMIC_DRAW); // numbers from OpenGLVertices in gamestate
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT,GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    //----------
    real32 FullScreenQuadXYUV[24] = 
    {
        -1,1,0,1,
        -1,-1,0,0,
        1,1,1,1,
        -1,-1,0,0,
        1,-1,1,0,
        1,1,1,1
    };
    glGenVertexArrays(1, &FXAAVAO);
    glGenBuffers(1, &FXAAVBO);
    glBindVertexArray(FXAAVAO);
    glBindBuffer(GL_ARRAY_BUFFER,FXAAVBO);
    glBufferData(GL_ARRAY_BUFFER,(96), &FullScreenQuadXYUV, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT,GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    //----------set uniforms
    real32 Proj[4][4] = {};
    real32* ProjPoint = &Proj[0][0];
    real32 NearDist = 0.1f;
    real32 FarDist = 60.0f; // have to change in frag shader also. 60m draw distance.
    float OneOverDepth = 1.0f / (FarDist - NearDist);
    Proj[1][1] = 1;
    Proj[0][0] = 1;
    Proj[2][2] = FarDist * OneOverDepth;
    Proj[3][2] = (-FarDist * NearDist) * OneOverDepth;
    Proj[2][3] = 1;
    Proj[3][3] = 0;
    glUseProgram(ProgramID);
    GLint ProjLoc = glGetUniformLocation(ProgramID, "ProjectionMatrix");
    glUniformMatrix4fv(ProjLoc, 1, GL_FALSE,ProjPoint);
    //----------
    real32 DitherMat[4][4] = {};
    real32* DitherPoint = &DitherMat[0][0];
    DitherMat [0][0] = 1.0f / 17.0f;
    DitherMat [0][1] = 9.0f / 17.0f;
    DitherMat [0][2] = 3.0f / 17.0f;
    DitherMat [0][3] = 11.0f / 17.0f;
    DitherMat [1][0] = 13.0f / 17.0f;
    DitherMat [1][1] = 5.0f / 17.0f;
    DitherMat [1][2] = 15.0f / 17.0f;
    DitherMat [1][3] = 7.0f / 17.0f;
    DitherMat [2][0] = 4.0f / 17.0f;
    DitherMat [2][1] = 12.0f / 17.0f;
    DitherMat [2][2] = 2.0f / 17.0f;
    DitherMat [2][3] = 10.0f / 17.0f;
    DitherMat [3][0] = 16.0f / 17.0f;
    DitherMat [3][1] = 8.0f / 17.0f;
    DitherMat [3][2] = 14.0f / 17.0f;
    DitherMat [3][3] = 6.0f / 17.0f;
    GLint DitherLoc = glGetUniformLocation(ProgramID, "DitherMatrix");
    glUniformMatrix4fv(DitherLoc, 1, GL_FALSE,DitherPoint);
    GLint ArrayTexLocation = glGetUniformLocation(ProgramID, "ourTexture");
    glUniform1i(ArrayTexLocation,0);
    //----------
    glUseProgram(HUDProgramID);
    DitherLoc = glGetUniformLocation(HUDProgramID, "DitherMatrix");
    glUniformMatrix4fv(DitherLoc, 1, GL_FALSE,DitherPoint);
    GLint HUDArrayTexLocation = glGetUniformLocation(HUDProgramID, "ourTexture");
    glUniform1i(HUDArrayTexLocation,0);
    //----------
    real32 PixelSize[2] = 
    {
        1.0f/(real32)CurrentWindowWidth,
        1.0f/(real32)CurrentWindowHeight
    };
    glUseProgram(FXAAProgramID);
    GLint PixelSizeLoc = glGetUniformLocation(FXAAProgramID, "PixelSize");
    glUniform2f(PixelSizeLoc,PixelSize[0],PixelSize[1]);
    GLint FXAATexLocation = glGetUniformLocation(FXAAProgramID, "tex0");
    glUniform1i(FXAATexLocation,0);
    
    //----------texture
    GLuint Texture = 0;
    GLsizei Width = 128;
    GLsizei Height = 128;
    GLsizei LayerCount = 256;
    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY,Texture);
    GLfloat fLargest;
    glGetFloatv(MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
    glTexParameterf(GL_TEXTURE_2D_ARRAY,TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexImage3D(GL_TEXTURE_2D_ARRAY,0,GL_RGBA,Width,Height,LayerCount,0,GL_BGRA,GL_UNSIGNED_BYTE,0);
    LoadTexture("TextureDefault.bmp",TEXTURENAME_DEFAULT);
    LoadTexture("Water.bmp",TEXTURENAME_WATER);
    LoadTexture("Soldier.bmp",TEXTURENAME_SOLDIER);
    LoadTexture("Font1.bmp",TEXTURENAME_FONT1);
    LoadTexture("Font2.bmp",TEXTURENAME_FONT2);
    LoadTexture("TestBlack.bmp",TEXTURENAME_BLACK);
    LoadTexture("TestGray.bmp",TEXTURENAME_GRAY);
    LoadTexture("TestWhite.bmp",TEXTURENAME_WHITE);
    LoadTexture("TestBlue.bmp",TEXTURENAME_BLUE);
    LoadTexture("TestGreen.bmp",TEXTURENAME_GREEN);
    LoadTexture("TestRed.bmp",TEXTURENAME_RED);
    LoadTexture("XAxisMove.bmp",TEXTURENAME_XAXISMOVE);
    LoadTexture("YAxisMove.bmp",TEXTURENAME_YAXISMOVE);
    LoadTexture("ZAxisMove.bmp",TEXTURENAME_ZAXISMOVE);
    LoadTexture("XAxisScale.bmp",TEXTURENAME_XAXISSCALE);
    LoadTexture("YAxisScale.bmp",TEXTURENAME_YAXISSCALE);
    LoadTexture("ZAxisScale.bmp",TEXTURENAME_ZAXISSCALE);
    LoadTexture("RotateAxis.bmp",TEXTURENAME_ROTATEAXIS);
    LoadTexture("Outline.bmp",TEXTURENAME_OUTLINE);
    LoadTexture("Selected.bmp",TEXTURENAME_SELECTED);
    LoadTexture("Damage.bmp",TEXTURENAME_DAMAGE);
    LoadTexture("Gradient.bmp",TEXTURENAME_GRADIENT);
    LoadTexture("GreenOutline.bmp",TEXTURENAME_GREENOUTLINE);
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    
    //----------
    glGenFramebuffers(1,&FrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER,FrameBuffer);
    glGenTextures(1,&FrameTexture);
    glBindTexture(GL_TEXTURE_2D, FrameTexture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,CurrentWindowWidth,CurrentWindowHeight,0,GL_BGRA,GL_UNSIGNED_BYTE,0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,FrameTexture,0);
    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,CurrentWindowWidth,CurrentWindowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

//------------------------------

internal void
OpenGLRender(game_state* GameState)
{
    //----------draw entities
    
    glUseProgram(ProgramID);
    glBindFramebuffer(GL_FRAMEBUFFER,FrameBuffer);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBufferSubData(GL_ARRAY_BUFFER,0,(GameState->VerticeCount)*4,&GameState->OpenGLVertices);
    glDrawArrays(GL_TRIANGLES,0,(GameState->VerticeCount/6));
    
    //----------FXAA// TODO(NAME): one pixel apron on top and right caused by fxaa.fix
    
    glUseProgram(FXAAProgramID);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glBindVertexArray(FXAAVAO);
    glBindBuffer(GL_ARRAY_BUFFER,FXAAVBO);
    glDrawArrays(GL_TRIANGLES,0,6);
    
    //----------draw hud
    
    glUseProgram(HUDProgramID);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glClear(GL_DEPTH_BUFFER_BIT);//clear to sort HUD
    glBufferSubData(GL_ARRAY_BUFFER,0,(GameState->HUDVerticeCount)*4,&GameState->OpenGLHUDVertices);// TODO(NAME): we are tossing entity data. should offset in buffer then draw. will care when solidifying HUD 
    glDrawArrays(GL_TRIANGLES,0,(GameState->HUDVerticeCount/6));
}