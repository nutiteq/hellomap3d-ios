/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_THREADWORKER_H_
#define _NUTI_THREADWORKER_H_

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
