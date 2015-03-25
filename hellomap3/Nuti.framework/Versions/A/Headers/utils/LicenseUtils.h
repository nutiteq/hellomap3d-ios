/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_LICENSEUTILS_H_
#define _NUTI_LICENSEUTILS_H_

#include <string>
#include <mutex>

namespace Nuti {
    
    namespace LicenseType {
        enum LicenseType {
            LICENSE_TYPE_EVALUATION,
            LICENSE_TYPE_EXPIRED,
            LICENSE_TYPE_NUTITEQ,
            LICENSE_TYPE_CUSTOM
        };
    };
    
    class LicenseUtils {
    public:
        static LicenseType::LicenseType RegisterLicense(const std::string& licenseString);

        static std::string GetUserKey();
        
    private:
        LicenseUtils();

        static const std::string LICENSE_PREFIX;
        
        static const std::string PUBLIC_KEY;
        
        static const std::string PRODUCT_VERSION;

        static std::string _UserKey;

        static std::mutex _Mutex;
    };
    
}

#endif
