/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_GEOJSONGEOMETRYWRITER_H_
#define _NUTI_GEOJSONGEOMETRYWRITER_H_

#include "core/MapPos.h"

#include <memory>
#include <mutex>
#include <cstddef>
#include <vector>
#include <stack>

namespace rapidjson {
    class CrtAllocator;
    template <typename BaseAllocator> class MemoryPoolAllocator;
    template<typename CharType> struct UTF8;
    template <typename Encoding, typename Allocator> class GenericValue;
    typedef GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator> > Value;
}

namespace Nuti {
    class Geometry;

    /**
     * A GeoJSON writer. Generates human-readable GeoJSON representation of the geometry.
     * Supports both 2D and 3D coordinate serialization.
     */
    class GeoJSONGeometryWriter {
    public:
        /**
         * Constructs a new GeoJSONGeometryWriter object with default settings.
         */
        GeoJSONGeometryWriter();

        /**
         * Returns the state of Z coordinate serialization.
         * @return True if Z coordinate is stored in GeoJSON output, false otherwise. The default is false.
         */
        bool getZ() const;
        /**
         * Sets the state of Z coordinate serialization.
         * @param z True when Z coordinate should be serialized, false otherwise.
         */
        void setZ(bool z);

        /**
         * Creates a GeoJSON string corresponding to the specified geometry.
         * @param geometry The geometry to write.
         * @return The corresponding GeoJSON string.
         */
        std::string writeGeometry(const std::shared_ptr<Geometry>& geometry) const;

    private:
        void writeGeometry(const std::shared_ptr<Geometry>& geometry, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator) const;
        void writePoint(const MapPos& pos, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator) const;
        void writeRing(const std::vector<MapPos>& ring, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator) const;
        void writeRings(const std::vector<std::vector<MapPos> >& rings, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator) const;

        bool _z;

        mutable std::mutex _mutex;
    };

}

#endif
