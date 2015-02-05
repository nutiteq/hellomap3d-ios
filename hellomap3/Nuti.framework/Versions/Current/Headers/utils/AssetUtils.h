#ifndef ASSETUTILS_H_
#define ASSETUTILS_H_

#include <string>
#include <vector>

struct AAssetManager;

namespace Nuti {

/**
 * A helper class for managing application-bundled assets.
 */
class AssetUtils {
public:
	/**
	 * Loads the specified bundled resource.
	 * @param path The path of the resource to load. The path is relative to application root folder.
	 * @return The loaded resource as a byte vector or null if the resource was not found or could not be loaded.
	 * @deprecated Use LoadBytes instead.
	 */
	static std::shared_ptr<std::vector<unsigned char> > loadBytes(const std::string& path) { return LoadBytes(path); }

	/**
	 * Loads the specified bundled resource.
	 * @param path The path of the resource to load. The path is relative to application root folder.
	 * @return The loaded resource as a byte vector or null if the resource was not found or could not be loaded.
	 */
	static std::shared_ptr<std::vector<unsigned char> > LoadBytes(const std::string& path);

	/**
	 * Calculates path for the bundled resource.
	 * @param resourceName The name of the resource.
	 * @return The full path for the resource. Result will be empty string if the resource was not found.
	 * @deprecated Use CalculateResourcePath instead.
	 */
	static std::string calculateResourcePath(const std::string& resourceName) { return CalculateResourcePath(resourceName); }
	
	/**
	 * Calculates path for the bundled resource.
	 * @param resourceName The name of the resource.
	 * @return The full path for the resource. Result will be empty string if the resource was not found.
	 */
	static std::string CalculateResourcePath(const std::string& resourceName);
	
	/**
	 * Calculates writable path for the given file name.
	 * @param fileName The file name to use.
	 * @return The full path for the given file name.
	 * @deprecated Use CalculateResourcePath instead.
	 */
	static std::string calculateWritablePath(const std::string& fileName) { return CalculateWritablePath(fileName); }

	/**
	 * Calculates writable path for the given file name.
	 * @param fileName The file name to use.
	 * @return The full path for the given file name.
	 */
	static std::string CalculateWritablePath(const std::string& fileName);
};

}

#endif
