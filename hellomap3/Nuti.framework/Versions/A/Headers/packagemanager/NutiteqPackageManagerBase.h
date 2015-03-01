/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NUTITEQPACKAGEMANAGERBASE_H_
#define _NUTI_NUTITEQPACKAGEMANAGERBASE_H_

#include "PackageManager.h"

namespace Nuti {
	
	/**
	 * Base class for package manager that connects to Nutiteq online services.
	 */
	class NutiteqPackageManagerBase : public PackageManager {
	public:
		/**
		 * Constructs a PackageManager object, given application context and data folder.
		 * The data folder must exist before creating a new package manager and it is assumed to be persistent.
		 * Note: the package manager must be explicitly started using start() method!
		 * @param source Name of the package source. Currently "nutiteq.mbstreets" source is available
		 * @param dataFolder The folder where downloaded packages are kept. It must exist and must be writable.
		 * @param deviceId Device-specific id
		 */
		NutiteqPackageManagerBase(const std::string& source, const std::string& dataFolder, const std::string& deviceId);
		
	protected:
		virtual std::string createPackageUrl(const std::string& packageId, int version, const std::string& baseUrl, bool downloaded) const;

		virtual std::shared_ptr<PackageInfo> getCustomPackage(const std::string& packageId, int version) const;
		
	private:
		static const std::string PACKAGE_LIST_URL;
		static const std::string CUSTOM_BBOX_PACKAGE_URL;

		std::string _source;
	};
}

#endif
