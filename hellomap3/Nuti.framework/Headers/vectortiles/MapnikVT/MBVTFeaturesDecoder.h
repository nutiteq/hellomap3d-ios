/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_MBVTFEATURESDECODER_H_
#define _NUTI_MAPNIKVT_MBVTFEATURESDECODER_H_

#include "FeaturesDecoder.h"
#include "Logger.h"

#include <memory>
#include <vector>

#include <cglib/mat.h>

namespace Nuti { namespace MapnikVT {
	class MBVTFeaturesDecoder : public FeaturesDecoder {
	public:
		MBVTFeaturesDecoder(const std::vector<unsigned char>& data, const cglib::mat3x3<float>& transform, const std::shared_ptr<Mapnik::Logger>& logger);
		virtual ~MBVTFeaturesDecoder();

		virtual const cglib::bounding_box<float, 2>& getClipRect() const override;
		virtual std::shared_ptr<Features> decodeLayer(const std::string& name) const override;

	private:
		class Impl;

		std::unique_ptr<Impl> _impl;
	};
} }

#endif
