/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_FILEUTILS_H_
#define _NUTI_FILEUTILS_H_

#include <string>

namespace Nuti {
    
    class FileUtils {
    public:
        static std::string GetFileName(const std::string& fullPath);

        static std::string GetFilePath(const std::string& fullPath);

        static std::string NormalizePath(const std::string& path);
 
    private:
        FileUtils();
    };

}

#endif
