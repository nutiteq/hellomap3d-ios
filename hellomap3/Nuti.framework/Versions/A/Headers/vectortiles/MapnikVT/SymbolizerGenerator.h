/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_SYMBOLIZERGENERATOR_H_
#define _NUTI_MAPNIKVT_SYMBOLIZERGENERATOR_H_

#include <memory>
#include <string>

#include <pugixml.hpp>

namespace Nuti { namespace MapnikVT {
    class Logger;
    class Symbolizer;
	
    class SymbolizerGenerator {
    public:
        explicit SymbolizerGenerator(std::shared_ptr<Logger> logger) : _logger(std::move(logger)) { }
        virtual ~SymbolizerGenerator() = default;

        virtual std::shared_ptr<pugi::xml_node> generateSymbolizer(const Symbolizer& symbolizer) const;

    protected:
        const std::shared_ptr<Logger> _logger;
    };
} }

#endif
