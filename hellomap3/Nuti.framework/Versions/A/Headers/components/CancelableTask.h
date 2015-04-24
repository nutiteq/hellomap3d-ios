/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CANCELABLETASK_H_
#define _NUTI_CANCELABLETASK_H_

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
