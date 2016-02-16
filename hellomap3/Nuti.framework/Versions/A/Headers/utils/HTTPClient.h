/*
* Copyright 2014 Nutiteq Llc. All rights reserved.
* Copying and using this code is allowed only according
* to license terms, as given in https://www.nutiteq.com/license/
*/

#ifndef _NUTI_HTTPCLIENT_H_
#define _NUTI_HTTPCLIENT_H_

#include <memory>
#include <string>
#include <map>
#include <vector>
#include <mutex>
#include <cstdint>
#include <functional>

namespace Nuti {

    class HTTPClient {
    public:
        typedef std::function<bool(std::uint64_t, std::uint64_t, const unsigned char*, size_t)> HandlerFn;

        explicit HTTPClient(bool log);

        int get(const std::string& url, const std::map<std::string, std::string>& requestHeaders, std::map<std::string, std::string>& responseHeaders, std::shared_ptr<std::vector<unsigned char> >& responseData) const;
        int get(const std::string& url, const std::map<std::string, std::string>& requestHeaders, std::map<std::string, std::string>& responseHeaders, HandlerFn handler, std::uint64_t offset) const;

    private:
        struct Connection;

        int handleGetRequest(Connection& connection, const std::string& url, const std::map<std::string, std::string>& requestHeaders, std::map<std::string, std::string>& responseHeaders, HandlerFn handler, std::uint64_t offset) const;

        bool _log;
        mutable std::multimap<std::pair<std::string, int>, std::shared_ptr<Connection> > _connectionMap;
        mutable std::mutex _mutex;

        static const int BUFFER_SIZE;
    };

}

#endif
