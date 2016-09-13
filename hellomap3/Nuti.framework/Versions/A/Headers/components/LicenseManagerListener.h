/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_LICENSEMANAGERLISTENER_H_
#define _NUTI_LICENSEMANAGERLISTENER_H_

namespace Nuti {

    /**
     * An internal listener class for notifying about license update events.
     */
    class LicenseManagerListener {
    public:
        virtual ~LicenseManagerListener() { }
    
        /**
         * Called when the new license has been retrieved.
         */
        virtual void onLicenseUpdated(const std::string& licenseKey) = 0;
    };
    
}

#endif
