/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_FEATURESDECODER_H_
#define _NUTI_MAPNIKVT_FEATURESDECODER_H_

#include "Features.h"

#include <memory>

#include <cglib/bbox.h>

namespace Nuti { namespace MapnikVT {
	class FeaturesDecoder {
	public:
		using Features = std::vector<std::shared_ptr<Feature>>;

		virtual ~FeaturesDecoder() = default;

		virtual const cglib::bounding_box<float, 2>& getClipRect() const = 0;
		virtual std::shared_ptr<Features> decodeLayer(const std::string& name) const = 0;
	};
} }

#endif
