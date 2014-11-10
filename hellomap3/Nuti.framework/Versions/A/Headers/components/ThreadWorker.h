#ifndef THREADWORKER_H_
#define THREADWORKER_H_

namespace Nuti {

class ThreadWorker {
public:
	virtual ~ThreadWorker() {}

	virtual void operator()() = 0;

protected:
	ThreadWorker() {}

};

}

#endif
