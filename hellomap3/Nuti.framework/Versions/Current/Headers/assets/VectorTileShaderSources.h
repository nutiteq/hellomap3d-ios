#ifndef VECTORTILESHADERSOURCES_H_
#define VECTORTILESHADERSOURCES_H_

#include <assets/ShaderSource.h>

#include <string>

static std::string vectortile_background_vert_glsl = R"GLSL(
attribute vec3 aVertexPosition;

uniform mat4 uMVPMatrix;

void main(void) {
    gl_Position = uMVPMatrix * vec4(aVertexPosition, 1.0);
}
)GLSL";

static std::string vectortile_background_frag_glsl = R"GLSL(
precision mediump float;

uniform lowp vec4 uColor;

void main(void) {
  gl_FragColor = uColor;
}
)GLSL";

static std::string vectortile_backgroundpattern_vert_glsl = R"GLSL(
attribute vec3 aVertexPosition;

uniform mat4 uMVPMatrix;

varying vec2 vUV;

void main(void) {
    vUV = vec2(aVertexPosition[0], aVertexPosition[1]);
    gl_Position = uMVPMatrix * vec4(aVertexPosition, 1.0);
}
)GLSL";

static std::string vectortile_backgroundpattern_frag_glsl = R"GLSL(
precision mediump float;

uniform sampler2D uPattern;
uniform lowp vec4 uColor;

varying vec2 vUV;

void main(void) {
  vec4 patternColor = texture2D(uPattern, vUV);
  gl_FragColor = uColor * (1.0 - patternColor.a) + patternColor;
}
)GLSL";

static std::string vectortile_label_vert_glsl = R"GLSL(
attribute vec3 aVertexPosition;
attribute vec2 aVertexUV;
attribute vec4 aVertexColor;

uniform mat4 uMVPMatrix;

varying lowp vec4 vColor;
varying vec2 vUV;

void main(void) {
    vColor = aVertexColor;
    vUV = aVertexUV;
    gl_Position = uMVPMatrix * vec4(aVertexPosition, 1.0);
}
)GLSL";

static std::string vectortile_label_frag_glsl = R"GLSL(
precision mediump float;

uniform sampler2D uBitmap;

varying lowp vec4 vColor;
varying vec2 vUV;

void main(void) {
  gl_FragColor = texture2D(uBitmap, vUV) * vColor;
}
)GLSL";

static std::string vectortile_line_vert_glsl = R"GLSL(
attribute vec2 aVertexPosition;
attribute vec2 aVertexBinormal;
attribute vec4 aVertexAttribs;

uniform mat4 uMVPMatrix;
uniform float uBinormalScale;
uniform float uHalfResolution;
uniform float uInvHalfResolution;

uniform vec4 uColorTable[32];
uniform float uWidthTable[32];

varying lowp vec4 vColor;
varying highp vec2 vDist;
varying highp float vWidth;

void main(void) {
    int styleIndex = int(aVertexAttribs[0]);
    float width = uWidthTable[styleIndex];
    float roundedWidth = ceil(width * uHalfResolution + 1.0) * uInvHalfResolution;
    vec3 pos = vec3(aVertexPosition + uBinormalScale * roundedWidth * aVertexBinormal, 0.0);
    vColor = uColorTable[styleIndex];
    vDist = vec2(aVertexAttribs[1], aVertexAttribs[2]) * roundedWidth;
    vWidth = width - uInvHalfResolution;
    gl_Position = uMVPMatrix * vec4(pos, 1.0);
}
)GLSL";

static std::string vectortile_line_frag_glsl = R"GLSL(
precision mediump float;

uniform highp float uGamma;

varying lowp vec4 vColor;
varying highp vec2 vDist;
varying highp float vWidth;

void main(void) {
  highp float dist = length(vDist) - vWidth;
  lowp float a = clamp(1.0 - dist * uGamma, 0.0, 1.0);
  gl_FragColor = vColor * a;
}
)GLSL";

