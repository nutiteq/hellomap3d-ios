/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_WKBGEOMETRYREADER_H_
#define _NUTI_WKBGEOMETRYREADER_H_

#ifdef _NUTI_WKBT_SUPPORT

#include "core/MapPos.h"

#include <memory>
#include <vector>
#include <stack>
#include <cstddef>

namespace Nuti {
    class Geometry;

    /**
     * A WKB reader. Reads binary version of the Well Known Text representation of the geometry.
     */
    class WKBGeometryReader {
    public:
        /**
         * Constructs a new WKBGeometryReader object.
         */
        WKBGeometryReader();

        /**
         * Reads geometry from the specified WKB data vector.
         * @param wkb The WKB data vector to read.
         * @return The geometry read from the data vector. Null if reading failed.
         */
        std::shared_ptr<Geometry> readGeometry(const std::vector<unsigned char>& wkb) const;

    private:
        struct Stream {
            Stream(const std::vector<unsigned char>& data);

            void pushBigEndian(bool little);
            void popBigEndian();

            unsigned char readByte();
            uint32_t readUInt32();
            double readDouble();
        
        private:
            const std::vector<unsigned char>& _data;
            size_t _offset;
            std::stack<bool> _bigEndian;
        };

        std::shared_ptr<Geometry> readGeometry(Stream& stream) const;
        MapPos readPoint(Stream& stream, uint32_t type) const;
        std::vector<MapPos> readRing(Stream& stream, uint32_t type) const;
        std::vector<std::vector<MapPos> > readRings(Stream& stream, uint32_t type) const;
    };

}

#endif

#endif
