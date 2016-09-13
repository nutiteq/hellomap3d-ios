/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVTLOGGER_H_
#define _NUTI_MAPNIKVTLOGGER_H_

#include "vectortiles/MapnikVT/Logger.h"
#include "utils/Log.h"

namespace Nuti {
    
    class MapnikVTLogger : public MapnikVT::Logger {
    public:
        explicit MapnikVTLogger(const std::string& tag) : _tag(tag) { }
    
        virtual void write(Severity severity, const std::string& msg) {
            switch (severity) {
            case Severity::INFO:
                Log::Infof("%s: %s", _tag.c_str(), msg.c_str());
                break;
            case Severity::WARNING:
                Log::Warnf("%s: %s", _tag.c_str(), msg.c_str());
                break;
            case Severity::ERROR:
                Log::Errorf("%s: %s", _tag.c_str(), msg.c_str());
                break;
            }
        }

    private:
        const std::string _tag;
    };
    
}

#endif
