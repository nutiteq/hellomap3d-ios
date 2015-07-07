/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_GEOJSONGEOMETRYREADER_H_
#define _NUTI_GEOJSONGEOMETRYREADER_H_

#include "core/MapPos.h"

#include <memory>
#include <string>
#include <vector>

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
     * A GeoJSON parser.
     * Only Geometry objects are supported, Features and FeatureCollections are not supported.
     */
    class GeoJSONGeometryReader {
    public:
        /**
         * Constructs a new GeoJSONGeometryReader object.
         */
        GeoJSONGeometryReader();

        /**
         * Reads geometry from the specified GeoJSON string.
         * @param geoJSON The GeoJSON string to read.
         * @return The geometry read from the string. Null if reading failed.
         */
        std::shared_ptr<Geometry> readGeometry(const std::string& geoJSON) const;

    private:
        std::shared_ptr<Geometry> readGeometry(const rapidjson::Value& value) const;
        MapPos readPoint(const rapidjson::Value& value) const;
        std::vector<MapPos> readRing(const rapidjson::Value& value) const;
        std::vector<std::vector<MapPos> > readRings(const rapidjson::Value& value) const;
    };

}

#endif
