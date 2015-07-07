/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_BITMAPCANVAS_H_
#define _NUTI_BITMAPCANVAS_H_

#include "core/ScreenPos.h"
#include "core/ScreenBounds.h"
#include "graphics/Color.h"

#include <memory>
#include <vector>

namespace Nuti {
    class Bitmap;

    /**
     * A canvas class for constructing bitmaps procedurally.
     */
    class BitmapCanvas {
    public:
        enum DrawMode {
            FILL,
            STROKE
        };

        BitmapCanvas(int width, int height);
        virtual ~BitmapCanvas();

        void setDrawMode(DrawMode mode);
        void setColor(const Color& color);
        void setStrokeWidth(float width);
        void setFont(const std::string& name, float size);

        void pushClipRect(const ScreenBounds& clipRect);
        void popClipRect();

        void drawText(std::string text, const ScreenPos& pos, int maxWidth, bool breakLines);
        void drawPolygon(const std::vector<ScreenPos>& poses);
        void drawRoundRect(const ScreenBounds& rect, float radius);
        void drawBitmap(const ScreenBounds& rect, const std::shared_ptr<Bitmap>& bitmap);

        ScreenBounds measureTextSize(std::string text, int maxWidth, bool breakLines);

        std::shared_ptr<Bitmap> buildBitmap(bool pow2Padding) const;

    protected:
        struct State;
		
        std::unique_ptr<State> _state;
    };
}

#endif
