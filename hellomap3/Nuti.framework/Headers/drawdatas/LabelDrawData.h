#ifndef LABELDRAWDATA_H_
#define LABELDRAWDATA_H_

#include "drawdatas/BillboardDrawData.h"

namespace Nuti {

class Label;
class LabelStyle;
class ViewState;

class LabelDrawData: public BillboardDrawData {
public:
	LabelDrawData(const Label& label, const LabelStyle& style,
                  const Projection& projection, const ViewState& viewState);
	virtual ~LabelDrawData();
};

}

#endif
