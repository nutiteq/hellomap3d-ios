/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_PACKAGEMANAGERLISTENER_H_
#define _NUTI_PACKAGEMANAGERLISTENER_H_

#ifdef _NUTI_PACKAGEMANAGER_SUPPORT

#include <string>
#include <memory>

#include "PackageStatus.h"

namespace Nuti {

	namespace PackageErrorType {
		/**
		 * Possible error types for failed package downloads.
		 */
		enum PackageErrorType {
			/**
			 * Internal or system error.
			 */
			PACKAGE_ERROR_TYPE_SYSTEM,
			/**
			 * Connection or network error.
			 */
			PACKAGE_ERROR_TYPE_CONNECTION,
			/**
			 * The number of downloaded packages exceeded subscription limit.
			 */
			PACKAGE_ERROR_TYPE_DOWNLOAD_LIMIT_EXCEEDED,
			/**
			 * The bounding box of the package contains too many tiles.
			 * This error is only returned for custom bounding box packages.
			 */
			PACKAGE_ERROR_TYPE_PACKAGE_TOO_BIG,
            /**
             * The license does not allow downloading offline packages.
             */
            PACKAGE_ERROR_TYPE_NO_OFFLINE_PLAN
		};
	}

	/**
	 * Base class for map package manager event listeners.
	 * Includes callbacks for package list events and individual package events.
	 */
	class PackageManagerListener {
	public:
		virtual ~PackageManagerListener() { }

		/**
		 * Listener method that is called when server package list has been successfully updated.
		 */
		virtual void onPackageListUpdated() = 0;
		/**
		 * Listener method that is called when server package could not be downloaded or updated.
		 */
		virtual void onPackageListFailed() = 0;

		/**
		 * Listener method that is called when a package status has changed.
		 * Information about the status of the package (current action, progress, etc) is explictly given with this event.
		 * @param id The id of the package whose status has changed
		 * @param version The version of the package whose status has changed
		 * @param status The current status of the package
		 */
		virtual void onPackageStatusChanged(const std::string& id, int version, const std::shared_ptr<PackageStatus>& status) = 0;
		/**
		 * Listener method that is called when a package download has been cancelled.
		 * @param id The id of the package that has been cancelled
		 * @param version The version of the package that has been cancelled
		 */
		virtual void onPackageCancelled(const std::string& id, int version) = 0;
		/**
		 * Listener method that is called when a package is successfully updated (downloaded or removed).
		 * @param id The id of the package that has been updated
		 * @param version The version of the package that has been updated
		 */
		virtual void onPackageUpdated(const std::string& id, int version) = 0;
		/**
		 * Listener method that is called when updating a package failed (network error, etc).
		 * @param id The id of the package that failed
		 * @param version The version of the package that failed
		 * @param errorType Reason or type of the failure
		 */
		virtual void onPackageFailed(const std::string& id, int version, PackageErrorType::PackageErrorType errorType) = 0;
	};

}

#endif

#endif
