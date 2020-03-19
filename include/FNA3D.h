/* FNA3D - 3D Graphics Library for FNA
 *
 * Copyright (c) 2020 Ethan Lee
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software in a
 * product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * Ethan "flibitijibibo" Lee <flibitijibibo@flibitijibibo.com>
 *
 */

#ifndef FNA3D_H
#define FNA3D_H

#ifdef _WIN32
#define FNA3DAPI __declspec(dllexport)
#define FNA3DCALL __cdecl
#else
#define FNA3DAPI
#define FNA3DCALL
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Type Declarations */

typedef struct FNA3D_Device FNA3D_Device;
typedef struct FNA3D_Texture FNA3D_Texture;
typedef struct FNA3D_Buffer FNA3D_Buffer;
typedef struct FNA3D_Renderbuffer FNA3D_Renderbuffer;
typedef struct FNA3D_Effect FNA3D_Effect;
typedef struct FNA3D_Query FNA3D_Query;
typedef struct FNA3D_Backbuffer FNA3D_Backbuffer;

/* Enumerations, should match XNA 4.0 */

typedef enum
{
	FNA3D_PRESENTINTERVAL_DEFAULT,
	FNA3D_PRESENTINTERVAL_ONE,
	FNA3D_PRESENTINTERVAL_TWO,
	FNA3D_PRESENTINTERVAL_IMMEDIATE
} FNA3D_PresentInterval;

typedef enum
{
	FNA3D_DISPLAYORIENTATION_DEFAULT,
	FNA3D_DISPLAYORIENTATION_LANDSCAPELEFT,
	FNA3D_DISPLAYORIENTATION_LANDSCAPERIGHT,
	FNA3D_DISPLAYORIENTATION_PORTRAIT
} FNA3D_DisplayOrientation;

typedef enum
{
	FNA3D_RENDERTARGETUSAGE_DISCARDCONTENTS,
	FNA3D_RENDERTARGETUSAGE_PRESERVECONTENTS,
	FNA3D_RENDERTARGETUSAGE_PLATFORMCONTENTS
} FNA3D_RenderTargetUsage;

typedef enum
{
	FNA3D_CLEAROPTIONS_TARGET	= 1,
	FNA3D_CLEAROPTIONS_DEPTHBUFFER	= 2,
	FNA3D_CLEAROPTIONS_STENCIL	= 4
} FNA3D_ClearOptions;

typedef enum
{
	FNA3D_PRIMITIVETYPE_TRIANGLELIST,
	FNA3D_PRIMITIVETYPE_TRIANGLESTRIP,
	FNA3D_PRIMITIVETYPE_LINELIST,
	FNA3D_PRIMITIVETYPE_LINESTRIP,
	FNA3D_PRIMITIVETYPE_POINTLIST_EXT
} FNA3D_PrimitiveType;

typedef enum
{
	FNA3D_INDEXELEMENTSIZE_16BIT,
	FNA3D_INDEXELEMENTSIZE_32BIT
} FNA3D_IndexElementSize;

typedef enum
{
	FNA3D_SURFACEFORMAT_COLOR,
	FNA3D_SURFACEFORMAT_BGR565,
	FNA3D_SURFACEFORMAT_BGRA5551,
	FNA3D_SURFACEFORMAT_BGRA4444,
	FNA3D_SURFACEFORMAT_DXT1,
	FNA3D_SURFACEFORMAT_DXT3,
	FNA3D_SURFACEFORMAT_DXT5,
	FNA3D_SURFACEFORMAT_NORMALIZEDBYTE2,
	FNA3D_SURFACEFORMAT_NORMALIZEDBYTE4,
	FNA3D_SURFACEFORMAT_RGBA1010102,
	FNA3D_SURFACEFORMAT_RG32,
	FNA3D_SURFACEFORMAT_RGBA64,
	FNA3D_SURFACEFORMAT_ALPHA8,
	FNA3D_SURFACEFORMAT_SINGLE,
	FNA3D_SURFACEFORMAT_VECTOR2,
	FNA3D_SURFACEFORMAT_VECTOR4,
	FNA3D_SURFACEFORMAT_HALFSINGLE,
	FNA3D_SURFACEFORMAT_HALFVECTOR2,
	FNA3D_SURFACEFORMAT_HALFVECTOR4,
	FNA3D_SURFACEFORMAT_HDRBLENDABLE,
	FNA3D_SURFACEFORMAT_COLORBGRA_EXT
} FNA3D_SurfaceFormat;

