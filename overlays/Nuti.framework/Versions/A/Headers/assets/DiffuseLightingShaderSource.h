#ifndef DIFFUSELIGHTINGSHADERSOURCE_H_
#define DIFFUSELIGHTINGSHADERSOURCE_H_

#include <assets/ShaderSource.h>

#include <string>

static std::string diffuse_lighting_vert_glsl =
    "#version 100\n"

    "attribute vec4 a_color;"
    "attribute vec4 a_coord;"
    "attribute vec3 a_normal;"
    "attribute vec2 a_texCoord;"
    "uniform vec4 u_ambientColor;"
    "uniform vec4 u_lightColor;"
    "uniform vec3 u_lightDir;"
    "uniform mat4 u_mvpMat;"
    "varying vec4 v_color;"
    "varying vec2 v_texCoord;"
    "void main() {"
    "   float dotProduct = max(0.0, dot(a_normal, u_lightDir));"
    "	v_color = (u_ambientColor + u_lightColor * dotProduct) * a_color;"
    "   v_texCoord = a_texCoord;"
    "	gl_Position = u_mvpMat * a_coord;"
    "}";

static std::string diffuse_lighting_frag_glsl =
    "#version 100\n"

    "precision mediump float;"

    "uniform sampler2D u_tex;"
    "varying vec4 v_color;"
    "varying vec2 v_texCoord;"
    "void main() {"
    "	vec4 color = texture2D(u_tex, v_texCoord) * v_color;"
    "	if (color.a == 0.0) {"
    "		discard;"
    "	}"
    "	gl_FragColor = color;"
    "}";

static unsigned char diffuse_lighting_prog_data[] = {
    0x89, 0x50, 0x4e};

static unsigned int diffuse_lighting_prog_data_len = 3;

static Nuti::ShaderSource diffuse_lighting_shader_source("diffuse-lighting", &diffuse_lighting_vert_glsl, &diffuse_lighting_frag_glsl,
                                                         diffuse_lighting_prog_data, diffuse_lighting_prog_data_len);

#endif