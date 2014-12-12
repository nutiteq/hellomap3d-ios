#ifndef _NUTI_LOCALVECTORDATASOURCE_H_
#define _NUTI_LOCALVECTORDATASOURCE_H_

#include "datasources/VectorDataSource.h"
#include "utils/SpatialIndex.h"

#include <memory>

namespace Nuti {
	class GeometrySimplifier;

	namespace LocalSpatialIndexType {
		/**
		 * Spatial index type for local data source.
		 */
		enum LocalSpatialIndexType {
			/**
			 * Null index, fastest if few elements are used. No element culling is performed.
			 */
			NULL_SPATIAL_INDEX,
			
			/**
			 * K-d tree index, element culling is exact and fast.
			 */
			KDTREE_SPATIAL_INDEX
		};
	}

	/**
	 * A modifiable vector data source that keeps all the elements in the local memory.
	 * Optionally vector elements can be kept in a spatial index and only the visible elements get rendered.
	 * There can be a small delay before previously invisible elements become visible after view changes.
	 * This makes it suitable for cases where there are a large number of static vector elements.
	 *
	 * The draw order of vector elements within the data source is undefined.
	 */
	class LocalVectorDataSource: public VectorDataSource {
	public:
		/**
		 * Constructs an LocalVectorDataSource object with no spatial index.
		 * @param projection The projection used by this data source.
		 */
		LocalVectorDataSource(const std::shared_ptr<Projection>& projection);
		/**
		 * Constructs an LocalVectorDataSource object with specified spatial index.
		 * @param projection The projection used by this data source.
		 * @param spatialIndexType The spatial index type to use.
		 */
		LocalVectorDataSource(const std::shared_ptr<Projection>& projection, LocalSpatialIndexType::LocalSpatialIndexType spatialIndexType);
		virtual ~LocalVectorDataSource();
		
		virtual std::vector<std::shared_ptr<VectorElement> > loadElements(const std::shared_ptr<CullState>& cullState);
		
		/**
		 * Returns all vector elements added to this data source using add() and addAll() methods.
		 * @return A vector containing all the vector elements in this data source.
		 */
		std::vector<std::shared_ptr<VectorElement> > getAll() const;
		
		/**
		 * Adds a vector element to the data source. The vector element's coordinates are expected to be
		 * in the data source's projection's coordinate system. The order in which the elements are added has
		 * no effect on the order they get rendered.
		 * @param element The vector element to be added.
		 */
		void add(const std::shared_ptr<VectorElement>& element);
		/**
		 * Adds multiple vector elements to the data source. The vector elements' coordinates are expected to be
		 * in the data source's projection's coordinate system. The order in which the elements are added has
		 * no effect on the order they get rendered.
		 * @param elements A vector of vector elements to be added.
		 */
		void addAll(const std::vector<std::shared_ptr<VectorElement> >& elements);
		/**
		 * Removes a vector element from the data source.
		 * @param elementToRemove The vector element to be removed.
		 * @return True if the vector element existed in the data source.
		 */
		
		bool remove(const std::shared_ptr<VectorElement>& elementToRemove);
		/**
		 * Removes all vector elements from the data source.
		 * @return The removed vector elements.
		 */
		std::vector<std::shared_ptr<VectorElement> > removeAll();
		
		/**
		 * Returns the active geometry simplifier of the data source.
		 * @return The current geometry simplifier (can be null)
		 */
		const std::shared_ptr<GeometrySimplifier>& getGeometrySimplifier() const;
		/**
		 * Attaches geometry simplifier to the data source. If the specified simplifier is null, detaches any active simplifier.
		 * @param simplifier The new geometry simplifier to use (can be null).
		 */
		void setGeometrySimplifier(const std::shared_ptr<GeometrySimplifier>& simplifier);
		
	private:
		std::shared_ptr<GeometrySimplifier> _geometrySimplifier;
		std::shared_ptr<SpatialIndex<std::shared_ptr<VectorElement> > > _spatialIndex;
		
		unsigned int _elementId;

		mutable std::mutex _mutex;
	};
	
}

#endif
