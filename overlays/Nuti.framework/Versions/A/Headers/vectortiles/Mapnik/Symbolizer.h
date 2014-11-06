#pragma once

#include <string>

namespace Nuti {
	namespace Mapnik {
		class Symbolizer {
		public:
			virtual ~Symbolizer() = default;

			virtual void setParameter(const std::string& name, const std::string& value) = 0;
		};
	}
}
