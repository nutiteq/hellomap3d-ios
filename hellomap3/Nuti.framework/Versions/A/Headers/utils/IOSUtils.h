/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_IOSUTILS_H_
#define _NUTI_IOSUTILS_H_

#include <mutex>
#include <string>

namespace Nuti {

    /**
     * IOSUtils is an internal class of the SDK.
     * It is not intended for public usage.
     */
    class IOSUtils {
    public:
        static void InitializeLog();

    private:
        IOSUtils();
    };

}

#endif
