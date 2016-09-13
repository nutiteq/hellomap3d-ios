/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_POINTSYMBOLIZER_H_
#define _NUTI_MAPNIKVT_POINTSYMBOLIZER_H_

#include "Symbolizer.h"

namespace Nuti { namespace MapnikVT {
	class PointSymbolizer : public Symbolizer {
	public:
        explicit PointSymbolizer(std::shared_ptr<Logger> logger) : Symbolizer(std::move(logger)) { }

		virtual void build(const FeatureCollection& featureCollection, const SymbolizerContext& symbolizerContext, const ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

	protected:
        virtual void bindParameter(const std::string& name, const std::string& value) override;

        static std::shared_ptr<VT::Bitmap> createRectangleBitmap(float size);

		enum { RECTANGLE_SIZE = 4 };

		std::string _file;
		VT::Color _fill = VT::Color(0xff000000);
		float _opacity = 1.0f;
		float _width = 10.0f;
		float _height = 10.0f;
		bool _allowOverlap = false;
		bool _ignorePlacement = false;
		cglib::mat3x3<float> _transform = cglib::mat3x3<float>::identity();
	};
} }

#endif
