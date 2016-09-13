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

        struct HeaderLess {
            bool operator() (const std::string& header1, const std::string& header2) const {
                return std::lexicographical_compare(header1.begin(), header1.end(), header2.begin(), header2.end(), [](char c1, char c2) {
                    return uncase(c1) < uncase(c2);
                });
            }

        private:
            static char uncase(char c) {
                return c >= 'A' && c <= 'Z' ? (c - 'A' + 'a') : c;
            }
        };

        struct Request {
            std::string url;
            std::string method = "GET";
            std::uint64_t contentOffset = 0;
            std::map<std::string, std::string, HeaderLess> headers;
            std::vector<unsigned char> body;

            explicit Request(const std::string& url) : url(url) { }
        };

        struct Response {
            int statusCode = -1;
            std::map<std::string, std::string, HeaderLess> headers;
            std::vector<unsigned char> body;

            Response() { }
            explicit Response(int statusCode) : statusCode(statusCode) { }
        };

        explicit HTTPClient(bool log);

        int get(const std::string& url, const std::map<std::string, std::string>& requestHeaders, std::map<std::string, std::string>& responseHeaders, std::shared_ptr<std::vector<unsigned char> >& responseData) const;
        int get(const std::string& url, const std::map<std::string, std::string>& requestHeaders, std::map<std::string, std::string>& responseHeaders, HandlerFn handler, std::uint64_t offset) const;

    private:
        class Impl {
        public:
            virtual ~Impl();
            
            virtual Response makeRequest(const Request& request, HandlerFn handler) const = 0;
        };

        class PionImpl;
        class AndroidImpl;
        class CFImpl;
        class WinSockImpl;

        bool _log;
        std::unique_ptr<Impl> _impl;
    };

}

#endif