typedef enum
{
	FNA3D_DEPTHFORMAT_NONE,
	FNA3D_DEPTHFORMAT_D16,
	FNA3D_DEPTHFORMAT_D24,
	FNA3D_DEPTHFORMAT_D24S8
} FNA3D_DepthFormat;

typedef enum
{
	FNA3D_CUBEMAPFACE_POSITIVEX,
	FNA3D_CUBEMAPFACE_NEGATIVEX,
	FNA3D_CUBEMAPFACE_POSITIVEY,
	FNA3D_CUBEMAPFACE_NEGATIVEY,
	FNA3D_CUBEMAPFACE_POSITIVEZ,
	FNA3D_CUBEMAPFACE_NEGATIVEZ
} FNA3D_CubeMapFace;

typedef enum
{
	FNA3D_BUFFERUSAGE_NONE,
	FNA3D_BUFFERUSAGE_WRITEONLY
} FNA3D_BufferUsage;

typedef enum
{
	FNA3D_SETDATAOPTIONS_NONE,
	FNA3D_SETDATAOPTIONS_DISCARD,
	FNA3D_SETDATAOPTIONS_NOOVERWRITE
} FNA3D_SetDataOptions;

typedef enum
{
	FNA3D_BLEND_ONE,
	FNA3D_BLEND_ZERO,
	FNA3D_BLEND_SOURCECOLOR,
	FNA3D_BLEND_INVERSESOURCECOLOR,
	FNA3D_BLEND_SOURCEALPHA,
	FNA3D_BLEND_INVERSESOURCEALPHA,
	FNA3D_BLEND_DESTINATIONCOLOR,
	FNA3D_BLEND_INVERSEDESTINATIONCOLOR,
	FNA3D_BLEND_DESTINATIONALPHA,
	FNA3D_BLEND_INVERSEDESTINATIONALPHA,
	FNA3D_BLEND_BLENDFACTOR,
	FNA3D_BLEND_INVERSEBLENDFACTOR,
	FNA3D_BLEND_SOURCEALPHASATURATION
} FNA3D_Blend;

typedef enum
{
	FNA3D_BLENDFUNCTION_ADD,
	FNA3D_BLENDFUNCTION_SUBTRACT,
	FNA3D_BLENDFUNCTION_REVERSESUBTRACT,
	FNA3D_BLENDFUNCTION_MAX,
	FNA3D_BLENDFUNCTION_MIN
} FNA3D_BlendFunction;

typedef enum
{
	FNA3D_COLORWRITECHANNELS_NONE	= 0,
	FNA3D_COLORWRITECHANNELS_RED	= 1,
	FNA3D_COLORWRITECHANNELS_GREEN	= 2,
	FNA3D_COLORWRITECHANNELS_BLUE	= 4,
	FNA3D_COLORWRITECHANNELS_ALPHA	= 8,
	FNA3D_COLORWRITECHANNELS_ALL	= 15
} FNA3D_ColorWriteChannels;

typedef enum
{
	FNA3D_STENCILOPERATION_KEEP,
	FNA3D_STENCILOPERATION_ZERO,
	FNA3D_STENCILOPERATION_REPLACE,
	FNA3D_STENCILOPERATION_INCREMENT,
	FNA3D_STENCILOPERATION_DECREMENT,
	FNA3D_STENCILOPERATION_INCREMENTSATURATION,
	FNA3D_STENCILOPERATION_DECREMENTSATURATION,
	FNA3D_STENCILOPERATION_INVERT
} FNA3D_StencilOperation;

typedef enum
{
	FNA3D_COMPAREFUNCTION_ALWAYS,
	FNA3D_COMPAREFUNCTION_NEVER,
	FNA3D_COMPAREFUNCTION_LESS,
	FNA3D_COMPAREFUNCTION_LESSEQUAL,
	FNA3D_COMPAREFUNCTION_EQUAL,
	FNA3D_COMPAREFUNCTION_GREATEREQUAL,
	FNA3D_COMPAREFUNCTION_GREATER,
	FNA3D_COMPAREFUNCTION_NOTEQUAL
} FNA3D_CompareFunction;

