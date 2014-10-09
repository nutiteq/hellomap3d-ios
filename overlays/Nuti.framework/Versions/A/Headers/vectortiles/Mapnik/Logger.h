#pragma once

#include <string>

namespace Nuti {
	namespace Mapnik {
		class Logger {
		public:
			enum class Severity {
				INFO, WARNING, ERROR
			};

			virtual ~Logger() = default;

			virtual void write(Severity severity, const std::string& msg) = 0;
		};
	}
}
