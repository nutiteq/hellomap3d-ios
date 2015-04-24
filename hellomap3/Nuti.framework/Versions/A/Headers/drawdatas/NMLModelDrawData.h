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

namespace Nuti {
    class NMLModel;

    class NMLModelDrawData : public VectorElementDrawData {
    public:
        NMLModelDrawData(const std::shared_ptr<NMLModel>& model, const cglib::mat4x4<double>& localMat);
    
        std::shared_ptr<NMLModel> getModel() const;
        const cglib::mat4x4<double>& getLocalMat() const;
    
    private:
        std::shared_ptr<NMLModel> _model;
        cglib::mat4x4<double> _localMat;
    };
    
}

#endif
