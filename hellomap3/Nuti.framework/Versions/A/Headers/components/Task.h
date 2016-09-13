/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_TASK_H_
#define _NUTI_TASK_H_

#include <memory>

namespace Nuti {

    class Task : public std::enable_shared_from_this<Task> {
    public:
        virtual ~Task() {}

        void operator()();

    protected:
        Task() {}

        virtual void run() = 0;
    };

}

#endif