typedef enum
{
	FNA3D_CULLMODE_NONE,
	FNA3D_CULLMODE_CULLCLOCKWISEFACE,
	FNA3D_CULLMODE_CULLCOUNTERCLOCKWISEFACE
} FNA3D_CullMode;

typedef enum
{
	FNA3D_FILLMODE_SOLID,
	FNA3D_FILLMODE_WIREFRAME
} FNA3D_FillMode;

typedef enum
{
	FNA_TEXTUREADDRESSMODE_WRAP,
	FNA_TEXTUREADDRESSMODE_CLAMP,
	FNA_TEXTUREADDRESSMODE_MIRROR,
} FNA3D_TextureAddressMode;

typedef enum
{
	FNA3D_TEXTUREFILTER_LINEAR,
	FNA3D_TEXTUREFILTER_POINT,
	FNA3D_TEXTUREFILTER_ANISOTROPIC,
	FNA3D_TEXTUREFILTER_LINEAR_MIPPOINT,
	FNA3D_TEXTUREFILTER_POINT_MIPLINEAR,
	FNA3D_TEXTUREFILTER_MINLINEAR_MAGPOINT_MIPLINEAR,
	FNA3D_TEXTUREFILTER_MINLINEAR_MAGPOINT_MIPPOINT,
	FNA3D_TEXTUREFILTER_MINPOINT_MAGLINEAR_MIPLINEAR,
	FNA3D_TEXTUREFILTER_MINPOINT_MAGLINEAR_MIPPOINT
} FNA3D_TextureFilter;

/* Structures, should match XNA 4.0 */

typedef struct FNA3D_Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} FNA3D_Color;

typedef struct FNA3D_Rect
{
	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;
} FNA3D_Rect;

typedef struct FNA3D_Vec4
{
	float x;
	float y;
	float z;
	float w;
} FNA3D_Vec4;

typedef struct FNA3D_Viewport
{
	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;
	float minDepth;
	float maxDepth;
} FNA3D_Viewport;

typedef struct FNA3D_BlendState
{
	FNA3D_Color blendColor;
	int32_t multisampleMask;
	FNA3D_BlendFunction blendFunc;
	FNA3D_BlendFunction blendFuncAlpha;
	FNA3D_Blend srcBlend;
	FNA3D_Blend dstBlend;
	FNA3D_Blend srcBlendAlpha;
	FNA3D_Blend dstBlendAlpha;
	FNA3D_ColorWriteChannels colorWriteEnable;
	FNA3D_ColorWriteChannels colorWriteEnable1;
	FNA3D_ColorWriteChannels colorWriteEnable2;
	FNA3D_ColorWriteChannels colorWriteEnable3;
} FNA3D_BlendState;

typedef struct FNA3D_DepthStencilState
{
	uint8_t zEnable;
	uint8_t zWriteEnable;
	FNA3D_CompareFunction depthFunc;
	uint8_t stencilEnable;
	int32_t stencilWriteMask;
	uint8_t separateStencilEnable;
	int32_t stencilRef;
	int32_t stencilMask;
	FNA3D_CompareFunction stencilFunc;
	FNA3D_StencilOperation stencilFail;
	FNA3D_StencilOperation stencilZFail;
	FNA3D_StencilOperation stencilPass;
	FNA3D_CompareFunction ccwStencilFunc;
	FNA3D_StencilOperation ccwStencilFail;
	FNA3D_StencilOperation ccwStencilZFail;
	FNA3D_StencilOperation ccwStencilPass;
} FNA3D_DepthStencilState;

typedef struct FNA3D_RasterizerState
{
	uint8_t scissorTestEnable;
	FNA3D_CullMode cullFrontFace;
	FNA3D_FillMode fillMode;
	float depthBias;
	float slopeScaleDepthBias;
	uint8_t multiSampleEnable;
} FNA3D_RasterizerState;

typedef struct FNA3D_SamplerState
{
	FNA3D_TextureAddressMode addressU;
	FNA3D_TextureAddressMode addressV;
	FNA3D_TextureAddressMode addressW;
	FNA3D_TextureFilter filter;
	int32_t maxAnisotropy;
	int32_t maxMipLevel;
	float mipMapLevelOfDetailBias;
} FNA3D_SamplerState;

