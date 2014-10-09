#ifndef NETWORKUTILS_H_
#define NETWORKUTILS_H_

#include <memory>
#include <string>
#include <vector>

namespace Nuti {

class NetworkUtils {
public:
	static std::shared_ptr<std::vector<unsigned char> > LoadBytes(const std::string& url);

	static std::string ParseURLHostName(std::string url);

	static std::string ParseURLPort(std::string url);

	static std::string ParseURLFileName(std::string url);

private:
	static const int BUFFER_SIZE = 1024;

};

}

#endif
