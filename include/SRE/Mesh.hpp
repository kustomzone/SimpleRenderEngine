#pragma once

#include "glm/glm.hpp"
#include <vector>
#include "SRE/MeshTopology.hpp"

#include "SRE/Export.hpp"

namespace SRE {

    class Shader;

    /**
     * Represents a Mesh object.
     * When constructing a mesh object, its data is uploaded to the CPU and is no longer available on the CPU.
     * A mesh is composed of a list of
     * - vertexPositions (vec3)
     * - normals (vec3)
     * - uvs (aka. texture coordinates) (vec2)
     *
     * A mesh also has a meshType, which can be either: MeshTopology::Points, MeshTopology::Lines, or MeshTopology::Triangles
     */
    class DllExport Mesh {
    public:
        Mesh(std::vector<glm::vec3> &vertexPositions, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uvs, MeshTopology meshTopology = MeshTopology::Triangles);
        ~Mesh();

        void update(std::vector<glm::vec3> &vertexPositions, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uvs);

        int getVertexCount();
        MeshTopology getMeshTopology();

        static Mesh* createQuad();
        static Mesh* createCube();
        static Mesh* createSphere();
    private:
        MeshTopology meshTopology;
        unsigned int vertexBufferId;
        unsigned int vertexArrayObject;
        int vertexCount;

        void bind();

        friend class SimpleRenderEngine;
    };
}