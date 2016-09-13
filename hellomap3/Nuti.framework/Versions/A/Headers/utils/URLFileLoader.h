/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_URLFILELOADER_H_
#define _NUTI_URLFILELOADER_H_

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <mutex>

namespace Nuti {
    
    class URLFileLoader {
    public:
        URLFileLoader(const std::string& tag, bool cacheFiles);
        virtual ~URLFileLoader();

        bool loadFile(const std::string& url, std::shared_ptr<std::vector<unsigned char> >& data) const;
        
    private:
        const std::string _tag;
        const bool _cacheFiles;
        mutable std::map<std::string, std::shared_ptr<std::vector<unsigned char> > > _cachedFiles;
        mutable std::mutex _mutex;
    };

}

#endif
