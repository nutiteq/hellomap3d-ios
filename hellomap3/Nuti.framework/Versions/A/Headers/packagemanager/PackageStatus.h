/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_PACKAGESTATUS_H_
#define _NUTI_PACKAGESTATUS_H_

namespace Nuti {
	
	namespace PackageAction {
		/**
		 * The current action that describes the operation being performed with the package.
		 */
		enum PackageAction {
			/**
			 * Package is ready.
			 */
			PACKAGE_ACTION_READY = 0,
			/**
			 * Package is waiting in the task queue.
			 */
			PACKAGE_ACTION_WAITING = 1,
			/**
			 * Package is being downloaded.
			 */
			PACKAGE_ACTION_DOWNLOADING = 2,
			/**
			 * Package data is being copied.
			 */
			PACKAGE_ACTION_COPYING = 3,
			/**
			 * Package is being removed.
			 */
			PACKAGE_ACTION_REMOVING = 4
		};
	}

	/**
	 * The status of the map package. This includes information whether the package is ready, queued for processing, downloading, etc.
	 * Also it contains information if the package processing is paused and about the progress.
	 */
	class PackageStatus {
	public:
		/**
		 * Constructs a new status.
		 * @param currentAction The current action being performed with the package.
		 * @param paused True if the action is paused.
		 * @param progress The progress of the operation (in the range 0..100)
		 */
		PackageStatus(PackageAction::PackageAction currentAction, bool paused, float progress) : _currentAction(currentAction), _paused(paused), _progress(progress) { }

		/**
		 * Returns the current action being performed.
		 * @return The current action being performed.
		 */
		PackageAction::PackageAction getCurrentAction() const {
			return _currentAction;
		}

		/**
		 * Returns the paused state of the action.
		 * @return True when the action is paused, false if the action is active.
		 */
		bool isPaused() const {
			return _paused;
		}

		/**
		 * Returns the progress of the action.
		 * @return The progress of the action (in the range 0..100)
		 */
		float getProgress() const {
			return _progress;
		}

	private:
		PackageAction::PackageAction _currentAction;
		bool _paused;
		float _progress;
	};
}

#endif
