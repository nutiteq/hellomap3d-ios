/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_VALUE_H_
#define _NUTI_MAPNIK_VALUE_H_

#include <memory>
#include <string>
#include <utility>
#include <ostream>

#include <boost/lexical_cast.hpp>

namespace Nuti { namespace Mapnik {
	class Value {
	public:
		enum class Type {
			NULL_VALUE, BOOL_VALUE, LONG_VALUE, DOUBLE_VALUE, STRING_VALUE
		};

		Value() = default;
		Value(const Value& val) { *this = val; }
		Value(Value&& val) { *this = std::move(val); }
		explicit Value(bool val) : _type(Type::BOOL_VALUE) { _value.p.b = val; }
		explicit Value(long long val) : _type(Type::LONG_VALUE) { _value.p.l = val; }
		explicit Value(double val) : _type(Type::DOUBLE_VALUE) { _value.p.d = val; }
		explicit Value(const std::string& val) : _type(Type::STRING_VALUE) { _value.s = val; }

		Type getType() const { return _type; }

		bool getBool() const { return _value.p.b; }
		long long getLong() const { return _value.p.l; }
		double getDouble() const { return _value.p.d; }
		const std::string& getString() const { return _value.s; }

		Value& operator = (const Value& val) {
			if (val._type != Type::STRING_VALUE) {
				_type = val._type;
				_value.p = val._value.p;
				return *this;
			}

			_type = Type::STRING_VALUE;
			_value.s = val._value.s;
			return *this;
		}

		Value& operator = (Value&& val) {
			std::swap(_type, val._type);
			std::swap(_value.p, val._value.p);
			std::swap(_value.s, val._value.s);
			return *this;
		}

		bool operator == (const Value& val) const {
			if (_type != val._type) {
				return false;
			}
			switch (_type) {
			case Type::BOOL_VALUE:
				return _value.p.b == val._value.p.b;
			case Type::LONG_VALUE:
				return _value.p.l == val._value.p.l;
			case Type::DOUBLE_VALUE:
				return _value.p.d == val._value.p.d;
			case Type::STRING_VALUE:
				return _value.s == val._value.s;
			default:
				return true;
			}
		}

		bool operator != (const Value& val) const {
			return !(*this == val);
		}

	private:
		Type _type = Type::NULL_VALUE;

		struct {
			union {
				bool b;
				long long l;
				double d;
			} p;
			std::string s;
		} _value;
	};

	inline std::ostream& operator << (std::ostream& os, const Value& val) {
		switch (val.getType()) {
		case Value::Type::BOOL_VALUE:
			return os << val.getBool();
		case Value::Type::LONG_VALUE:
			return os << val.getLong();
		case Value::Type::DOUBLE_VALUE:
			return os << val.getDouble();
		case Value::Type::STRING_VALUE:
			return os << val.getString();
		default:
			return os;
		}
	}
} }

#endif
