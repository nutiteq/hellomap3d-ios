#ifndef POPUPDRAWDATA_H_
#define POPUPDRAWDATA_H_

#include "drawdatas/BillboardDrawData.h"

namespace Nuti {

class Options;
class Popup;
class PopupStyle;
class ViewState;

class PopupDrawData: public BillboardDrawData {
public:
	PopupDrawData(Popup& popup, const PopupStyle& style, const Projection& projection, const Options& options, const ViewState& viewState);
	virtual ~PopupDrawData();
};

}

#endif
