/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NUTITEQONLINEROUTINGSERVICE_H_
#define _NUTI_NUTITEQONLINEROUTINGSERVICE_H_

#include "routing/RoutingService.h"

#include <memory>
#include <string>

namespace Nuti {
    class Projection;

    /**
     * An online routing service that connects to Nutiteq-provided routing server.
     */
    class NutiteqOnlineRoutingService : public RoutingService {
    public:
        /**
         * Constructs a new NutiteqOnlineRoutingService instance given service source.
         * @param source The source id of the service.
         */
        NutiteqOnlineRoutingService(const std::string& source);
        virtual ~NutiteqOnlineRoutingService();

        virtual std::shared_ptr<RoutingResult> calculateRoute(const std::shared_ptr<RoutingRequest>& request) const;

    protected:
        std::string _source;
        
        static const double COORDINATE_SCALE;
    };
    
}

#endif
