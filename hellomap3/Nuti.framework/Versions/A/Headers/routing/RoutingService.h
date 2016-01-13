/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_ROUTINGSERVICE_H_
#define _NUTI_ROUTINGSERVICE_H_

#include "routing/RoutingRequest.h"
#include "routing/RoutingResult.h"

#include <memory>

namespace Nuti {

    /**
     * An abstract base class for routing services (either online or offline).
     */
    class RoutingService {
    public:
        virtual ~RoutingService();

        /**
         * Calculates routing result (path) based on routing result.
         * @param request The routing request defining via points.
         * @return The result or null if routing failed.
         */
        virtual std::shared_ptr<RoutingResult> calculateRoute(const std::shared_ptr<RoutingRequest>& request) const = 0;

    protected:
        /**
         * The default constructor.
         */
        RoutingService();
    };
    
}

#endif
