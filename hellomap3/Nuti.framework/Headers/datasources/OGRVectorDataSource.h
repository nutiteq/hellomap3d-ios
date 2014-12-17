/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_OGRVECTORDATASOURCE_H_
#define _NUTI_OGRVECTORDATASOURCE_H_

#ifdef _NUTI_GDAL_SUPPORT

#include "VectorDataSource.h"
#include "core/MapBounds.h"

#include <vector>

class OGRLayer;
class OGRDataSource;
class OGRSpatialReference;
class OGRCoordinateTransformation;

namespace Nuti {
    class StyleSelector;
    class ViewState;
    class GeometrySimplifier;

    /**
     * High-level vector element data source that supports various OGR data formats.
     * Shapefiles, GeoJSON, KML files can be used using this data source.
     */
    class OGRVectorDataSource : public VectorDataSource {
    public:
        /**
         * Constructs a new OGR data source given style selector and OGR supported data file.
         * If data file contains multiple layers, all layers will be used.
         * @param projection The projection to use for data coordinates. Note that if actual data is in different coordinates, coordinates will be re-projected.
         * @param styleSelector The style selector to use when loading geometry from OGR file.
         * @param fileName The full path of the data file
         */
        OGRVectorDataSource(const std::shared_ptr<Projection>& projection, const std::shared_ptr<StyleSelector>& styleSelector, const std::string& fileName);

        /**
         * Constructs a new OGR data source given style selector, data file and layer name.
         * @param projection The projection to use for data coordinates. Note that if actual data is in different coordinates, coordinates will be re-projected.
         * @param styleSelector The style selector to use when loading geometry from OGR file.
         * @param fileName The full path of the data file
         * @param layerName The name of the layer to use.
         */
        OGRVectorDataSource(const std::shared_ptr<Projection>& projection, const std::shared_ptr<StyleSelector>& styleSelector, const std::string& fileName, const std::string& layerName);
        virtual ~OGRVectorDataSource();

        /**
         * Returns the current code page used for decoding DBF text data. The default is ISO-8859-1.
         * @return The current code page for text data.
         */
        const std::string& getCodePage() const;
        /**
         * Specifies the code page to use for decoding DBF text data.
         * @param codePage The codepage to use (for example, "CP1254", or any other iconv encoding)
         */
        void setCodePage(const std::string& codePage);

        /**
         * Returns the active geometry simplifier of the data source.
         * @return The current geometry simplifier (can be null)
         */
        const std::shared_ptr<GeometrySimplifier>& getGeometrySimplifier() const;
        /**
         * Attaches geometry simplifier to the data source. If the specified simplifier is null, detaches any active simplifier.
         * @param simplifier The new geometry simplifier to use (can be null).
         */
        void setGeometrySimplifier(const std::shared_ptr<GeometrySimplifier>& simplifier);
        
        /**
         * Returns the extent of this data source. Extent is the minimal bounding box encompassing all the elements.
         * @return The minimal bounding box for the elements.
         */
        MapBounds getDataExtent() const;
        
        /**
         * Finds the total feature count for this data source. For simple geometry, this corresponds to element count. In case of multigeometry, each feature is divided into multiple elements.
         * @return The feature count for the data source.
         */
        int getFeatureCount() const;
        
        /**
         * Returns the names of active layers.
         * @return The names of the used layers from the data source.
         */
        std::vector<std::string> getActiveLayerNames() const;
        
        /**
         * Returns the names of all layers in the data source. This list may contain layers that are not used.
         * @return The names of the layers contained in the data source.
         */
        std::vector<std::string> getAvailableLayerNames() const;
        
        virtual std::vector<std::shared_ptr<VectorElement> > loadElements(const std::shared_ptr<CullState>& cullState);
        
        /**
         * Sets global OGR configuration option. This method can be used to redefine default locale, for example.
         * @param name The name of the option parameter to set ("SHAPE_ENCODING", for example)
         * @param value The value of the parameter.
         */
        static void SetConfigOption(const std::string& name, const std::string& value);
        /**
         * Returns the value of global OGR configuration option.
         * @param name The name of the the option parameter to read.
         * @return The value of the specified option parameter.
         */
        static std::string GetConfigOption(const std::string& name);
        
    private:
        struct LayerSpatialReference;

        void createFeatures(const ViewState& viewState, long long id, const std::shared_ptr<Geometry>& geometry, const std::map<std::string, std::string>& metaData, std::vector<std::shared_ptr<VectorElement> >& elements) const;

        std::string _codePage;
        std::shared_ptr<StyleSelector> _styleSelector;
        std::shared_ptr<GeometrySimplifier> _geometrySimplifier;
        std::vector<std::string> _activeLayerNames;
        std::vector<std::string> _availableLayerNames;
        OGRDataSource* _poDS;
        std::vector<OGRLayer*> _poLayers;
        std::map<OGRLayer*, std::shared_ptr<LayerSpatialReference> > _poLayerSpatialReferenceMap;
        
        mutable std::mutex _mutex;
    };
}

#endif

#endif
