/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CARTOCSS_CARTOCSSMAPNIKTRANSLATOR_H_
#define _NUTI_CARTOCSS_CARTOCSSMAPNIKTRANSLATOR_H_

#include "Expression.h"
#include "Predicate.h"
#include "CartoCSSCompiler.h"
#include "MapnikVT/Map.h"
#include "MapnikVT/Rule.h"
#include "MapnikVT/Expression.h"
#include "MapnikVT/Predicate.h"
#include "MapnikVT/Logger.h"

#include <memory>
#include <string>
#include <vector>

namespace Nuti { namespace CartoCSS {
    class CartoCSSMapnikTranslator {
    public:
        class TranslatorException : public std::runtime_error {
        public:
            explicit TranslatorException(const std::string& msg) : runtime_error(msg) { }
        };

        explicit CartoCSSMapnikTranslator(std::shared_ptr<MapnikVT::Logger> logger) : _logger(std::move(logger)) { }

        virtual std::shared_ptr<MapnikVT::Rule> buildRule(const CartoCSSCompiler::PropertySet& propertySet, const std::shared_ptr<MapnikVT::Map>& map, int zoom) const;

        virtual std::shared_ptr<MapnikVT::Symbolizer> buildSymbolizer(const std::string& symbolizerType, const std::list<CartoCSSCompiler::Property>& properties, const std::shared_ptr<MapnikVT::Map>& map, int zoom) const;

        virtual std::string buildExpressionString(const std::shared_ptr<const Expression>& expr) const;

        virtual std::string buildEscapedExpressionString(const std::shared_ptr<const Expression>& expr) const;

        virtual std::shared_ptr<MapnikVT::Predicate> buildPredicate(const std::shared_ptr<const Predicate>& pred) const;

        virtual std::shared_ptr<MapnikVT::ComparisonPredicate::Operator> buildOperator(OpPredicate::Op op) const;

    protected:
        virtual MapnikVT::Value buildValue(const Value& val) const;

        virtual std::string getPropertySymbolizerId(const std::string& propertyName) const;

        std::shared_ptr<MapnikVT::Logger> _logger;

    private:
        struct ValueBuilder;
        
        static const std::vector<std::string> _symbolizerList;
        static const std::map<std::string, std::string> _symbolizerPropertyMap;
    };
} }

#endif
