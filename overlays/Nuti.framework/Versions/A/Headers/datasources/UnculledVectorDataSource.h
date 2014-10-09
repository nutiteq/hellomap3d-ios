#ifndef UNCULLEDVECTORDATASOURCE_H_
#define UNCULLEDVECTORDATASOURCE_H_

#include "datasources/VectorDataSource.h"

namespace Nuti {

/**
 * A modifiable vector data source that keeps all the elements in the local memory.
 * All elements are always rendered regardless of the current view state. This makes it suitable for cases
 * where there are only a few constantly changing elements. For example, GPS location.
 *
 * The draw order of vector elements within the data source is undefined.
 */
class UnculledVectorDataSource: public VectorDataSource {
public:
    /**
     * Constructs an UnculledVectorDataSource object.
     * @param projection The projection used by this data source.
     */
	UnculledVectorDataSource(const std::shared_ptr<Projection>& projection);
	virtual ~UnculledVectorDataSource();

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
	std::vector<std::shared_ptr<VectorElement> > _elements;
    
    unsigned int _elementId;

};

}

#endif
