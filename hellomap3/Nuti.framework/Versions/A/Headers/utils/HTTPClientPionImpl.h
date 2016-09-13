/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_HTTPCLIENTPIONIMPL_H_
#define _NUTI_HTTPCLIENTPIONIMPL_H_

#include <asio.hpp>
#include <pion/http/parser.hpp>
#include <pion/http/response.hpp>
#include <pion/tcp/connection.hpp>

#include "HTTPClient.h"

namespace Nuti {

    class HTTPClient::PionImpl : public HTTPClient::Impl {
    public:
        explicit PionImpl(bool log);

        virtual HTTPClient::Response makeRequest(const HTTPClient::Request& request, HTTPClient::HandlerFn handler) const;

    private:
        struct Connection {
            int maxRequests;
            std::chrono::steady_clock::time_point keepAliveTime;
            asio::io_service ioService;
            std::shared_ptr<pion::tcp::connection> connection;

            Connection(const std::string& host, std::uint16_t port);

            bool isValid() const;
        };

        HTTPClient::Response makeRequest(Connection& connection, const HTTPClient::Request& request, HTTPClient::HandlerFn handler) const;

        bool _log;
        mutable std::multimap<std::pair<std::string, int>, std::shared_ptr<Connection> > _connectionMap;
        mutable std::mutex _mutex;
    };

}

#endif
