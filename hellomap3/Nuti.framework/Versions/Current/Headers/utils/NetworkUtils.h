/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NETWORKUTILS_H_
#define _NUTI_NETWORKUTILS_H_

#include <memory>
#include <string>
#include <vector>
#include <map>

namespace Nuti {

    class NetworkUtils {
    public:
		static bool GetHTTP(const std::string& url, std::shared_ptr<std::vector<unsigned char> >& responseData, bool log);

		static bool GetHTTP(const std::string& url, const std::map<std::string, std::string>& requestHeaders, std::map<std::string, std::string>& responseHeaders, std::shared_ptr<std::vector<unsigned char> >& responseData, bool log);
		
		static int GetMaxAgeHTTPHeader(const std::map<std::string, std::string>& headers);
    
        static std::string URLEncode(const std::string& value);
    
        static std::string URLEncodeMap(const std::map<std::string, std::string>& valueMap);
    
        static std::string URLDecode(const std::string& encValue);
    
        static std::map<std::string, std::string> URLDecodeMap(const std::string& encValueMap);
    
        static std::string BuildURLFromParameters(const std::string& baseUrl, const std::map<std::string, std::string>& params);
    
        static std::string ParseURLHostName(std::string url);
    
        static int ParseURLPort(std::string url);
    
        static std::string ParseURLPath(std::string url);
    
    private:
        static const int BUFFER_SIZE = 1024;
    };
    
}

#endif