static std::string vectortile_linepattern_vert_glsl = R"GLSL(
attribute vec2 aVertexPosition;
attribute vec2 aVertexBinormal;
attribute vec2 aVertexUV;
attribute vec4 aVertexAttribs;

uniform float uUVScale;
uniform float uZoomScale;
uniform float uBinormalScale;
uniform float uHalfResolution;
uniform float uInvHalfResolution;
uniform mat4 uMVPMatrix;

uniform vec4 uColorTable[32];
uniform float uWidthTable[32];

varying lowp vec4 vColor;
varying vec2 vUV;
varying highp vec2 vDist;
varying highp float vWidth;

void main(void) {
    int styleIndex = int(aVertexAttribs[0]);
    float width = uWidthTable[styleIndex];
    float roundedWidth = ceil(width * uHalfResolution + 1.0) * uInvHalfResolution;
    vec3 pos = vec3(aVertexPosition + uBinormalScale * roundedWidth * aVertexBinormal, 0.0);
    vColor = uColorTable[styleIndex];
    vUV = vec2(uZoomScale * uUVScale * aVertexUV[0], uUVScale * aVertexUV[1]);
    vDist = vec2(aVertexAttribs[1], aVertexAttribs[2]) * roundedWidth;
    vWidth = width - uInvHalfResolution;
    gl_Position = uMVPMatrix * vec4(pos, 1.0);
}
)GLSL";

static std::string vectortile_linepattern_frag_glsl = R"GLSL(
precision mediump float;

uniform sampler2D uPattern;
uniform highp float uGamma;

varying lowp vec4 vColor;
varying vec2 vUV;
varying highp vec2 vDist;
varying highp float vWidth;

void main(void) {
  highp float dist = length(vDist) - vWidth;
  lowp float a = clamp(1.0 - dist * uGamma, 0.0, 1.0);
  gl_FragColor = texture2D(uPattern, vUV) * vColor * a;
}
)GLSL";

static std::string vectortile_polygon_vert_glsl = R"GLSL(
attribute vec2 aVertexPosition;
attribute vec4 aVertexAttribs;

uniform mat4 uMVPMatrix;

uniform vec4 uColorTable[32];

varying lowp vec4 vColor;

void main(void) {
    int styleIndex = int(aVertexAttribs[0]);
    vec3 pos = vec3(aVertexPosition, 0.0);
    vColor = uColorTable[styleIndex];
    gl_Position = uMVPMatrix * vec4(pos, 1.0);
}
)GLSL";

static std::string vectortile_polygon_frag_glsl = R"GLSL(
precision mediump float;

varying lowp vec4 vColor;

void main(void) {
  gl_FragColor = vColor;
}
)GLSL";

static std::string vectortile_polygonpattern_vert_glsl = R"GLSL(
attribute vec2 aVertexPosition;
attribute vec2 aVertexUV;
attribute vec4 aVertexAttribs;

uniform float uUVScale;
uniform float uZoomScale;
uniform mat4 uMVPMatrix;

uniform vec4 uColorTable[32];
uniform float uScaleTable[32];

varying lowp vec4 vColor;
varying vec2 vUV;

void main(void) {
    int styleIndex = int(aVertexAttribs[0]);
    vec3 pos = vec3(aVertexPosition, 0.0);
    vColor = uColorTable[styleIndex];
    vUV = uZoomScale * uUVScale * aVertexUV;
    gl_Position = uMVPMatrix * vec4(pos, 1.0);
}
)GLSL";

static std::string vectortile_polygonpattern_frag_glsl = R"GLSL(
precision mediump float;

uniform sampler2D uPattern;

varying lowp vec4 vColor;
varying vec2 vUV;

void main(void) {
  gl_FragColor = texture2D(uPattern, vUV) * vColor;
}
)GLSL";

static std::string vectortile_polygon3d_vert_glsl = R"GLSL(
attribute vec2 aVertexPosition;
attribute vec2 aVertexBinormal;
attribute float aVertexHeight;
attribute vec4 aVertexAttribs;

