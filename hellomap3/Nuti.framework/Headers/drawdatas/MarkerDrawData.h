#ifndef MARKERDRAWDATA_H_
#define MARKERDRAWDATA_H_

#include "drawdatas/BillboardDrawData.h"

namespace Nuti {

class Marker;
class MarkerStyle;

class MarkerDrawData: public BillboardDrawData {
public:
	MarkerDrawData(const Marker& marker, const MarkerStyle& style, const Projection& projection);
	virtual ~MarkerDrawData();
};

}

#endif
