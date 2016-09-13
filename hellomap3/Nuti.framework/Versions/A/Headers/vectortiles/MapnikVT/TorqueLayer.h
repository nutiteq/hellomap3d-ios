/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_TORQUELAYER_H_
#define _NUTI_MAPNIKVT_TORQUELAYER_H_

#include "Layer.h"

namespace Nuti { namespace MapnikVT {
	class TorqueLayer : public Layer {
	public:
        explicit TorqueLayer(std::string name, int frameOffset, std::vector<std::string> styleNames) : Layer(std::move(name), std::move(styleNames)), _frameOffset(frameOffset) { }

        int getFrameOffset() const { return _frameOffset; }

	private:
		const int _frameOffset;
	};
} }

#endif