typedef struct FNA3D_PresentationParameters
{
	uint32_t backBufferWidth;
	uint32_t backBufferHeight;
	FNA3D_SurfaceFormat backBufferFormat;
	int32_t multiSampleCount;
	void* deviceWindowHandle;
	uint8_t isFullScreen;
	FNA3D_SurfaceFormat depthStencilFormat;
	FNA3D_PresentInterval presentationInterval;
	FNA3D_DisplayOrientation displayOrientation;
	FNA3D_RenderTargetUsage renderTargetUsage;
} FNA3D_PresentationParameters;

/* Functions */

/* Init/Quit */

/* This should be called before window creation!
 * Returns an SDL_WindowFlags mask.
 */
FNA3DAPI uint32_t FNA3D_PrepareWindowAttributes(uint8_t debugMode);

FNA3DAPI FNA3D_Device* FNA3D_CreateDevice(
	FNA3D_PresentationParameters *presentationParameters
);

FNA3DAPI void FNA3D_DestroyDevice(FNA3D_Device *device);

/* Begin/End Frame */

FNA3DAPI void FNA3D_BeginFrame(FNA3D_Device *device);

FNA3DAPI void FNA3D_SwapBuffers(
	FNA3D_Device *device,
	FNA3D_Rect *sourceRectangle,
	FNA3D_Rect *destinationRectangle,
	void* overrideWindowHandle
);

FNA3DAPI void FNA3D_SetPresentationInterval(
	FNA3D_Device *device,
	FNA3D_PresentInterval presentInterval
);

/* Drawing */

FNA3DAPI void FNA3D_Clear(
	FNA3D_Device *device,
	FNA3D_ClearOptions options,
	FNA3D_Vec4 *color,
	float depth,
	int32_t stencil
);

FNA3DAPI void FNA3D_DrawIndexedPrimitives(
	FNA3D_Device *device,
	FNA3D_PrimitiveType primitiveType,
	int32_t baseVertex,
	int32_t minVertexIndex,
	int32_t numVertices,
	int32_t startIndex,
	int32_t primitiveCount,
	FNA3D_Buffer *indices,
	FNA3D_IndexElementSize indexElementSize
);
FNA3DAPI void FNA3D_DrawInstancedPrimitives(
	FNA3D_Device *device,
	FNA3D_PrimitiveType primitiveType,
	int32_t baseVertex,
	int32_t minVertexIndex,
	int32_t numVertices,
	int32_t startIndex,
	int32_t primitiveCount,
	int32_t instanceCount,
	FNA3D_Buffer *indices,
	FNA3D_IndexElementSize indexElementSize
);
FNA3DAPI void FNA3D_DrawPrimitives(
	FNA3D_Device *device,
	FNA3D_PrimitiveType primitiveType,
	int32_t vertexStart,
	int32_t primitiveCount
);
FNA3DAPI void FNA3D_DrawUserIndexedPrimitives(
	FNA3D_Device *device,
	FNA3D_PrimitiveType primitiveType,
	void* vertexData,
	int32_t vertexOffset,
	int32_t numVertices,
	void* indexData,
	int32_t indexOffset,
	FNA3D_IndexElementSize indexElementSize,
	int32_t primitiveCount
);
FNA3DAPI void FNA3D_DrawUserPrimitives(
	FNA3D_Device *device,
	FNA3D_PrimitiveType primitiveType,
	void* vertexData,
	int32_t vertexOffset,
	int32_t primitiveCount
);

/* Mutable Render States */

FNA3DAPI void FNA3D_SetViewport(FNA3D_Device *device, FNA3D_Viewport *viewport);
FNA3DAPI void FNA3D_SetScissorRect(FNA3D_Device *device, FNA3D_Rect *scissor);

FNA3DAPI void FNA3D_GetBlendFactor(
	FNA3D_Device *device,
	FNA3D_Color *blendFactor
);
FNA3DAPI void FNA3D_SetBlendFactor(
	FNA3D_Device *device,
	FNA3D_Color *blendFactor
);

FNA3DAPI int32_t FNA3D_GetMultiSampleMask(FNA3D_Device *device);
FNA3DAPI void FNA3D_SetMultiSampleMask(FNA3D_Device *device, int32_t mask);

