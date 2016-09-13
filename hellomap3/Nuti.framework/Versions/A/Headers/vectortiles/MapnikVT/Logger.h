/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_LOGGER_H_
#define _NUTI_MAPNIKVT_LOGGER_H_

#include <string>

namespace Nuti { namespace MapnikVT {
	class Logger {
	public:
		enum class Severity {
			INFO, WARNING, ERROR
		};

		virtual ~Logger() = default;

		virtual void write(Severity severity, const std::string& msg) = 0;
	};
} }

#endif
