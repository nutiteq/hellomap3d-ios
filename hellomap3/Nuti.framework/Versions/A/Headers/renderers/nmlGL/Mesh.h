/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NMLGL_MESH_H_
#define _NUTI_NMLGL_MESH_H_

#include "BaseTypes.h"

#include <memory>
#include <vector>

namespace nml {
    class Mesh;
    class MeshOp;
}

namespace Nuti { namespace nmlGL {
    class Submesh;
        
    class Mesh {
    public:
        Mesh(const nml::Mesh& mesh);
        Mesh(const Mesh& glMesh, const nml::MeshOp& meshOp);

        void create(const std::shared_ptr<GLContext>& gl);
        void dispose(const std::shared_ptr<GLContext>& gl);

        const std::vector<std::shared_ptr<Submesh>>& getSubmeshList() const;

        int getTotalGeometrySize() const;

    private:
        std::vector<std::shared_ptr<Submesh>> _submeshList;
    };

} }

#endif
