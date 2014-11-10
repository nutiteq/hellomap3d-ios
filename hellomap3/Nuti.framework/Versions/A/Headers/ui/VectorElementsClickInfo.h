#ifndef VECTORELEMENTSCLICKINFO_H_
#define VECTORELEMENTSCLICKINFO_H_

#include "ui/MapEventListener.h"
#include "ui/VectorElementClickInfo.h"

#include <memory>
#include <vector>

namespace Nuti {
    
/**
 * A container class that stores information about clicked vector elements.
 *
 * A single click may result in multiple vector elements being returned, all of which are 
 * located at the click position. If that's the case, the vector elements will be sorted
 * by their distance to the camera and their draw order. The first VectorElementClickInfo in the
 * vector of VectorElementClickInfos corresponds to the top-most element on the screen.
 */
class VectorElementsClickInfo {
public:
    /**
     * Constructs a VectorElementsClickInfo object from a click type and a VectorElementClickInfos.
     * @param clickType The click type.
     * @param vectorElementClickInfos The sorted list of VectorElementClickInfo objects.
     */
	VectorElementsClickInfo(ClickType::ClickType clickType,
			const std::shared_ptr<std::vector<VectorElementClickInfo> >& vectorElementClickInfos);
	virtual ~VectorElementsClickInfo();

    /**
     * Returns the click type.
     * @return The type of the click performed.
     */
	ClickType::ClickType getClickType() const;

    /**
     * Returns the sorted list of VectorElementClickInfo objects.
     * @return The list of VectorElementClickInfo objects sorted by their distance to the camera and 
     *         their draw order. The first element in the vector is the top-most element on the screen.
     */
	std::shared_ptr<std::vector<VectorElementClickInfo> > getVectorElementClickInfos() const;

private:
	ClickType::ClickType _clickType;

	std::shared_ptr<std::vector<VectorElementClickInfo> > _vectorElementClickInfos;

};

}

#endif
