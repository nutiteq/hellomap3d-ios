#ifndef NMLMODELDRAWDATA_H_
#define NMLMODELDRAWDATA_H_

#include "VectorElementDrawData.h"
#include "vectorelements/NMLModel.h"
#include "nmlpackage/GLModel.h"

#include <memory>

namespace Nuti {

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
