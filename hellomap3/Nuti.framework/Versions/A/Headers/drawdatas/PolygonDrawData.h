/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_POLYGONDRAWDATA_H_
#define _NUTI_POLYGONDRAWDATA_H_

#include "core/MapBounds.h"
#include "drawdatas/VectorElementDrawData.h"
#include "styles/PolygonStyle.h"

#include <memory>
#include <vector>

namespace Nuti {
    class LineDrawData;
    class MapPos;
    class PolygonGeometry;
    class PolygonStyle;
    class Projection;
    
    class PolygonDrawData : public VectorElementDrawData {
    public:
        PolygonDrawData(const PolygonGeometry& geometry, const PolygonStyle& style, const Projection& projection);
        PolygonDrawData(const PolygonDrawData& drawData);
        virtual ~PolygonDrawData();
    
        const std::shared_ptr<Bitmap> getBitmap() const;
    
        const MapBounds& getBoundingBox() const;
    
        const std::vector<std::vector<MapPos> >& getCoords() const;
    
        const std::vector<std::vector<unsigned int> >& getIndices() const;
    
        const std::vector<LineDrawData>& getLineDrawDatas() const;
    
        virtual void offsetHorizontally(double offset);
    
    private:
        static const int MAX_INDICES_PER_ELEMENT = 3;
    
        std::shared_ptr<Bitmap> _bitmap;
    
        MapBounds _boundingBox;
    
        std::vector<std::vector<MapPos> > _coords;

        std::vector<std::vector<unsigned int> > _indices;
    
        std::vector<LineDrawData> _lineDrawDatas;
    };
    
}

#endif
