/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_FILTER_H_
#define _NUTI_MAPNIKVT_FILTER_H_

#include <memory>

namespace Nuti { namespace MapnikVT {
	class Predicate;

	class Filter {
	public:
		enum class Type {
			FILTER,
			ELSEFILTER,
			ALSOFILTER
		};

		explicit Filter(Type type, std::shared_ptr<Predicate> pred) : _type(type), _pred(std::move(pred)) { }

		Type getType() const { return _type; }
		const std::shared_ptr<Predicate>& getPredicate() const { return _pred; }

	private:
		const Type _type;
		const std::shared_ptr<Predicate> _pred;
	};
} }

#endif