FNA3DAPI int32_t FNA3D_GetReferenceStencil(FNA3D_Device *device);
FNA3DAPI void FNA3D_SetReferenceStencil(FNA3D_Device *device, int32_t ref);

/* Immutable Render States */

FNA3DAPI void FNA3D_SetBlendState(
	FNA3D_Device *device,
	FNA3D_BlendState *blendState
);
FNA3DAPI void FNA3D_SetDepthStencilState(
	FNA3D_Device *device,
	FNA3D_DepthStencilState *depthStencilState
);
FNA3DAPI void FNA3D_ApplyRasterizerState(
	FNA3D_Device *device,
	FNA3D_RasterizerState *rasterizerState
);
FNA3DAPI void VerifySampler(
	FNA3D_Device *device,
	int32_t index,
	FNA3D_Texture *texture,
	FNA3D_SamplerState *sampler
);

/* Vertex State */

FNA3DAPI void FNA3D_ApplyVertexBufferBindings(
	FNA3D_Device *device,
	/* FIXME: Oh shit VertexBufferBinding[] bindings, */
	int32_t numBindings,
	uint8_t bindingsUpdated,
	int32_t baseVertex
);

FNA3DAPI void FNA3D_ApplyVertexDeclaration(
	FNA3D_Device *device,
	/* FIXME: Oh shit VertexDeclaration vertexDeclaration, */
	void* ptr,
	int32_t vertexOffset
);

/* Render Targets */

FNA3DAPI void FNA3D_SetRenderTargets(
	FNA3D_Device *device,
	/* FIXME: Oh shit RenderTargetBinding[] renderTargets, */
	FNA3D_Renderbuffer *renderbuffer,
	FNA3D_DepthFormat depthFormat
);

FNA3DAPI void FNA3D_ResolveTarget(
	FNA3D_Device *device
	/* FIXME: Oh shit RenderTargetBinding target */
);

/* Backbuffer Functions */

FNA3DAPI FNA3D_Backbuffer* FNA3D_GetBackbuffer(FNA3D_Device *device);

FNA3DAPI void FNA3D_ResetBackbuffer(
	FNA3D_Device *device,
	FNA3D_PresentationParameters *presentationParameters
);

FNA3DAPI void FNA3D_ReadBackbuffer(
	FNA3D_Device *device,
	void* data,
	int32_t dataLen,
	int32_t startIndex,
	int32_t elementCount,
	int32_t elementSizeInBytes,
	int32_t x,
	int32_t y,
	int32_t w,
	int32_t h
);

/* Textures */

