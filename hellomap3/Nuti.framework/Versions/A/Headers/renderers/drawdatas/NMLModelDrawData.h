/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NMLMODELDRAWDATA_H_
#define _NUTI_NMLMODELDRAWDATA_H_

#include "VectorElementDrawData.h"

#include <memory>

#include <cglib/mat.h>

namespace nml {
    class Model;
}

namespace Nuti {

    class NMLModelDrawData : public VectorElementDrawData {
    public:
        NMLModelDrawData(const std::shared_ptr<nml::Model>& sourceModel, const cglib::mat4x4<double>& localMat);
    
        std::shared_ptr<nml::Model> getSourceModel() const;
        const cglib::mat4x4<double>& getLocalMat() const;
        
        virtual void offsetHorizontally(double offset);
    
    private:
        std::shared_ptr<nml::Model> _sourceModel;
        cglib::mat4x4<double> _localMat;
    };
    
}

#endif
