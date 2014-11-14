#ifndef NMLMODELDATASOURCE_H_
#define NMLMODELDATASOURCE_H_

#include "datasources/VectorDataSource.h"
#include "vectorelements/NMLModel.h"

#include <memory>

namespace Nuti {

class Projection;
class ViewState;

/**
 * An abstract base class for 3D NML model data sources. This is an envelope-based data source.
 */
class NMLModelDataSource : public VectorDataSource {
public:
    virtual ~NMLModelDataSource();

protected:
	NMLModelDataSource(const std::shared_ptr<Projection>& projection);
    
};

}

#endif