FNA3DAPI FNA3D_Texture* FNA3D_CreateTexture2D(
	FNA3D_Device *device,
	FNA3D_SurfaceFormat format,
	int32_t width,
	int32_t height,
	int32_t levelCount,
	uint8_t isRenderTarget
);
FNA3DAPI FNA3D_Texture* FNA3D_CreateTexture3D(
	FNA3D_Device *device,
	FNA3D_SurfaceFormat format,
	int32_t width,
	int32_t height,
	int32_t depth,
	int32_t levelCount
);
FNA3DAPI FNA3D_Texture* FNA3D_CreateTextureCube(
	FNA3D_Device *device,
	FNA3D_SurfaceFormat format,
	int32_t size,
	int32_t levelCount,
	uint8_t isRenderTarget
);
FNA3DAPI void FNA3D_AddDisposeTexture(
	FNA3D_Device *device,
	FNA3D_Texture *texture
);
FNA3DAPI void FNA3D_SetTextureData2D(
	FNA3D_Device *device,
	FNA3D_Texture *texture,
	FNA3D_SurfaceFormat format,
	int32_t x,
	int32_t y,
	int32_t w,
	int32_t h,
	int32_t level,
	void* data,
	int32_t dataLength
);
FNA3DAPI void FNA3D_SetTextureData3D(
	FNA3D_Device *device,
	FNA3D_Texture *texture,
	FNA3D_SurfaceFormat format,
	int32_t level,
	int32_t left,
	int32_t top,
	int32_t right,
	int32_t bottom,
	int32_t front,
	int32_t back,
	void* data,
	int32_t dataLength
);
FNA3DAPI void FNA3D_SetTextureDataCube(
	FNA3D_Device *device,
	FNA3D_Texture *texture,
	FNA3D_SurfaceFormat format,
	int32_t x,
	int32_t y,
	int32_t w,
	int32_t h,
	FNA3D_CubeMapFace cubeMapFace,
	int32_t level,
	void* data,
	int32_t dataLength
);
FNA3DAPI void FNA3D_SetTextureDataYUV(
	FNA3D_Device *device,
	FNA3D_Texture *textures,
	void* ptr
);
FNA3DAPI void FNA3D_GetTextureData2D(
	FNA3D_Device *device,
	FNA3D_Texture *texture,
	FNA3D_SurfaceFormat format,
	int32_t textureWidth,
	int32_t textureHeight,
	int32_t level,
	int32_t x,
	int32_t y,
	int32_t w,
	int32_t h,
	void* data,
	int32_t startIndex,
	int32_t elementCount,
	int32_t elementSizeInBytes
);
FNA3DAPI void FNA3D_GetTextureData3D(
	FNA3D_Device *device,
	FNA3D_Texture *texture,
	FNA3D_SurfaceFormat format,
	int32_t left,
	int32_t top,
	int32_t front,
	int32_t right,
	int32_t bottom,
	int32_t back,
	int32_t level,
	void* data,
	int32_t startIndex,
	int32_t elementCount,
	int32_t elementSizeInBytes
);
FNA3DAPI void FNA3D_GetTextureDataCube(
	FNA3D_Device *device,
	FNA3D_Texture *texture,
	FNA3D_SurfaceFormat format,
	int32_t textureSize,
	FNA3D_CubeMapFace cubeMapFace,
	int32_t level,
	int32_t x,
	int32_t y,
	int32_t w,
	int32_t h,
	void* data,
	int32_t startIndex,
	int32_t elementCount,
	int32_t elementSizeInBytes
);

/* Renderbuffers */

FNA3DAPI FNA3D_Renderbuffer* FNA3D_GenColorRenderbuffer(
	FNA3D_Device *device,
	int32_t width,
	int32_t height,
	FNA3D_SurfaceFormat format,
	int32_t multiSampleCount,
	FNA3D_Texture *texture
);
FNA3DAPI FNA3D_Renderbuffer* FNA3D_GenDepthStencilRenderbuffer(
	FNA3D_Device *device,
	int32_t width,
	int32_t height,
	FNA3D_DepthFormat format,
	int32_t multiSampleCount
);
FNA3DAPI void FNA3D_AddDisposeRenderbuffer(
	FNA3D_Device *device,
	FNA3D_Renderbuffer *renderbuffer
);

/* Vertex Buffers */

FNA3DAPI FNA3D_Buffer* FNA3D_GenVertexBuffer(
	FNA3D_Device *device,
	uint8_t dynamic,
	FNA3D_BufferUsage usage,
	int32_t vertexCount,
	int32_t vertexStride
);
FNA3DAPI void FNA3D_AddDisposeVertexBuffer(
	FNA3D_Device *device,
	FNA3D_Buffer *buffer
);
FNA3DAPI void FNA3D_SetVertexBufferData(
	FNA3D_Device *device,
	FNA3D_Buffer *buffer,
	int32_t offsetInBytes,
	void* data,
	int32_t dataLength,
	FNA3D_SetDataOptions options
);
FNA3DAPI void FNA3D_GetVertexBufferData(
	FNA3D_Device *device,
	FNA3D_Buffer *buffer,
	int32_t offsetInBytes,
	void* data,
	int32_t startIndex,
	int32_t elementCount,
	int32_t elementSizeInBytes,
	int32_t vertexStride
);

/* Index Buffers */

FNA3DAPI FNA3D_Buffer* FNA3D_GenIndexBuffer(
	FNA3D_Device *device,
	uint8_t dynamic,
	FNA3D_BufferUsage usage,
	int32_t indexCount,
	FNA3D_IndexElementSize indexElementSize
);
FNA3DAPI void FNA3D_AddDisposeIndexBuffer(
	FNA3D_Device *device,
	FNA3D_Buffer *buffer
);
FNA3DAPI void FNA3D_SetIndexBufferData(
	FNA3D_Device *device,
	FNA3D_Buffer *buffer,
	int32_t offsetInBytes,
	void* data,
	int32_t dataLength,
	FNA3D_SetDataOptions options
);
FNA3DAPI void FNA3D_GetIndexBufferData(
	FNA3D_Device *device,
	FNA3D_Buffer *buffer,
	int32_t offsetInBytes,
	void* data,
	int32_t startIndex,
	int32_t elementCount,
	int32_t elementSizeInBytes
);

