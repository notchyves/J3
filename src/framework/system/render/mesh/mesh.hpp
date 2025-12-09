#pragma once
#include "common.hpp"

#include "framework/system/render/buffer/d3d_buffer.hpp"
#include "vertex.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct mesh {
    std::vector<vertex> vertices;
    std::vector<DWORD> indices;

    std::unique_ptr<d3d_buffer> vertex_buffer;
    std::unique_ptr<d3d_buffer> index_buffer;

    mesh(const std::vector<vertex>& vertices, const std::vector<DWORD>& indices)
        : vertices(vertices), indices(indices) {
        this->vertex_buffer = std::make_unique<d3d_buffer>();
        this->index_buffer = std::make_unique<d3d_buffer>();
    }

    mesh(const mesh& other) {
        this->vertices = other.vertices;
        this->indices = other.indices;

        // buffers will be recreated on render
        this->vertex_buffer = std::make_unique<d3d_buffer>();
        this->index_buffer = std::make_unique<d3d_buffer>();
    }

    // load verts and indices from file or resource
    static std::vector<mesh> load(const std::string& path) {
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(
            path,
            aiProcess_Triangulate | aiProcess_ConvertToLeftHanded
        );

        if (scene == nullptr) {
            spdlog::error("Failed to load mesh from path: {}", path);
            return { };
        }

        return process_nodes(scene, scene->mRootNode);
    }

    static std::vector<mesh> load(const resource& res) {
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFileFromMemory(
            res.data(),
            res.size(),
            aiProcess_Triangulate | aiProcess_ConvertToLeftHanded
        );

        if (scene == nullptr) {
            spdlog::error("Failed to load mesh from memory");
            return { };
        }

        return process_nodes(scene, scene->mRootNode);
    }

private:
    static std::vector<mesh> process_nodes(const aiScene* scene, const aiNode* node) {
        std::vector<mesh> ret;
        
        for (UINT i = 0; i < node->mNumMeshes; i++) {
            aiMesh* m = scene->mMeshes[node->mMeshes[i]];
            ret.push_back(process_mesh(m));
        }

        for (UINT i = 0; i < node->mNumChildren; i++) {
            for (auto meshes = process_nodes(scene, node->mChildren[i]);
                const auto& m : meshes) {
                ret.push_back(m);
            }
        }

        return ret;
    }

    static mesh process_mesh(const aiMesh* m) {
        std::vector<vertex> vertices;
        std::vector<DWORD> indices;

        bool has_uv = m->mTextureCoords[0];
        
        for (UINT i = 0; i < m->mNumVertices; i++) {
            vertex v;

            v.position.x = m->mVertices[i].x;
            v.position.y = m->mVertices[i].y;
            v.position.z = m->mVertices[i].z;

            if (has_uv) {
                v.uv.x = m->mTextureCoords[0][i].x;
                v.uv.y = m->mTextureCoords[0][i].y;
            }

            v.color = { 0, 0, 0, 0.75f };

            vertices.push_back(v);
        }

        for (UINT i = 0; i < m->mNumFaces; i++) {
            aiFace f = m->mFaces[i];

            for (UINT j = 0; j < f.mNumIndices; j++) {
                indices.push_back(f.mIndices[j]);
            }
        }

        return { vertices, indices };
    }
};
