#ifndef TASK_H_
#define TASK_H_

namespace Nuti {

class Task {
public:
	virtual ~Task() {}
    
    virtual void run() = 0;

	void operator()();
    
protected:
	Task() {}
};

}

#endif
