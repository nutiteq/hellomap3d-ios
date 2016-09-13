/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_HTTPCLIENTCFIMPL_H_
#define _NUTI_HTTPCLIENTCFIMPL_H_

#include <CFNetwork/CFNetwork.h>

#include "utils/HTTPClient.h"

namespace Nuti {

    class HTTPClient::CFImpl : public HTTPClient::Impl {
    public:
        explicit CFImpl(bool log);

        virtual HTTPClient::Response makeRequest(const HTTPClient::Request& request, HTTPClient::HandlerFn handler) const;

    private:
        bool _log;
    };

}

#endif
