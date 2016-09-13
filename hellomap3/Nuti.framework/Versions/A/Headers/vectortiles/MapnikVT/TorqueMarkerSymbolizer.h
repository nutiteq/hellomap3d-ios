/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_TORQUEMARKERSYMBOLIZER_H_
#define _NUTI_MAPNIKVT_TORQUEMARKERSYMBOLIZER_H_

#include "Symbolizer.h"

namespace Nuti { namespace MapnikVT {
	class TorqueMarkerSymbolizer : public Symbolizer {
	public:
        explicit TorqueMarkerSymbolizer(std::shared_ptr<Logger> logger) : Symbolizer(std::move(logger)) { }

		virtual void build(const FeatureCollection& featureCollection, const SymbolizerContext& symbolizerContext, const ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

	protected:
        virtual void bindParameter(const std::string& name, const std::string& value) override;

        static std::shared_ptr<VT::Bitmap> makeEllipseBitmap(float width, float height, const VT::Color& color, float strokeWidth, const VT::Color& strokeColor);
        static std::shared_ptr<VT::Bitmap> makeRectangleBitmap(float width, float height, const VT::Color& color, float strokeWidth, const VT::Color& strokeColor);

        enum { DEFAULT_MARKER_SIZE = 10 };
        enum { SUPERSAMPLING_FACTOR = 4 };

        std::string _file;
        std::string _markerType;
        VT::Color _fill = VT::Color(0xff0000ff);
        float _fillOpacity = 1.0f;
		float _width = 10.0f; 
        VT::Color _stroke = VT::Color(0xff000000);
        float _strokeOpacity = 1.0f;
        float _strokeWidth = 0.0f;
        std::string _compOp = "src-over";
    };
} }

#endif
