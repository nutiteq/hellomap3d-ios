#ifndef ASSETUTILS_H_
#define ASSETUTILS_H_

#include <string>
#include <vector>

struct AAssetManager;

namespace Nuti {

class AssetUtils {
public:
	static std::shared_ptr<std::vector<unsigned char> > loadBytes(const std::string& path);

	static std::string calculateResourcePath(const std::string& resourceName);
    
    static std::string calculateWritablePath(const std::string& fileName);
    
};

}

#endif
