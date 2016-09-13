/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VT_COLOR_H_
#define _NUTI_VT_COLOR_H_

#include <algorithm>

#include <cglib/vec.h>

namespace Nuti { namespace VT {
    class Color {
    public:
        Color() {
            _components[0] = _components[1] = _components[2] = _components[3] = 0;
        }
        
        explicit Color(unsigned int value) {
            _components[0] = ((value >> 16) & 255) * (1.0f / 255.0f);
            _components[1] = ((value >>  8) & 255) * (1.0f / 255.0f);
            _components[2] = ((value >>  0) & 255) * (1.0f / 255.0f);
            _components[3] = ((value >> 24) & 255) * (1.0f / 255.0f);
        }
        
        explicit Color(float r, float g, float b, float a) {
            _components[0] = r;
            _components[1] = g;
            _components[2] = b;
            _components[3] = a;
        }

        float& operator [] (std::size_t i) {
            return _components[i];
        }

        float operator [] (std::size_t i) const {
            return _components[i];
        }

        unsigned int value() const {
            cglib::vec4<unsigned char> components = rgba8();
            unsigned int val = components[3];
            val = (val << 8) | components[0];
            val = (val << 8) | components[1];
            val = (val << 8) | components[2];
            return val;
        }

        unsigned int flippedValue() const {
            cglib::vec4<unsigned char> components = rgba8();
            unsigned int val = components[3];
            val = (val << 8) | components[2];
            val = (val << 8) | components[1];
            val = (val << 8) | components[0];
            return val;
        }

        cglib::vec4<float> rgba() const {
            return cglib::vec4<float>(_components[0], _components[1], _components[2], _components[3]);
        }

        cglib::vec4<unsigned char> rgba8() const {
            cglib::vec4<unsigned char> components8;
            for (std::size_t i = 0; i < 4; i++) {
                float c = std::max(0.0f, std::min(1.0f, _components[i]));
                components8[i] = static_cast<unsigned char>(c * 255.0f + 0.5f);
            }
            return components8;
        }

    private:
        float _components[4]; // rgba
    };

    inline Color operator + (const Color& color1, const Color& color2) {
        return Color(color1[0] + color2[0], color1[1] + color2[1], color1[2] + color2[2], color1[3] + color2[3]);
    }

    inline Color operator - (const Color& color1, const Color& color2) {
        return Color(color1[0] - color2[0], color1[1] - color2[1], color1[2] - color2[2], color1[3] - color2[3]);
    }

    inline Color operator * (const Color& color1, const Color& color2) {
        return Color(color1[0] * color2[0], color1[1] * color2[1], color1[2] * color2[2], color1[3] * color2[3]);
    }

    inline Color operator * (const Color& color1, float c2) {
        return Color(color1[0] * c2, color1[1] * c2, color1[2] * c2, color1[3] * c2);
    }

    inline Color operator * (float c1, const Color& color2) {
        return Color(c1 * color2[0], c1 * color2[1], c1 * color2[2], c1 * color2[3]);
    }

    inline bool operator == (const Color& color1, const Color& color2) {
        return color1.rgba() == color2.rgba();
    }
    
    inline bool operator != (const Color& color1, const Color& color2) {
        return !(color1 == color2);
    }

    inline Color blendColor(const Color& color, float blendFactor) {
        return color * blendFactor;
    }
} }

#endif
