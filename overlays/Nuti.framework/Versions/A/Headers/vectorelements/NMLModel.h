#ifndef NMLMODEL_H_
#define NMLMODEL_H_

#include "VectorElement.h"
#include "core/MapVec.h"

#include <memory>
#include <vector>

#include <cglib/mat.h>

namespace NMLPackage {
class Model;
}

namespace Nuti {
    
class MapPos;
class NMLModelDrawData;
class PointGeometry;

/**
 * A 3D model that can be displayed on the map.
 *
 * NML models can be created from Collada files directly and placed anywhere on the map or converted from KMZ files.
 * NML models are optimized for fast loading and rendering.
 */
class NMLModel : public VectorElement {
public:
    /**
     * Constructs a NMLModel object from a geometry object and a source model.
     * @param geometry The geometry object that defines the location of this model.
     * @param sourceModel The 3D source model that defines what this model looks like.
     */
	NMLModel(const std::shared_ptr<PointGeometry>& geometry, const std::shared_ptr<NMLPackage::Model>& sourceModel);
    /**
     * Constructs a NMLModel object from a map position and a source model.
     * @param poses The map position that defines the location of this model.
     * @param sourceModel The 3D source model that defines what this model looks like.
     */
    NMLModel(const MapPos& pos, const std::shared_ptr<NMLPackage::Model>& sourceModel);
	/**
	* Constructs a NMLModel object from a geometry object and serialized model data.
	* @param geometry The geometry object that defines the location of this model.
	* @param sourceModelData Serialized data for 3D model.
	*/
	NMLModel(const std::shared_ptr<PointGeometry>& geometry, const std::shared_ptr<std::vector<unsigned char> >& sourceModelData);
	/**
	* Constructs a NMLModel object from a map position and serialized model data.
	* @param poses The map position that defines the location of this model.
	* @param sourceModelData Serialized data for 3D model.
	*/
	NMLModel(const MapPos& pos, const std::shared_ptr<std::vector<unsigned char> >& sourceModelData);
	virtual ~NMLModel();

    virtual const MapBounds& getBounds() const;
    
	std::shared_ptr<PointGeometry> getGeometry() const;
	/**
     * Sets the location for this model.
     * @param geometry The new geometry object that defines the location of this model.
     */
	void setGeometry(const std::shared_ptr<PointGeometry>& geometry);
	/**
     * Sets the location for this model.
     * @param pos The new map position that defines the location of this model.
     */
    void setPos(const MapPos& pos);
    
    /**
	 * Returns a local transformation matrix. Includes rotation and scaling transformation.
	 * @return A 4x4 transformation matrix.
	 */
	cglib::mat4x4<float> getLocalMat() const;

	/**
	 * Returns the rotation axis of this model. If rotation angle is 0, then the axis is irrelevant.
	 * @return The rotation axis vector.
	 */
    const MapVec& getRotationAxis() const;

	/**
	 * Returns the rotation angle of this model.
	 * @return The rotation angle of this model in degrees.
	 */
	float getRotationAngle() const;

	/**
	 * Sets the rotation of this model using an axis and an angle.
	 * @param axis The axis of rotation.
	 * @param angle The rotation angle in degrees.
	 */
	void setRotation(const MapVec& axis, float angle);

	/**
	 * Returns the scale of this model.
	 * @return model The relative scale.
	 */
	float getScale() const;

	/**
	 * Sets the scale of this model. The default is 1.
	 * @param scale The relative scale of this model.
	 */
	void setScale(float scale);
    
    /**
     * Returns the source model of this model.
     * @return The 3D source model that defines what this model looks like.
     */
	std::shared_ptr<NMLPackage::Model> getSourceModel() const;
    
protected:
    friend class NMLModelRenderer;
    friend class VectorLayer;
    
    std::shared_ptr<NMLModelDrawData> getDrawData() const;
    void setDrawData(const std::shared_ptr<NMLModelDrawData>& drawData);
    
private:
    static std::shared_ptr<NMLPackage::Model> ParseModel(const std::vector<unsigned char>& modelData);
    
    MapBounds _bounds;
    
    std::shared_ptr<NMLModelDrawData> _drawData;
    
	MapVec _rotationAxis;
	float _rotationAngle;
    
	float _scale;
    
	std::shared_ptr<NMLPackage::Model> _sourceModel;
};

}

#endif
