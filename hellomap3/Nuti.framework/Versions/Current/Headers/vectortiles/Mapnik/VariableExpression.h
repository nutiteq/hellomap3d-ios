/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_VARIABLEEXPRESSION_H_
#define _NUTI_MAPNIK_VARIABLEEXPRESSION_H_

#include "Expression.h"
#include "ConstExpression.h"
#include "ExpressionContext.h"

#include <string>

namespace Nuti { namespace Mapnik {
	class VariableExpression : public Expression {
	public:
		explicit VariableExpression(const std::string& variableName) : _variableExpr(std::make_shared<ConstExpression>(Value(variableName))) { }
		explicit VariableExpression(const std::shared_ptr<Expression>& variableExpr) : _variableExpr(variableExpr) { }

		const std::shared_ptr<Expression>& getVariableExpression() const { return _variableExpr; }
		std::string getVariableName(const ExpressionContext& context) const { return context.evaluateString(*_variableExpr); }

		virtual Value evaluate(const ExpressionContext& context) const override {
			return context.getVariable(getVariableName(context));
		}

	private:
		const std::shared_ptr<Expression> _variableExpr;
	};
} }

#endif
