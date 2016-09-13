/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_VALUECONVERTER_H_
#define _NUTI_MAPNIKVT_VALUECONVERTER_H_

#include "Value.h"

#include <boost/lexical_cast.hpp>

namespace Nuti { namespace MapnikVT {
	template <typename V>
	struct ValueConverter {
        static V convert(const Value& val) {
            return boost::apply_visitor(Converter(), val);
        }

    private:
        struct Converter : boost::static_visitor<V> {
            V operator() (boost::blank) const { return V(); }
            V operator() (const std::string& val) const {
                try {
                    return boost::lexical_cast<V>(val);
                }
                catch (const boost::bad_lexical_cast&) {
                    return V();
                }
            }
            template <typename T> V operator() (T val) const { return static_cast<V>(val); }
        };
    };

    template <>
    struct ValueConverter<boost::blank> {
        static boost::blank convert(const Value& val) {
            return boost::blank();
        }
    };

    template <>
	struct ValueConverter<bool> {
		static bool convert(const Value& val) {
            return boost::apply_visitor(Converter(), val);
		}

    private:
        struct Converter : boost::static_visitor<bool> {
            bool operator() (boost::blank) const { return false; }
            bool operator() (bool val) const { return val; }
            bool operator() (const std::string& val) const { return !val.empty(); }
            template <typename T> bool operator() (T val) const { return val != 0; }
        };
	};

	template <>
	struct ValueConverter<std::string> {
		static std::string convert(const Value& val) {
            return boost::apply_visitor(Converter(), val);
        }

    private:
        struct Converter : boost::static_visitor<std::string> {
            std::string operator() (boost::blank) const { return std::string(); }
            std::string operator() (const std::string& val) const { return val; }
            template <typename T> std::string operator() (T val) const {
                try {
                    return boost::lexical_cast<std::string>(val);
                }
                catch (const boost::bad_lexical_cast&) {
                    return std::string();
                }
            }
        };
    };
} }

#endif
