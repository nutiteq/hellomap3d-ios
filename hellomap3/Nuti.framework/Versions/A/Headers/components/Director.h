/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_DIRECTOR_H_
#define _NUTI_DIRECTOR_H_

namespace Nuti {

    class Director {
    public:
        virtual ~Director() { }
        
        virtual void retainDirector() = 0;
        virtual void releaseDirector() = 0;

        virtual void* getDirectorObject() const = 0;
    };

}

#endif
