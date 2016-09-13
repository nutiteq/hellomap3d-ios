/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VT_BITMAPCANVAS_H_
#define _NUTI_VT_BITMAPCANVAS_H_

#include "Color.h"
#include "Bitmap.h"

#include <cstdint>
#include <vector>
#include <memory>

namespace Nuti { namespace VT {
    class BitmapCanvas {
    public:
        explicit BitmapCanvas(int width, int height);

        void setOpacity(float opacity);
        void setColor(const Color& color);
        
        void drawPixel(int x, int y, float a);
        void drawRectangle(float x0, float y0, float x1, float y1);
        void drawTriangle(float x0, float y0, float x1, float y1, float x2, float y2);
        void drawEllipse(float x0, float y0, float rx, float ry);

        std::shared_ptr<Bitmap> buildBitmap() const;

    private:

        const int _width;
        const int _height;
        float _opacity = 1.0f;
        std::uint32_t _color = 0xffffffff;
        std::vector<std::uint32_t> _data;
    };
} }

#endif
