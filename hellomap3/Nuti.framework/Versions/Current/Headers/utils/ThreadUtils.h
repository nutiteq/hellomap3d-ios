#ifndef THREADUTILS_H
#define THREADUTILS_H

#include <thread>

namespace Nuti {

class ThreadWorker;

namespace ThreadPriority {
	enum ThreadPriority {MINIMUM = 20, LOW = 10, NORMAL = 0, HIGH = -10, MAXIMUM = -20};
}

class ThreadUtils {
public:
	static void SetThreadPriority(ThreadPriority::ThreadPriority priority);
};

}

#endif