/* Effects */

FNA3DAPI FNA3D_Effect* FNA3D_CreateEffect(
	FNA3D_Device *device,
	uint8_t *effectCode
);
FNA3DAPI FNA3D_Effect* FNA3D_CloneEffect(
	FNA3D_Device *device,
	FNA3D_Effect *effect
);
FNA3DAPI void FNA3D_AddDisposeEffect(
	FNA3D_Device *device,
	FNA3D_Effect *effect
);
FNA3DAPI void FNA3D_ApplyEffect(
	FNA3D_Device *device,
	FNA3D_Effect *effect,
	void* technique, /* FIXME: Should be MojoShader */
	uint32_t pass,
	void* stateChanges /* FIXME: Should be MojoShader */
);
FNA3DAPI void FNA3D_BeginPassRestore(
	FNA3D_Device *device,
	FNA3D_Effect *effect,
	void* stateChanges /* FIXME: Should be MojoShader */
);
FNA3DAPI void FNA3D_EndPassRestore(
	FNA3D_Device *device,
	FNA3D_Effect *effect
);
#endif

/* Queries */

FNA3DAPI FNA3D_Query* FNA3D_CreateQuery(FNA3D_Device *device);
FNA3DAPI void FNA3D_AddDisposeQuery(FNA3D_Device *device, FNA3D_Query *query);
FNA3DAPI void FNA3D_QueryBegin(FNA3D_Device *device, FNA3D_Query *query);
FNA3DAPI void FNA3D_QueryEnd(FNA3D_Device *device, FNA3D_Query *query);
FNA3DAPI uint8_t FNA3D_QueryComplete(FNA3D_Device *device, FNA3D_Query *query);
FNA3DAPI int32_t FNA3D_QueryPixelCount(
	FNA3D_Device *device,
	FNA3D_Query *query
);

/* Feature Queries */

FNA3DAPI uint8_t FNA3D_SupportsDXT1(FNA3D_Device *device);
FNA3DAPI uint8_t FNA3D_SupportsS3TC(FNA3D_Device *device);
FNA3DAPI uint8_t FNA3D_SupportsHardwareInstancing(FNA3D_Device *device);
FNA3DAPI uint8_t FNA3D_SupportsNoOverwrite(FNA3D_Device *device);

FNA3DAPI int32_t FNA3D_GetMaxTextureSlots(FNA3D_Device *device);
FNA3DAPI int32_t FNA3D_GetMaxMultiSampleCount(FNA3D_Device *device);

/* Debugging */

FNA3DAPI void FNA3D_SetStringMarker(FNA3D_Device *device, const char *text);

/* TODO: Debug callback function...? */

/* Buffer Objects */

FNA3DAPI intptr_t FNA3D_GetBufferSize(
	FNA3D_Device *device,
	FNA3D_Buffer *buffer
);

/* Effect Objects */

FNA3DAPI void* FNA3D_GetEffectData(
	FNA3D_Device *device,
	FNA3D_Effect *effect
);

/* Backbuffer Objects */

FNA3DAPI int32_t FNA3D_GetBackbufferWidth(
	FNA3D_Device *device,
	FNA3D_Backbuffer *backbuffer
);
FNA3DAPI int32_t FNA3D_GetBackbufferHeight(
	FNA3D_Device *device,
	FNA3D_Backbuffer *backbuffer
);
FNA3DAPI FNA3D_DepthFormat FNA3D_GetBackbufferDepthFormat(
	FNA3D_Device *device,
	FNA3D_Backbuffer *backbuffer
);
FNA3DAPI int32_t FNA3D_GetBackbufferMultiSampleCount(
	FNA3D_Device *device,
	FNA3D_Backbuffer *backbuffer
);
FNA3DAPI void FNA3D_ResetFramebuffer(
	FNA3D_Device *device,
	FNA3D_Backbuffer *backbuffer,
	FNA3D_PresentationParameters *presentationParameters
);

#ifdef __cplusplus
}
#endif /* __cplusplus */
