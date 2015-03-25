/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_GENERALUTILS_H_
#define _NUTI_GENERALUTILS_H_

#include <string>
#include <vector>

namespace Nuti {

    class GeneralUtils {
    public:
        template <typename T>
        static T Clamp(const T& value, const T& low, const T& high) {
            return value < low ? low : (value > high ? high : value);
        }
    
        static long long IntPow(int x, unsigned int p);
    
        static unsigned int UpperPow2(unsigned int n);
    
        static bool IsPow2(unsigned int n);
    
        static void ReplaceSubstrings(std::string& base, const std::string& search, const std::string& replace);
        
        static std::vector<std::string>& Split(const std::string& s, char delim, std::vector<std::string>& elems);
        
        static std::vector<std::string> Split(const std::string& s, char delim);

    private:
        GeneralUtils();
    };
    
}

#endif
