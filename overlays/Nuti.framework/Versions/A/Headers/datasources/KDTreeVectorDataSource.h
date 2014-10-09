#ifndef KDTREEVECTORDATASOURCE_H_
#define KDTREEVECTORDATASOURCE_H_

#include "datasources/VectorDataSource.h"
#include "utils/KDTree.h"

namespace Nuti {

/**
 * A modifiable vector data source that keeps all the elements in the local memory.
 * The vector elements are kept in a k-d tree structure and only the visible elements get rendererd. 
 * There can be a small delay before previously invisible elements become visible after view changes.
 * This makes it suitable for cases where there are a large number of static vector elements.
 *
 * The draw order of vector elements within the data source is undefined.
 */
class KDTreeVectorDataSource: public VectorDataSource {
public:
    /**
     * Constructs an KDTreeVectorDataSource object.
     * @param projection The projection used by this data source.
     */
	KDTreeVectorDataSource(const std::shared_ptr<Projection>& projection);
	virtual ~KDTreeVectorDataSource();

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
     * @param element The vector element to be removed.
     * @return True if the vector element existed in the data source.
     */
    
	bool remove(const std::shared_ptr<VectorElement>& elementToRemove);
    /**
     * Removes all vector elements from the data source.
     * @return The removed vector elements.
     */
	std::vector<std::shared_ptr<VectorElement> > removeAll();

protected:
	KDTree<std::shared_ptr<VectorElement> > _kdTree;
    
    unsigned int _elementId;

};

}

#endif
