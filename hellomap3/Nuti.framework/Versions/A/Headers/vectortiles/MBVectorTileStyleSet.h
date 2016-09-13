/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MBVECTORTILESTYLESET_H_
#define _NUTI_MBVECTORTILESTYLESET_H_

#include <string>
#include <map>
#include <vector>
#include <memory>

namespace Nuti {

    /**
     * Style set for MapBox vector tiles. Style set is a read-only key-value containers,
     * their contents should not be read or used at application level.
     */
    class MBVectorTileStyleSet {
    public:
        /**
         * Constructs a styleset from byte vector.
         * @param data Zipped style set data.
         */
        MBVectorTileStyleSet(const std::shared_ptr<std::vector<unsigned char> >& data);
        virtual ~MBVectorTileStyleSet();
    
        /**
         * Returns list of element names in this style set.
         * All listed elements can read using getElement API.
         * @return List of element names.
         */
        std::vector<std::string> getElementNames() const;
    
        /**
         * Returns the specified element from the style set.
         * @param name Element name to read.
         * @returns Pointer to the element data, if element exists and was successfully read. Null pointer otherwise.
         */
        std::shared_ptr<std::vector<unsigned char> > getElement(const std::string& name) const;
    
    private:
        std::shared_ptr<void> _handle;
        std::shared_ptr<std::vector<unsigned char> > _data;
        std::map<std::string, unsigned int> _elementIndexMap;
    };
    
}

#endif
