/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_POLYGON3DDRAWDATA_H_
#define _NUTI_POLYGON3DDRAWDATA_H_

#include "core/MapBounds.h"
#include "drawdatas/VectorElementDrawData.h"

#include <memory>
#include <vector>
#include <cglib/vec.h>

namespace Nuti {
    class MapPos;
    class Polygon3D;
    class Polygon3DStyle;
    class Projection;
    
    class Polygon3DDrawData : public VectorElementDrawData {
    public:
        Polygon3DDrawData(const Polygon3D& polygon3D, const Polygon3DStyle& style, const Projection& projection);
        Polygon3DDrawData(const Polygon3DDrawData& drawData);
        virtual ~Polygon3DDrawData();
    
        const MapBounds& getBoundingBox() const;
    
        const std::vector<MapPos>& getCoords() const;
    
		const std::vector<cglib::vec3<float> >& getNormals() const;
    
        void offsetHorizontally(double offset);
    
    private:
        static const int MAX_INDICES_PER_ELEMENT = 3;
    
        MapBounds _boundingBox;
    
        std::vector<MapPos> _coords;
        
        std::vector<cglib::vec3<float> > _normals;
    };
    
}

#endif
