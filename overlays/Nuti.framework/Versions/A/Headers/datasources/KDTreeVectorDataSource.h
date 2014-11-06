#ifndef KDTREEVECTORDATASOURCE_H_
#define KDTREEVECTORDATASOURCE_H_

#include "datasources/LocalVectorDataSource.h"

namespace Nuti {

/**
 * A modifiable vector data source that keeps all the elements in the local memory.
 * The vector elements are kept in a k-d tree structure and only the visible elements get rendererd. 
 * There can be a small delay before previously invisible elements become visible after view changes.
 * This makes it suitable for cases where there are a large number of static vector elements.
 *
 * The draw order of vector elements within the data source is undefined.
 * @deprecated This class is deprecated, use LocalVectorDataSource directly.
 */
class KDTreeVectorDataSource: public LocalVectorDataSource {
public:
    /**
     * Constructs an KDTreeVectorDataSource object.
     * @param projection The projection used by this data source.
     */
	KDTreeVectorDataSource(const std::shared_ptr<Projection>& projection) : LocalVectorDataSource(projection, LocalSpatialIndexType::KDTREE_SPATIAL_INDEX) { }
};

}

#endif
