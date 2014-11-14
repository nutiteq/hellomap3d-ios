#ifndef VECTORELEMENTDRAWDATA_H_
#define VECTORELEMENTDRAWDATA_H_

#include "graphics/Color.h"

#include <memory>

namespace Nuti {

class VectorElement;

class VectorElementDrawData {
public:
	virtual ~VectorElementDrawData();

	const Color& getColor() const;

protected:
	VectorElementDrawData(const Color& color);

private:
	Color _color;

};

}

#endif
