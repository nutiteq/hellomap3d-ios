/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_PACKAGESTATUS_H_
#define _NUTI_PACKAGESTATUS_H_

namespace Nuti {
	/**
	 * The status of the map package. This includes information whether the package is ready, queued for processing, downloading, etc.
	 * Also it contains information if the package processing is paused and about the progress.
	 */
	class PackageStatus {
	public:
		/**
		 * The current action that describes the operation being performed with the package.
		 */
		enum Action {
			/**
			 * Package is ready.
			 */
			READY = 0,
			/**
			 * Package is waiting in the task queue.
			 */
			WAITING = 1,
			/**
			 * Package is being downloaded.
			 */
			DOWNLOADING = 2,
			/**
			 * Package data is being copied.
			 */
			COPYING = 3,
			/**
			 * Package is being removed.
			 */
			REMOVING = 4
		};

		/**
		 * Constructs a new status.
		 * @param action The current action being performed with the package.
		 * @param paused True if the action is paused.
		 * @param progress The progress of the operation (in the range 0..100)
		 */
		PackageStatus(Action action, bool paused, float progress) : _action(action), _paused(paused), _progress(progress) { }

		/**
		 * Returns the current action being performed.
		 * @return The current action being performed.
		 */
		Action getAction() const {
			return _action;
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
		Action _action;
		bool _paused;
		float _progress;
	};
}

#endif
