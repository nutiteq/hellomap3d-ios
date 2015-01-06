/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VECTORELEMENTDRAWDATA_H_
#define _NUTI_VECTORELEMENTDRAWDATA_H_

#include "graphics/Color.h"

#include <memory>

namespace Nuti {
    class VectorElement;
    
    class VectorElementDrawData {
    public:
        virtual ~VectorElementDrawData();
    
        const Color& getColor() const;
    
    protected:
        VectorElementDrawData(const Color& color);
    
    private:
        Color _color;
    };
    
}

#endif
