/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CARTOCSS_TORQUECARTOCSSMAPNIKTRANSLATOR_H_
#define _NUTI_CARTOCSS_TORQUECARTOCSSMAPNIKTRANSLATOR_H_

#include "CartoCSSMapnikTranslator.h"

namespace Nuti { namespace CartoCSS {
    class TorqueCartoCSSMapnikTranslator : public CartoCSSMapnikTranslator {
    public:
        explicit TorqueCartoCSSMapnikTranslator(std::shared_ptr<MapnikVT::Logger> logger) : CartoCSSMapnikTranslator(std::move(logger)) { }

        virtual std::shared_ptr<MapnikVT::Symbolizer> buildSymbolizer(const std::string& symbolizerType, const std::list<CartoCSSCompiler::Property>& properties, const std::shared_ptr<MapnikVT::Map>& map, int zoom) const override;

    protected:
        virtual std::string getPropertySymbolizerId(const std::string& propertyName) const override;

    private:
        static const std::map<std::string, std::string> _symbolizerPropertyMap;
    };
} }

#endif
