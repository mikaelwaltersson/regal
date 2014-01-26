/*
  Copyright (c) 2011-2012 NVIDIA Corporation
  Copyright (c) 2011-2012 Cass Everitt
  Copyright (c) 2012 Scott Nations
  Copyright (c) 2012 Mathias Schott
  Copyright (c) 2012 Nigel Stewart
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
  OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __REGAL_STATE_H__
#define __REGAL_STATE_H__

#include "RegalUtil.h"

#if REGAL_EMULATION

REGAL_GLOBAL_BEGIN

#include <cstring>    // For memset, memcpy

#include <string>
#include <algorithm>  // For std::swap

#include "RegalContext.h"
#include "RegalPrint.h"

#include "RegalEmu.h"
#include "RegalToken.h"
#include "RegalDispatch.h"

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

//
// OpenGL State Tracking
//
// Motivating requirements:
//
//  - Emulation of glPushAttrib and glPopAttrib for OpenGL ES and
//    core OpenGL that lack the functionality.
//
//  - OpenGL state capture, browsing, diff and serialization.
//
// See also:
//
//  - Gallium3D
//    http://wiki.freedesktop.org/wiki/Software/gallium
//    http://dri.freedesktop.org/doxygen/gallium/p__state_8h-source.html
//
//  - Tracking Graphics State For Networked Rendering
//    Ian Buck, Greg Humphreys and Pat Hanrahan.
//    Stanford University
//    Proceedings of the 2000 Eurographics/SIGGRAPH Workshop on Graphics Hardware
//    http://graphics.stanford.edu/papers/state_tracking/
//
//  - Chromium: A Stream Processing Framework for Interactive Rendering on Clusters
//    Greg Humphreys, Mike Houston, Ren Ng
//    Stanford University
//    SIGGRAPH 2002
//    http://graphics.stanford.edu/papers/cr/
//

#define REGAL_FIXED_FUNCTION_MATRIX_STACK_DEPTH 128
#define REGAL_FIXED_FUNCTION_MAX_LIGHTS           8
#define REGAL_FIXED_FUNCTION_MAX_CLIP_PLANES      8
#define REGAL_FIXED_FUNCTION_MAX_CLIP_DISTANCES   8

namespace State
{

typedef StringList string_list;

  template <typename Procs>
inline static void setEnable(Procs &dt, const GLenum cap, const GLboolean enable)
{
  if (enable)
    RglEnable( dt, cap);
  else
    RglDisable( dt, cap);
}

  template <typename Procs>
inline static void setEnablei(Procs &dt, const GLenum cap, const GLuint index, const GLboolean enable)
{
  if (enable)
    RglEnablei( dt, cap,index);
  else
    RglDisablei( dt, cap,index);
}

inline static void enableToString(string_list &tmp, const GLboolean b, const char *bEnum, const char *delim = "\n")
{
  tmp << print_string(b ? "glEnable(" : "glDisable(",bEnum,");",delim);
}

inline static void enableiToString(string_list &tmp, const GLboolean b, const char *bEnum, const GLuint index, const char *delim = "\n")
{
  tmp << print_string(b ? "glEnablei(" : "glDisablei(",bEnum,",",index,");",delim);
}

//
// glPushAttrib(GL_ENABLE_BIT)
//

struct Enable
{
  GLboolean   alphaTest;                 // GL_ALPHA_TEST
  GLboolean   autoNormal;                // GL_AUTO_NORMAL
  GLboolean   blend[REGAL_EMU_MAX_DRAW_BUFFERS]; // GL_BLEND
  GLboolean   clipDistance[REGAL_FIXED_FUNCTION_MAX_CLIP_DISTANCES]; // GL_CLIP_DISTANCEi
  GLenum      clampFragmentColor;        // GL_CLAMP_FRAGMENT_COLOR
  GLenum      clampReadColor;            // GL_CLAMP_READ_COLOR
  GLenum      clampVertexColor;          // GL_CLAMP_VERTEX_COLOR
  GLboolean   colorLogicOp;              // GL_COLOR_LOGIC_OP
  GLboolean   colorMaterial;             // GL_COLOR_MATERIAL
  GLboolean   colorSum;                  // GL_COLOR_SUM
  GLboolean   colorTable;                // GL_COLOR_TABLE
  GLboolean   convolution1d;             // GL_CONVOLUTION_1D
  GLboolean   convolution2d;             // GL_CONVOLUTION_2D
  GLboolean   cullFace;                  // GL_CULL_FACE
  GLboolean   depthClamp;                // GL_DEPTH_CLAMP
  GLboolean   depthTest;                 // GL_DEPTH_TEST
  GLboolean   dither;                    // GL_DITHER
  GLboolean   fog;                       // GL_FOG
  GLboolean   framebufferSRGB;           // GL_FRAMEBUFFER_SRGB
  GLboolean   histogram;                 // GL_HISTOGRAM
  GLboolean   indexLogicOp;              // GL_INDEX_LOGIC_OP
  GLboolean   light[REGAL_FIXED_FUNCTION_MAX_LIGHTS]; // GL_LIGHTi
  GLboolean   lighting;                  // GL_LIGHTING
  GLboolean   lineSmooth;                // GL_LINE_SMOOTH
  GLboolean   lineStipple;               // GL_LINE_STIPPLE
  GLboolean   map1Color4;                // GL_MAP1_COLOR_4
  GLboolean   map1Index;                 // GL_MAP1_INDEX
  GLboolean   map1Normal;                // GL_MAP1_NORMAL
  GLboolean   map1TextureCoord1;         // GL_MAP1_TEXTURE_COORD_1
  GLboolean   map1TextureCoord2;         // GL_MAP1_TEXTURE_COORD_2
  GLboolean   map1TextureCoord3;         // GL_MAP1_TEXTURE_COORD_3
  GLboolean   map1TextureCoord4;         // GL_MAP1_TEXTURE_COORD_4
  GLboolean   map1Vertex3;               // GL_MAP1_VERTEX_3
  GLboolean   map1Vertex4;               // GL_MAP1_VERTEX_4
  GLboolean   map2Color4;                // GL_MAP2_COLOR_4
  GLboolean   map2Index;                 // GL_MAP2_INDEX
  GLboolean   map2Normal;                // GL_MAP2_NORMAL
  GLboolean   map2TextureCoord1;         // GL_MAP2_TEXTURE_COORD_1
  GLboolean   map2TextureCoord2;         // GL_MAP2_TEXTURE_COORD_2
  GLboolean   map2TextureCoord3;         // GL_MAP2_TEXTURE_COORD_3
  GLboolean   map2TextureCoord4;         // GL_MAP2_TEXTURE_COORD_4
  GLboolean   map2Vertex3;               // GL_MAP2_VERTEX_3
  GLboolean   map2Vertex4;               // GL_MAP2_VERTEX_4
  GLboolean   minmax;                    // GL_MINMAX
  GLboolean   multisample;               // GL_MULTISAMPLE
  GLboolean   normalize;                 // GL_NORMALIZE
  GLboolean   pointSmooth;               // GL_POINT_SMOOTH
  GLboolean   pointSprite;               // GL_POINT_SPRITE
  GLboolean   polygonOffsetFill;         // GL_POLYGON_OFFSET_FILL
  GLboolean   polygonOffsetLine;         // GL_POLYGON_OFFSET_LINE
  GLboolean   polygonOffsetPoint;        // GL_POLYGON_OFFSET_POINT
  GLboolean   polygonSmooth;             // GL_POLYGON_SMOOTH
  GLboolean   polygonStipple;            // GL_POLYGON_STIPPLE
  GLboolean   postColorMatrixColorTable; // GL_POST_COLOR_MATRIX_COLOR_TABLE
  GLboolean   postConvolutionColorTable; // GL_POST_CONVOLUTION_COLOR_TABLE
  GLboolean   programPointSize;          // GL_PROGRAM_POINT_SIZE
  GLboolean   rescaleNormal;             // GL_RESCALE_NORMAL
  GLboolean   sampleAlphaToCoverage;     // GL_SAMPLE_ALPHA_TO_COVERAGE
  GLboolean   sampleAlphaToOne;          // GL_SAMPLE_ALPHA_TO_ONE
  GLboolean   sampleCoverage;            // GL_SAMPLE_COVERAGE
  GLboolean   sampleShading;             // GL_SAMPLE_SHADING
  GLboolean   separable2d;               // GL_SEPARABLE_2D
  GLboolean   scissorTest[REGAL_EMU_MAX_VIEWPORTS]; // GL_SCISSOR_TEST
  GLboolean   stencilTest;               // GL_STENCIL_TEST
  GLboolean   texture1d[REGAL_EMU_MAX_TEXTURE_UNITS];        // GL_TEXTURE_1D
  GLboolean   texture2d[REGAL_EMU_MAX_TEXTURE_UNITS];        // GL_TEXTURE_2D
  GLboolean   texture3d[REGAL_EMU_MAX_TEXTURE_UNITS];        // GL_TEXTURE_3D
  GLboolean   textureCubeMap[REGAL_EMU_MAX_TEXTURE_UNITS];   // GL_TEXTURE_CUBE_MAP
  GLboolean   textureRectangle[REGAL_EMU_MAX_TEXTURE_UNITS]; // GL_TEXTURE_RECTANGLE
  GLboolean   textureGenS[REGAL_EMU_MAX_TEXTURE_UNITS];      // GL_TEXTURE_GEN_S
  GLboolean   textureGenT[REGAL_EMU_MAX_TEXTURE_UNITS];      // GL_TEXTURE_GEN_T
  GLboolean   textureGenR[REGAL_EMU_MAX_TEXTURE_UNITS];      // GL_TEXTURE_GEN_R
  GLboolean   textureGenQ[REGAL_EMU_MAX_TEXTURE_UNITS];      // GL_TEXTURE_GEN_Q
  GLboolean   vertexProgramTwoSide;      // GL_VERTEX_PROGRAM_TWO_SIDE

  inline Enable()
    : alphaTest(GL_FALSE)
    , autoNormal(GL_FALSE)
    , clampFragmentColor(GL_FIXED_ONLY)
    , clampReadColor(GL_FIXED_ONLY)
    , clampVertexColor(GL_TRUE)
    , colorLogicOp(GL_FALSE)
    , colorMaterial(GL_FALSE)
    , colorSum(GL_FALSE)
    , colorTable(GL_FALSE)
    , convolution1d(GL_FALSE)
    , convolution2d(GL_FALSE)
    , cullFace(GL_FALSE)
    , depthClamp(GL_FALSE)
    , depthTest(GL_FALSE)
    , dither(GL_TRUE)
    , fog(GL_FALSE)
    , framebufferSRGB(GL_FALSE)
    , histogram(GL_FALSE)
    , indexLogicOp(GL_FALSE)
    , lighting(GL_FALSE)
    , lineSmooth(GL_FALSE)
    , lineStipple(GL_FALSE)
    , map1Color4(GL_FALSE)
    , map1Index(GL_FALSE)
    , map1Normal(GL_FALSE)
    , map1TextureCoord1(GL_FALSE)
    , map1TextureCoord2(GL_FALSE)
    , map1TextureCoord3(GL_FALSE)
    , map1TextureCoord4(GL_FALSE)
    , map1Vertex3(GL_FALSE)
    , map1Vertex4(GL_FALSE)
    , map2Color4(GL_FALSE)
    , map2Index(GL_FALSE)
    , map2Normal(GL_FALSE)
    , map2TextureCoord1(GL_FALSE)
    , map2TextureCoord2(GL_FALSE)
    , map2TextureCoord3(GL_FALSE)
    , map2TextureCoord4(GL_FALSE)
    , map2Vertex3(GL_FALSE)
    , map2Vertex4(GL_FALSE)
    , minmax(GL_FALSE)
    , multisample(GL_TRUE)
    , normalize(GL_FALSE)
    , pointSmooth(GL_FALSE)
    , pointSprite(GL_FALSE)
    , polygonOffsetFill(GL_FALSE)
    , polygonOffsetLine(GL_FALSE)
    , polygonOffsetPoint(GL_FALSE)
    , polygonSmooth(GL_FALSE)
    , polygonStipple(GL_FALSE)
    , postColorMatrixColorTable(GL_FALSE)
    , postConvolutionColorTable(GL_FALSE)
    , programPointSize(GL_FALSE)
    , rescaleNormal(GL_FALSE)
    , sampleAlphaToCoverage(GL_FALSE)
    , sampleAlphaToOne(GL_FALSE)
    , sampleCoverage(GL_FALSE)
    , sampleShading(GL_FALSE)
    , separable2d(GL_FALSE)
    , stencilTest(GL_FALSE)
    , vertexProgramTwoSide(GL_FALSE)
  {
    size_t n = array_size( blend );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( blend, ii );
      blend[ii] = GL_FALSE;
    }
    n = array_size( clipDistance );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( clipDistance, ii );
      clipDistance[ii] = GL_FALSE;
    }
    n = array_size( light );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( light, ii );
      light[ii] = GL_FALSE;
    }
    n = array_size( scissorTest );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( scissorTest, ii );
      scissorTest[ii] = GL_FALSE;
    }
    n = array_size( texture1d );
    RegalAssert( array_size( texture2d ) == n );
    RegalAssert( array_size( texture3d ) == n );
    RegalAssert( array_size( textureCubeMap ) == n );
    RegalAssert( array_size( textureRectangle ) == n );
    RegalAssert( array_size( textureGenQ ) == n );
    RegalAssert( array_size( textureGenR ) == n );
    RegalAssert( array_size( textureGenS ) == n );
    RegalAssert( array_size( textureGenT ) == n );
    for (size_t ii=0; ii<n; ii++)
    {
      texture1d[ii] = GL_FALSE;
      texture2d[ii] = GL_FALSE;
      texture3d[ii] = GL_FALSE;
      textureCubeMap[ii] = GL_FALSE;
      textureRectangle[ii] = GL_FALSE;
      textureGenQ[ii] = GL_FALSE;
      textureGenR[ii] = GL_FALSE;
      textureGenS[ii] = GL_FALSE;
      textureGenT[ii] = GL_FALSE;
    }
  }

  inline Enable(const Enable &other)
  {
    if (this!=&other)
      std::memcpy(this,&other,sizeof(Enable));
  }

  inline Enable &swap(Enable &other)
  {
    std::swap(alphaTest,other.alphaTest);
    std::swap(autoNormal,other.autoNormal);
    std::swap_ranges(blend,blend+REGAL_EMU_MAX_DRAW_BUFFERS,other.blend);
    std::swap(clampFragmentColor,other.clampFragmentColor);
    std::swap(clampReadColor,other.clampReadColor);
    std::swap(clampVertexColor,other.clampVertexColor);
    std::swap_ranges(clipDistance,clipDistance+REGAL_FIXED_FUNCTION_MAX_CLIP_DISTANCES,other.clipDistance);
    std::swap(colorLogicOp,other.colorLogicOp);
    std::swap(colorMaterial,other.colorMaterial);
    std::swap(colorSum,other.colorSum);
    std::swap(colorTable,other.colorTable);
    std::swap(convolution1d,other.convolution1d);
    std::swap(convolution2d,other.convolution2d);
    std::swap(cullFace,other.cullFace);
    std::swap(depthClamp,other.depthClamp);
    std::swap(depthTest,other.depthTest);
    std::swap(dither,other.dither);
    std::swap(fog,other.fog);
    std::swap(framebufferSRGB,other.framebufferSRGB);
    std::swap(histogram,other.histogram);
    std::swap(indexLogicOp,other.indexLogicOp);
    std::swap_ranges(light,light+REGAL_FIXED_FUNCTION_MAX_LIGHTS,other.light);
    std::swap(lighting,other.lighting);
    std::swap(lineSmooth,other.lineSmooth);
    std::swap(lineStipple,other.lineStipple);
    std::swap(map1Color4,other.map1Color4);
    std::swap(map1Index,other.map1Index);
    std::swap(map1Normal,other.map1Normal);
    std::swap(map1TextureCoord1,other.map1TextureCoord1);
    std::swap(map1TextureCoord2,other.map1TextureCoord2);
    std::swap(map1TextureCoord3,other.map1TextureCoord3);
    std::swap(map1TextureCoord4,other.map1TextureCoord4);
    std::swap(map1Vertex3,other.map1Vertex3);
    std::swap(map1Vertex4,other.map1Vertex4);
    std::swap(map2Color4,other.map2Color4);
    std::swap(map2Index,other.map2Index);
    std::swap(map2Normal,other.map2Normal);
    std::swap(map2TextureCoord1,other.map2TextureCoord1);
    std::swap(map2TextureCoord2,other.map2TextureCoord2);
    std::swap(map2TextureCoord3,other.map2TextureCoord3);
    std::swap(map2TextureCoord4,other.map2TextureCoord4);
    std::swap(map2Vertex3,other.map2Vertex3);
    std::swap(map2Vertex4,other.map2Vertex4);
    std::swap(minmax,other.minmax);
    std::swap(multisample,other.multisample);
    std::swap(normalize,other.normalize);
    std::swap(pointSmooth,other.pointSmooth);
    std::swap(pointSprite,other.pointSprite);
    std::swap(polygonOffsetFill,other.polygonOffsetFill);
    std::swap(polygonOffsetLine,other.polygonOffsetLine);
    std::swap(polygonOffsetPoint,other.polygonOffsetPoint);
    std::swap(polygonSmooth,other.polygonSmooth);
    std::swap(polygonStipple,other.polygonStipple);
    std::swap(postColorMatrixColorTable,other.postColorMatrixColorTable);
    std::swap(postConvolutionColorTable,other.postConvolutionColorTable);
    std::swap(programPointSize,other.programPointSize);
    std::swap(rescaleNormal,other.rescaleNormal);
    std::swap(sampleAlphaToCoverage,other.sampleAlphaToCoverage);
    std::swap(sampleAlphaToOne,other.sampleAlphaToOne);
    std::swap(sampleCoverage,other.sampleCoverage);
    std::swap(sampleShading,other.sampleShading);
    std::swap_ranges(scissorTest,scissorTest+REGAL_EMU_MAX_VIEWPORTS,other.scissorTest);
    std::swap(separable2d,other.separable2d);
    std::swap(stencilTest,other.stencilTest);
    std::swap_ranges(texture1d,texture1d+REGAL_EMU_MAX_TEXTURE_UNITS,other.texture1d);
    std::swap_ranges(texture2d,texture2d+REGAL_EMU_MAX_TEXTURE_UNITS,other.texture2d);
    std::swap_ranges(texture3d,texture3d+REGAL_EMU_MAX_TEXTURE_UNITS,other.texture3d);
    std::swap_ranges(textureCubeMap,textureCubeMap+REGAL_EMU_MAX_TEXTURE_UNITS,other.textureCubeMap);
    std::swap_ranges(textureRectangle,textureRectangle+REGAL_EMU_MAX_TEXTURE_UNITS,other.textureRectangle);
    std::swap_ranges(textureGenQ,textureGenQ+REGAL_EMU_MAX_TEXTURE_UNITS,other.textureGenQ);
    std::swap_ranges(textureGenR,textureGenR+REGAL_EMU_MAX_TEXTURE_UNITS,other.textureGenR);
    std::swap_ranges(textureGenS,textureGenS+REGAL_EMU_MAX_TEXTURE_UNITS,other.textureGenS);
    std::swap_ranges(textureGenT,textureGenT+REGAL_EMU_MAX_TEXTURE_UNITS,other.textureGenT);
    std::swap(vertexProgramTwoSide,other.vertexProgramTwoSide);
    return *this;
  }

  template <typename Procs>
  inline Enable &get(Procs & dt)
  {
    RegalContext & ctx = *dt.glIsEnabled.layer->GetContext();

    alphaTest = RglIsEnabled( dt,GL_ALPHA_TEST);
    autoNormal = RglIsEnabled( dt,GL_AUTO_NORMAL);
    size_t n = array_size( blend );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( blend, ii );
      blend[ii] = RglIsEnabledi( dt,GL_BLEND, static_cast<GLuint>(ii));
    }
    RglGetIntegerv( dt,GL_CLAMP_FRAGMENT_COLOR,reinterpret_cast<GLint *>(&clampFragmentColor));
    RglGetIntegerv( dt,GL_CLAMP_READ_COLOR,reinterpret_cast<GLint *>(&clampReadColor));
    RglGetIntegerv( dt,GL_CLAMP_VERTEX_COLOR,reinterpret_cast<GLint *>(&clampVertexColor));
    n = array_size( clipDistance );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( clipDistance, ii );
      clipDistance[ii] = RglIsEnabled( dt,static_cast<GLenum>(GL_CLIP_DISTANCE0+ii));
    }
    colorLogicOp  = RglIsEnabled( dt,GL_COLOR_LOGIC_OP);
    colorMaterial = RglIsEnabled( dt,GL_COLOR_MATERIAL);
    colorSum = RglIsEnabled( dt,GL_COLOR_SUM);
    colorTable = RglIsEnabled( dt,GL_COLOR_TABLE);
    convolution1d = RglIsEnabled( dt,GL_CONVOLUTION_1D);
    convolution2d = RglIsEnabled( dt,GL_CONVOLUTION_2D);
    cullFace = RglIsEnabled( dt,GL_CULL_FACE);
    depthClamp = RglIsEnabled( dt,GL_DEPTH_CLAMP);
    depthTest = RglIsEnabled( dt,GL_DEPTH_TEST);
    dither = RglIsEnabled( dt,GL_DITHER);
    fog = RglIsEnabled( dt,GL_FOG);
    framebufferSRGB = RglIsEnabled( dt,GL_FRAMEBUFFER_SRGB);
    histogram = RglIsEnabled( dt,GL_HISTOGRAM);
    indexLogicOp = RglIsEnabled( dt,GL_INDEX_LOGIC_OP);
    n = array_size( light );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( light, ii );
      light[ii] = RglIsEnabled( dt,static_cast<GLenum>(GL_LIGHT0+ii));
    }
    lighting = RglIsEnabled( dt,GL_LIGHTING);
    lineSmooth = RglIsEnabled( dt,GL_LINE_SMOOTH);
    lineStipple = RglIsEnabled( dt,GL_LINE_STIPPLE);
    map1Color4 = RglIsEnabled( dt,GL_MAP1_COLOR_4);
    map1Index = RglIsEnabled( dt,GL_MAP1_INDEX);
    map1Normal = RglIsEnabled( dt,GL_MAP1_NORMAL);
    map1TextureCoord1 = RglIsEnabled( dt,GL_MAP1_TEXTURE_COORD_1);
    map1TextureCoord2 = RglIsEnabled( dt,GL_MAP1_TEXTURE_COORD_2);
    map1TextureCoord3 = RglIsEnabled( dt,GL_MAP1_TEXTURE_COORD_3);
    map1TextureCoord4 = RglIsEnabled( dt,GL_MAP1_TEXTURE_COORD_4);
    map1Vertex3 = RglIsEnabled( dt,GL_MAP1_VERTEX_3);
    map1Vertex4 = RglIsEnabled( dt,GL_MAP1_VERTEX_4);
    map2Color4 = RglIsEnabled( dt,GL_MAP2_COLOR_4);
    map2Index = RglIsEnabled( dt,GL_MAP2_INDEX);
    map2Normal = RglIsEnabled( dt,GL_MAP2_NORMAL);
    map2TextureCoord1 = RglIsEnabled( dt,GL_MAP2_TEXTURE_COORD_1);
    map2TextureCoord2 = RglIsEnabled( dt,GL_MAP2_TEXTURE_COORD_2);
    map2TextureCoord3 = RglIsEnabled( dt,GL_MAP2_TEXTURE_COORD_3);
    map2TextureCoord4 = RglIsEnabled( dt,GL_MAP2_TEXTURE_COORD_4);
    map2Vertex3 = RglIsEnabled( dt,GL_MAP2_VERTEX_3);
    map2Vertex4 = RglIsEnabled( dt,GL_MAP2_VERTEX_4);
    minmax = RglIsEnabled( dt,GL_MINMAX);
    multisample = RglIsEnabled( dt,GL_MULTISAMPLE);
    normalize = RglIsEnabled( dt,GL_NORMALIZE);
    pointSmooth = RglIsEnabled( dt,GL_POINT_SMOOTH);
    pointSprite = RglIsEnabled( dt,GL_POINT_SPRITE);
    polygonOffsetFill = RglIsEnabled( dt,GL_POLYGON_OFFSET_FILL);
    polygonOffsetLine = RglIsEnabled( dt,GL_POLYGON_OFFSET_LINE);
    polygonOffsetPoint = RglIsEnabled( dt,GL_POLYGON_OFFSET_POINT);
    polygonSmooth = RglIsEnabled( dt,GL_POLYGON_SMOOTH);
    polygonStipple = RglIsEnabled( dt,GL_POLYGON_STIPPLE);
    postColorMatrixColorTable = RglIsEnabled( dt,GL_POST_COLOR_MATRIX_COLOR_TABLE);
    postConvolutionColorTable = RglIsEnabled( dt,GL_POST_CONVOLUTION_COLOR_TABLE);
    programPointSize = RglIsEnabled( dt,GL_PROGRAM_POINT_SIZE);
    rescaleNormal = RglIsEnabled( dt,GL_RESCALE_NORMAL);
    sampleAlphaToCoverage = RglIsEnabled( dt,GL_SAMPLE_ALPHA_TO_COVERAGE);
    sampleAlphaToOne = RglIsEnabled( dt,GL_SAMPLE_ALPHA_TO_ONE);
    sampleCoverage = RglIsEnabled( dt,GL_SAMPLE_COVERAGE);
    
    if (ctx.info->gl_version_4_0 || ctx.info->gl_arb_sample_shading)
      sampleShading = RglIsEnabled( dt,GL_SAMPLE_SHADING);
    separable2d = RglIsEnabled( dt,GL_SEPARABLE_2D);
    stencilTest = RglIsEnabled( dt,GL_STENCIL_TEST);
    n = array_size( scissorTest );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( scissorTest, ii );
      scissorTest[ii] = RglIsEnabledi( dt,GL_SCISSOR_TEST,static_cast<GLuint>(ii));
    }
    n = array_size( texture1d );
    RegalAssert( array_size( texture2d ) == n );
    RegalAssert( array_size( texture3d ) == n );
    RegalAssert( array_size( textureCubeMap ) == n );
    RegalAssert( array_size( textureRectangle ) == n );
    RegalAssert( array_size( textureGenS ) == n );
    RegalAssert( array_size( textureGenT ) == n );
    RegalAssert( array_size( textureGenR ) == n );
    RegalAssert( array_size( textureGenQ ) == n );
    for (GLuint ii=0; ii<static_cast<GLuint>(n); ii++)
    {
      texture1d[ii]      = RglIsEnabledi( dt,GL_TEXTURE_1D,ii);
      texture2d[ii]      = RglIsEnabledi( dt,GL_TEXTURE_2D,ii);
      texture3d[ii]      = RglIsEnabledi( dt,GL_TEXTURE_3D,ii);
      textureCubeMap[ii] = RglIsEnabledi( dt,GL_TEXTURE_CUBE_MAP,ii);
      textureRectangle[ii] = RglIsEnabledi( dt,GL_TEXTURE_RECTANGLE,ii);
      textureGenS[ii]    = RglIsEnabledi( dt,GL_TEXTURE_GEN_S,ii);
      textureGenT[ii]    = RglIsEnabledi( dt,GL_TEXTURE_GEN_T,ii);
      textureGenR[ii]    = RglIsEnabledi( dt,GL_TEXTURE_GEN_R,ii);
      textureGenQ[ii]    = RglIsEnabledi( dt,GL_TEXTURE_GEN_Q,ii);
    }
    vertexProgramTwoSide = RglIsEnabled( dt,GL_VERTEX_PROGRAM_TWO_SIDE);
    return *this;
  }

  template <typename Procs>
  inline const Enable &set(Procs & dt) const
  {
    RegalContext & ctx = *dt.glIsEnabled.layer->GetContext();
    
    setEnable(dt,GL_ALPHA_TEST,alphaTest);
    setEnable(dt,GL_AUTO_NORMAL,autoNormal);
    size_t n = array_size( blend );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( blend, ii );
      setEnablei(dt,GL_BLEND,static_cast<GLuint>(ii),blend[ii]);
    }
    setEnable(dt,GL_COLOR_LOGIC_OP,colorLogicOp);
    RglClampColor( dt,GL_CLAMP_FRAGMENT_COLOR,clampFragmentColor);
    RglClampColor( dt,GL_CLAMP_READ_COLOR,clampReadColor);
    RglClampColor( dt,GL_CLAMP_VERTEX_COLOR,clampVertexColor);
    n = array_size( clipDistance );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( clipDistance, ii );
      setEnable(dt,static_cast<GLenum>(GL_CLIP_DISTANCE0+ii),clipDistance[ii]);
    }
    setEnable(dt,GL_COLOR_MATERIAL,colorMaterial);
    setEnable(dt,GL_COLOR_SUM,colorSum);
    setEnable(dt,GL_COLOR_TABLE,colorTable);
    setEnable(dt,GL_CONVOLUTION_1D,convolution1d);
    setEnable(dt,GL_CONVOLUTION_2D,convolution2d);
    setEnable(dt,GL_CULL_FACE,cullFace);
    setEnable(dt,GL_DEPTH_CLAMP,depthClamp);
    setEnable(dt,GL_DEPTH_TEST,depthTest);
    setEnable(dt,GL_DITHER,dither);
    setEnable(dt,GL_FOG,fog);
    setEnable(dt,GL_FRAMEBUFFER_SRGB,framebufferSRGB);
    setEnable(dt,GL_HISTOGRAM,histogram);
    setEnable(dt,GL_INDEX_LOGIC_OP,indexLogicOp);
    n = array_size( light );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( light, ii );
      setEnable(dt,static_cast<GLenum>(GL_LIGHT0+ii),light[ii]);
    }
    setEnable(dt,GL_LIGHTING,lighting);
    setEnable(dt,GL_LINE_SMOOTH,lineSmooth);
    setEnable(dt,GL_LINE_STIPPLE,lineStipple);
    setEnable(dt,GL_MAP1_COLOR_4,map1Color4);
    setEnable(dt,GL_MAP1_INDEX,map1Index);
    setEnable(dt,GL_MAP1_NORMAL,map1Normal);
    setEnable(dt,GL_MAP1_TEXTURE_COORD_1,map1TextureCoord1);
    setEnable(dt,GL_MAP1_TEXTURE_COORD_2,map1TextureCoord2);
    setEnable(dt,GL_MAP1_TEXTURE_COORD_3,map1TextureCoord3);
    setEnable(dt,GL_MAP1_TEXTURE_COORD_4,map1TextureCoord4);
    setEnable(dt,GL_MAP1_VERTEX_3,map1Vertex3);
    setEnable(dt,GL_MAP1_VERTEX_4,map1Vertex4);
    setEnable(dt,GL_MAP2_COLOR_4,map2Color4);
    setEnable(dt,GL_MAP2_INDEX,map2Index);
    setEnable(dt,GL_MAP2_NORMAL,map2Normal);
    setEnable(dt,GL_MAP2_TEXTURE_COORD_1,map2TextureCoord1);
    setEnable(dt,GL_MAP2_TEXTURE_COORD_2,map2TextureCoord2);
    setEnable(dt,GL_MAP2_TEXTURE_COORD_3,map2TextureCoord3);
    setEnable(dt,GL_MAP2_TEXTURE_COORD_4,map2TextureCoord4);
    setEnable(dt,GL_MAP2_VERTEX_3,map2Vertex3);
    setEnable(dt,GL_MAP2_VERTEX_4,map2Vertex4);
    setEnable(dt,GL_MINMAX,minmax);
    setEnable(dt,GL_MULTISAMPLE,multisample);
    setEnable(dt,GL_NORMALIZE,normalize);
    setEnable(dt,GL_POINT_SMOOTH,pointSmooth);
    setEnable(dt,GL_POINT_SPRITE,pointSprite);
    setEnable(dt,GL_POLYGON_OFFSET_FILL,polygonOffsetFill);
    setEnable(dt,GL_POLYGON_OFFSET_LINE,polygonOffsetLine);
    setEnable(dt,GL_POLYGON_OFFSET_POINT,polygonOffsetPoint);
    setEnable(dt,GL_POLYGON_SMOOTH,polygonSmooth);
    setEnable(dt,GL_POLYGON_STIPPLE,polygonStipple);
    setEnable(dt,GL_POST_COLOR_MATRIX_COLOR_TABLE,postColorMatrixColorTable);
    setEnable(dt,GL_POST_CONVOLUTION_COLOR_TABLE,postConvolutionColorTable);
    setEnable(dt,GL_PROGRAM_POINT_SIZE,programPointSize);
    setEnable(dt,GL_RESCALE_NORMAL,rescaleNormal);
    setEnable(dt,GL_SAMPLE_ALPHA_TO_COVERAGE,sampleAlphaToCoverage);
    setEnable(dt,GL_SAMPLE_ALPHA_TO_ONE,sampleAlphaToOne);
    setEnable(dt,GL_SAMPLE_COVERAGE,sampleCoverage);

    if (ctx.info->gl_version_4_0 || ctx.info->gl_arb_sample_shading)
      setEnable(dt,GL_SAMPLE_SHADING,sampleShading);
    setEnable(dt,GL_SEPARABLE_2D,separable2d);
    setEnable(dt,GL_STENCIL_TEST,stencilTest);
    n = array_size( scissorTest );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( scissorTest, ii );
      setEnablei(dt,GL_SCISSOR_TEST,static_cast<GLuint>(ii),scissorTest[ii]);
    }
    n = array_size( texture1d );
    RegalAssert( array_size( texture2d ) == n );
    RegalAssert( array_size( texture3d ) == n );
    RegalAssert( array_size( textureCubeMap ) == n );
    RegalAssert( array_size( textureRectangle ) == n );
    RegalAssert( array_size( textureGenS ) == n );
    RegalAssert( array_size( textureGenT ) == n );
    RegalAssert( array_size( textureGenR ) == n );
    RegalAssert( array_size( textureGenQ ) == n );
    for (GLuint ii=0; ii<static_cast<GLuint>(n); ii++)
    {
      setEnablei(dt,GL_TEXTURE_1D,ii,texture1d[ii]);
      setEnablei(dt,GL_TEXTURE_2D,ii,texture2d[ii]);
      setEnablei(dt,GL_TEXTURE_3D,ii,texture3d[ii]);
      setEnablei(dt,GL_TEXTURE_CUBE_MAP,ii,textureCubeMap[ii]);
      setEnablei(dt,GL_TEXTURE_RECTANGLE,ii,textureRectangle[ii]);
      setEnablei(dt,GL_TEXTURE_GEN_S,ii,textureGenS[ii]);
      setEnablei(dt,GL_TEXTURE_GEN_T,ii,textureGenT[ii]);
      setEnablei(dt,GL_TEXTURE_GEN_R,ii,textureGenR[ii]);
      setEnablei(dt,GL_TEXTURE_GEN_Q,ii,textureGenQ[ii]);
    }
    setEnable(dt,GL_VERTEX_PROGRAM_TWO_SIDE,vertexProgramTwoSide);
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    enableToString(tmp, alphaTest, "GL_ALPHA_TEST",delim);
    enableToString(tmp, autoNormal, "GL_AUTO_NORMAL",delim);
    size_t n = array_size( blend );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( blend, ii );
      enableiToString(tmp, blend[ii], "GL_BLEND", static_cast<GLuint>(ii),delim);
    }
    tmp << print_string("glClampColor(GL_CLAMP_FRAGMENT_COLOR",Token::toString(clampFragmentColor),");",delim);
    tmp << print_string("glClampColor(GL_CLAMP_READ_COLOR",Token::toString(clampReadColor),");",delim);
    tmp << print_string("glClampColor(GL_CLAMP_VERTEX_COLOR",Token::toString(clampVertexColor),");",delim);
    n = array_size( clipDistance );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( clipDistance, ii );
      enableiToString(tmp, clipDistance[ii], "GL_CLIP_DISTANCE", static_cast<GLuint>(ii), delim);
    }
    enableToString(tmp, colorLogicOp, "GL_COLOR_LOGIC_OP",delim);
    enableToString(tmp, colorMaterial, "GL_COLOR_MATERIAL",delim);
    enableToString(tmp, colorSum, "GL_COLOR_SUM",delim);
    enableToString(tmp, colorTable, "GL_COLOR_TABLE",delim);
    enableToString(tmp, convolution1d, "GL_CONVOLUTION_1D",delim);
    enableToString(tmp, convolution2d, "GL_CONVOLUTION_2D",delim);
    enableToString(tmp, cullFace, "GL_CULL_FACE",delim);
    enableToString(tmp, depthTest, "GL_DEPTH_TEST",delim);
    enableToString(tmp, depthClamp, "GL_DEPTH_CLAMP",delim);
    enableToString(tmp, dither, "GL_DITHER",delim);
    enableToString(tmp, fog, "GL_FOG",delim);
    enableToString(tmp, framebufferSRGB, "GL_FRAMEBUFFER_SRGB",delim);
    enableToString(tmp, histogram, "GL_HISTOGRAM",delim);
    n = array_size( light );
    for (size_t ii=0; ii<n; ii++)
    {
      GLenum lightx = static_cast<GLenum>(GL_LIGHT0 + ii);
      RegalAssertArrayIndex( light, ii );
      tmp << print_string(light[ii] ? "glEnable(" : "glDisable(",Token::toString(lightx),");",delim);
    }
    enableToString(tmp, lighting, "GL_LIGHTING",delim);
    enableToString(tmp, lineSmooth, "GL_LINE_SMOOTH",delim);
    enableToString(tmp, lineStipple, "GL_LINE_STIPPLE",delim);
    enableToString(tmp, indexLogicOp, "GL_INDEX_LOGIC_OP",delim);
    enableToString(tmp, map1Color4, "GL_MAP1_COLOR_4",delim);
    enableToString(tmp, map1Index, "GL_MAP1_INDEX",delim);
    enableToString(tmp, map1Normal, "GL_MAP1_NORMAL",delim);
    enableToString(tmp, map1TextureCoord1, "GL_MAP1_TEXTURE_COORD_1",delim);
    enableToString(tmp, map1TextureCoord2, "GL_MAP1_TEXTURE_COORD_2",delim);
    enableToString(tmp, map1TextureCoord3, "GL_MAP1_TEXTURE_COORD_3",delim);
    enableToString(tmp, map1TextureCoord4, "GL_MAP1_TEXTURE_COORD_4",delim);
    enableToString(tmp, map1Vertex3, "GL_MAP1_VERTEX_3",delim);
    enableToString(tmp, map1Vertex4, "GL_MAP1_VERTEX_4",delim);
    enableToString(tmp, map2Color4, "GL_MAP2_COLOR_4",delim);
    enableToString(tmp, map2Index, "GL_MAP2_INDEX",delim);
    enableToString(tmp, map2Normal, "GL_MAP2_NORMAL",delim);
    enableToString(tmp, map2TextureCoord1, "GL_MAP2_TEXTURE_COORD_1",delim);
    enableToString(tmp, map2TextureCoord2, "GL_MAP2_TEXTURE_COORD_2",delim);
    enableToString(tmp, map2TextureCoord3, "GL_MAP2_TEXTURE_COORD_3",delim);
    enableToString(tmp, map2TextureCoord4, "GL_MAP2_TEXTURE_COORD_4",delim);
    enableToString(tmp, map2Vertex3, "GL_MAP2_VERTEX_3",delim);
    enableToString(tmp, map2Vertex4, "GL_MAP2_VERTEX_4",delim);
    enableToString(tmp, minmax, "GL_MINMAX",delim);
    enableToString(tmp, multisample, "GL_MULTISAMPLE",delim);
    enableToString(tmp, normalize, "GL_NORMALIZE",delim);
    enableToString(tmp, pointSmooth, "GL_POINT_SMOOTH",delim);
    enableToString(tmp, pointSprite, "GL_POINT_SPRITE",delim);
    enableToString(tmp, polygonOffsetLine, "GL_POLYGON_OFFSET_LINE",delim);
    enableToString(tmp, polygonOffsetFill, "GL_POLYGON_OFFSET_FILL",delim);
    enableToString(tmp, polygonOffsetPoint, "GL_POLYGON_OFFSET_POINT",delim);
    enableToString(tmp, polygonSmooth, "GL_POLYGON_SMOOTH",delim);
    enableToString(tmp, polygonStipple, "GL_POLYGON_STIPPLE",delim);
    enableToString(tmp, postConvolutionColorTable, "GL_POST_CONVOLUTION_COLOR_TABLE",delim);
    enableToString(tmp, postColorMatrixColorTable, "GL_POST_COLOR_MATRIX_COLOR_TABLE",delim);
    enableToString(tmp, programPointSize, "GL_PROGRAM_POINT_SIZE",delim);
    enableToString(tmp, rescaleNormal, "GL_RESCALE_NORMAL",delim);
    enableToString(tmp, sampleAlphaToCoverage, "GL_SAMPLE_ALPHA_TO_COVERAGE",delim);
    enableToString(tmp, sampleAlphaToOne, "GL_SAMPLE_ALPHA_TO_ONE",delim);
    enableToString(tmp, sampleCoverage, "GL_SAMPLE_COVERAGE",delim);
    enableToString(tmp, sampleShading, "GL_SAMPLE_SHADING",delim);
    enableToString(tmp, separable2d, "GL_SEPARABLE_2D",delim);
    enableToString(tmp, stencilTest, "GL_STENCIL_TEST",delim);
    n = array_size( scissorTest );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( scissorTest, ii );
      enableiToString(tmp, scissorTest[ii], "GL_SCISSOR_TEST", static_cast<GLuint>(ii),delim);
    }
    n = array_size( texture1d );
    RegalAssert( array_size( texture2d ) == n );
    RegalAssert( array_size( texture3d ) == n );
    RegalAssert( array_size( textureCubeMap ) == n );
    RegalAssert( array_size( textureRectangle ) == n );
    RegalAssert( array_size( textureGenS ) == n );
    RegalAssert( array_size( textureGenT ) == n );
    RegalAssert( array_size( textureGenR ) == n );
    RegalAssert( array_size( textureGenQ ) == n );
    for (GLuint ii=0; ii<static_cast<GLuint>(n); ii++)
    {
      enableiToString(tmp, texture1d[ii], "GL_TEXTURE_1D", ii, delim);
      enableiToString(tmp, texture2d[ii], "GL_TEXTURE_2D", ii, delim);
      enableiToString(tmp, texture3d[ii], "GL_TEXTURE_3D", ii, delim);
      enableiToString(tmp, textureCubeMap[ii], "GL_TEXTURE_CUBE_MAP", ii, delim);
      enableiToString(tmp, textureRectangle[ii], "GL_TEXTURE_RECTANGLE", ii, delim);
      enableiToString(tmp, textureGenS[ii], "GL_TEXTURE_GEN_S", ii, delim);
      enableiToString(tmp, textureGenT[ii], "GL_TEXTURE_GEN_T", ii, delim);
      enableiToString(tmp, textureGenR[ii], "GL_TEXTURE_GEN_R", ii, delim);
      enableiToString(tmp, textureGenQ[ii], "GL_TEXTURE_GEN_Q", ii, delim);
    }
    enableToString(tmp, vertexProgramTwoSide, "GL_VERTEX_PROGRAM_TWO_SIDE",delim);
    return tmp.str();
  }
};

//
// glPushAttrib(GL_DEPTH_BUFFER_BIT)
//

struct Depth
{
  GLboolean   enable;
  GLenum      func;
  GLclampd    clear;
  GLboolean   mask;

  inline Depth()
    : enable(GL_FALSE), func(GL_LESS), clear(1.0), mask(GL_TRUE)
  {
  }

  inline Depth &swap(Depth &other)
  {
    std::swap(enable,other.enable);
    std::swap(func,other.func);
    std::swap(clear,other.clear);
    std::swap(mask,other.mask);
    return *this;
  }

  template <typename Procs>
  inline Depth &get(Procs &dt)
  {
    enable = RglIsEnabled( dt,  GL_DEPTH_TEST );
    RglGetIntegerv( dt,  GL_DEPTH_FUNC, reinterpret_cast<GLint *>(&func) );
    RglGetFloatv( dt,  GL_DEPTH_CLEAR_VALUE, reinterpret_cast<GLfloat *>(&clear) );
    RglGetBooleanv( dt,  GL_DEPTH_WRITEMASK, &mask );
    return *this;
  }

  template <typename Procs>
  inline const Depth &set(Procs &dt) const
  {
    setEnable( dt, GL_DEPTH_TEST, enable);
    RglDepthFunc( dt, func );
    RglClearDepth( dt, clear );
    RglDepthMask( dt, mask );
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    enableToString(tmp, enable, "GL_DEPTH_TEST", delim);
    tmp << print_string("glDepthfunc(",Token::toString(func),");",delim);
    tmp << print_string("glClearDepth(",clear,");",delim);
    tmp << print_string("glDepthMask(",mask ? "GL_TRUE" : "GL_FALSE",");",delim);
    return tmp.str();
  }

  template <typename T> inline void glClearDepth(T depth)
  {
    clear = static_cast<GLclampd>(depth);
  }

  inline void glDepthFunc(GLenum f)
  {
    func = f;
  }

  inline void glDepthMask(GLboolean m)
  {
    mask = m;
  }
};

struct StencilFace
{
  GLenum func;      // glStencilFunc
  GLint  ref;       // glStencilFunc
  GLuint valueMask; // glStencilFunc
  GLuint writeMask; // glStencilMask
  GLenum fail;      // glStencilOp
  GLenum zfail;     // glStencilOp
  GLenum zpass;     // glStencilOp

  inline StencilFace()
    : func     (GL_ALWAYS),
      ref      (0),
      valueMask(~0u),
      writeMask(~0u),
      fail     (GL_KEEP),
      zfail    (GL_KEEP),
      zpass    (GL_KEEP)
  {
  }

  inline StencilFace &swap(StencilFace &other)
  {
    std::swap(func,     other.func);
    std::swap(ref,      other.ref);
    std::swap(valueMask,other.valueMask);
    std::swap(writeMask,other.writeMask);
    std::swap(fail,     other.fail);
    std::swap(zfail,    other.zfail);
    std::swap(zpass,    other.zpass);
    return *this;
  }

  template <typename Procs>
  inline StencilFace &get(Procs &dt, GLenum face)
  {
    RglGetIntegerv( dt, face==GL_FRONT ? GL_STENCIL_FUNC            : GL_STENCIL_BACK_FUNC,            reinterpret_cast<GLint *>(&func)     );
    RglGetIntegerv( dt, face==GL_FRONT ? GL_STENCIL_REF             : GL_STENCIL_BACK_REF,             &ref                                 );
    RglGetIntegerv( dt, face==GL_FRONT ? GL_STENCIL_VALUE_MASK      : GL_STENCIL_BACK_VALUE_MASK,      reinterpret_cast<GLint *>(&valueMask));
    RglGetIntegerv( dt, face==GL_FRONT ? GL_STENCIL_WRITEMASK       : GL_STENCIL_BACK_WRITEMASK,       reinterpret_cast<GLint *>(&writeMask));
    RglGetIntegerv( dt, face==GL_FRONT ? GL_STENCIL_FAIL            : GL_STENCIL_BACK_FAIL,            reinterpret_cast<GLint *>(&fail)     );
    RglGetIntegerv( dt, face==GL_FRONT ? GL_STENCIL_PASS_DEPTH_FAIL : GL_STENCIL_BACK_PASS_DEPTH_FAIL, reinterpret_cast<GLint *>(&zfail)    );
    RglGetIntegerv( dt, face==GL_FRONT ? GL_STENCIL_PASS_DEPTH_PASS : GL_STENCIL_BACK_PASS_DEPTH_PASS, reinterpret_cast<GLint *>(&zpass)    );
    return *this;
  }

  template <typename Procs>
  inline const StencilFace &set(Procs &dt, GLenum face) const
  {
    RglStencilFuncSeparate( dt, face,func,ref,valueMask);
    RglStencilMaskSeparate( dt, face,writeMask);
    RglStencilOpSeparate( dt, face,fail,zfail,zpass);
    return *this;
  }

  inline std::string toString(GLenum face,const char *delim = "\n") const
  {
    string_list tmp;
    tmp << print_string("glStencilFuncSeparate(",Token::toString(face),",",Token::toString(func),",",ref,",0x",print_hex(valueMask),");",delim);
    tmp << print_string("glStencilMaskSeparate(",Token::toString(face),",0x",print_hex(writeMask),");",delim);
    tmp << print_string("glStencilOpSeparate(",Token::toString(face),",",Token::toString(fail),",",Token::toString(zfail),",",Token::toString(zpass),");",delim);
    return tmp.str();
  }
};

//
// glPushAttrib(GL_STENCIL_BUFFER_BIT)
//

struct Stencil
{
  GLboolean   enable;
  GLint       clear;
  StencilFace front;
  StencilFace back;

  inline Stencil()
    : enable(GL_FALSE), clear(0)
  {
  }

  inline Stencil &swap(Stencil &other)
  {
    std::swap(enable,other.enable);
    std::swap(clear,other.clear);
    front.swap(other.front);
    back.swap(other.back);
    return *this;
  }

  template <typename Procs>
  inline Stencil &get(Procs &dt)
  {
    enable = RglIsEnabled( dt, GL_STENCIL_TEST);
    RglGetIntegerv( dt, GL_STENCIL_CLEAR_VALUE,&clear);
    front.get(dt,GL_FRONT);
    back.get(dt,GL_BACK );   // What about GL < 2.0 ?
    return *this;
  }

  template <typename Procs>
  inline const Stencil &set(Procs &dt) const
  {
    setEnable( dt, GL_STENCIL_TEST, enable );
    RglClearStencil( dt, clear );
    front.set( dt, GL_FRONT );
    back.set( dt, GL_BACK );
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    enableToString(tmp, enable, "GL_STENCIL_TEST", delim);
    tmp << print_string("glClearStencil(",clear,");",delim);
    tmp << front.toString(GL_FRONT,delim);
    tmp << front.toString(GL_BACK,delim);
    return tmp.str();
  }

  inline void glClearStencil(GLint s)
  {
    clear = s;
  }

  inline void glStencilFunc(GLenum func, GLint ref, GLuint mask)
  {
    front.func      = back.func      = func;
    front.ref       = back.ref       = ref;
    front.valueMask = back.valueMask = mask;
  }

  inline void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
  {
    switch (face)
    {
      case GL_FRONT:
        front.func      = func;
        front.ref       = ref;
        front.valueMask = mask;
        break;
      case GL_BACK:
        back.func       = func;
        back.ref        = ref;
        back.valueMask  = mask;
        break;
      case GL_FRONT_AND_BACK:
        front.func      = back.func      = func;
        front.ref       = back.ref       = ref;
        front.valueMask = back.valueMask = mask;
        break;
      default:
        RegalAssert(face==GL_FRONT || face==GL_BACK || face==GL_FRONT_AND_BACK);
        break;
    }
  }

  inline void glStencilMask(GLuint mask)
  {
    front.writeMask = back.writeMask = mask;
  }

  inline void glStencilMaskSeparate(GLenum face, GLuint mask)
  {
    switch (face)
    {
      case GL_FRONT:
        front.writeMask = mask;
        break;
      case GL_BACK:
        back.writeMask  = mask;
        break;
      case GL_FRONT_AND_BACK:
        front.writeMask = back.writeMask = mask;
        break;
      default:
        RegalAssert(face==GL_FRONT || face==GL_BACK || face==GL_FRONT_AND_BACK);
        break;
    }
  }

  inline void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
  {
    front.fail  = back.fail  = fail;
    front.zfail = back.zfail = zfail;
    front.zpass = back.zpass = zpass;
  }

  inline void glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
  {
    switch (face)
    {
      case GL_FRONT:
        front.fail  = fail;
        front.zfail = zfail;
        front.zpass = zpass;
        break;
      case GL_BACK:
        back.fail   = fail;
        back.zfail  = zfail;
        back.zpass  = zpass;
        break;
      case GL_FRONT_AND_BACK:
        front.fail  = back.fail  = fail;
        front.zfail = back.zfail = zfail;
        front.zpass = back.zpass = zpass;
        break;
      default:
        RegalAssert(face==GL_FRONT || face==GL_BACK || face==GL_FRONT_AND_BACK);
        break;
    }
  }
};

//
// glPushAttrib(GL_POLYGON_BIT)
//

struct Polygon
{
  GLboolean   cullEnable;
  GLenum      cullFaceMode;
  GLenum      frontFace;
  GLenum      mode[2];
  GLboolean   smoothEnable;
  GLboolean   stippleEnable;
  GLboolean   offsetFill;
  GLboolean   offsetLine;
  GLboolean   offsetPoint;
  GLfloat     factor;
  GLfloat     units;

  inline Polygon()
    : cullEnable(GL_FALSE)
    , cullFaceMode(GL_BACK)
    , frontFace(GL_CCW)
    , smoothEnable(GL_FALSE)
    , stippleEnable(GL_FALSE)
    , offsetFill(GL_FALSE)
    , offsetLine(GL_FALSE)
    , offsetPoint(GL_FALSE)
    , factor(0)
    , units(0)
  {
    mode[0] = mode[1] = GL_FILL;
  }

  inline Polygon &swap(Polygon &other)
  {
    std::swap(cullEnable,other.cullEnable);
    std::swap(cullFaceMode,other.cullFaceMode);
    std::swap(frontFace,other.frontFace);
    std::swap_ranges(mode,mode+2,other.mode);
    std::swap(smoothEnable,other.smoothEnable);
    std::swap(stippleEnable,other.stippleEnable);
    std::swap(offsetFill,other.offsetFill);
    std::swap(offsetLine,other.offsetLine);
    std::swap(offsetPoint,other.offsetPoint);
    std::swap(factor,other.factor);
    std::swap(units,other.units);
    return *this;
  }

  template <typename Procs>
  inline Polygon &get(Procs &dt)
  {
    cullEnable = RglIsEnabled( dt, GL_CULL_FACE);
    RglGetIntegerv( dt, GL_CULL_FACE_MODE,reinterpret_cast<GLint *>(&cullFaceMode));
    RglGetIntegerv( dt, GL_FRONT_FACE,reinterpret_cast<GLint *>(&frontFace));
    RglGetIntegerv( dt, GL_POLYGON_MODE,reinterpret_cast<GLint *>(mode));
    RglGetIntegerv( dt, GL_FRONT_FACE,reinterpret_cast<GLint *>(&frontFace));
    smoothEnable  = RglIsEnabled( dt, GL_POLYGON_SMOOTH);
    stippleEnable = RglIsEnabled( dt, GL_POLYGON_STIPPLE);
    offsetFill    = RglIsEnabled( dt, GL_POLYGON_OFFSET_FILL);
    offsetLine    = RglIsEnabled( dt, GL_POLYGON_OFFSET_LINE);
    offsetPoint   = RglIsEnabled( dt, GL_POLYGON_OFFSET_POINT);
    RglGetFloatv( dt, GL_POLYGON_OFFSET_FACTOR,&factor);
    RglGetFloatv( dt, GL_POLYGON_OFFSET_UNITS,&units);
    return *this;
  }

  template <typename Procs>
  inline const Polygon &set(Procs &dt) const
  {
    setEnable(dt,GL_CULL_FACE,cullEnable);
    RglCullFace( dt, cullFaceMode);
    RglFrontFace( dt, frontFace);
    RglPolygonMode( dt, GL_FRONT,mode[0]);
    RglPolygonMode( dt, GL_BACK,mode[1]);
    setEnable(dt,GL_POLYGON_SMOOTH,smoothEnable);
    setEnable(dt,GL_POLYGON_STIPPLE,stippleEnable);
    setEnable(dt,GL_POLYGON_OFFSET_FILL,offsetFill);
    setEnable(dt,GL_POLYGON_OFFSET_LINE,offsetLine);
    setEnable(dt,GL_POLYGON_OFFSET_POINT,offsetPoint);
    RglPolygonOffset( dt, factor,units);
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    enableToString(tmp, cullEnable, "GL_CULL_FACE", delim);
    tmp << print_string("glCullFace(",Token::toString(cullFaceMode),");",delim);
    tmp << print_string("glFrontFace(",Token::toString(frontFace),");",delim);
    tmp << print_string("glPolygonMode(GL_FRONT,",Token::toString(mode[0]),");",delim);
    tmp << print_string("glPolygonMode(GL_BACK,",Token::toString(mode[1]),");",delim);
    enableToString(tmp, smoothEnable, "GL_POLYGON_SMOOTH", delim);
    enableToString(tmp, stippleEnable, "GL_POLYGON_STIPPLE", delim);
    enableToString(tmp, offsetFill, "GL_POLYGON_OFFSET_FILL", delim);
    enableToString(tmp, offsetLine, "GL_POLYGON_OFFSET_LINE", delim);
    enableToString(tmp, offsetPoint, "GL_POLYGON_OFFSET_POINT", delim);
    tmp << print_string("glPolygonOffset(",factor,",",units,");",delim);
    return tmp.str();
  }

  inline void glCullFace(GLenum mode)
  {
    cullFaceMode = mode;
  }

  inline void glFrontFace(GLenum mode)
  {
    frontFace = mode;
  }

  inline void glPolygonMode(GLenum f, GLenum m)
  {
    switch (f)
    {
      case GL_FRONT:
        mode[0] = m;
        break;
      case GL_BACK:
        mode[1] = m;
        break;
      case GL_FRONT_AND_BACK:
        mode[0] = mode[1] = m;
        break;
      default:
        break;
    }
  }

  inline void glPolygonOffset(GLfloat f, GLfloat u)
  {
    factor = f;
    units  = u;
  }
};

//
// glPushAttrib(GL_TRANSFORM_BIT)
//

struct ClipPlaneEquation
{
  GLdouble data[4];

  inline ClipPlaneEquation()
  {
    data[0] = data[1] = data[2] = data[3] = 0.0f;
  }

  bool operator!= (const ClipPlaneEquation &other) const
  {
    return (data[0] != other.data[0]) || (data[1] != other.data[1]) || (data[2] != other.data[2]) || (data[3] != other.data[3]);
  }
};

struct ClipPlane
{
  GLboolean enabled;
  ClipPlaneEquation equation;

  inline ClipPlane()
    : enabled(false)
  {
  }

  inline ClipPlane &swap(ClipPlane &other)
  {
    std::swap(enabled,other.enabled);
    std::swap(equation,other.equation);
    return *this;
  }
};

struct Transform
{
  // This state matches glspec43.compatability.20120806.pdf Table 23.10,
  // except possibly extended a bit to allow for extra clip planes.

  ClipPlane   clipPlane[REGAL_FIXED_FUNCTION_MAX_CLIP_PLANES];
  GLenum      matrixMode;
  GLboolean   normalize;
  GLboolean   rescaleNormal;
  GLboolean   depthClamp;

  inline Transform()
    : matrixMode(GL_MODELVIEW), normalize(GL_FALSE), rescaleNormal(GL_FALSE), depthClamp(GL_FALSE)
  {
    size_t n = array_size( clipPlane );
    for (size_t i = 0; i < n; i++)
    {
      RegalAssertArrayIndex( clipPlane, i );
      clipPlane[i] = ClipPlane();
    }
  }

  inline size_t maxPlanes() const
  {
    return sizeof(clipPlane)/sizeof(ClipPlane);
  }

  inline Transform &swap(Transform &other)
  {
    std::swap_ranges(clipPlane,clipPlane+REGAL_FIXED_FUNCTION_MAX_CLIP_PLANES,other.clipPlane);
    std::swap(matrixMode,other.matrixMode);
    std::swap(normalize,other.normalize);
    std::swap(rescaleNormal,other.rescaleNormal);
    std::swap(depthClamp,other.depthClamp);
    return *this;
  }

  template <typename Procs>
  inline const Transform &transition(Procs &dt, Transform &current) const
  {
    size_t n = array_size( clipPlane );
    for (size_t i = 0; i < n; i++)
    {
      RegalAssertArrayIndex( clipPlane, i );
      if (current.clipPlane[i].enabled != clipPlane[i].enabled)
        setEnable(dt, static_cast<GLenum>(GL_CLIP_PLANE0 + i), clipPlane[i].enabled);

      if (current.clipPlane[i].equation != clipPlane[i].equation)
        RglClipPlane( dt, static_cast<GLenum>(GL_CLIP_PLANE0 + i), clipPlane[i].equation.data);
    }

    if (current.matrixMode != matrixMode)
      RglMatrixMode( dt, matrixMode);

    if (current.normalize != normalize)
      setEnable(dt, GL_NORMALIZE, normalize);

    if (current.rescaleNormal != rescaleNormal)
      setEnable(dt, GL_RESCALE_NORMAL, rescaleNormal);

    if (current.depthClamp != depthClamp )
      setEnable(dt, GL_DEPTH_CLAMP, depthClamp );

    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    size_t n = array_size( clipPlane );
    for (size_t i = 0; i < n; i++)
    {
      RegalAssertArrayIndex( clipPlane, i );
      GLenum plane = static_cast<GLenum>(GL_CLIP_PLANE0 + i);
      enableToString(tmp, clipPlane[i].enabled, Token::toString(plane), delim);
      tmp << print_string("glClipPlane(",Token::toString(plane),", [ ", clipPlane[i].equation.data[0],
                          ", ", clipPlane[i].equation.data[1],
                          ", ", clipPlane[i].equation.data[2],
                          ", ", clipPlane[i].equation.data[3]," ]);",delim);
    }
    tmp << print_string("glMatrixMode(",Token::toString(matrixMode),");",delim);
    enableToString(tmp, normalize, "GL_NORMALIZE", delim);
    enableToString(tmp, rescaleNormal, "GL_RESCALE_NORMAL", delim);
    enableToString(tmp, depthClamp, "GL_DEPTH_CLAMP", delim);
    return tmp.str();
  }

  inline void glClipPlane(GLenum plane, const GLdouble *equation)
  {
    GLint planeIndex = plane - GL_CLIP_PLANE0;
    RegalAssert(planeIndex >= 0 && static_cast<size_t>(planeIndex) < array_size( clipPlane ));
    if (planeIndex >= 0 && static_cast<size_t>(planeIndex) < array_size( clipPlane ))
    {
      RegalAssertArrayIndex( clipPlane, planeIndex );
      clipPlane[planeIndex].equation.data[0] = equation[0];
      clipPlane[planeIndex].equation.data[1] = equation[1];
      clipPlane[planeIndex].equation.data[2] = equation[2];
      clipPlane[planeIndex].equation.data[3] = equation[3];
    }
  }

  inline void glMatrixMode(GLenum mode)
  {
    matrixMode = mode;
  }
};

//
// glPushAttrib(GL_HINT_BIT)
//

struct Hint
{
  GLenum perspectiveCorrection;
  GLenum pointSmooth;
  GLenum lineSmooth;
  GLenum polygonSmooth;
  GLenum fog;
  GLenum generateMipmap;
  GLenum textureCompression;
  GLenum fragmentShaderDerivative;

  inline Hint()
    : perspectiveCorrection(GL_DONT_CARE)
    , pointSmooth(GL_DONT_CARE)
    , lineSmooth(GL_DONT_CARE)
    , polygonSmooth(GL_DONT_CARE)
    , fog(GL_DONT_CARE)
    , generateMipmap(GL_DONT_CARE)
    , textureCompression(GL_DONT_CARE)
    , fragmentShaderDerivative(GL_DONT_CARE)
  {
  }

  inline Hint &swap(Hint &other)
  {
    std::swap(perspectiveCorrection, other.perspectiveCorrection);
    std::swap(pointSmooth, other.pointSmooth);
    std::swap(lineSmooth, other.lineSmooth);
    std::swap(polygonSmooth, other.polygonSmooth);
    std::swap(fog, other.fog);
    std::swap(generateMipmap, other.generateMipmap);
    std::swap(textureCompression, other.textureCompression);
    std::swap(fragmentShaderDerivative, other.fragmentShaderDerivative);
    return *this;
  }

  template <typename Procs>
  inline Hint &get(Procs &dt)
  {
    RglGetIntegerv( dt, GL_PERSPECTIVE_CORRECTION_HINT,reinterpret_cast<GLint *>(&perspectiveCorrection));
    RglGetIntegerv( dt, GL_POINT_SMOOTH_HINT,reinterpret_cast<GLint *>(&pointSmooth));
    RglGetIntegerv( dt, GL_LINE_SMOOTH_HINT,reinterpret_cast<GLint *>(&lineSmooth));
    RglGetIntegerv( dt, GL_POLYGON_SMOOTH_HINT,reinterpret_cast<GLint *>(&polygonSmooth));
    RglGetIntegerv( dt, GL_FOG_HINT,reinterpret_cast<GLint *>(&fog));
    RglGetIntegerv( dt, GL_GENERATE_MIPMAP_HINT,reinterpret_cast<GLint *>(&generateMipmap));
    RglGetIntegerv( dt, GL_TEXTURE_COMPRESSION_HINT,reinterpret_cast<GLint *>(&textureCompression));
    RglGetIntegerv( dt, GL_FRAGMENT_SHADER_DERIVATIVE_HINT,reinterpret_cast<GLint *>(&fragmentShaderDerivative));
    return *this;
  }

  template <typename Procs>
  inline const Hint &set(Procs &dt) const
  {
    RglHint( dt, GL_PERSPECTIVE_CORRECTION_HINT, perspectiveCorrection);
    RglHint( dt, GL_POINT_SMOOTH_HINT, pointSmooth);
    RglHint( dt, GL_LINE_SMOOTH_HINT, lineSmooth);
    RglHint( dt, GL_POLYGON_SMOOTH_HINT, polygonSmooth);
    RglHint( dt, GL_FOG_HINT, fog);
    RglHint( dt, GL_GENERATE_MIPMAP_HINT, generateMipmap);
    RglHint( dt, GL_TEXTURE_COMPRESSION_HINT, textureCompression);
    RglHint( dt, GL_FRAGMENT_SHADER_DERIVATIVE_HINT, fragmentShaderDerivative);
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    tmp << print_string("glHint(GL_PERSPECTIVE_CORRECTION_HINT,",Token::toString(perspectiveCorrection),");",delim);
    tmp << print_string("glHint(GL_POINT_SMOOTH_HINT,",Token::toString(pointSmooth),");",delim);
    tmp << print_string("glHint(GL_LINE_SMOOTH_HINT,",Token::toString(lineSmooth),");",delim);
    tmp << print_string("glHint(GL_POLYGON_SMOOTH_HINT,",Token::toString(polygonSmooth),");",delim);
    tmp << print_string("glHint(GL_FOG_HINT,",Token::toString(fog),");",delim);
    tmp << print_string("glHint(GL_GENERATE_MIPMAP_HINT,",Token::toString(generateMipmap),");",delim);
    tmp << print_string("glHint(GL_TEXTURE_COMPRESSION_HINT,",Token::toString(textureCompression),");",delim);
    tmp << print_string("glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,",Token::toString(fragmentShaderDerivative),");",delim);
    return tmp.str();
  }

  void glHint(GLenum target, GLenum mode)
  {
    switch (target)
    {
      case GL_PERSPECTIVE_CORRECTION_HINT:
        perspectiveCorrection = mode;
        break;
      case GL_POINT_SMOOTH_HINT:
        pointSmooth = mode;
        break;
      case GL_LINE_SMOOTH_HINT:
        lineSmooth = mode;
        break;
      case GL_POLYGON_SMOOTH_HINT:
        polygonSmooth = mode;
        break;
      case GL_FOG_HINT:
        fog = mode;
        break;
      case GL_GENERATE_MIPMAP_HINT:
        generateMipmap = mode;
        break;
      case GL_TEXTURE_COMPRESSION_HINT:
        textureCompression = mode;
        break;
      case GL_FRAGMENT_SHADER_DERIVATIVE_HINT:
        fragmentShaderDerivative = mode;
        break;
      default:
        break;
    }
  }
};

//
// glPushAttrib(GL_LIST_BIT)
//

struct List
{
  GLuint base;

  inline List()
    : base(0)
  {
  }

  inline List &swap(List &other)
  {
    std::swap(base,other.base);
    return *this;
  }

  template <typename Procs>
  inline List &get(Procs &dt)
  {
    RglGetIntegerv( dt, GL_LIST_BASE,reinterpret_cast<GLint *>(&base));
    return *this;
  }

  template <typename Procs>
  inline const List &set(Procs &dt) const
  {
    RglListBase( dt, base);
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    tmp << print_string("glListBase(",base,");",delim);
    return tmp.str();
  }

  inline void glListBase( GLuint b )
  {
    base = b;
  }
};

//
// glPushAttrib(GL_ACCUM_BUFFER_BIT)
//

struct AccumBuffer
{
  GLfloat clear[4];

  inline AccumBuffer()
  {
    clear[0] = clear[1] = clear[2] = clear[3] = 0.0f;
  }

  inline AccumBuffer &swap(AccumBuffer &other)
  {
    std::swap_ranges(clear,clear+4,other.clear);
    return *this;
  }

  template <typename Procs>
  inline AccumBuffer &get(Procs &dt)
  {
    RglGetFloatv( dt, GL_ACCUM_CLEAR_VALUE,&(clear[0]));
    return *this;
  }

  template <typename Procs>
  inline const AccumBuffer &set(Procs &dt) const
  {
    RglClearAccum( dt, clear[0],clear[1],clear[2],clear[3]);
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    tmp << print_string("glClearAccum(",clear[0],",",clear[1],",",clear[2],",",clear[3],");",delim);
    return tmp.str();
  }

  inline void glClearAccum(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
  {
    clear[0] = r;
    clear[1] = g;
    clear[2] = b;
    clear[3] = a;
  }
};

//
// glPushAttrib(GL_SCISSOR_BIT)
//

struct Scissor
{
  GLboolean   scissorTest[REGAL_EMU_MAX_VIEWPORTS];   // GL_SCISSOR_TEST
  GLint       scissorBox[REGAL_EMU_MAX_VIEWPORTS][4]; // GL_SCISSOR_BOX
  bool        valid[REGAL_EMU_MAX_VIEWPORTS];

  inline Scissor()
  {
    size_t n = array_size( scissorTest );
    RegalAssert(array_size( valid ) == n);
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( scissorTest, ii );
      RegalAssertArrayIndex( valid, ii );
      scissorTest[ii] = GL_FALSE;
      scissorBox[ii][0] = 0;
      scissorBox[ii][1] = 0;
      scissorBox[ii][2] = 0;
      scissorBox[ii][3] = 0;
      valid[ii] = false;
    }
  }

  inline Scissor(const Scissor &other)
  {
    if (this!=&other)
      std::memcpy(this,&other,sizeof(Scissor));
  }

  bool fullyDefined() const
  {
    size_t n = array_size( valid );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( valid, ii );
      if (!valid[ii])
        return false;
    }
    return true;
  }

  template <typename Procs>
  void getUndefined(Procs &dt)
  {
    size_t n = array_size( valid );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( valid, ii );
      if (!valid[ii])
      {
        RglGetIntegeri_v(dt, GL_SCISSOR_BOX, static_cast<GLuint>(ii), &scissorBox[ii][0]);
        valid[ii] = true;
      }
    }
  }

  inline Scissor &swap(Scissor &other)
  {
    std::swap_ranges(scissorTest,scissorTest+REGAL_EMU_MAX_VIEWPORTS,other.scissorTest);
    std::swap_ranges(&scissorBox[0][0],&scissorBox[0][0]+(REGAL_EMU_MAX_VIEWPORTS*4),&other.scissorBox[0][0]);
    std::swap_ranges(valid,valid+REGAL_EMU_MAX_VIEWPORTS,other.valid);
    return *this;
  }

  template <typename Procs>
  inline Scissor &get(Procs &dt)
  {
    size_t n = array_size( scissorTest );
    RegalAssert(array_size( valid ) == n);
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( scissorTest, ii );
      RegalAssertArrayIndex( valid, ii );
      scissorTest[ii] = RglIsEnabledi( dt, GL_SCISSOR_TEST,static_cast<GLuint>(ii));
      RglGetIntegeri_v( dt, GL_SCISSOR_BOX, static_cast<GLuint>(ii), &scissorBox[ii][0]);
      valid[ii] = true;
    }
    return *this;
  }

  template <typename Procs>
  inline const Scissor &set(Procs &dt) const
  {
    size_t n = array_size( scissorTest );
    RegalAssert(array_size( valid ) == n);
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( scissorTest, ii );
      RegalAssertArrayIndex( valid, ii );
      setEnablei(dt, GL_SCISSOR_TEST,static_cast<GLuint>(ii),scissorTest[ii]);
      if (valid[ii])
        RglScissorIndexedv( dt, static_cast<GLuint>(ii), &scissorBox[ii][0]);
    }
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    size_t n = array_size( scissorTest );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( scissorTest, ii );
      enableiToString(tmp, scissorTest[ii], "GL_SCISSOR_TEST", static_cast<GLuint>(ii), delim);
    }
    n = array_size( valid );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( valid, ii );
      if (valid[ii])
        tmp << print_string("glScissorIndexedv(",ii,", [ ",scissorBox[ii][0],",",scissorBox[ii][1],",",scissorBox[ii][2],",",scissorBox[ii][3]," ] );",delim);
      else
        tmp << print_string("glScissorIndexedv(",ii,", [ *not valid* ] );",delim);
    }
    return tmp.str();
  }

  void glScissor( GLint left, GLint bottom, GLsizei width, GLsizei height )
  {
    size_t n = array_size( valid );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( valid, ii );
      scissorBox[ii][0] = left;
      scissorBox[ii][1] = bottom;
      scissorBox[ii][2] = width;
      scissorBox[ii][3] = height;
      valid[ii] = true;
    }
  }

  void glScissorArrayv( GLuint first, GLsizei count, const GLint *v )
  {
    size_t last = static_cast<size_t>(first + count);
    size_t n = array_size( valid );
    if (last < n)
    {
      for (size_t ii=first; ii<last; ii++)
      {
        RegalAssertArrayIndex( valid, ii );
        scissorBox[ii][0] = v[0];
        scissorBox[ii][1] = v[1];
        scissorBox[ii][2] = v[2];
        scissorBox[ii][3] = v[3];
        valid[ii] = true;
        v += 4;
      }
    }
  }

  void glScissorIndexed( GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height )
  {
    if (static_cast<size_t>(index) < array_size( valid ))
    {
      RegalAssertArrayIndex( valid, index );
      scissorBox[index][0] = left;
      scissorBox[index][1] = bottom;
      scissorBox[index][2] = width;
      scissorBox[index][3] = height;
      valid[index] = true;
    }
  }

  void glScissorIndexedv( GLuint index, const GLint *v )
  {
    if (static_cast<size_t>(index) < array_size( valid ))
    {
      RegalAssertArrayIndex( valid, index );
      scissorBox[index][0] = v[0];
      scissorBox[index][1] = v[1];
      scissorBox[index][2] = v[2];
      scissorBox[index][3] = v[3];
      valid[index] = true;
    }
  }
};

//
// glPushAttrib(GL_VIEWPORT_BIT)
//

struct Viewport
{
  GLfloat  viewport[REGAL_EMU_MAX_VIEWPORTS][4]; // GL_VIEWPORT
  GLclampd depthRange[REGAL_EMU_MAX_VIEWPORTS][2]; // GL_DEPTH_RANGE
  bool     valid[REGAL_EMU_MAX_VIEWPORTS];

  inline Viewport()
  {
    size_t n = array_size( valid );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( valid, ii );
      viewport[ii][0] = 0.0f;
      viewport[ii][1] = 0.0f;
      viewport[ii][2] = 0.0f;
      viewport[ii][3] = 0.0f;
      depthRange[ii][0] = 0.0f;
      depthRange[ii][1] = 1.0f;
      valid[ii] = false;
    }
  }

  bool fullyDefined() const
  {
    size_t n = array_size( valid );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( valid, ii );
      if (!valid[ii])
        return false;
    }
    return true;
  }

  template <typename Procs>
  inline void getUndefined(Procs &dt)
  {
    size_t n = array_size( valid );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( valid, ii );
      RglGetFloati_v( dt, GL_VIEWPORT, static_cast<GLuint>(ii), &viewport[ii][0]);
      valid[ii] = true;
    }
  }

  inline Viewport &swap(Viewport &other)
  {
    std::swap_ranges(&viewport[0][0],&viewport[0][0]+(REGAL_EMU_MAX_VIEWPORTS*4),&other.viewport[0][0]);
    std::swap_ranges(&depthRange[0][0],&depthRange[0][0]+(REGAL_EMU_MAX_VIEWPORTS*2),&other.depthRange[0][0]);
    std::swap_ranges(valid,valid+REGAL_EMU_MAX_VIEWPORTS,other.valid);
    return *this;
  }

  template <typename Procs>
  inline Viewport &get(Procs &dt)
  {
    size_t n = array_size( valid );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( valid, ii );
      RglGetFloati_v( dt, GL_VIEWPORT, static_cast<GLuint>(ii), &viewport[ii][0]);
      RglGetDoublei_v( dt, GL_DEPTH_RANGE, static_cast<GLuint>(ii), &depthRange[ii][0]);
      valid[ii] = true;
    }
    return *this;
  }

  template <typename Procs>
  inline const Viewport &set(Procs &dt) const
  {
    RglDepthRangeArrayv( dt, 0, REGAL_EMU_MAX_VIEWPORTS, &depthRange[0][0] );
    size_t n = array_size( valid );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( valid, ii );
      if (valid[ii])
        RglViewportIndexedfv( dt, static_cast<GLuint>(ii), &viewport[ii][0] );
    }
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    size_t n = array_size( valid );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( valid, ii );
      if (valid[ii])
        tmp << print_string("glViewportIndexedfv(",ii,", [ ",viewport[ii][0],",",viewport[ii][1],",",viewport[ii][2],",",viewport[ii][3]," ] );",delim);
      else
        tmp << print_string("glViewportIndexedfv(",ii,", [ *not valid* ] );",delim);
    }
    for (size_t ii=0; ii<REGAL_EMU_MAX_VIEWPORTS; ii++)
      tmp << print_string("glDepthRangeIndexed(",ii,",",depthRange[ii][0],",",depthRange[ii][1],");",delim);
    return tmp.str();
  }

  template <typename T> void glDepthRange( T n, T f )
  {
    for (size_t ii=0; ii<REGAL_EMU_MAX_VIEWPORTS; ii++)
    {
      depthRange[ii][0] = static_cast<GLdouble>(n);
      depthRange[ii][1] = static_cast<GLdouble>(f);
    }
  }

  void glDepthRangeArrayv( GLuint first, GLsizei count, const GLdouble *v )
  {
    GLuint last = first + count;
    if (last > REGAL_EMU_MAX_VIEWPORTS)
      last = REGAL_EMU_MAX_VIEWPORTS;
    for (size_t ii = first; ii < last; ii++)
    {
      depthRange[ii][0] = v[0];
      depthRange[ii][1] = v[1];
      v += 2;
    }
  }

  void glDepthRangeIndexed( GLuint index, GLdouble n, GLdouble f )
  {
    if (index < REGAL_EMU_MAX_VIEWPORTS)
    {
      depthRange[index][0] = n;
      depthRange[index][1] = f;
    }
  }

  void glViewport( GLint x, GLint y, GLsizei w, GLsizei h )
  {
    Internal("Regal::State::Viewport::glViewport( ",x,", ",y,", ",w,", ",h," )");
    for (size_t ii=0; ii<REGAL_EMU_MAX_VIEWPORTS; ii++)
    {
      viewport[ii][0] = static_cast<GLfloat>(x);
      viewport[ii][1] = static_cast<GLfloat>(y);
      viewport[ii][2] = static_cast<GLfloat>(w);
      viewport[ii][3] = static_cast<GLfloat>(h);
      valid[ii] = true;
    }
  }

  void glViewportArrayv( GLuint first, GLsizei count, const GLfloat *v )
  {
    size_t n = array_size( valid );
    size_t last = static_cast<size_t>(first + count);
    if (last < n)
    {
      for (size_t ii=first; ii<last; ii++)
      {
        RegalAssertArrayIndex( valid, ii );
        viewport[ii][0] = v[0];
        viewport[ii][1] = v[1];
        viewport[ii][2] = v[2];
        viewport[ii][3] = v[3];
        valid[ii] = true;
        v += 4;
      }
    }
  }

  void glViewportIndexedf( GLuint index, GLfloat x, GLfloat y, GLfloat w, float h )
  {
    if (static_cast<size_t>(index) < array_size( valid ))
    {
      RegalAssertArrayIndex( valid, index );
      viewport[index][0] = x;
      viewport[index][1] = y;
      viewport[index][2] = w;
      viewport[index][3] = h;
      valid[index] = true;
    }
  }

  void glViewportIndexedfv( GLuint index, const GLfloat *v )
  {
    if (static_cast<size_t>(index) < array_size( valid ))
    {
      RegalAssertArrayIndex( valid, index );
      viewport[index][0] = v[0];
      viewport[index][1] = v[1];
      viewport[index][2] = v[2];
      viewport[index][3] = v[3];
      valid[index] = true;
    }
  }
};

//
// glPushAttrib(GL_LINE_BIT)
//

struct Line
{
  GLfloat     width;          // GL_LINE_WIDTH
  GLboolean   smooth;         // GL_LINE_SMOOTH
  GLboolean   stipple;        // GL_LINE_STIPPLE
  GLint       stippleRepeat;  // GL_LINE_STIPPLE_REPEAT
  GLushort    stipplePattern; // GL_LINE_STIPPLE_PATTERN

  inline Line()
    : width(1.0)
    , smooth(GL_FALSE)
    , stipple(GL_FALSE)
    , stippleRepeat(1)
    , stipplePattern(static_cast<GLushort>(~0))
  {
  }

  inline Line &swap(Line &other)
  {
    std::swap(width,other.width);
    std::swap(smooth,other.smooth);
    std::swap(stipple,other.stipple);
    std::swap(stippleRepeat,other.stippleRepeat);
    std::swap(stipplePattern,other.stipplePattern);
    return *this;
  }

  template <typename Procs>
  inline Line &get(Procs &dt)
  {
    RglGetFloatv( dt, GL_LINE_WIDTH,&width);
    smooth = RglIsEnabled( dt, GL_LINE_SMOOTH);
    stipple = RglIsEnabled( dt, GL_LINE_STIPPLE);
    RglGetIntegerv( dt, GL_LINE_STIPPLE_PATTERN,&stippleRepeat);
    stipplePattern = static_cast<GLushort>(stippleRepeat);
    RglGetIntegerv( dt, GL_LINE_STIPPLE_REPEAT,&stippleRepeat);
    return *this;
  }

  template <typename Procs>
  inline const Line &set(Procs &dt) const
  {
    RglLineWidth( dt, width);
    setEnable(dt, GL_LINE_SMOOTH, smooth);
    setEnable(dt, GL_LINE_STIPPLE, stipple);
    RglLineStipple( dt, stippleRepeat, stipplePattern);
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    tmp << print_string("glLineWidth(",width,");",delim);
    enableToString(tmp, smooth, "GL_LINE_SMOOTH", delim);
    enableToString(tmp, stipple, "GL_LINE_STIPPLE", delim);
    tmp << print_string("glLineStipple(",stippleRepeat,",0x",print_hex(stipplePattern),");",delim);
    return tmp.str();
  }

  inline void glLineStipple( GLint repeat, GLushort pattern )
  {
    stippleRepeat = repeat;
    stipplePattern = pattern;
  }

  inline void glLineWidth(GLfloat w)
  {
    width = w;
  }
};

//
// glPushAttrib(GL_MULTISAMPLE_BIT)
//

struct Multisample
{
  GLboolean   multisample;               // GL_MULTISAMPLE
  GLboolean   sampleAlphaToCoverage;     // GL_SAMPLE_ALPHA_TO_COVERAGE
  GLboolean   sampleAlphaToOne;          // GL_SAMPLE_ALPHA_TO_ONE
  GLboolean   sampleCoverage;            // GL_SAMPLE_COVERAGE
  GLclampf    sampleCoverageValue;       // GL_SAMPLE_COVERAGE_VALUE
  GLboolean   sampleCoverageInvert;      // GL_SAMPLE_COVERAGE_INVERT
  GLboolean   sampleShading;             // GL_SAMPLE_SHADING
  GLfloat     minSampleShadingValue;     // GL_MIN_SAMPLE_SHADING_VALUE

  inline Multisample()
    : multisample(GL_TRUE)
    , sampleAlphaToCoverage(GL_FALSE)
    , sampleAlphaToOne(GL_FALSE)
    , sampleCoverage(GL_FALSE)
    , sampleCoverageValue(1)
    , sampleCoverageInvert(GL_FALSE)
    , sampleShading(GL_FALSE)
    , minSampleShadingValue(0)
  {
  }

  inline Multisample &swap(Multisample &other)
  {
    std::swap(multisample,other.multisample);
    std::swap(sampleAlphaToCoverage,other.sampleAlphaToCoverage);
    std::swap(sampleAlphaToOne,other.sampleAlphaToOne);
    std::swap(sampleCoverage,other.sampleCoverage);
    std::swap(sampleCoverageValue,other.sampleCoverageValue);
    std::swap(sampleCoverageInvert,other.sampleCoverageInvert);
    std::swap(sampleShading,other.sampleShading);
    std::swap(minSampleShadingValue,other.minSampleShadingValue);
    return *this;
  }

  template <typename Procs>
  inline Multisample &get( Procs & dt)
  {
    RegalContext & ctx = *dt.glIsEnabled.layer->GetContext();
    
    multisample = RglIsEnabled( dt, GL_MULTISAMPLE);
    sampleAlphaToCoverage = RglIsEnabled( dt, GL_SAMPLE_ALPHA_TO_COVERAGE);
    sampleAlphaToOne = RglIsEnabled( dt, GL_SAMPLE_ALPHA_TO_ONE);
    sampleCoverage = RglIsEnabled( dt, GL_SAMPLE_COVERAGE);
    RglGetFloatv( dt, GL_SAMPLE_COVERAGE_VALUE,&sampleCoverageValue);
    RglGetBooleanv( dt, GL_SAMPLE_COVERAGE_INVERT,&sampleCoverageInvert);
    if (ctx.info->gl_version_4_0 || ctx.info->gl_arb_sample_shading)
      sampleShading = RglIsEnabled( dt, GL_SAMPLE_SHADING);
    RglGetFloatv( dt, GL_MIN_SAMPLE_SHADING_VALUE,&minSampleShadingValue);
    return *this;
  }

  template <typename Procs>
  inline const Multisample &set(Procs & dt) const
  {
    RegalContext & ctx = *dt.glIsEnabled.layer->GetContext();
    
    setEnable(dt,GL_MULTISAMPLE,multisample);
    setEnable(dt,GL_SAMPLE_ALPHA_TO_COVERAGE,sampleAlphaToCoverage);
    setEnable(dt,GL_SAMPLE_ALPHA_TO_ONE,sampleAlphaToOne);
    setEnable(dt,GL_SAMPLE_COVERAGE,sampleCoverage);
    RglSampleCoverage( dt,sampleCoverageValue, sampleCoverageInvert);
    if (ctx.info->gl_version_4_0 || ctx.info->gl_arb_sample_shading)
      setEnable(dt,GL_SAMPLE_SHADING,sampleShading);
    RglMinSampleShading( dt,minSampleShadingValue);
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    enableToString(tmp, multisample, "GL_MULTISAMPLE", delim);
    enableToString(tmp, sampleAlphaToCoverage, "GL_SAMPLE_ALPHA_TO_COVERAGE", delim);
    enableToString(tmp, sampleAlphaToOne, "GL_SAMPLE_ALPHA_TO_ONE", delim);
    enableToString(tmp, sampleCoverage, "GL_SAMPLE_COVERAGE", delim);
    tmp << print_string("glSampleCoverage(",sampleCoverageValue,",",sampleCoverageInvert,");",delim);
    enableToString(tmp, sampleShading, "GL_SAMPLE_SHADING", delim);
    tmp << print_string("glMinSampleShading(",minSampleShadingValue,");",delim);
    return tmp.str();
  }

  inline void glMinSampleShading( GLfloat value )
  {
    minSampleShadingValue = value;
  }

  inline void glSampleCoverage( GLfloat value, GLboolean invert )
  {
    sampleCoverageValue = value;
    sampleCoverageInvert = invert;
  }
};

//
// glPushAttrib(GL_EVAL_BIT)
//

struct Eval
{
  GLboolean   autoNormal;                // GL_AUTO_NORMAL
  GLboolean   map1dEnables[9];           // GL_MAP1_x
  GLboolean   map2dEnables[9];           // GL_MAP2_x
  GLdouble    map1GridDomain[2];         // GL_MAP1_GRID_DOMAIN
  GLdouble    map2GridDomain[4];         // GL_MAP2_GRID_DOMAIN
  GLuint      map1GridSegments;          // GL_MAP1_GRID_SEGMENTS
  GLuint      map2GridSegments[2];       // GL_MAP2_GRID_SEGMENTS

  inline Eval()
    : autoNormal(GL_FALSE)
    , map1GridSegments(1)
  {
    RegalAssert(static_cast<int>(GL_MAP1_VERTEX_4-GL_MAP1_COLOR_4) == 8);
    RegalAssert(static_cast<int>(GL_MAP2_VERTEX_4-GL_MAP2_COLOR_4) == 8);
    for (size_t ii=0; ii<9; ii++)
    {
      map1dEnables[ii] = GL_FALSE;
      map2dEnables[ii] = GL_FALSE;
    }
    map1GridDomain[0] = 0.0;
    map1GridDomain[1] = 1.0;
    map2GridSegments[0] = 1;
    map2GridSegments[1] = 1;
    map2GridDomain[0] = 0.0;
    map2GridDomain[1] = 1.0;
    map2GridDomain[2] = 0.0;
    map2GridDomain[3] = 1.0;
  }

  inline Eval &swap(Eval &other)
  {
    std::swap(autoNormal,other.autoNormal);
    std::swap_ranges(map1dEnables,map1dEnables+9,other.map1dEnables);
    std::swap_ranges(map2dEnables,map2dEnables+9,other.map2dEnables);
    std::swap_ranges(map1GridDomain,map1GridDomain+2,other.map1GridDomain);
    std::swap_ranges(map2GridDomain,map2GridDomain+4,other.map2GridDomain);
    std::swap(map1GridSegments,other.map1GridSegments);
    std::swap_ranges(map2GridSegments,map2GridSegments+2,other.map2GridSegments);
    return *this;
  }

  template <typename Procs>
  inline Eval &get(Procs &dt)
  {
    autoNormal = RglIsEnabled( dt, GL_AUTO_NORMAL);
    for (size_t ii=0; ii<9; ii++)
      map1dEnables[ii] = RglIsEnabled( dt, static_cast<GLenum>(GL_MAP1_COLOR_4+ii));
    for (size_t ii=0; ii<9; ii++)
      map2dEnables[ii] = RglIsEnabled( dt, static_cast<GLenum>(GL_MAP2_COLOR_4+ii));
    RglGetDoublev( dt, GL_MAP1_GRID_DOMAIN, map1GridDomain);
    RglGetDoublev( dt, GL_MAP2_GRID_DOMAIN, map2GridDomain);
    RglGetIntegerv( dt, GL_MAP1_GRID_SEGMENTS,reinterpret_cast<GLint *>(&map1GridSegments));
    RglGetIntegerv( dt, GL_MAP2_GRID_SEGMENTS,reinterpret_cast<GLint *>(&map2GridSegments));
    return *this;
  }

  template <typename Procs>
  inline const Eval &set(Procs &dt) const
  {
    setEnable(dt,GL_AUTO_NORMAL,autoNormal);
    for (size_t ii=0; ii<9; ii++)
      setEnable(dt,static_cast<GLenum>(GL_MAP1_COLOR_4+ii),map1dEnables[ii]);
    for (size_t ii=0; ii<9; ii++)
      setEnable(dt,static_cast<GLenum>(GL_MAP2_COLOR_4+ii),map2dEnables[ii]);
    RglMapGrid1d( dt, map1GridSegments, map1GridDomain[0], map1GridDomain[1]);
    RglMapGrid2d( dt, map2GridSegments[0], map2GridDomain[0], map2GridDomain[1],
                             map2GridSegments[1], map2GridDomain[2], map2GridDomain[3]);
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    enableToString(tmp, autoNormal, "GL_AUTO_NORMAL",delim);
    for (size_t ii=0; ii<9; ii++)
      enableToString(tmp,map1dEnables[ii],Token::toString(static_cast<GLenum>(GL_MAP1_COLOR_4+ii)),delim);
    for (size_t ii=0; ii<9; ii++)
      enableToString(tmp,map2dEnables[ii],Token::toString(static_cast<GLenum>(GL_MAP2_COLOR_4+ii)),delim);
    tmp << print_string("glMapGrid1d(",map1GridSegments,",",map1GridDomain[0],",",map1GridDomain[1],");",delim);
    tmp << print_string("glMapGrid2d(",map2GridSegments[0],",",map2GridDomain[0],",",map2GridDomain[1],
                        map2GridSegments[1],",",map2GridDomain[2],",",map2GridDomain[3],");",delim);
    return tmp.str();
  }

  template <typename T> inline void glMapGrid1( GLint n, T u1, T u2 )
  {
    map1GridSegments = n;
    map1GridDomain[0] = static_cast<GLdouble>(u1);
    map1GridDomain[1] = static_cast<GLdouble>(u2);
  }

  template <typename T> inline void glMapGrid2( GLint un, T u1, T u2, GLint vn, T v1, T v2 )
  {
    map2GridSegments[0] = un;
    map2GridDomain[0] = static_cast<GLdouble>(u1);
    map2GridDomain[1] = static_cast<GLdouble>(u2);
    map2GridSegments[1] = vn;
    map2GridDomain[2] = static_cast<GLdouble>(v1);
    map2GridDomain[3] = static_cast<GLdouble>(v2);
  }
};

//
// glPushAttrib(GL_FOG_BIT)
//

struct Fog
{
  GLfloat   color[4]; // GL_FOG_COLOR
  GLfloat   index;    // GL_FOG_INDEX
  GLfloat   density;  // GL_FOG_DENSITY
  GLfloat   start;    // GL_FOG_START
  GLfloat   end;      // GL_FOG_END
  GLenum    mode;     // GL_FOG_MODE
  GLboolean enable;   // GL_FOG
  GLenum    coordSrc; // GL_FOG_COORD_SRC
  GLboolean colorSum; // GL_COLOR_SUM

  inline Fog()
    : index(0)
    , density(1)
    , start(1)
    , end(1)
    , mode(GL_EXP)
    , enable(GL_FALSE)
    , coordSrc(GL_FRAGMENT_DEPTH)
    , colorSum(GL_FALSE)
  {
    color[0] = 0.0f;
    color[1] = 0.0f;
    color[2] = 0.0f;
    color[3] = 0.0f;
  }

  inline Fog &swap(Fog &other)
  {
    std::swap_ranges(color,color+4,other.color);
    std::swap(index,other.index);
    std::swap(density,other.density);
    std::swap(start,other.start);
    std::swap(end,other.end);
    std::swap(mode,other.mode);
    std::swap(enable,other.enable);
    std::swap(coordSrc,other.coordSrc);
    std::swap(colorSum,other.colorSum);
    return *this;
  }

  template <typename Procs>
  inline Fog &get(Procs &dt)
  {
    RglGetFloatv( dt, GL_FOG_COLOR,color);
    RglGetFloatv( dt, GL_FOG_INDEX,&index);
    RglGetFloatv( dt, GL_FOG_DENSITY,&density);
    RglGetFloatv( dt, GL_FOG_START,&start);
    RglGetFloatv( dt, GL_FOG_END,&end);
    RglGetIntegerv( dt, GL_FOG_MODE,reinterpret_cast<GLint *>(&mode));
    enable = RglIsEnabled( dt, GL_FOG);
    RglGetIntegerv( dt, GL_FOG_COORD_SRC,reinterpret_cast<GLint *>(&coordSrc));
    colorSum = RglIsEnabled( dt, GL_COLOR_SUM);
    return *this;
  }

  template <typename Procs>
  inline const Fog &set(Procs &dt) const
  {
    RglFogfv( dt, GL_FOG_COLOR,color);
    RglFogf( dt, GL_FOG_INDEX,index);
    RglFogf( dt, GL_FOG_DENSITY,density);
    RglFogf( dt, GL_FOG_START,start);
    RglFogf( dt, GL_FOG_END,end);
    RglFogi( dt, GL_FOG_MODE,mode);
    setEnable(dt,GL_FOG,enable);
    RglFogi( dt, GL_FOG_COORD_SRC,coordSrc);
    setEnable(dt,GL_COLOR_SUM,colorSum);
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    tmp << print_string("glFogfv(GL_FOG_COLOR,[",color[0],",",color[1],",",color[2],",",color[3],",","] );",delim);
    tmp << print_string("glFogf(GL_FOG_INDEX,",index,");",delim);
    tmp << print_string("glFogf(GL_FOG_DENSITY,",density,");",delim);
    tmp << print_string("glFogf(GL_FOG_START,",start,");",delim);
    tmp << print_string("glFogf(GL_FOG_END,",end,");",delim);
    tmp << print_string("glFogi(GL_FOG_MODE,",Token::toString(mode),");",delim);
    enableToString(tmp, enable, "GL_FOG",delim);
    tmp << print_string("glFogi(GL_FOG_COORD_SRC,",Token::toString(coordSrc),");",delim);
    enableToString(tmp, colorSum, "GL_COLOR_SUM",delim);
    return tmp.str();
  }
};

//
// glPushAttrib(GL_POINT_BIT)
//

struct Point
{
  GLfloat    size;                                      // GL_POINT_SIZE
  GLboolean  smooth;                                    // GL_POINT_SMOOTH
  GLboolean  sprite;                                    // GL_POINT_SPRITE
  GLfloat    sizeMin;                                   // GL_POINT_SIZE_MIN
  GLfloat    sizeMax;                                   // GL_POINT_SIZE_MAX
  GLfloat    fadeThresholdSize;                         // GL_POINT_FADE_THRESHOLD_SIZE
  GLfloat    distanceAttenuation[3];                    // GL_POINT_DISTANCE_ATTENUATION
  GLenum     spriteCoordOrigin;                         // GL_POINT_SPRITE_COORD_ORIGIN
  GLboolean  coordReplace[REGAL_EMU_MAX_TEXTURE_UNITS]; // GL_COORD_REPLACE

  inline Point()
    : size(1)
    , smooth(GL_FALSE)
    , sprite(GL_FALSE)
    , sizeMin(0)
    , sizeMax(1)        // Max of the impl. dependent max. aliased and smooth point sizes.
    , fadeThresholdSize(1)
    , spriteCoordOrigin(GL_UPPER_LEFT)
  {
    distanceAttenuation[0] = 1.0f;
    distanceAttenuation[1] = 0.0f;
    distanceAttenuation[2] = 0.0f;
    size_t n = array_size( coordReplace );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( coordReplace, ii );
      coordReplace[ii] = GL_FALSE;
    }
  }

  inline Point &swap(Point &other)
  {
    std::swap(size,other.size);
    std::swap(smooth,other.smooth);
    std::swap(sprite,other.sprite);
    std::swap(sizeMin,other.sizeMin);
    std::swap(sizeMax,other.sizeMax);
    std::swap(fadeThresholdSize,other.fadeThresholdSize);
    std::swap_ranges(distanceAttenuation,distanceAttenuation+3,other.distanceAttenuation);
    std::swap(spriteCoordOrigin,other.spriteCoordOrigin);
    std::swap_ranges(coordReplace,coordReplace+REGAL_EMU_MAX_TEXTURE_UNITS,other.coordReplace);
    return *this;
  }

  template <typename Procs>
  inline Point &get(Procs &dt)
  {
    RglGetFloatv( dt, GL_POINT_SIZE,&size);
    smooth = RglIsEnabled( dt, GL_POINT_SMOOTH);
    sprite = RglIsEnabled( dt, GL_POINT_SPRITE);
    RglGetFloatv( dt, GL_POINT_SIZE_MIN,&sizeMin);
    RglGetFloatv( dt, GL_POINT_SIZE_MAX,&sizeMin);
    RglGetFloatv( dt, GL_POINT_FADE_THRESHOLD_SIZE,&fadeThresholdSize);
    RglGetFloatv( dt, GL_POINT_DISTANCE_ATTENUATION,distanceAttenuation);
    RglGetIntegerv( dt, GL_POINT_SPRITE_COORD_ORIGIN,reinterpret_cast<GLint *>(&spriteCoordOrigin));
    size_t n = array_size( coordReplace );
    for (size_t ii=0; ii<n; ii++)
    {
      GLint coord;
      RglGetMultiTexEnvivEXT( dt, static_cast<GLenum>(GL_TEXTURE0+ii),GL_POINT_SPRITE,GL_COORD_REPLACE,&coord);
      RegalAssertArrayIndex( coordReplace, ii );
      coordReplace[ii] = static_cast<GLboolean>(coord);
    }
    return *this;
  }

  template <typename Procs>
  inline const Point &set(Procs &dt) const
  {
    RglPointSize( dt, size);
    setEnable(dt,GL_POINT_SMOOTH,smooth);
    setEnable(dt,GL_POINT_SPRITE,sprite);
    RglPointParameterf( dt, GL_POINT_SIZE_MIN,sizeMin);
    RglPointParameterf( dt, GL_POINT_SIZE_MAX,sizeMax);
    RglPointParameterf( dt, GL_POINT_FADE_THRESHOLD_SIZE,fadeThresholdSize);
    RglPointParameterfv( dt, GL_POINT_DISTANCE_ATTENUATION,distanceAttenuation);
    RglPointParameteri( dt, GL_POINT_SPRITE_COORD_ORIGIN,spriteCoordOrigin);
    size_t n = array_size( coordReplace );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( coordReplace, ii );
      RglMultiTexEnviEXT( dt, static_cast<GLenum>(GL_TEXTURE0+ii),GL_POINT_SPRITE,GL_COORD_REPLACE,coordReplace[ii]);
    }
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    tmp << print_string("glPointSize(",size,");",delim);
    enableToString(tmp, smooth, "GL_POINT_SMOOTH",delim);
    enableToString(tmp, sprite, "GL_POINT_SPRITE",delim);
    tmp << print_string("glPointParameterf(GL_POINT_SIZE_MIN",sizeMin,");",delim);
    tmp << print_string("glPointParameterf(GL_POINT_SIZE_MAX",sizeMax,");",delim);
    tmp << print_string("glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE",fadeThresholdSize,");",delim);
    tmp << print_string("glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, [ ",distanceAttenuation[0],", ",
                        distanceAttenuation[1],", ",
                        distanceAttenuation[2]," ]);",delim);
    tmp << print_string("glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN",Token::toString(spriteCoordOrigin),");",delim);
    size_t n = array_size( coordReplace );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( coordReplace, ii );
      tmp << print_string("glMultiTexEnviEXT(",Token::toString(static_cast<GLenum>(GL_TEXTURE0+ii)),",GL_POINT_SPRITE,GL_COORD_REPLACE,",coordReplace[ii],");",delim);
    }
    return tmp.str();
  }

  template <typename T> void glMultiTexEnv(GLenum texunit, GLenum target, GLenum pname, T param)
  {
    glMultiTexEnvv(texunit, target, pname, &param);
  }

  template <typename T> void glMultiTexEnvv(GLenum texunit, GLenum target, GLenum pname, const T *params)
  {
    if ((target == GL_POINT_SPRITE) && (pname == GL_COORD_REPLACE))
    {
      GLint unit = texunit - GL_TEXTURE0;
      if ((unit >= 0) && (static_cast<size_t>(unit) < array_size( coordReplace )))
      {
        RegalAssertArrayIndex( coordReplace, unit );
        coordReplace[unit] = static_cast<GLboolean>(params[0]);
      }
    }
  }

  template <typename T> void glPointParameter( GLenum pname, T param )
  {
    switch (pname)
    {
      case GL_POINT_SIZE_MIN:
        sizeMin = static_cast<GLfloat>(param);
        break;
      case GL_POINT_SIZE_MAX:
        sizeMax = static_cast<GLfloat>(param);
        break;
      case GL_POINT_FADE_THRESHOLD_SIZE:
        fadeThresholdSize = static_cast<GLfloat>(param);
        break;
      case GL_POINT_SPRITE_COORD_ORIGIN:
        spriteCoordOrigin = static_cast<GLenum>(param);
        break;
      default:
        break;
    }
  }

  template <typename T> void glPointParameterv( GLenum pname, const T *params )
  {
    switch (pname)
    {
      case GL_POINT_DISTANCE_ATTENUATION:
        distanceAttenuation[0] = static_cast<GLfloat>(params[0]);
        distanceAttenuation[1] = static_cast<GLfloat>(params[1]);
        distanceAttenuation[2] = static_cast<GLfloat>(params[2]);
        break;
      default:
        break;
    }
  }

  inline void glPointSize(GLfloat s)
  {
    size = s;
  }
};

//
// glPushAttrib(GL_POLYGON_STIPPLE_BIT)
//

struct PolygonStipple
{
  GLubyte pattern[32*4];

  inline PolygonStipple()
  {
    std::memset(pattern,0xff,sizeof(pattern));
  }

  inline PolygonStipple &swap(PolygonStipple &other)
  {
    std::swap_ranges(pattern,pattern+(32*4),other.pattern);
    return *this;
  }

  template <typename Procs>
  inline PolygonStipple &get(Procs &dt)
  {
    RglGetPolygonStipple( dt, pattern);
    return *this;
  }

  template <typename Procs>
  inline const PolygonStipple &set(Procs &dt) const
  {
    RglPolygonStipple( dt, pattern);
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    tmp << print_string("glPolygonStipple([");
    for (size_t ii=0; ii<(32*4)-1; ii++)
      tmp << print_string(" 0x",print_hex(pattern[ii]),",");
    tmp << print_string(" 0x",print_hex(pattern[(32*4)-1]),"]);",delim);
    return tmp.str();
  }

  void glPolygonStipple( const GLubyte *p )
  {
    for (size_t ii=0; ii<(32*4); ii++)
      pattern[ii] = p[ii];
  }
};

//
// glPushAttrib(GL_COLOR_BUFFER_BIT)
//

struct ColorBuffer
{
  GLenum      clampFragmentColor;                         // GL_CLAMP_FRAGMENT_COLOR
  GLenum      clampReadColor;                             // GL_CLAMP_READ_COLOR
  GLboolean   alphaTest;                                  // GL_ALPHA_TEST
  GLenum      alphaTestFunc;                              // GL_ALPHA_TEST_FUNC
  GLclampf    alphaTestRef;                               // GL_ALPHA_TEST_REF
  GLboolean   blend[REGAL_EMU_MAX_DRAW_BUFFERS];              // GL_BLEND
  GLenum      blendSrcRgb[REGAL_EMU_MAX_DRAW_BUFFERS];        // GL_BLEND_SRC_RGB
  GLenum      blendSrcAlpha[REGAL_EMU_MAX_DRAW_BUFFERS];      // GL_BLEND_SRC_ALPHA
  GLenum      blendDstRgb[REGAL_EMU_MAX_DRAW_BUFFERS];        // GL_BLEND_DST_RGB
  GLenum      blendDstAlpha[REGAL_EMU_MAX_DRAW_BUFFERS];      // GL_BLEND_DST_ALPHA
  GLenum      blendEquationRgb[REGAL_EMU_MAX_DRAW_BUFFERS];   // GL_BLEND_EQUATION_RGB
  GLenum      blendEquationAlpha[REGAL_EMU_MAX_DRAW_BUFFERS]; // GL_BLEND_EQUATION_ALPHA
  GLclampf    blendColor[4];                              // GL_BLEND_COLOR
  GLboolean   framebufferSRGB;                            // GL_FRAMEBUFFER_SRGB
  GLboolean   dither;                                     // GL_DITHER
  GLboolean   indexLogicOp;                               // GL_INDEX_LOGIC_OP
  GLboolean   colorLogicOp;                               // GL_COLOR_LOGIC_OP
  GLenum      logicOpMode;                                // GL_LOGIC_OP_MODE
  GLuint      indexWritemask;                             // GL_INDEX_WRITEMASK
  GLboolean   colorWritemask[REGAL_EMU_MAX_DRAW_BUFFERS][4];  // GL_COLOR_WRITEMASK
  GLclampf    colorClearValue[4];                         // GL_COLOR_CLEAR_VALUE
  GLfloat     indexClearValue;                            // GL_INDEX_CLEAR_VALUE
  GLenum      drawBuffers[REGAL_EMU_MAX_DRAW_BUFFERS];        // GL_DRAW_BUFERi
  bool        valid;

  inline ColorBuffer()
    : clampFragmentColor(GL_FIXED_ONLY)
    , clampReadColor(GL_FIXED_ONLY)
    , alphaTest(GL_FALSE)
    , alphaTestFunc(GL_ALWAYS)
    , alphaTestRef(0)
    , framebufferSRGB(GL_FALSE)
    , dither(GL_TRUE)
    , indexLogicOp(GL_FALSE)
    , colorLogicOp(GL_FALSE)
    , logicOpMode(GL_COPY)
    , indexWritemask(static_cast<GLuint>(~0))
    , indexClearValue(0)
    , valid(false)
  {
    blendColor[0] = 0.0f;
    blendColor[1] = 0.0f;
    blendColor[2] = 0.0f;
    blendColor[3] = 0.0f;

    colorClearValue[0] = 0.0f;
    colorClearValue[1] = 0.0f;
    colorClearValue[2] = 0.0f;
    colorClearValue[3] = 0.0f;

    size_t n = array_size( blend );
    RegalAssert(array_size( blendSrcRgb ) == n);
    RegalAssert(array_size( blendSrcAlpha ) == n);
    RegalAssert(array_size( blendDstRgb ) == n);
    RegalAssert(array_size( blendDstAlpha ) == n);
    RegalAssert(array_size( blendEquationRgb ) == n);
    RegalAssert(array_size( blendEquationAlpha ) == n);
    RegalAssert(array_size( drawBuffers ) == n);
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( blend, ii );
      blend[ii] = GL_FALSE;
      blendSrcRgb[ii] = GL_ONE;
      blendSrcAlpha[ii] = GL_ONE;
      blendDstRgb[ii] = GL_ZERO;
      blendDstAlpha[ii] = GL_ZERO;
      blendEquationRgb[ii]   = GL_FUNC_ADD;
      blendEquationAlpha[ii] = GL_FUNC_ADD;
      colorWritemask[ii][0] = GL_TRUE;
      colorWritemask[ii][1] = GL_TRUE;
      colorWritemask[ii][2] = GL_TRUE;
      colorWritemask[ii][3] = GL_TRUE;
      drawBuffers[ii] = GL_NONE;
    }
  }

  inline bool fullyDefined() const
  {
    return valid;
  }

  template <typename Procs>
  void getUndefined(Procs &dt)
  {
    if (!valid)
    {
      size_t n = array_size( drawBuffers );
      for (size_t ii=0; ii<n; ii++)
      {
        RegalAssertArrayIndex( drawBuffers, ii );
        RglGetIntegerv(dt, static_cast<GLenum>(GL_DRAW_BUFFER0+ii), reinterpret_cast<GLint *>(&drawBuffers[ii]));
      }
      valid = true;
    }
  }

  inline ColorBuffer &swap(ColorBuffer &other)
  {
    std::swap(clampFragmentColor,other.clampFragmentColor);
    std::swap(clampReadColor,other.clampReadColor);
    std::swap(alphaTest,other.alphaTest);
    std::swap(alphaTestFunc,other.alphaTestFunc);
    std::swap(alphaTestRef,other.alphaTestRef);
    std::swap_ranges(blend,blend+REGAL_EMU_MAX_DRAW_BUFFERS,other.blend);
    std::swap_ranges(blendSrcRgb,blendSrcRgb+REGAL_EMU_MAX_DRAW_BUFFERS,other.blendSrcRgb);
    std::swap_ranges(blendSrcAlpha,blendSrcAlpha+REGAL_EMU_MAX_DRAW_BUFFERS,other.blendSrcAlpha);
    std::swap_ranges(blendDstRgb,blendDstRgb+REGAL_EMU_MAX_DRAW_BUFFERS,other.blendDstRgb);
    std::swap_ranges(blendDstAlpha,blendDstAlpha+REGAL_EMU_MAX_DRAW_BUFFERS,other.blendDstAlpha);
    std::swap_ranges(blendEquationRgb,blendEquationRgb+REGAL_EMU_MAX_DRAW_BUFFERS,other.blendEquationRgb);
    std::swap_ranges(blendEquationAlpha,blendEquationAlpha+REGAL_EMU_MAX_DRAW_BUFFERS,other.blendEquationAlpha);
    std::swap_ranges(blendColor,blendColor+4,other.blendColor);
    std::swap(framebufferSRGB,other.framebufferSRGB);
    std::swap(dither,other.dither);
    std::swap(indexLogicOp,other.indexLogicOp);
    std::swap(colorLogicOp,other.colorLogicOp);
    std::swap(logicOpMode,other.logicOpMode);
    std::swap(indexWritemask,other.indexWritemask);
    std::swap_ranges(&colorWritemask[0][0],&colorWritemask[0][0]+(REGAL_EMU_MAX_DRAW_BUFFERS*4),&other.colorWritemask[0][0]);
    std::swap_ranges(colorClearValue,colorClearValue+4,other.colorClearValue);
    std::swap(indexClearValue,other.indexClearValue);
    std::swap_ranges(drawBuffers,drawBuffers+REGAL_EMU_MAX_DRAW_BUFFERS,other.drawBuffers);
    return *this;
  }

  template <typename Procs>
  inline ColorBuffer &get(Procs &dt)
  {
    RglGetIntegerv( dt, GL_CLAMP_FRAGMENT_COLOR,reinterpret_cast<GLint *>(&clampFragmentColor));
    RglGetIntegerv( dt, GL_CLAMP_READ_COLOR,reinterpret_cast<GLint *>(&clampReadColor));
    alphaTest = RglIsEnabled( dt, GL_ALPHA_TEST);
    RglGetIntegerv( dt, GL_ALPHA_TEST_FUNC,reinterpret_cast<GLint *>(&alphaTestFunc));
    RglGetFloatv( dt, GL_ALPHA_TEST_REF,&alphaTestRef);
    size_t n = array_size( blend );
    for (GLuint ii=0; ii<static_cast<GLuint>(n); ii++)
    {
      RegalAssertArrayIndex( blend, ii );
      blend[ii] = RglIsEnabledi( dt, GL_BLEND, ii);
    }
    n = array_size( blendSrcRgb );
    for (GLuint ii=0; ii<static_cast<GLuint>(n); ii++)
    {
      RegalAssertArrayIndex( blendSrcRgb, ii );
      RglGetIntegeri_v( dt, GL_BLEND_SRC_RGB, ii, reinterpret_cast<GLint *>(&blendSrcRgb[ii]));
    }
    n = array_size( blendSrcAlpha );
    for (GLuint ii=0; ii<static_cast<GLuint>(n); ii++)
    {
      RegalAssertArrayIndex( blendSrcAlpha, ii );
      RglGetIntegeri_v( dt, GL_BLEND_SRC_ALPHA, ii, reinterpret_cast<GLint *>(&blendSrcAlpha[ii]));
    }
    n = array_size( blendDstRgb );
    for (GLuint ii=0; ii<static_cast<GLuint>(n); ii++)
    {
      RegalAssertArrayIndex( blendDstRgb, ii );
      RglGetIntegeri_v( dt, GL_BLEND_DST_RGB, ii, reinterpret_cast<GLint *>(&blendDstRgb[ii]));
    }
    n = array_size( blendDstAlpha );
    for (GLuint ii=0; ii<static_cast<GLuint>(n); ii++)
    {
      RegalAssertArrayIndex( blendDstAlpha, ii );
      RglGetIntegeri_v( dt, GL_BLEND_DST_ALPHA, ii, reinterpret_cast<GLint *>(&blendDstAlpha[ii]));
    }
    n = array_size( blendEquationRgb );
    for (GLuint ii=0; ii<static_cast<GLuint>(n); ii++)
    {
      RegalAssertArrayIndex( blendEquationRgb, ii );
      RglGetIntegeri_v( dt, GL_BLEND_EQUATION_RGB, ii, reinterpret_cast<GLint *>(&blendEquationRgb[ii]));
    }
    n = array_size( blendEquationAlpha );
    for (GLuint ii=0; ii<static_cast<GLuint>(n); ii++)
    {
      RegalAssertArrayIndex( blendEquationAlpha, ii );
      RglGetIntegeri_v( dt, GL_BLEND_EQUATION_ALPHA, ii, reinterpret_cast<GLint *>(&blendEquationAlpha[ii]));
    }
    RglGetFloatv( dt, GL_BLEND_COLOR,blendColor);
    framebufferSRGB = RglIsEnabled( dt, GL_FRAMEBUFFER_SRGB);
    dither = RglIsEnabled( dt, GL_DITHER);
    indexLogicOp = RglIsEnabled( dt, GL_INDEX_LOGIC_OP);
    colorLogicOp  = RglIsEnabled( dt, GL_COLOR_LOGIC_OP);
    RglGetIntegerv( dt, GL_LOGIC_OP_MODE, reinterpret_cast<GLint *>(&logicOpMode));
    RglGetIntegerv( dt, GL_INDEX_WRITEMASK, reinterpret_cast<GLint *>(&indexWritemask));
    for (GLuint ii=0; ii<REGAL_EMU_MAX_DRAW_BUFFERS; ii++)
      RglGetBooleani_v( dt, GL_COLOR_WRITEMASK, ii, &colorWritemask[ii][0]);
    RglGetFloatv( dt, GL_COLOR_CLEAR_VALUE,colorClearValue);
    RglGetFloatv( dt, GL_INDEX_CLEAR_VALUE,&indexClearValue);
    n = array_size( drawBuffers );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( drawBuffers, ii );
      RglGetIntegerv( dt, static_cast<GLenum>(GL_DRAW_BUFFER0+ii), reinterpret_cast<GLint *>(&drawBuffers[ii]));
    }
    return *this;
  }

  template <typename Procs>
  inline const ColorBuffer &set(Procs &dt) const
  {
    RglClampColor( dt, GL_CLAMP_FRAGMENT_COLOR,clampFragmentColor);
    RglClampColor( dt, GL_CLAMP_READ_COLOR,clampReadColor);
    setEnable(dt,GL_ALPHA_TEST,alphaTest);
    RglAlphaFunc( dt, alphaTestFunc,alphaTestRef);
    size_t n = array_size( blend );
    for (GLuint ii=0; ii<static_cast<GLuint>(n); ii++)
    {
      RegalAssertArrayIndex( blend, ii );
      setEnablei(dt,GL_BLEND,ii,blend[ii]);
    }
    n = array_size( blendSrcRgb );
    RegalAssert(array_size( blendSrcAlpha ) == n);
    RegalAssert(array_size( blendDstRgb ) == n);
    RegalAssert(array_size( blendDstAlpha ) == n);
    for (GLuint ii=0; ii<static_cast<GLuint>(n); ii++)
    {
      RegalAssertArrayIndex( blendSrcRgb, ii );
      RglBlendFuncSeparatei( dt, ii,blendSrcRgb[ii],blendSrcAlpha[ii],blendDstRgb[ii],blendDstAlpha[ii]);
    }
    n = array_size( blendEquationRgb );
    RegalAssert(array_size( blendEquationAlpha ) == n);
    for (GLuint ii=0; ii<static_cast<GLuint>(n); ii++)
    {
      RegalAssertArrayIndex( blendEquationRgb, ii );
      RglBlendEquationSeparatei( dt, ii,blendEquationRgb[ii],blendEquationAlpha[ii]);
    }
    RglBlendColor( dt, blendColor[0],blendColor[1],blendColor[2],blendColor[3]);
    setEnable(dt,GL_FRAMEBUFFER_SRGB,framebufferSRGB);
    setEnable(dt,GL_DITHER,dither);
    setEnable(dt,GL_INDEX_LOGIC_OP,indexLogicOp);
    setEnable(dt,GL_COLOR_LOGIC_OP,colorLogicOp);
    RglLogicOp( dt, logicOpMode);
    RglIndexMask( dt, indexWritemask);
    for (GLuint ii=0; ii<REGAL_EMU_MAX_DRAW_BUFFERS; ii++)
      RglColorMaski( dt, ii, colorWritemask[ii][0], colorWritemask[ii][1], colorWritemask[ii][2], colorWritemask[ii][3]);
    RglClearColor( dt, colorClearValue[0],colorClearValue[1],colorClearValue[2],colorClearValue[3]);
    RglClearIndex( dt, indexClearValue);
    if (valid)
    {
      RegalAssert(array_size( drawBuffers ) >= REGAL_EMU_MAX_DRAW_BUFFERS);
      RglDrawBuffers( dt, REGAL_EMU_MAX_DRAW_BUFFERS, drawBuffers);
    }
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    tmp << print_string("glClampColor(GL_CLAMP_FRAGMENT_COLOR",",",Token::toString(clampFragmentColor),");",delim);
    tmp << print_string("glClampColor(GL_CLAMP_READ_COLOR",",",Token::toString(clampReadColor),");",delim);
    enableToString(tmp, alphaTest, "GL_ALPHA_TEST",delim);
    tmp << print_string("glAlphaFunc(",Token::toString(alphaTestFunc),",",alphaTestRef,");",delim);
    size_t n = array_size( blend );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( blend, ii );
      enableiToString(tmp, blend[ii], "GL_BLEND", static_cast<GLuint>(ii),delim);
    }
    n = array_size( blendSrcRgb );
    RegalAssert(array_size( blendSrcAlpha ) == n);
    RegalAssert(array_size( blendDstRgb ) == n);
    RegalAssert(array_size( blendDstAlpha ) == n);
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( blendSrcRgb, ii );
      tmp << print_string("glBlendFuncSeparatei(",ii,",",Token::toString(blendSrcRgb[ii]),",",Token::toString(blendSrcAlpha[ii]),",",Token::toString(blendDstRgb[ii]),",",Token::toString(blendDstAlpha[ii]),");",delim);
    }
    n = array_size( blendEquationRgb );
    RegalAssert(array_size( blendEquationAlpha ) == n);
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( blendEquationRgb, ii );
      tmp << print_string("glBlendEquationSeparatei(",ii,",",Token::toString(blendEquationRgb[ii]),",",Token::toString(blendEquationAlpha[ii]),");",delim);
    }
    tmp << print_string("glBlendColor(",blendColor[0],",",blendColor[1],",",blendColor[2],",",blendColor[3],");",delim);
    enableToString(tmp, framebufferSRGB, "GL_FRAMEBUFFER_SRGB",delim);
    enableToString(tmp, dither, "GL_DITHER",delim);
    enableToString(tmp, indexLogicOp, "GL_INDEX_LOGIC_OP",delim);
    enableToString(tmp, colorLogicOp, "GL_COLOR_LOGIC_OP",delim);
    tmp << print_string("glLogicOp(",Token::toString(logicOpMode),");",delim);
    tmp << print_string("glIndexMask(0x",print_hex(indexWritemask),");",delim);
    for (size_t ii=0; ii<REGAL_EMU_MAX_DRAW_BUFFERS; ii++)
      tmp << print_string("glColorMaski(",ii,",", colorWritemask[ii][0],",",colorWritemask[ii][1],",",colorWritemask[ii][2],",",colorWritemask[ii][3],");",delim);
    tmp << print_string("glClearColor(",colorClearValue[0],",",colorClearValue[1],",",colorClearValue[2],",",colorClearValue[3],");",delim);
    tmp << print_string("glClearIndex(",indexClearValue,");",delim);
    if (valid)
    {
      tmp << print_string("glDrawBuffers(",REGAL_EMU_MAX_DRAW_BUFFERS,", [");
      RegalAssert( array_size( drawBuffers ) >= REGAL_EMU_MAX_DRAW_BUFFERS );
      for (size_t ii=0; ii<REGAL_EMU_MAX_DRAW_BUFFERS-1; ii++)
      {
        RegalAssertArrayIndex( drawBuffers, ii );
        tmp << print_string(" ",Token::toString(drawBuffers[ii]),",");
      }
      RegalAssertArrayIndex( drawBuffers, REGAL_EMU_MAX_DRAW_BUFFERS-1 );
      tmp << print_string(" ",Token::toString(drawBuffers[REGAL_EMU_MAX_DRAW_BUFFERS-1]),"]);",delim);
    }
    else
      tmp << print_string("glDrawBuffers(",REGAL_EMU_MAX_DRAW_BUFFERS,", [ *not valid* ]);",delim);
    return tmp.str();
  }

  inline void glAlphaFunc(GLenum func, GLclampf ref)
  {
    alphaTestFunc = func;
    alphaTestRef = ref;
  }

  inline void glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
  {
    blendColor[0] = red;
    blendColor[1] = green;
    blendColor[2] = blue;
    blendColor[3] = alpha;
  }

  void glBlendEquation(GLenum mode)
  {
    for (GLuint buf=0; buf<REGAL_EMU_MAX_DRAW_BUFFERS; buf++)
      glBlendEquationi(buf, mode);
  }

  void glBlendEquationi(GLuint buf, GLenum mode)
  {
    size_t n = array_size( blendEquationRgb );
    RegalAssert( array_size( blendEquationAlpha ) == n );
    if (buf < n)
    {
      RegalAssertArrayIndex( blendEquationRgb, buf );
      RegalAssertArrayIndex( blendEquationAlpha, buf );
      blendEquationRgb[buf] = blendEquationAlpha[buf] = mode;
    }
  }

  void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
  {
    for (GLuint buf=0; buf<REGAL_EMU_MAX_DRAW_BUFFERS; buf++)
      glBlendEquationSeparatei(buf, modeRGB, modeAlpha);
  }

  void glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
  {
    size_t n = array_size( blendEquationRgb );
    RegalAssert( array_size( blendEquationAlpha ) == n );
    if (buf < n)
    {
      RegalAssertArrayIndex( blendEquationRgb, buf );
      RegalAssertArrayIndex( blendEquationAlpha, buf );
      blendEquationRgb[buf]   = modeRGB;
      blendEquationAlpha[buf] = modeAlpha;
    }
  }

  void glBlendFunc(GLenum src, GLenum dst)
  {
    for (GLuint buf=0; buf<REGAL_EMU_MAX_DRAW_BUFFERS; buf++)
      glBlendFunci(buf, src, dst);
  }

  void glBlendFunci(GLuint buf, GLenum src, GLenum dst)
  {
    size_t n = array_size( blendSrcRgb );
    RegalAssert( array_size( blendSrcAlpha ) == n );
    RegalAssert( array_size( blendDstRgb ) == n );
    RegalAssert( array_size( blendDstAlpha ) == n );
    if (buf < n)
    {
      RegalAssertArrayIndex( blendSrcRgb, buf );
      RegalAssertArrayIndex( blendSrcAlpha, buf );
      RegalAssertArrayIndex( blendDstRgb, buf );
      RegalAssertArrayIndex( blendDstAlpha, buf );
      blendSrcRgb[buf] = blendSrcAlpha[buf] = src;
      blendDstRgb[buf] = blendDstAlpha[buf] = dst;
    }
  }

  void glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
  {
    for (GLuint buf=0; buf<REGAL_EMU_MAX_DRAW_BUFFERS; buf++)
      glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
  }

  inline void glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
  {
    size_t n = array_size( blendSrcRgb );
    RegalAssert( array_size( blendSrcAlpha ) == n );
    RegalAssert( array_size( blendDstRgb ) == n );
    RegalAssert( array_size( blendDstAlpha ) == n );
    if (buf < n)
    {
      RegalAssertArrayIndex( blendSrcRgb, buf );
      RegalAssertArrayIndex( blendSrcAlpha, buf );
      RegalAssertArrayIndex( blendDstRgb, buf );
      RegalAssertArrayIndex( blendDstAlpha, buf );
      blendSrcRgb[buf]   = srcRGB;
      blendDstRgb[buf]   = dstRGB;
      blendSrcAlpha[buf] = srcAlpha;
      blendDstAlpha[buf] = dstAlpha;
    }
  }
  inline void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
  {
    colorClearValue[0] = red;
    colorClearValue[1] = green;
    colorClearValue[2] = blue;
    colorClearValue[3] = alpha;
  }

  inline void glClearIndex(GLfloat c)
  {
    indexClearValue = c;
  }

  void glColorMask(GLboolean r, GLboolean g, GLboolean b, GLboolean a)
  {
    for (GLuint index=0; index<REGAL_EMU_MAX_DRAW_BUFFERS; index++)
      glColorMaski(index, r, g, b, a);
  }

  void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
  {
    if (index < REGAL_EMU_MAX_DRAW_BUFFERS)
    {
      colorWritemask[index][0] = r;
      colorWritemask[index][1] = g;
      colorWritemask[index][2] = b;
      colorWritemask[index][3] = a;
    }
  }

  void glDrawBuffer(GLenum buf)
  {
    drawBuffers[0] = buf;
    size_t n = array_size( drawBuffers );
    for (size_t ii=1; ii<n; ii++)
    {
      RegalAssertArrayIndex( drawBuffers, ii );
      drawBuffers[ii] = GL_NONE;
    }
  }

  void glDrawBuffers(GLsizei stop, const GLenum *bufs)
  {
    size_t s = static_cast<size_t>(stop);
    size_t n = array_size( drawBuffers );
    if (s < n)
    {
      for (size_t ii=0; ii<s; ii++)
      {
        RegalAssertArrayIndex( drawBuffers, ii );
        drawBuffers[ii] = bufs[ii];
      }
      for (size_t ii=s; ii<n; ii++)
      {
        RegalAssertArrayIndex( drawBuffers, ii );
        drawBuffers[ii] = GL_NONE;
      }
    }
  }

  inline void glIndexMask(GLuint mask)
  {
    indexWritemask = mask;
  }

  inline void glLogicOp(GLenum op)
  {
    logicOpMode = op;
  }
};

//
// glPushAttrib(GL_PIXEL_MODE_BIT)
//

struct PixelMode
{
  GLenum      readBuffer;                   // GL_READ_BUFFER
  GLboolean   mapColor;                     // GL_MAP_COLOR
  GLboolean   mapStencil;                   // GL_MAP_STENCIL
  GLint       indexShift;                   // GL_INDEX_SHIFT
  GLint       indexOffset;                  // GL_INDEX_OFFSET
  GLfloat     redScale;                     // GL_RED_SCALE
  GLfloat     redBias;                      // GL_RED_BIAS
  GLfloat     greenScale;                   // GL_GREEN_SCALE
  GLfloat     greenBias;                    // GL_GREEN_BIAS
  GLfloat     blueScale;                    // GL_BLUE_SCALE
  GLfloat     blueBias;                     // GL_BLUE_BIAS
  GLfloat     alphaScale;                   // GL_ALPHA_SCALE
  GLfloat     alphaBias;                    // GL_ALPHA_BIAS
  GLboolean   colorTable;                   // GL_COLOR_TABLE
  GLboolean   postConvolutionColorTable;    // GL_POST_CONVOLUTION_COLOR_TABLE
  GLboolean   postColorMatrixColorTable;    // GL_POST_COLOR_MATRIX_COLOR_TABLE
  GLfloat     colorTableScale[3][4];        // GL_COLOR_TABLE_SCALE
  GLfloat     colorTableBias[3][4];         // GL_COLOR_TABLE_BIAS
  GLboolean   convolution1d;                // GL_CONVOLUTION_1D
  GLboolean   convolution2d;                // GL_CONVOLUTION_2D
  GLboolean   separable2d;                  // GL_SEPARABLE_2D
  GLfloat     convolutionBorderColor[3][4]; // GL_CONVOLUTION_BORDER_COLOR
  GLenum      convolutionBorderMode[3];     // GL_CONVOLUTION_BORDER_MODE
  GLfloat     convolutionFilterScale[3][4]; // GL_CONVOLUTION_FILTER_SCALE
  GLfloat     convolutionFilterBias[3][4];  // GL_CONVOLUTION_FILTER_BIAS
  GLfloat     postConvolutionRedScale;      // GL_POST_CONVOLUTION_RED_SCALE
  GLfloat     postConvolutionRedBias;       // GL_POST_CONVOLUTION_RED_BIAS
  GLfloat     postConvolutionGreenScale;    // GL_POST_CONVOLUTION_GREEN_SCALE
  GLfloat     postConvolutionGreenBias;     // GL_POST_CONVOLUTION_GREEN_BIAS
  GLfloat     postConvolutionBlueScale;     // GL_POST_CONVOLUTION_BLUE_SCALE
  GLfloat     postConvolutionBlueBias;      // GL_POST_CONVOLUTION_BLUE_BIAS
  GLfloat     postConvolutionAlphaScale;    // GL_POST_CONVOLUTION_ALPHA_SCALE
  GLfloat     postConvolutionAlphaBias;     // GL_POST_CONVOLUTION_ALPHA_BIAS
  GLfloat     postColorMatrixRedScale;      // GL_POST_COLOR_MATRIX_RED_SCALE
  GLfloat     postColorMatrixRedBias;       // GL_POST_COLOR_MATRIX_RED_BIAS
  GLfloat     postColorMatrixGreenScale;    // GL_POST_COLOR_MATRIX_GREEN_SCALE
  GLfloat     postColorMatrixGreenBias;     // GL_POST_COLOR_MATRIX_GREEN_BIAS
  GLfloat     postColorMatrixBlueScale;     // GL_POST_COLOR_MATRIX_BLUE_SCALE
  GLfloat     postColorMatrixBlueBias;      // GL_POST_COLOR_MATRIX_BLUE_BIAS
  GLfloat     postColorMatrixAlphaScale;    // GL_POST_COLOR_MATRIX_ALPHA_SCALE
  GLfloat     postColorMatrixAlphaBias;     // GL_POST_COLOR_MATRIX_ALPHA_BIAS
  GLboolean   histogram;                    // GL_HISTOGRAM
  GLboolean   minmax;                       // GL_MINMAX
  GLfloat     zoomX;                        // GL_ZOOM_X
  GLfloat     zoomY;                        // GL_ZOOM_Y
  bool        valid;

  inline PixelMode()
    : readBuffer(0)
    , mapColor(GL_FALSE)
    , mapStencil(GL_FALSE)
    , indexShift(0)
    , indexOffset(0)
    , redScale(1)
    , redBias(0)
    , greenScale(1)
    , greenBias(0)
    , blueScale(1)
    , blueBias(0)
    , alphaScale(1)
    , alphaBias(0)
    , colorTable(GL_FALSE)
    , postConvolutionColorTable(GL_FALSE)
    , postColorMatrixColorTable(GL_FALSE)
    , convolution1d(GL_FALSE)
    , convolution2d(GL_FALSE)
    , separable2d(GL_FALSE)
    , postConvolutionRedScale(1)
    , postConvolutionRedBias(0)
    , postConvolutionGreenScale(1)
    , postConvolutionGreenBias(0)
    , postConvolutionBlueScale(1)
    , postConvolutionBlueBias(0)
    , postConvolutionAlphaScale(1)
    , postConvolutionAlphaBias(0)
    , postColorMatrixRedScale(1)
    , postColorMatrixRedBias(0)
    , postColorMatrixGreenScale(1)
    , postColorMatrixGreenBias(0)
    , postColorMatrixBlueScale(1)
    , postColorMatrixBlueBias(0)
    , postColorMatrixAlphaScale(1)
    , postColorMatrixAlphaBias(0)
    , histogram(GL_FALSE)
    , minmax(GL_FALSE)
    , zoomX(1)
    , zoomY(1)
    , valid(false)
  {
    for (size_t ii=0; ii<4; ii++)
    {
      colorTableScale[0][ii] = 1.0f;
      colorTableScale[1][ii] = 1.0f;
      colorTableScale[2][ii] = 1.0f;
      colorTableBias[0][ii] = 0.0f;
      colorTableBias[1][ii] = 0.0f;
      colorTableBias[2][ii] = 0.0f;
      convolutionBorderColor[0][ii] = 0.0f;
      convolutionBorderColor[1][ii] = 0.0f;
      convolutionBorderColor[2][ii] = 0.0f;
      convolutionFilterScale[0][ii] = 1.0f;
      convolutionFilterScale[1][ii] = 1.0f;
      convolutionFilterScale[2][ii] = 1.0f;
      convolutionFilterBias[0][ii] = 0.0f;
      convolutionFilterBias[1][ii] = 0.0f;
      convolutionFilterBias[2][ii] = 0.0f;
    }

    convolutionBorderMode[0] = GL_REDUCE;
    convolutionBorderMode[1] = GL_REDUCE;
    convolutionBorderMode[2] = GL_REDUCE;
  }

  inline bool fullyDefined() const
  {
    return valid;
  }

  template <typename Procs>
  void getUndefined(Procs &dt)
  {
    if (!valid)
    {
      RglGetIntegerv( dt, GL_READ_BUFFER,reinterpret_cast<GLint *>(&readBuffer));
      valid = true;
    }
  }

  inline PixelMode &swap(PixelMode &other)
  {
    std::swap(readBuffer,other.readBuffer);
    std::swap(mapColor,other.mapColor);
    std::swap(mapStencil,other.mapStencil);
    std::swap(indexShift,other.indexShift);
    std::swap(indexOffset,other.indexOffset);
    std::swap(redScale,other.redScale);
    std::swap(redBias,other.redBias);
    std::swap(greenScale,other.greenScale);
    std::swap(greenBias,other.greenBias);
    std::swap(blueScale,other.blueScale);
    std::swap(blueBias,other.blueBias);
    std::swap(alphaScale,other.alphaScale);
    std::swap(alphaBias,other.alphaBias);
    std::swap(colorTable,other.colorTable);
    std::swap(postConvolutionColorTable,other.postConvolutionColorTable);
    std::swap(postColorMatrixColorTable,other.postColorMatrixColorTable);
    std::swap_ranges(&colorTableScale[0][0],&colorTableScale[0][0]+(3*4),&other.colorTableScale[0][0]);
    std::swap_ranges(&colorTableBias[0][0],&colorTableBias[0][0]+(3*4),&other.colorTableBias[0][0]);
    std::swap(convolution1d,other.convolution1d);
    std::swap(convolution2d,other.convolution2d);
    std::swap(separable2d,other.separable2d);
    std::swap_ranges(&convolutionBorderColor[0][0],&convolutionBorderColor[0][0]+(3*4),&other.convolutionBorderColor[0][0]);
    std::swap_ranges(convolutionBorderMode,convolutionBorderMode+3,other.convolutionBorderMode);
    std::swap_ranges(&convolutionFilterScale[0][0],&convolutionFilterScale[0][0]+(3*4),&other.convolutionFilterScale[0][0]);
    std::swap_ranges(&convolutionFilterBias[0][0],&convolutionFilterBias[0][0]+(3*4),&other.convolutionFilterBias[0][0]);
    std::swap(postConvolutionRedScale,other.postConvolutionRedScale);
    std::swap(postConvolutionRedBias,other.postConvolutionRedBias);
    std::swap(postConvolutionGreenScale,other.postConvolutionGreenScale);
    std::swap(postConvolutionGreenBias,other.postConvolutionGreenBias);
    std::swap(postConvolutionBlueScale,other.postConvolutionBlueScale);
    std::swap(postConvolutionBlueBias,other.postConvolutionBlueBias);
    std::swap(postConvolutionAlphaScale,other.postConvolutionAlphaScale);
    std::swap(postConvolutionAlphaBias,other.postConvolutionAlphaBias);
    std::swap(postColorMatrixRedScale,other.postColorMatrixRedScale);
    std::swap(postColorMatrixRedBias,other.postColorMatrixRedBias);
    std::swap(postColorMatrixGreenScale,other.postColorMatrixGreenScale);
    std::swap(postColorMatrixGreenBias,other.postColorMatrixGreenBias);
    std::swap(postColorMatrixBlueScale,other.postColorMatrixBlueScale);
    std::swap(postColorMatrixBlueBias,other.postColorMatrixBlueBias);
    std::swap(postColorMatrixAlphaScale,other.postColorMatrixAlphaScale);
    std::swap(postColorMatrixAlphaBias,other.postColorMatrixAlphaBias);
    std::swap(histogram,other.histogram);
    std::swap(minmax,other.minmax);
    std::swap(zoomX,other.zoomX);
    std::swap(zoomY,other.zoomY);
    return *this;
  }

  template <typename Procs>
  inline PixelMode &get(Procs &dt)
  {
    RglGetIntegerv( dt, GL_READ_BUFFER,reinterpret_cast<GLint *>(&readBuffer));
    RglGetBooleanv( dt, GL_MAP_COLOR,&mapColor);
    RglGetBooleanv( dt, GL_MAP_STENCIL,&mapStencil);
    RglGetIntegerv( dt, GL_INDEX_SHIFT,&indexShift);
    RglGetIntegerv( dt, GL_INDEX_OFFSET,&indexOffset);
    RglGetFloatv( dt, GL_RED_SCALE,&redScale);
    RglGetFloatv( dt, GL_RED_BIAS,&redBias);
    RglGetFloatv( dt, GL_GREEN_SCALE,&greenScale);
    RglGetFloatv( dt, GL_GREEN_BIAS,&greenBias);
    RglGetFloatv( dt, GL_BLUE_SCALE,&blueScale);
    RglGetFloatv( dt, GL_BLUE_BIAS,&blueBias);
    RglGetFloatv( dt, GL_ALPHA_SCALE,&alphaScale);
    RglGetFloatv( dt, GL_ALPHA_BIAS,&alphaBias);
    colorTable = RglIsEnabled( dt, GL_COLOR_TABLE);
    postConvolutionColorTable = RglIsEnabled( dt, GL_POST_CONVOLUTION_COLOR_TABLE);
    postColorMatrixColorTable = RglIsEnabled( dt, GL_POST_COLOR_MATRIX_COLOR_TABLE);
    RglGetColorTableParameterfv( dt, GL_COLOR_TABLE,                   GL_COLOR_TABLE_SCALE, &colorTableScale[0][0]);
    RglGetColorTableParameterfv( dt, GL_COLOR_TABLE,                   GL_COLOR_TABLE_BIAS,  &colorTableBias[0][0]);
    RglGetColorTableParameterfv( dt, GL_POST_CONVOLUTION_COLOR_TABLE,  GL_COLOR_TABLE_SCALE, &colorTableScale[1][0]);
    RglGetColorTableParameterfv( dt, GL_POST_CONVOLUTION_COLOR_TABLE,  GL_COLOR_TABLE_BIAS,  &colorTableBias[1][0]);
    RglGetColorTableParameterfv( dt, GL_POST_COLOR_MATRIX_COLOR_TABLE, GL_COLOR_TABLE_SCALE, &colorTableScale[2][0]);
    RglGetColorTableParameterfv( dt, GL_POST_COLOR_MATRIX_COLOR_TABLE, GL_COLOR_TABLE_BIAS,  &colorTableBias[2][0]);
    convolution1d = RglIsEnabled( dt, GL_CONVOLUTION_1D);
    convolution2d = RglIsEnabled( dt, GL_CONVOLUTION_2D);
    separable2d = RglIsEnabled( dt, GL_SEPARABLE_2D);
    RglGetConvolutionParameterfv( dt, GL_CONVOLUTION_1D, GL_CONVOLUTION_BORDER_COLOR, &convolutionBorderColor[0][0]);
    RglGetConvolutionParameteriv( dt, GL_CONVOLUTION_1D, GL_CONVOLUTION_BORDER_MODE,  reinterpret_cast<GLint *>(&convolutionBorderMode[0]));
    RglGetConvolutionParameterfv( dt, GL_CONVOLUTION_1D, GL_CONVOLUTION_FILTER_SCALE, &convolutionFilterScale[0][0]);
    RglGetConvolutionParameterfv( dt, GL_CONVOLUTION_1D, GL_CONVOLUTION_FILTER_BIAS,  &convolutionFilterBias [0][0]);
    RglGetConvolutionParameterfv( dt, GL_CONVOLUTION_2D, GL_CONVOLUTION_BORDER_COLOR, &convolutionBorderColor[1][0]);
    RglGetConvolutionParameteriv( dt, GL_CONVOLUTION_2D, GL_CONVOLUTION_BORDER_MODE,  reinterpret_cast<GLint *>(&convolutionBorderMode[1]));
    RglGetConvolutionParameterfv( dt, GL_CONVOLUTION_2D, GL_CONVOLUTION_FILTER_SCALE, &convolutionFilterScale[1][0]);
    RglGetConvolutionParameterfv( dt, GL_CONVOLUTION_2D, GL_CONVOLUTION_FILTER_BIAS,  &convolutionFilterBias [1][0]);
    RglGetConvolutionParameterfv( dt, GL_SEPARABLE_2D,   GL_CONVOLUTION_BORDER_COLOR, &convolutionBorderColor[2][0]);
    RglGetConvolutionParameteriv( dt, GL_SEPARABLE_2D,   GL_CONVOLUTION_BORDER_MODE,  reinterpret_cast<GLint *>(&convolutionBorderMode[2]));
    RglGetConvolutionParameterfv( dt, GL_SEPARABLE_2D,   GL_CONVOLUTION_FILTER_SCALE, &convolutionFilterScale[2][0]);
    RglGetConvolutionParameterfv( dt, GL_SEPARABLE_2D,   GL_CONVOLUTION_FILTER_BIAS,  &convolutionFilterBias [2][0]);
    RglGetFloatv( dt, GL_POST_CONVOLUTION_RED_SCALE,&postConvolutionRedScale);
    RglGetFloatv( dt, GL_POST_CONVOLUTION_RED_BIAS,&postConvolutionRedBias);
    RglGetFloatv( dt, GL_POST_CONVOLUTION_GREEN_SCALE,&postConvolutionGreenScale);
    RglGetFloatv( dt, GL_POST_CONVOLUTION_GREEN_BIAS,&postConvolutionGreenBias);
    RglGetFloatv( dt, GL_POST_CONVOLUTION_BLUE_SCALE,&postConvolutionBlueScale);
    RglGetFloatv( dt, GL_POST_CONVOLUTION_BLUE_BIAS,&postConvolutionBlueBias);
    RglGetFloatv( dt, GL_POST_CONVOLUTION_ALPHA_SCALE,&postConvolutionAlphaScale);
    RglGetFloatv( dt, GL_POST_CONVOLUTION_ALPHA_BIAS,&postConvolutionAlphaBias);
    RglGetFloatv( dt, GL_POST_COLOR_MATRIX_RED_SCALE,&postColorMatrixRedScale);
    RglGetFloatv( dt, GL_POST_COLOR_MATRIX_RED_BIAS,&postColorMatrixRedBias);
    RglGetFloatv( dt, GL_POST_COLOR_MATRIX_GREEN_SCALE,&postColorMatrixGreenScale);
    RglGetFloatv( dt, GL_POST_COLOR_MATRIX_GREEN_BIAS,&postColorMatrixGreenBias);
    RglGetFloatv( dt, GL_POST_COLOR_MATRIX_BLUE_SCALE,&postColorMatrixBlueScale);
    RglGetFloatv( dt, GL_POST_COLOR_MATRIX_BLUE_BIAS,&postColorMatrixBlueBias);
    RglGetFloatv( dt, GL_POST_COLOR_MATRIX_ALPHA_SCALE,&postColorMatrixAlphaScale);
    RglGetFloatv( dt, GL_POST_COLOR_MATRIX_ALPHA_BIAS,&postColorMatrixAlphaBias);
    histogram = RglIsEnabled( dt, GL_HISTOGRAM);
    minmax = RglIsEnabled( dt, GL_MINMAX);
    RglGetFloatv( dt, GL_ZOOM_X,&zoomX);
    RglGetFloatv( dt, GL_ZOOM_Y,&zoomY);
    return *this;
  }

  template <typename Procs>
  inline const PixelMode &set(Procs &dt) const
  {
    if (valid)
      RglReadBuffer( dt, readBuffer);
    RglPixelTransferi( dt, GL_MAP_COLOR, mapColor);
    RglPixelTransferi( dt, GL_MAP_STENCIL,mapStencil);
    RglPixelTransferi( dt, GL_INDEX_SHIFT,indexShift);
    RglPixelTransferi( dt, GL_INDEX_OFFSET,indexOffset);
    RglPixelTransferf( dt, GL_RED_SCALE,redScale);
    RglPixelTransferf( dt, GL_RED_BIAS,redBias);
    RglPixelTransferf( dt, GL_GREEN_SCALE,greenScale);
    RglPixelTransferf( dt, GL_GREEN_BIAS,greenBias);
    RglPixelTransferf( dt, GL_BLUE_SCALE,blueScale);
    RglPixelTransferf( dt, GL_BLUE_BIAS,blueBias);
    RglPixelTransferf( dt, GL_ALPHA_SCALE,alphaScale);
    RglPixelTransferf( dt, GL_ALPHA_BIAS,alphaBias);
    setEnable(dt,GL_COLOR_TABLE,colorTable);
    setEnable(dt,GL_POST_CONVOLUTION_COLOR_TABLE,postConvolutionColorTable);
    setEnable(dt,GL_POST_COLOR_MATRIX_COLOR_TABLE,postColorMatrixColorTable);
    RglColorTableParameterfv( dt, GL_COLOR_TABLE,                   GL_COLOR_TABLE_SCALE, &colorTableScale[0][0]);
    RglColorTableParameterfv( dt, GL_COLOR_TABLE,                   GL_COLOR_TABLE_BIAS,  &colorTableBias[0][0]);
    RglColorTableParameterfv( dt, GL_POST_CONVOLUTION_COLOR_TABLE,  GL_COLOR_TABLE_SCALE, &colorTableScale[1][0]);
    RglColorTableParameterfv( dt, GL_POST_CONVOLUTION_COLOR_TABLE,  GL_COLOR_TABLE_BIAS,  &colorTableBias[1][0]);
    RglColorTableParameterfv( dt, GL_POST_COLOR_MATRIX_COLOR_TABLE, GL_COLOR_TABLE_SCALE, &colorTableScale[2][0]);
    RglColorTableParameterfv( dt, GL_POST_COLOR_MATRIX_COLOR_TABLE, GL_COLOR_TABLE_BIAS,  &colorTableBias[2][0]);
    setEnable(dt,GL_CONVOLUTION_1D,convolution1d);
    setEnable(dt,GL_CONVOLUTION_2D,convolution2d);
    setEnable(dt,GL_SEPARABLE_2D,separable2d);
    RglConvolutionParameterfv( dt, GL_CONVOLUTION_1D, GL_CONVOLUTION_BORDER_COLOR, &convolutionBorderColor[0][0]);
    RglConvolutionParameteri( dt, GL_CONVOLUTION_1D, GL_CONVOLUTION_BORDER_MODE,   convolutionBorderMode [0]);
    RglConvolutionParameterfv( dt, GL_CONVOLUTION_1D, GL_CONVOLUTION_FILTER_SCALE, &convolutionFilterScale[0][0]);
    RglConvolutionParameterfv( dt, GL_CONVOLUTION_1D, GL_CONVOLUTION_FILTER_BIAS,  &convolutionFilterBias [0][0]);
    RglConvolutionParameterfv( dt, GL_CONVOLUTION_2D, GL_CONVOLUTION_BORDER_COLOR, &convolutionBorderColor[1][0]);
    RglConvolutionParameteri( dt, GL_CONVOLUTION_2D, GL_CONVOLUTION_BORDER_MODE,   convolutionBorderMode [1]);
    RglConvolutionParameterfv( dt, GL_CONVOLUTION_2D, GL_CONVOLUTION_FILTER_SCALE, &convolutionFilterScale[1][0]);
    RglConvolutionParameterfv( dt, GL_CONVOLUTION_2D, GL_CONVOLUTION_FILTER_BIAS,  &convolutionFilterBias [1][0]);
    RglConvolutionParameterfv( dt, GL_SEPARABLE_2D,   GL_CONVOLUTION_BORDER_COLOR, &convolutionBorderColor[2][0]);
    RglConvolutionParameteri( dt, GL_SEPARABLE_2D,   GL_CONVOLUTION_BORDER_MODE,   convolutionBorderMode [2]);
    RglConvolutionParameterfv( dt, GL_SEPARABLE_2D,   GL_CONVOLUTION_FILTER_SCALE, &convolutionFilterScale[2][0]);
    RglConvolutionParameterfv( dt, GL_SEPARABLE_2D,   GL_CONVOLUTION_FILTER_BIAS,  &convolutionFilterBias [2][0]);
    RglPixelTransferf( dt, GL_POST_CONVOLUTION_RED_SCALE,   postConvolutionRedScale);
    RglPixelTransferf( dt, GL_POST_CONVOLUTION_RED_BIAS,    postConvolutionRedBias);
    RglPixelTransferf( dt, GL_POST_CONVOLUTION_GREEN_SCALE, postConvolutionGreenScale);
    RglPixelTransferf( dt, GL_POST_CONVOLUTION_GREEN_BIAS,  postConvolutionGreenBias);
    RglPixelTransferf( dt, GL_POST_CONVOLUTION_BLUE_SCALE,  postConvolutionBlueScale);
    RglPixelTransferf( dt, GL_POST_CONVOLUTION_BLUE_BIAS,   postConvolutionBlueBias);
    RglPixelTransferf( dt, GL_POST_CONVOLUTION_ALPHA_SCALE, postConvolutionAlphaScale);
    RglPixelTransferf( dt, GL_POST_CONVOLUTION_ALPHA_BIAS,  postConvolutionAlphaBias);
    RglPixelTransferf( dt, GL_POST_COLOR_MATRIX_RED_SCALE,  postColorMatrixRedScale);
    RglPixelTransferf( dt, GL_POST_COLOR_MATRIX_RED_BIAS,   postColorMatrixRedBias);
    RglPixelTransferf( dt, GL_POST_COLOR_MATRIX_GREEN_SCALE,postColorMatrixGreenScale);
    RglPixelTransferf( dt, GL_POST_COLOR_MATRIX_GREEN_BIAS, postColorMatrixGreenBias);
    RglPixelTransferf( dt, GL_POST_COLOR_MATRIX_BLUE_SCALE, postColorMatrixBlueScale);
    RglPixelTransferf( dt, GL_POST_COLOR_MATRIX_BLUE_BIAS,  postColorMatrixBlueBias);
    RglPixelTransferf( dt, GL_POST_COLOR_MATRIX_ALPHA_SCALE,postColorMatrixAlphaScale);
    RglPixelTransferf( dt, GL_POST_COLOR_MATRIX_ALPHA_BIAS, postColorMatrixAlphaBias);
    setEnable(dt,GL_HISTOGRAM,histogram);
    setEnable(dt,GL_MINMAX,minmax);
    RglPixelZoom( dt, zoomX,zoomY);
    return *this;
  }

  inline std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    if (valid)
      tmp << print_string("glReadBuffer(",Token::toString(readBuffer),");",delim);
    else
      tmp << print_string("glReadBuffer( *not valid* );",delim);
    tmp << print_string("glPixelTransferi(GL_MAP_COLOR,   ",mapColor,   ");",delim);
    tmp << print_string("glPixelTransferi(GL_MAP_STENCIL, ",mapStencil, ");",delim);
    tmp << print_string("glPixelTransferi(GL_INDEX_SHIFT, ",indexShift, ");",delim);
    tmp << print_string("glPixelTransferi(GL_INDEX_OFFSET,",indexOffset,");",delim);
    tmp << print_string("glPixelTransferf(GL_RED_SCALE,   ",redScale,   ");",delim);
    tmp << print_string("glPixelTransferf(GL_RED_BIAS,    ",redBias,    ");",delim);
    tmp << print_string("glPixelTransferf(GL_GREEN_SCALE, ",greenScale, ");",delim);
    tmp << print_string("glPixelTransferf(GL_GREEN_BIAS,  ",greenBias,  ");",delim);
    tmp << print_string("glPixelTransferf(GL_BLUE_SCALE,  ",blueScale,  ");",delim);
    tmp << print_string("glPixelTransferf(GL_BLUE_BIAS,   ",blueBias,   ");",delim);
    tmp << print_string("glPixelTransferf(GL_ALPHA_SCALE, ",alphaScale, ");",delim);
    tmp << print_string("glPixelTransferf(GL_ALPHA_BIAS,  ",alphaBias,  ");",delim);
    enableToString(tmp, colorTable, "GL_COLOR_TABLE",delim);
    enableToString(tmp, postConvolutionColorTable, "GL_POST_CONVOLUTION_COLOR_TABLE",delim);
    enableToString(tmp, postColorMatrixColorTable, "GL_POST_COLOR_MATRIX_COLOR_TABLE",delim);
    tmp << print_string("glColorTableParameterfv(GL_COLOR_TABLE,                   GL_COLOR_TABLE_SCALE, [",
                        colorTableScale[0][0],",", colorTableScale[0][1],",",
                        colorTableScale[0][2],",", colorTableScale[0][3],"]);",delim);
    tmp << print_string("glColorTableParameterfv(GL_COLOR_TABLE,                   GL_COLOR_TABLE_BIAS,  [",
                        colorTableBias[0][0],",", colorTableBias[0][1],",",
                        colorTableBias[0][2],",", colorTableBias[0][3],"]);",delim);
    tmp << print_string("glColorTableParameterfv(GL_POST_CONVOLUTION_COLOR_TABLE,  GL_COLOR_TABLE_SCALE,",
                        colorTableScale[1][0],",", colorTableScale[1][1],",",
                        colorTableScale[1][2],",", colorTableScale[1][3],"]);",delim);
    tmp << print_string("glColorTableParameterfv(GL_POST_CONVOLUTION_COLOR_TABLE,  GL_COLOR_TABLE_BIAS, ",
                        colorTableBias[1][0],",", colorTableBias[1][1],",",
                        colorTableBias[1][2],",", colorTableBias[1][3],"]);",delim);
    tmp << print_string("glColorTableParameterfv(GL_POST_COLOR_MATRIX_COLOR_TABLE, GL_COLOR_TABLE_SCALE,",
                        colorTableScale[2][0],",", colorTableScale[2][1],",",
                        colorTableScale[2][2],",", colorTableScale[2][3],"]);",delim);
    tmp << print_string("glColorTableParameterfv(GL_POST_COLOR_MATRIX_COLOR_TABLE, GL_COLOR_TABLE_BIAS, ",
                        colorTableBias[2][0],",", colorTableBias[2][1],",",
                        colorTableBias[2][2],",", colorTableBias[2][3],"]);",delim);
    enableToString(tmp, convolution1d, "GL_CONVOLUTION_1D",delim);
    enableToString(tmp, convolution2d, "GL_CONVOLUTION_2D",delim);
    enableToString(tmp, separable2d, "GL_SEPARABLE_2D",delim);
    tmp << print_string("glConvolutionParameterfv(GL_CONVOLUTION_1D, GL_CONVOLUTION_BORDER_COLOR, ",
                        convolutionBorderColor[0][0],",", convolutionBorderColor[0][1],",",
                        convolutionBorderColor[0][2],",", convolutionBorderColor[0][3],"]);",delim);
    tmp << print_string("glConvolutionParameteri (GL_CONVOLUTION_1D, GL_CONVOLUTION_BORDER_MODE,  ",
                        Token::toString(convolutionBorderMode[0]),");",delim);
    tmp << print_string("glConvolutionParameterfv(GL_CONVOLUTION_1D, GL_CONVOLUTION_FILTER_SCALE, ",
                        convolutionFilterScale[0][0],",", convolutionFilterScale[0][1],",",
                        convolutionFilterScale[0][2],",", convolutionFilterScale[0][3],"]);",delim);
    tmp << print_string("glConvolutionParameterfv(GL_CONVOLUTION_1D, GL_CONVOLUTION_FILTER_BIAS,  ",
                        convolutionFilterBias[0][0],",", convolutionFilterBias[0][1],",",
                        convolutionFilterBias[0][2],",", convolutionFilterBias[0][3],"]);",delim);
    tmp << print_string("glConvolutionParameterfv(GL_CONVOLUTION_2D, GL_CONVOLUTION_BORDER_COLOR, ",
                        convolutionBorderColor[1][0],",", convolutionBorderColor[1][1],",",
                        convolutionBorderColor[1][2],",", convolutionBorderColor[1][3],"]);",delim);
    tmp << print_string("glConvolutionParameteri (GL_CONVOLUTION_2D, GL_CONVOLUTION_BORDER_MODE,  ",
                        Token::toString(convolutionBorderMode[1]),");",delim);
    tmp << print_string("glConvolutionParameterfv(GL_CONVOLUTION_2D, GL_CONVOLUTION_FILTER_SCALE, ",
                        convolutionFilterScale[1][0],",", convolutionFilterScale[1][1],",",
                        convolutionFilterScale[1][2],",", convolutionFilterScale[1][3],"]);",delim);
    tmp << print_string("glConvolutionParameterfv(GL_CONVOLUTION_2D, GL_CONVOLUTION_FILTER_BIAS,  ",
                        convolutionFilterBias[1][0],",", convolutionFilterBias[1][1],",",
                        convolutionFilterBias[1][2],",", convolutionFilterBias[1][3],"]);",delim);
    tmp << print_string("glConvolutionParameterfv(GL_SEPARABLE_2D,   GL_CONVOLUTION_BORDER_COLOR, ",
                        convolutionBorderColor[2][0],",", convolutionBorderColor[2][1],",",
                        convolutionBorderColor[2][2],",", convolutionBorderColor[2][3],"]);",delim);
    tmp << print_string("glConvolutionParameteri (GL_SEPARABLE_2D,   GL_CONVOLUTION_BORDER_MODE,  ",
                        Token::toString(convolutionBorderMode[2]),");",delim);
    tmp << print_string("glConvolutionParameterfv(GL_SEPARABLE_2D,   GL_CONVOLUTION_FILTER_SCALE, ",
                        convolutionFilterScale[2][0],",", convolutionFilterScale[2][1],",",
                        convolutionFilterScale[2][2],",", convolutionFilterScale[2][3],"]);",delim);
    tmp << print_string("glConvolutionParameterfv(GL_SEPARABLE_2D,   GL_CONVOLUTION_FILTER_BIAS,  ",
                        convolutionFilterBias[2][0],",", convolutionFilterBias[2][1],",",
                        convolutionFilterBias[2][2],",", convolutionFilterBias[2][3],"]);",delim);
    tmp << print_string("glPixelTransferf(GL_POST_CONVOLUTION_RED_SCALE,   ",postConvolutionRedScale,  ");",delim);
    tmp << print_string("glPixelTransferf(GL_POST_CONVOLUTION_RED_BIAS,    ",postConvolutionRedBias,   ");",delim);
    tmp << print_string("glPixelTransferf(GL_POST_CONVOLUTION_GREEN_SCALE, ",postConvolutionGreenScale,");",delim);
    tmp << print_string("glPixelTransferf(GL_POST_CONVOLUTION_GREEN_BIAS,  ",postConvolutionGreenBias, ");",delim);
    tmp << print_string("glPixelTransferf(GL_POST_CONVOLUTION_BLUE_SCALE,  ",postConvolutionBlueScale, ");",delim);
    tmp << print_string("glPixelTransferf(GL_POST_CONVOLUTION_BLUE_BIAS,   ",postConvolutionBlueBias,  ");",delim);
    tmp << print_string("glPixelTransferf(GL_POST_CONVOLUTION_ALPHA_SCALE, ",postConvolutionAlphaScale,");",delim);
    tmp << print_string("glPixelTransferf(GL_POST_CONVOLUTION_ALPHA_BIAS,  ",postConvolutionAlphaBias, ");",delim);
    tmp << print_string("glPixelTransferf(GL_POST_COLOR_MATRIX_RED_SCALE,  ",postColorMatrixRedScale,  ");",delim);
    tmp << print_string("glPixelTransferf(GL_POST_COLOR_MATRIX_RED_BIAS,   ",postColorMatrixRedBias,   ");",delim);
    tmp << print_string("glPixelTransferf(GL_POST_COLOR_MATRIX_GREEN_SCALE,",postColorMatrixGreenScale,");",delim);
    tmp << print_string("glPixelTransferf(GL_POST_COLOR_MATRIX_GREEN_BIAS, ",postColorMatrixGreenBias, ");",delim);
    tmp << print_string("glPixelTransferf(GL_POST_COLOR_MATRIX_BLUE_SCALE, ",postColorMatrixBlueScale, ");",delim);
    tmp << print_string("glPixelTransferf(GL_POST_COLOR_MATRIX_BLUE_BIAS,  ",postColorMatrixBlueBias,  ");",delim);
    tmp << print_string("glPixelTransferf(GL_POST_COLOR_MATRIX_ALPHA_SCALE,",postColorMatrixAlphaScale,");",delim);
    tmp << print_string("glPixelTransferf(GL_POST_COLOR_MATRIX_ALPHA_BIAS, ",postColorMatrixAlphaBias, ");",delim);
    enableToString(tmp, histogram, "GL_HISTOGRAM",delim);
    enableToString(tmp, minmax, "GL_MINMAX",delim);
    tmp << print_string("glPixelZoom(",zoomX,",",zoomY,");",delim);
    return tmp.str();
  }

  template <typename T> void glColorTableParameterv( GLenum target, GLenum pname, const T *params )
  {
    int index;
    switch (target)
    {
      case GL_COLOR_TABLE:
        index = 0;
        break;
      case GL_POST_CONVOLUTION_COLOR_TABLE:
        index = 1;
        break;
      case GL_POST_COLOR_MATRIX_COLOR_TABLE:
        index = 2;
        break;
      default:
        return;
    }
    GLfloat *p = NULL;
    switch (pname)
    {
      case GL_COLOR_TABLE_SCALE:
        p = &colorTableScale[index][0];
        break;
      case GL_COLOR_TABLE_BIAS:
        p = &colorTableBias[index][0];
        break;
      default:
        return;
    }
    RegalAssert(p);
    for (size_t ii=0; ii<4; ii++)
      p[ii] = static_cast<GLfloat>(params[ii]);
  }

  template <typename T> void glConvolutionParameter( GLenum target, GLenum pname, const T param )
  {
    if (pname == GL_CONVOLUTION_BORDER_MODE)
    {
      switch (target)
      {
        case GL_CONVOLUTION_1D:
          convolutionBorderMode[0] = static_cast<GLenum>(param);
          break;
        case GL_CONVOLUTION_2D:
          convolutionBorderMode[1] = static_cast<GLenum>(param);
          break;
        case GL_SEPARABLE_2D:
          convolutionBorderMode[2] = static_cast<GLenum>(param);
          break;
        default:
          break;
      }
    }
  }

  template <typename T> void glConvolutionParameterv( GLenum target, GLenum pname, const T *params )
  {
    int index;
    switch (target)
    {
      case GL_CONVOLUTION_1D:
        index = 0;
        break;
      case GL_CONVOLUTION_2D:
        index = 1;
        break;
      case GL_SEPARABLE_2D:
        index = 2;
        break;
      default:
        return;
    }
    GLfloat *p = NULL;
    switch (pname)
    {
      case GL_CONVOLUTION_BORDER_COLOR:
        p = &convolutionBorderColor[index][0];
        break;
      case GL_CONVOLUTION_FILTER_SCALE:
        p = &convolutionFilterScale[index][0];
        break;
      case GL_CONVOLUTION_FILTER_BIAS:
        p = &convolutionFilterBias[index][0];
        break;
      default:
        return;
    }
    RegalAssert(p);
    for (size_t ii=0; ii<4; ii++)
      p[ii] = static_cast<GLfloat>(params[ii]);
  }

  template <typename T> void glPixelTransfer( GLenum pname, T value )
  {
    switch (pname)
    {
      case GL_MAP_COLOR:
        mapColor                  = value ? GL_TRUE : GL_FALSE;
        break;
      case GL_MAP_STENCIL:
        mapStencil                = value ? GL_TRUE : GL_FALSE;
        break;
      case GL_INDEX_SHIFT:
        indexShift                = static_cast<GLint>(value);
        break;
      case GL_INDEX_OFFSET:
        indexOffset               = static_cast<GLint>(value);
        break;
      case GL_RED_SCALE:
        redScale                  = static_cast<GLfloat>(value);
        break;
      case GL_RED_BIAS:
        redBias                   = static_cast<GLfloat>(value);
        break;
      case GL_GREEN_SCALE:
        greenScale                = static_cast<GLfloat>(value);
        break;
      case GL_GREEN_BIAS:
        greenBias                 = static_cast<GLfloat>(value);
        break;
      case GL_BLUE_SCALE:
        blueScale                 = static_cast<GLfloat>(value);
        break;
      case GL_BLUE_BIAS:
        blueBias                  = static_cast<GLfloat>(value);
        break;
      case GL_ALPHA_SCALE:
        alphaScale                = static_cast<GLfloat>(value);
        break;
      case GL_ALPHA_BIAS:
        alphaBias                 = static_cast<GLfloat>(value);
        break;
      case GL_POST_CONVOLUTION_RED_SCALE:
        postConvolutionRedScale   = static_cast<GLfloat>(value);
        break;
      case GL_POST_CONVOLUTION_RED_BIAS:
        postConvolutionRedBias    = static_cast<GLfloat>(value);
        break;
      case GL_POST_CONVOLUTION_GREEN_SCALE:
        postConvolutionGreenScale = static_cast<GLfloat>(value);
        break;
      case GL_POST_CONVOLUTION_GREEN_BIAS:
        postConvolutionGreenBias  = static_cast<GLfloat>(value);
        break;
      case GL_POST_CONVOLUTION_BLUE_SCALE:
        postConvolutionBlueScale  = static_cast<GLfloat>(value);
        break;
      case GL_POST_CONVOLUTION_BLUE_BIAS:
        postConvolutionBlueBias   = static_cast<GLfloat>(value);
        break;
      case GL_POST_CONVOLUTION_ALPHA_SCALE:
        postConvolutionAlphaScale = static_cast<GLfloat>(value);
        break;
      case GL_POST_CONVOLUTION_ALPHA_BIAS:
        postConvolutionAlphaBias  = static_cast<GLfloat>(value);
        break;
      case GL_POST_COLOR_MATRIX_RED_SCALE:
        postColorMatrixRedScale   = static_cast<GLfloat>(value);
        break;
      case GL_POST_COLOR_MATRIX_RED_BIAS:
        postColorMatrixRedBias    = static_cast<GLfloat>(value);
        break;
      case GL_POST_COLOR_MATRIX_GREEN_SCALE:
        postColorMatrixGreenScale = static_cast<GLfloat>(value);
        break;
      case GL_POST_COLOR_MATRIX_GREEN_BIAS:
        postColorMatrixGreenBias  = static_cast<GLfloat>(value);
        break;
      case GL_POST_COLOR_MATRIX_BLUE_SCALE:
        postColorMatrixBlueScale  = static_cast<GLfloat>(value);
        break;
      case GL_POST_COLOR_MATRIX_BLUE_BIAS:
        postColorMatrixBlueBias   = static_cast<GLfloat>(value);
        break;
      case GL_POST_COLOR_MATRIX_ALPHA_SCALE:
        postColorMatrixAlphaScale = static_cast<GLfloat>(value);
        break;
      case GL_POST_COLOR_MATRIX_ALPHA_BIAS:
        postColorMatrixAlphaBias  = static_cast<GLfloat>(value);
        break;
      default:
        break;
    }
  }

  inline void glPixelZoom( GLfloat Zx, GLfloat Zy )
  {
    zoomX = Zx;
    zoomY = Zy;
  }

  void glReadBuffer( GLenum src )
  {
    readBuffer = src;
  }
};

//
// glPushAttrib(GL_LIGHTING_BIT)
//
struct LightingFace
{
  GLfloat ambient[4];      // glMaterialfv GL_AMBIENT
  GLfloat diffuse[4];      // glMaterialfv GL_DIFFUSE
  GLfloat specular[4];     // glMaterialfv GL_SPECULAR
  GLfloat emission[4];     // glMaterialfv GL_EMISSION
  GLfloat shininess;       // glMaterialf  GL_SHININESS
  GLfloat colorIndexes[3]; // glMaterialfv GL_COLOR_INDEXES

  inline LightingFace()
    : shininess(0)
  {
    ambient[0] = 0.2f;
    ambient[1] = 0.2f;
    ambient[2] = 0.2f;
    ambient[3] = 1.0f;

    diffuse[0] = 0.8f;
    diffuse[1] = 0.8f;
    diffuse[2] = 0.8f;
    diffuse[3] = 1.0f;

    specular[0] = 0.0f;
    specular[1] = 0.0f;
    specular[2] = 0.0f;
    specular[3] = 1.0f;

    emission[0] = 0.0f;
    emission[1] = 0.0f;
    emission[2] = 0.0f;
    emission[3] = 1.0f;

    colorIndexes[0] = 0.0f;
    colorIndexes[1] = 1.0f;
    colorIndexes[2] = 1.0f;
  }

  inline LightingFace &swap(LightingFace &other)
  {
    std::swap_ranges(ambient,ambient+4,other.ambient);
    std::swap_ranges(diffuse,diffuse+4,other.diffuse);
    std::swap_ranges(specular,specular+4,other.specular);
    std::swap_ranges(emission,emission+4,other.emission);
    std::swap(shininess,other.shininess);
    std::swap_ranges(colorIndexes,colorIndexes+3,other.colorIndexes);
    return *this;
  }

  template <typename Procs>
  inline LightingFace &get(Procs &dt, GLenum face)
  {
    RglGetMaterialfv( dt, face, GL_AMBIENT,       ambient);
    RglGetMaterialfv( dt, face, GL_DIFFUSE,       diffuse);
    RglGetMaterialfv( dt, face, GL_SPECULAR,      specular);
    RglGetMaterialfv( dt, face, GL_EMISSION,      emission);
    RglGetMaterialfv( dt, face, GL_SHININESS,     &shininess);
    RglGetMaterialfv( dt, face, GL_COLOR_INDEXES, colorIndexes);
    return *this;
  }

  template <typename Procs>
  inline const LightingFace &set(Procs &dt, GLenum face) const
  {
    RglMaterialfv( dt, face, GL_AMBIENT,       ambient);
    RglMaterialfv( dt, face, GL_DIFFUSE,       diffuse);
    RglMaterialfv( dt, face, GL_SPECULAR,      specular);
    RglMaterialfv( dt, face, GL_EMISSION,      emission);
    RglMaterialf( dt, face, GL_SHININESS,     shininess);
    RglMaterialfv( dt, face, GL_COLOR_INDEXES, colorIndexes);
    return *this;
  }

  inline std::string toString(GLenum face,const char *delim = "\n") const
  {
    string_list tmp;
    tmp << print_string("glMaterialfv(",Token::toString(face),",GL_AMBIENT,[",
                        ambient[0],",", ambient[1],",", ambient[2],",", ambient[3],"]);",delim);
    tmp << print_string("glMaterialfv(",Token::toString(face),",GL_DIFFUSE,[",
                        diffuse[0],",", diffuse[1],",", diffuse[2],",", diffuse[3],"]);",delim);
    tmp << print_string("glMaterialfv(",Token::toString(face),",GL_SPECULAR,[",
                        specular[0],",", specular[1],",", specular[2],",", specular[3],"]);",delim);
    tmp << print_string("glMaterialfv(",Token::toString(face),",GL_EMISSION,[",
                        emission[0],",", emission[1],",", emission[2],",", emission[3],"]);",delim);
    tmp << print_string("glMaterialf(",Token::toString(face),",GL_SHININESS,",shininess,");",delim);
    tmp << print_string("glMaterialfv(",Token::toString(face),",GL_COLOR_INDEXES,[",
                        colorIndexes[0],",", colorIndexes[1],",", colorIndexes[2],"]);",delim);
    return tmp.str();
  }
};

struct LightingLight
{
  GLboolean     enabled;              // GL_LIGHTi enabled
  GLfloat       ambient[4];           // glLightfv GL_AMBIENT
  GLfloat       diffuse[4];           // glLightfv GL_DIFFUSE
  GLfloat       specular[4];          // glLightfv GL_SPECULAR
  GLfloat       position[4];          // glLightfv GL_POSITION
  GLfloat       constantAttenuation;  // glLightf  GL_CONSTANT_ATTENUATION
  GLfloat       linearAttenuation;    // glLightf  GL_LINEAR_ATTENUATION
  GLfloat       quadraticAttenuation; // glLightf  GL_QUADRATIC_ATTENUATION
  GLfloat       spotDirection[3];     // glLightfv GL_SPOT_DIRECTION
  GLfloat       spotExponent;         // glLightf  GL_SPOT_EXPONENT
  GLfloat       spotCutoff;           // glLightf  GL_SPOT_CUTOFF

  LightingLight()
    : enabled(GL_FALSE)
    , constantAttenuation(1)
    , linearAttenuation(0)
    , quadraticAttenuation(0)
    , spotExponent(0)
    , spotCutoff(180)
  {
    ambient[0] = 0.0f;
    ambient[1] = 0.0f;
    ambient[2] = 0.0f;
    ambient[3] = 1.0f;

    diffuse[0] = 0.0f;
    diffuse[1] = 0.0f;
    diffuse[2] = 0.0f;
    diffuse[3] = 1.0f;

    specular[0] = 0.0f;
    specular[1] = 0.0f;
    specular[2] = 0.0f;
    specular[3] = 1.0f;

    position[0] = 0.0f;
    position[1] = 0.0f;
    position[2] = 1.0f;
    position[3] = 0.0f;

    spotDirection[0] =  0.0f;
    spotDirection[1] =  0.0f;
    spotDirection[2] = -1.0f;
  }

  inline LightingLight &swap(LightingLight &other)
  {
    std::swap(enabled,other.enabled);
    std::swap_ranges(ambient,ambient+4,other.ambient);
    std::swap_ranges(diffuse,diffuse+4,other.diffuse);
    std::swap_ranges(specular,specular+4,other.specular);
    std::swap_ranges(position,position+4,other.position);
    std::swap(constantAttenuation,other.constantAttenuation);
    std::swap(linearAttenuation,other.linearAttenuation);
    std::swap(quadraticAttenuation,other.quadraticAttenuation);
    std::swap_ranges(spotDirection,spotDirection+3,other.spotDirection);
    std::swap(spotExponent,other.spotExponent);
    std::swap(spotCutoff,other.spotCutoff);
    return *this;
  }

  template <typename Procs>
  inline LightingLight &get(Procs &dt, GLenum light)
  {
    enabled = RglIsEnabled( dt, light);
    RglGetLightfv( dt, light, GL_AMBIENT,               ambient);
    RglGetLightfv( dt, light, GL_DIFFUSE,               diffuse);
    RglGetLightfv( dt, light, GL_SPECULAR,              specular);
    RglGetLightfv( dt, light, GL_POSITION,              position);
    RglGetLightfv( dt, light, GL_CONSTANT_ATTENUATION,  &constantAttenuation);
    RglGetLightfv( dt, light, GL_LINEAR_ATTENUATION,    &linearAttenuation);
    RglGetLightfv( dt, light, GL_QUADRATIC_ATTENUATION, &quadraticAttenuation);
    RglGetLightfv( dt, light, GL_SPOT_DIRECTION,        spotDirection);
    RglGetLightfv( dt, light, GL_SPOT_EXPONENT,         &spotExponent);
    RglGetLightfv( dt, light, GL_SPOT_CUTOFF,           &spotCutoff);
    return *this;
  }

  template <typename Procs>
  inline const LightingLight &set(Procs &dt, GLenum light) const
  {
    setEnable(dt,light,enabled);
    RglLightfv( dt, light, GL_AMBIENT,               ambient);
    RglLightfv( dt, light, GL_DIFFUSE,               diffuse);
    RglLightfv( dt, light, GL_SPECULAR,              specular);
    RglLightfv( dt, light, GL_POSITION,              position);
    RglLightf( dt, light, GL_CONSTANT_ATTENUATION,  constantAttenuation);
    RglLightf( dt, light, GL_LINEAR_ATTENUATION,    linearAttenuation);
    RglLightf( dt, light, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
    RglLightfv( dt, light, GL_SPOT_DIRECTION,        spotDirection);
    RglLightf( dt, light, GL_SPOT_EXPONENT,         spotExponent);
    RglLightf( dt, light, GL_SPOT_CUTOFF,           spotCutoff);
    return *this;
  }

  void toString(string_list &tmp, GLenum light, const char *delim = "\n") const
  {
    tmp << print_string(enabled ? "glEnable(" : "glDisable(",Token::toString(light),");",delim);
    tmp << print_string("glLightfv(",Token::toString(light),",GL_AMBIENT,[",
                        ambient[0],",", ambient[1],",", ambient[2],",", ambient[3],"]);",delim);
    tmp << print_string("glLightfv(",Token::toString(light),",GL_DIFFUSE,[",
                        diffuse[0],",", diffuse[1],",", diffuse[2],",", diffuse[3],"]);",delim);
    tmp << print_string("glLightfv(",Token::toString(light),",GL_SPECULAR,[",
                        specular[0],",", specular[1],",", specular[2],",", specular[3],"]);",delim);
    tmp << print_string("glLightfv(",Token::toString(light),",GL_POSITION,[",
                        position[0],",", position[1],",", position[2],",", position[3],"]);",delim);
    tmp << print_string("glLightf(",Token::toString(light),",GL_CONSTANT_ATTENUATION,",constantAttenuation,");",delim);
    tmp << print_string("glLightf(",Token::toString(light),",GL_LINEAR_ATTENUATION,",linearAttenuation,");",delim);
    tmp << print_string("glLightf(",Token::toString(light),",GL_QUADRATIC_ATTENUATION,",quadraticAttenuation,");",delim);
    tmp << print_string("glLightfv(",Token::toString(light),",GL_SPOT_DIRECTION,[",
                        spotDirection[0],",", spotDirection[1],",", spotDirection[2],"]);",delim);
    tmp << print_string("glLightf(",Token::toString(light),",GL_SPOT_EXPONENT,",spotExponent,");",delim);
    tmp << print_string("glLightf(",Token::toString(light),",GL_SPOT_CUTOFF,",spotCutoff,");",delim);
  }
};

struct Lighting
{
  GLenum        shadeModel;                              // GL_SHADE_MODEL
  GLenum        clampVertexColor;                        // GL_CLAMP_VERTEX_COLOR
  GLenum        provokingVertex;                         // GL_PROVOKING_VERTEX
  GLboolean     lighting;                                // GL_LIGHTING
  GLboolean     colorMaterial;                           // GL_COLOR_MATERIAL
  GLenum        colorMaterialParameter;                  // GL_COLOR_MATERIAL_PARAMETER
  GLenum        colorMaterialFace;                       // GL_COLOR_MATERIAL_FACE
  LightingFace  front;                                   // GL_FRONT
  LightingFace  back;                                    // GL_BACK
  GLfloat       lightModelAmbient[4];                    // GL_LIGHT_MODEL_AMBIENT
  GLboolean     lightModelLocalViewer;                   // GL_LIGHT_MODEL_LOCAL_VIEWER
  GLboolean     lightModelTwoSide;                       // GL_LIGHT_MODEL_TWO_SIDE
  GLenum        lightModelColorControl;                  // GL_LIGHT_MODEL_COLOR_CONTROL
  LightingLight lights[REGAL_FIXED_FUNCTION_MAX_LIGHTS]; // GL_LIGHTi

  Lighting()
    : shadeModel(GL_SMOOTH)
    , clampVertexColor(GL_TRUE)
    , provokingVertex(GL_LAST_VERTEX_CONVENTION)
    , lighting(GL_FALSE)
    , colorMaterial(GL_FALSE)
    , colorMaterialParameter(GL_AMBIENT_AND_DIFFUSE)
    , colorMaterialFace(GL_FRONT_AND_BACK)
    , lightModelLocalViewer(GL_FALSE)
    , lightModelTwoSide(GL_FALSE)
    , lightModelColorControl(GL_SINGLE_COLOR)
  {
    lightModelAmbient[0] = 0.2f;
    lightModelAmbient[1] = 0.2f;
    lightModelAmbient[2] = 0.2f;
    lightModelAmbient[3] = 1.0f;

    size_t n = array_size( lights );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( lights, ii );
      lights[ii] = LightingLight();
    }

    lights[0].diffuse[0] = 1.0f;
    lights[0].diffuse[1] = 1.0f;
    lights[0].diffuse[2] = 1.0f;

    lights[0].specular[0] = 1.0f;
    lights[0].specular[1] = 1.0f;
    lights[0].specular[2] = 1.0f;
  }

  Lighting &swap(Lighting &other)
  {
    std::swap(shadeModel,other.shadeModel);
    std::swap(clampVertexColor,other.clampVertexColor);
    std::swap(provokingVertex,other.provokingVertex);
    std::swap(lighting,other.lighting);
    std::swap(colorMaterial,other.colorMaterial);
    std::swap(colorMaterialParameter,other.colorMaterialParameter);
    std::swap(colorMaterialFace,other.colorMaterialFace);
    front.swap(other.front);
    back.swap(other.back);
    std::swap_ranges(lightModelAmbient,lightModelAmbient+4,other.lightModelAmbient);
    std::swap(lightModelLocalViewer,other.lightModelLocalViewer);
    std::swap(lightModelTwoSide,other.lightModelTwoSide);
    std::swap(lightModelColorControl,other.lightModelColorControl);
    size_t n = array_size( lights );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( lights, ii );
      lights[ii].swap(other.lights[ii]);
    }
    return *this;
  }

  template <typename Procs>
  Lighting &get(Procs &dt)
  {
    RglGetIntegerv( dt, GL_SHADE_MODEL,reinterpret_cast<GLint *>(&shadeModel));
    RglGetIntegerv( dt, GL_CLAMP_VERTEX_COLOR,reinterpret_cast<GLint *>(&clampVertexColor));
    RglGetIntegerv( dt, GL_PROVOKING_VERTEX,reinterpret_cast<GLint *>(&provokingVertex));
    lighting = RglIsEnabled( dt, GL_LIGHTING);
    colorMaterial = RglIsEnabled( dt, GL_COLOR_MATERIAL);
    RglGetIntegerv( dt, GL_COLOR_MATERIAL_PARAMETER,reinterpret_cast<GLint *>(&colorMaterialParameter));
    RglGetIntegerv( dt, GL_COLOR_MATERIAL_FACE,reinterpret_cast<GLint *>(&colorMaterialFace));
    front.get(dt,GL_FRONT);
    back.get(dt,GL_BACK);
    RglGetFloatv( dt, GL_LIGHT_MODEL_AMBIENT,lightModelAmbient);
    RglGetBooleanv( dt, GL_LIGHT_MODEL_LOCAL_VIEWER,&lightModelLocalViewer);
    RglGetBooleanv( dt, GL_LIGHT_MODEL_TWO_SIDE,&lightModelTwoSide);
    RglGetIntegerv( dt, GL_LIGHT_MODEL_COLOR_CONTROL,reinterpret_cast<GLint *>(&lightModelColorControl));
    size_t n = array_size( lights );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( lights, ii );
      lights[ii].get(dt,static_cast<GLenum>(GL_LIGHT0+ii));
    }
    return *this;
  }

  template <typename Procs>
  const Lighting &set(Procs &dt) const
  {
    RglShadeModel( dt, shadeModel);
    RglClampColor( dt, GL_CLAMP_VERTEX_COLOR,clampVertexColor);
    RglProvokingVertex( dt, provokingVertex);
    setEnable(dt,GL_LIGHTING,lighting);
    setEnable(dt,GL_COLOR_MATERIAL,colorMaterial);
    RglColorMaterial( dt, colorMaterialFace,colorMaterialParameter);
    front.set(dt,GL_FRONT);
    back.set(dt,GL_BACK);
    RglLightModelfv( dt, GL_LIGHT_MODEL_AMBIENT,lightModelAmbient);
    RglLightModeli( dt, GL_LIGHT_MODEL_LOCAL_VIEWER,lightModelLocalViewer);
    RglLightModeli( dt, GL_LIGHT_MODEL_TWO_SIDE,lightModelTwoSide);
    RglLightModeli( dt, GL_LIGHT_MODEL_COLOR_CONTROL,lightModelColorControl);
    size_t n = array_size( lights );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( lights, ii );
      lights[ii].set(dt,static_cast<GLenum>(GL_LIGHT0+ii));
    }
    return *this;
  }

  std::string toString(const char *delim = "\n") const
  {
    string_list tmp;
    tmp << print_string("glShadeModel(",Token::toString(shadeModel),");",delim);
    tmp << print_string("glClampColor(GL_CLAMP_VERTEX_COLOR,",Token::toString(clampVertexColor),");",delim);
    tmp << print_string("glProvokingVertex(",Token::toString(provokingVertex),");",delim);
    enableToString(tmp, lighting, "GL_LIGHTING",delim);
    enableToString(tmp, colorMaterial, "GL_COLOR_MATERIAL",delim);
    tmp << print_string("glColorMaterial(",Token::toString(colorMaterialFace),",",Token::toString(colorMaterialParameter),");",delim);
    tmp << front.toString(GL_FRONT,delim);
    tmp << front.toString(GL_BACK,delim);
    tmp << print_string("glLightModelfv(GL_LIGHT_MODEL_AMBIENT,[ ",
                        lightModelAmbient[0],", ",lightModelAmbient[1],", ",
                        lightModelAmbient[2],", ",lightModelAmbient[3]," ]);",delim);
    tmp << print_string("glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,",lightModelLocalViewer,");",delim);
    tmp << print_string("glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,",lightModelTwoSide,");",delim);
    tmp << print_string("glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,",Token::toString(lightModelColorControl),");",delim);
    size_t n = array_size( lights );
    for (size_t ii=0; ii<n; ii++)
    {
      RegalAssertArrayIndex( lights, ii );
      lights[ii].toString(tmp,static_cast<GLenum>(GL_LIGHT0+ii),delim);
    }
    return tmp.str();
  }

  inline void glColorMaterial( GLenum face, GLenum mode )
  {
    colorMaterialFace = face;
    colorMaterialParameter = mode;
  }

  template <typename T> void glLight( GLenum light, GLenum pname, T param )
  {
    GLint ii = static_cast<int>(light-GL_LIGHT0);

    size_t n = array_size( lights );

    if (ii < 0 || static_cast<size_t>(ii) >= n)
      return;

    RegalAssertArrayIndex( lights, ii );
    LightingLight &ll = lights[ii];

    switch (pname)
    {
      case GL_CONSTANT_ATTENUATION:
        ll.constantAttenuation  = static_cast<GLfloat>(param);
        break;
      case GL_LINEAR_ATTENUATION:
        ll.linearAttenuation    = static_cast<GLfloat>(param);
        break;
      case GL_QUADRATIC_ATTENUATION:
        ll.quadraticAttenuation = static_cast<GLfloat>(param);
        break;
      case GL_SPOT_EXPONENT:
        ll.spotExponent         = static_cast<GLfloat>(param);
        break;
      case GL_SPOT_CUTOFF:
        ll.spotCutoff           = static_cast<GLfloat>(param);
        break;
      default:
        break;
    }
  }

  template <typename T> void glLightv( GLenum light, GLenum pname, const T *params )
  {
    size_t ii = static_cast<size_t>(light-GL_LIGHT0);

    size_t n = array_size( lights );

    if (light < GL_LIGHT0 || ii >= n)
      return;

    RegalAssertArrayIndex( lights, ii );
    LightingLight &ll = lights[ii];

    GLfloat *p = NULL;
    switch (pname)
    {
      case GL_AMBIENT:
        p = ll.ambient;
        break;
      case GL_DIFFUSE:
        p = ll.diffuse;
        break;
      case GL_SPECULAR:
        p = ll.specular;
        break;
      case GL_POSITION:
        p = ll.position;
        break;
      case GL_SPOT_DIRECTION:
        p = ll.spotDirection;
        break;
      default:
        return;
    }

    GLuint stop = (pname == GL_SPOT_DIRECTION) ? 3 : 4;
    for (ii=0; ii<stop; ii++)
      p[ii] = static_cast<GLfloat>(params[ii]);
  }

  template <typename T> void glLightModel( GLenum pname, T param )
  {
    switch (pname)
    {
      case GL_LIGHT_MODEL_LOCAL_VIEWER:
        lightModelLocalViewer  = static_cast<GLboolean>(param);
        break;
      case GL_LIGHT_MODEL_TWO_SIDE:
        lightModelTwoSide      = static_cast<GLboolean>(param);
        break;
      case GL_LIGHT_MODEL_COLOR_CONTROL:
        lightModelColorControl = static_cast<GLenum>(param);
        break;
      default:
        break;
    }
  }

  template <typename T> void glLightModelv( GLenum pname, const T *params )
  {
    if (pname==GL_LIGHT_MODEL_AMBIENT)
    {
      lightModelAmbient[0] = static_cast<GLfloat>(params[0]);
      lightModelAmbient[1] = static_cast<GLfloat>(params[1]);
      lightModelAmbient[2] = static_cast<GLfloat>(params[2]);
      lightModelAmbient[3] = static_cast<GLfloat>(params[3]);
    }
  }

  template <typename T> void glMaterial( GLenum face, GLenum pname, T param )
  {
    if (pname == GL_SHININESS)
    {
      switch (face)
      {
        case GL_FRONT:
          front.shininess = static_cast<GLboolean>(param);
          break;
        case GL_BACK:
          back.shininess  = static_cast<GLboolean>(param);
          break;
        case GL_FRONT_AND_BACK:
          front.shininess = back.shininess = static_cast<GLboolean>(param);
          break;
        default:
          break;
      }
    }
  }

  template <typename T> void glMaterialv( GLenum face, GLenum pname, const T *params )
  {
    LightingFace *f[] = { NULL, NULL };

    switch (face)
    {
      case GL_FRONT:
        f[0] = &front;
        break;
      case GL_BACK:
        f[1] = &back;
        break;
      case GL_FRONT_AND_BACK:
        f[0] = &front;
        f[1] = &back;
        break;
      default:
        return;
    }

    for (size_t ii=0; ii<2; ii++)
    {
      if (f[ii])
      {
        GLfloat *p = NULL;
        GLuint   n = 0;
        switch (pname)
        {
          case GL_AMBIENT:
            p = f[ii]->ambient;
            n = 4;
            break;
          case GL_DIFFUSE:
            p = f[ii]->diffuse;
            n = 4;
            break;
          case GL_SPECULAR:
            p = f[ii]->specular;
            n = 4;
            break;
          case GL_EMISSION:
            p = f[ii]->emission;
            n = 4;
            break;
          case GL_SHININESS:
            p = &f[ii]->shininess;
            n = 1;
            break;
          case GL_COLOR_INDEXES:
            p = f[ii]->colorIndexes;
            n = 3;
            break;
          default:
            break;
        }

        if (p)
          for (size_t jj=0; jj<n; jj++)
            p[jj] = static_cast<GLfloat>(params[jj]);
      }
    }
  }

  inline void glProvokingVertex(GLenum provokeMode)
  {
    provokingVertex = provokeMode;
  }

  inline void glShadeModel(GLenum mode)
  {
    shadeModel = mode;
  }
};
}

REGAL_NAMESPACE_END

#endif // REGAL_EMULATION

#endif
