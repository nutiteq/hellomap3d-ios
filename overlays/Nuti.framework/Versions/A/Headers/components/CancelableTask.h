#ifndef CANCELABLETASK_H_
#define CANCELABLETASK_H_

#include "components/Task.h"

#include <mutex>

namespace Nuti {

class CancelableTask : public Task {
public:
	virtual ~CancelableTask() {}

	bool isCanceled() const {
		std::lock_guard<std::mutex> lock(_mutex);
		return _canceled;
	}

	virtual void cancel() {
		std::lock_guard<std::mutex> lock(_mutex);
		_canceled = true;
	}

protected:
	CancelableTask() :
		_canceled(false),
		_mutex()
	{}

	bool _canceled;

	mutable std::mutex _mutex;
};

}

#endif
