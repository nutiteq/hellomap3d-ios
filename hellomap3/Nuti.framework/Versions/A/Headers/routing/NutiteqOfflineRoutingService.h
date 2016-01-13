/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NUTITEQOFFLINEROUTINGSERVICE_H_
#define _NUTI_NUTITEQOFFLINEROUTINGSERVICE_H_

#include "routing/RoutingService.h"

#include <memory>
#include <string>

namespace Nuti {
    namespace Routing {
        class RouteFinder;
    }

    /**
     * An offline routing service that uses Nutiteq-specific routing database file.
     */
    class NutiteqOfflineRoutingService : public RoutingService {
    public:
        /**
         * Constructs a new NutiteqOfflineRoutingService instance given database file.
         * @param path The full path to the database file.
         */
        NutiteqOfflineRoutingService(const std::string& path);
        virtual ~NutiteqOfflineRoutingService();

        virtual std::shared_ptr<RoutingResult> calculateRoute(const std::shared_ptr<RoutingRequest>& request) const;

    protected:
        std::shared_ptr<Routing::RouteFinder> _routeFinder;
    };
    
}

#endif
