#ifndef UNCULLEDVECTORDATASOURCE_H_
#define UNCULLEDVECTORDATASOURCE_H_

#include "datasources/LocalVectorDataSource.h"

namespace Nuti {

/**
 * A modifiable vector data source that keeps all the elements in the local memory.
 * All elements are always rendered regardless of the current view state. This makes it suitable for cases
 * where there are only a few constantly changing elements. For example, GPS location.
 *
 * The draw order of vector elements within the data source is undefined.
 * @deprecated This class is deprecated, use LocalVectorDataSource directly.
 */
class UnculledVectorDataSource: public LocalVectorDataSource {
public:
    /**
     * Constructs an UnculledVectorDataSource object.
     * @param projection The projection used by this data source.
     */
	UnculledVectorDataSource(const std::shared_ptr<Projection>& projection) : LocalVectorDataSource(projection, LocalSpatialIndexType::NULL_SPATIAL_INDEX) { }
};

}

#endif
