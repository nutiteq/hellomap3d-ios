/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_THREADUTILS_H
#define _NUTI_THREADUTILS_H

#include <thread>

namespace Nuti {

    namespace ThreadPriority {
        enum ThreadPriority {MINIMUM = 20, LOW = 10, NORMAL = 0, HIGH = -10, MAXIMUM = -20};
    }

    class ThreadUtils {
    public:
        static void SetThreadPriority(ThreadPriority::ThreadPriority priority);

    private:
        ThreadUtils();
    };

}

#endif
