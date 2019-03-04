#pragma once

#include <vector>

#include "opengl/shaderprogram.h"

#include "../maths/vec.h"

struct Vertex{
    Vec3 vertice;
    Vec2 uv;
    Vec3 normal;

    Vertex() = default;
    Vertex(const Vec3 &vertice, const Vec2 &uv, const Vec3 &normal) : vertice(vertice), uv(uv), normal(normal) {}

    friend QDebug operator<<(QDebug dbg, const Vertex &vertex);
};


class Mesh{

    std::string o_name;
    std::vector<Vec3> m_Vertices;
    std::vector<Vec2> m_UVs;
    std::vector<Vec3> m_Normals;
    std::vector<unsigned int> m_Vertices_indexlist;
    std::vector<unsigned int> m_UVs_indexlist;
    std::vector<unsigned int> m_Normals_indexlist;

public:

    Mesh(const char* filepath);

    Mesh(std::vector<Vec3> &vertices,
    std::vector<Vec2> &uvs,
    std::vector<Vec3> &normals,
    std::vector<unsigned int> &vertices_indexlist,
    std::vector<unsigned int> &uvs_indexlist,
    std::vector<unsigned int> &normals_indexlist);

public:

    void getVertexList(std::vector<Vertex> &vertexList);

    void getVertexListwithElements(std::vector<Vertex> &vertexList, std::vector<unsigned short> &elements);

    inline const char* getMeshName() const { return o_name.c_str(); }
    inline unsigned long getN_Vertices() const { return m_Vertices.size(); }
    inline unsigned long getN_UVs() const { return m_UVs.size(); }
    inline unsigned long getN_Normals() const { return m_Normals.size(); }
    inline unsigned long getN_Vertices_index() const { return m_Vertices_indexlist.size(); }
    inline unsigned long getN_UVs_index() const { return m_UVs_indexlist.size(); }
    inline unsigned long getN_Normals_index() const { return m_Normals_indexlist.size(); }

private:

    bool load_obj(const char* filepath);

};
