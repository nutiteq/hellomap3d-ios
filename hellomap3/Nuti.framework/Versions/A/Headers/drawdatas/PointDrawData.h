/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_POINTDRAWDATA_H_
#define _NUTI_POINTDRAWDATA_H_

#include "core/MapPos.h"
#include "drawdatas/VectorElementDrawData.h"
#include "styles/PointStyle.h"

#include <memory>

namespace Nuti {
    class Bitmap;
    class PointGeometry;
    class PointStyle;
    class Projection;
    
    class PointDrawData : public VectorElementDrawData {
    public:
        PointDrawData(const PointGeometry& geometry, const PointStyle& style, const Projection& projection);
        virtual ~PointDrawData();
    
        const std::shared_ptr<Bitmap> getBitmap() const;
    
        float getClickScale() const;
    
        const MapPos& getPos() const;
    
        float getSize() const;
    
        virtual void offsetHorizontally(double offset);
    
    private:
        static const int IDEAL_CLICK_SIZE = 64;
    
        static const float CLICK_SIZE_COEF;
    
        std::shared_ptr<Bitmap> _bitmap;
    
        float _clickScale;
    
        MapPos _pos;
    
        float _size;
    };
    
}

#endif
