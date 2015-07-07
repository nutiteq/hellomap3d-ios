/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CLUSTERELEMENTBUILDER_H_
#define _NUTI_CLUSTERELEMENTBUILDER_H_

#include "core/MapPos.h"

#include <vector>
#include <memory>

namespace Nuti {
    class VectorElement;

    /**
     * A special callback interface for building cluster elements from set of existing vector element.
     */
    class ClusterElementBuilder {
    public:
        virtual ~ClusterElementBuilder() { }

        /**
         * Builds new cluster element given position and list of vector elements.
         * @param mapPos The position of the cluster element.
         * @param elements The list of elements that defines the cluster.
         * @return The created cluster element.
         */
        virtual std::shared_ptr<VectorElement> buildClusterElement(const MapPos& mapPos, const std::vector<std::shared_ptr<VectorElement> >& elements) const = 0;
    };
}

#endif