uniform mat4 uMVPMatrix;
uniform mat3 uTileMatrix;
uniform float uVertexScale;
uniform float uHeightScale;
uniform vec3 uLightDir;

uniform vec4 uColorTable[32];

varying highp vec2 vTilePos;
varying lowp vec4 vColor;
varying mediump float vHeight;

void main(void) {
    int styleIndex = int(aVertexAttribs[0]);
    vec3 pos = vec3(aVertexPosition, aVertexHeight * uHeightScale);
    vec4 color = uColorTable[styleIndex];
    if (aVertexAttribs[1] != 0.0) {
      vec3 binormal = vec3(aVertexBinormal, 0.0);
      color = vec4(color.rgb * (abs(dot(uLightDir, binormal)) * 0.5 + 0.5), color.a);
    }
    vTilePos = (uTileMatrix * vec3(aVertexPosition, 1.0)).xy;
    vColor = color;
    vHeight = aVertexAttribs[2];
    gl_Position = uMVPMatrix * vec4(pos, 1.0);
}
)GLSL";

static std::string vectortile_polygon3d_frag_glsl = R"GLSL(
precision mediump float;

uniform sampler2D uScreen;
uniform highp vec2 uInvScreenSize;

varying highp vec2 vTilePos;
varying lowp vec4 vColor;
varying mediump float vHeight;

void main(void) {
  if (min(vTilePos[0], vTilePos[1]) < -0.01 || max(vTilePos[0], vTilePos[1]) > 1.01) {
    discard;
  }
  lowp vec4 screenColor = texture2D(uScreen, vec2(gl_FragCoord.x * uInvScreenSize.x, gl_FragCoord.y * uInvScreenSize.y));
  gl_FragColor = vec4(screenColor.rgb * (1.0 - vColor.a) + vColor.rgb * (sqrt(vHeight) * 0.75 + 0.25), 1.0);
}
)GLSL";

static unsigned char vectortile_null_prog_data[] = {
    0x89, 0x50, 0x4e};

static std::map<std::string, Nuti::ShaderSource> vectortile_shader_source_map = {
	{ "background",	Nuti::ShaderSource("background", &vectortile_background_vert_glsl, &vectortile_background_frag_glsl, vectortile_null_prog_data, sizeof(vectortile_null_prog_data)) },
	{ "backgroundpattern", Nuti::ShaderSource("backgroundpattern", &vectortile_backgroundpattern_vert_glsl, &vectortile_backgroundpattern_frag_glsl, vectortile_null_prog_data, sizeof(vectortile_null_prog_data)) },
	{ "label", 	Nuti::ShaderSource("label", &vectortile_label_vert_glsl, &vectortile_label_frag_glsl, vectortile_null_prog_data, sizeof(vectortile_null_prog_data)) },
	{ "line", 	Nuti::ShaderSource("line", &vectortile_line_vert_glsl, &vectortile_line_frag_glsl, vectortile_null_prog_data, sizeof(vectortile_null_prog_data)) },
	{ "linepattern",Nuti::ShaderSource("linepattern", &vectortile_linepattern_vert_glsl, &vectortile_linepattern_frag_glsl, vectortile_null_prog_data, sizeof(vectortile_null_prog_data)) },
	{ "polygon", 	Nuti::ShaderSource("polygon", &vectortile_polygon_vert_glsl, &vectortile_polygon_frag_glsl, vectortile_null_prog_data, sizeof(vectortile_null_prog_data)) },
	{ "polygonpattern",Nuti::ShaderSource("polygonpattern", &vectortile_polygonpattern_vert_glsl, &vectortile_polygonpattern_frag_glsl, vectortile_null_prog_data, sizeof(vectortile_null_prog_data)) },
	{ "polygon3d", 	Nuti::ShaderSource("polygon3d", &vectortile_polygon3d_vert_glsl, &vectortile_polygon3d_frag_glsl, vectortile_null_prog_data, sizeof(vectortile_null_prog_data)) },
};

#endif
