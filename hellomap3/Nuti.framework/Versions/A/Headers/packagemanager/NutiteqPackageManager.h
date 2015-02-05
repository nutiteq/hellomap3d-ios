#ifndef NUTITEQPACKAGEMANAGER_H_
#define NUTITEQPACKAGEMANAGER_H_

#include <string>
#include "NutiteqPackageManagerBase.h"

namespace Nuti {

/**
 * Offline map package manager. Package manager supports downloading/removing packages.
 * It can be queried about available packages and status of the packages. It works asynchronously in
 * the background and can inform app when packages have been updated.
 * It works persistently. If a package download is started and app is closed, the download will resume
 * when the package manager is started next time.
 */
class NutiteqPackageManager : public NutiteqPackageManagerBase {
public:
	/**
	 * Constructs a PackageManager object, given application context and data folder.
	 * The data folder must exist before creating a new package manager and it is assumed to be persistent.
	 * Note: the package manager must be explicitly started using start() method!
	 * @param source Name of the package source. Currently "nutiteq.mbstreets" source is available
	 * @param dataFolder The folder where downloaded packages are kept. It must exist and must be writable.
	 */
	NutiteqPackageManager(const std::string& source, const std::string& dataFolder);
	
private:
	static std::string GetDeviceId();
};
	
}

#endif