/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CARTOCSS_CARTOCSSPARSER_H_
#define _NUTI_CARTOCSS_CARTOCSSPARSER_H_

#include "Expression.h"
#include "Predicate.h"
#include "StyleSheet.h"

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <stdexcept>

namespace Nuti { namespace CartoCSS {
    class CartoCSSParser {
    public:
        struct ParserError : std::runtime_error {
            explicit ParserError(const std::string& msg) : runtime_error(msg), _pos(0, 0) { }
            explicit ParserError(const std::string& msg, std::pair<int, int> pos) : runtime_error(msg), _pos(pos) { }

            std::pair<int, int> position() const { return _pos; }
        
        private:
            std::pair<int, int> _pos;
        };
        
        static StyleSheet parse(const std::string& cartoCSS);
        
    private:
        static std::pair<int, int> resolvePosition(const std::string& str, std::string::size_type pos);
    };
} }

#endif
