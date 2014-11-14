#ifndef LOCKER_H_
#define LOCKER_H_

#include <mutex>

namespace Nuti {

class Locker {
public:
	Locker();
	Locker(std::mutex& mutex);
	virtual ~Locker();

	void finalize();

private:
	std::mutex* _mutexPtr;
};

}

#endif
