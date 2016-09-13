/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NMLGL_MESHINSTANCE_H_
#define _NUTI_NMLGL_MESHINSTANCE_H_

#include "BaseTypes.h"

#include <map>
#include <vector>
#include <memory>
#include <string>

namespace nml {
    class MeshInstance;
}

namespace Nuti { namespace nmlGL {
    class Material;
    class Mesh;
    class Texture;
        
    class MeshInstance {
    public:
        MeshInstance(const nml::MeshInstance& meshInstance, const std::map<std::string, std::shared_ptr<Mesh>>& meshMap, const std::map<std::string, std::shared_ptr<Texture>>& textureMap);

        void replaceMesh(const std::string& meshId, const std::shared_ptr<Mesh>& glMesh);
        void replaceTexture(const std::string& textureId, const std::shared_ptr<Texture>& glTexture);

        void draw(const std::shared_ptr<GLContext>& gl);

        void calculateRayIntersections(const Ray& ray, std::vector<RayIntersection>& intersections) const;

        int getDrawCallCount() const;

    private:
        std::string _meshId;
        std::shared_ptr<Mesh> _mesh;
        std::map<std::string, std::shared_ptr<Material>> _materialMap;
        bool _transformEnabled;
        cglib::mat4x4<float> _transformMatrix;
    };

} }

#endif
