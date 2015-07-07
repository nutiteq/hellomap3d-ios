#ifndef _NUTI_RASTERTILESHADERSOURCE_H_
#define _NUTI_RASTERTILESHADERSOURCE_H_

#include "ShaderSource.h"

#include <string>

static std::string rastertile_vert_glsl =
    "#version 100\n"
    "attribute vec4 a_coord;"
    "attribute vec2 a_texCoord;"
    "varying vec2 v_texCoord;"
    "uniform mat4 u_mvpMat;"
    "void main() {"
    "	v_texCoord = a_texCoord;"
    "	gl_Position = u_mvpMat * a_coord;"
    "}";

static std::string rastertile_frag_glsl =
    "#version 100\n"
    "precision mediump float;"
    "varying vec2 v_texCoord;"
    "uniform vec4 u_color;"
    "uniform sampler2D u_tex;"
    "void main() {"
    "	vec4 color = texture2D(u_tex, v_texCoord) * u_color;"
    "	gl_FragColor = color;"
    "}";

static Nuti::ShaderSource rastertile_shader_source("rastertile", &rastertile_vert_glsl, &rastertile_frag_glsl);

#endif

