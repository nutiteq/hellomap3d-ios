/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NUTITEQPACKAGEMANAGER_H_
#define _NUTI_NUTITEQPACKAGEMANAGER_H_

#ifdef _NUTI_PACKAGEMANAGER_SUPPORT

#include "PackageManager.h"

namespace Nuti {
	
    /**
     * Offline map package manager that uses Nutiteq online service for map package downloads.
     * After packages are downloaded, they can be used offline without any connection to the server.
     */
	class NutiteqPackageManager : public PackageManager {
	public:
		/**
		 * Constructs a NutiteqPackageManager object, given application context and data folder.
		 * The data folder must exist before creating a new package manager and it is assumed to be persistent.
		 * Note: the package manager must be explicitly started using start() method!
		 * @param source Name of the package source. Default: "nutiteq.osm"
		 * @param dataFolder The folder where downloaded packages are kept. It must exist and must be writable.
		 */
		NutiteqPackageManager(const std::string& source, const std::string& dataFolder);
        virtual ~NutiteqPackageManager();
		
	protected:
        static std::string GetLocalEncKey();

        virtual std::string createPackageUrl(const std::string& packageId, int version, const std::string& baseUrl, bool downloaded) const;

		virtual std::shared_ptr<PackageInfo> getCustomPackage(const std::string& packageId, int version) const;
		
	private:
		static const std::string PACKAGE_LIST_URL;

        static const std::string CUSTOM_BBOX_PACKAGE_URL;
        
        static const std::string SERVER_ENC_KEY;

		std::string _source;
	};
}

#endif

#endif
