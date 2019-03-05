#include "mesh.h"
#include "../utils/utils.h"
#include <QFile>


Mesh::Mesh(const char* filepath){
    load_obj(filepath);
}

Mesh::Mesh(std::vector<vec3> &vertices,
           std::vector<vec2> &uvs,
           std::vector<vec3> &normals,
           std::vector<unsigned int> &vertices_indexlist,
           std::vector<unsigned int> &uvs_indexlist,
           std::vector<unsigned int> &normals_indexlist)
    : m_Vertices(vertices), m_UVs(uvs), m_Normals(normals), m_Vertices_indexlist(vertices_indexlist), m_UVs_indexlist(uvs_indexlist), m_Normals_indexlist(normals_indexlist){

}

void Mesh::getVertexList(std::vector<Vertex> &vertexList){
    vertexList = std::vector<Vertex>(m_Vertices_indexlist.size(), Vertex({0,0,0},{-1,-1},{0,0,0}));
    unsigned long i = 0;
    for(auto index : m_Vertices_indexlist){
        vertexList[i].vertice = m_Vertices[index];
        if(m_UVs.size())
            vertexList[i].uv = m_UVs[m_UVs_indexlist[i]];
        if(m_Normals.size())
            vertexList[i].normal = m_Normals[m_Normals_indexlist[i]];

        i++;
    }
}

void Mesh::getVertexListwithElements(std::vector<Vertex> &vertexList, std::vector<unsigned short> &elements){
    vertexList = std::vector<Vertex>(m_Vertices.size(), Vertex({0,0,0},{0,0},{0,0,0}));
    unsigned long i = 0;
    for(Vertex &vertex : vertexList){
        vertex.vertice = m_Vertices[i];
        vertex.uv = {0,0};
        vertex.normal = {0,0,0};
        i++;
    }
    for(auto vertice_index : m_Vertices_indexlist){
        elements.push_back(vertice_index);
    }
    //So funciona os vertices
}

bool Mesh::load_obj(const char* filepath){
    QFile file(filepath);
    if( !file.open(QIODevice::ReadOnly) ){
        LOG << "Impossible to open the file !\n";
        return false;
    }
    char line[128];
    while (file.readLine(line, 128) != -1){
        if (char* s = strstr(line, "o ")){
            o_name = std::string(s+2);
        }else if (char* s = strstr(line, "v ")){
            char xc[10],yc[10],zc[10];
            sscanf(s+2, "%s %s %s", xc, yc, zc);
            float x,y,z;
            x = QString(xc).toFloat();
            y = QString(yc).toFloat();
            z = QString(zc).toFloat();
            m_Vertices.push_back({x,y,z});
        }else if (char* s = strstr(line, "vt ")) {
            char xc[10],yc[10];
            sscanf(s+3, "%s %s", xc, yc);
            float x,y;
            x = QString(xc).toFloat();
            y = QString(yc).toFloat();
            m_UVs.push_back({x,y});
        }else if (char* s = strstr(line, "vn ")) {
            char xc[10],yc[10],zc[10];
            sscanf(s+3, "%s %s %s", xc, yc, zc);
            float x,y,z;
            x = QString(xc).toFloat();
            y = QString(yc).toFloat();
            z = QString(zc).toFloat();
            m_Normals.push_back({x,y,z});
        }else if (char* s = strstr(line, "f ")){
            unsigned int vertexIndex[3] = {1,1,1}, uvIndex[3] = {1,1,1}, normalIndex[3] = {1,1,1};

            if (m_UVs.size() && m_Normals.size()) {
                int matches = sscanf(s+2, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                if (matches != 9){
                    LOG << "File can't be read by our simple parser : ( Try exporting with other options : " << matches;
                    return false;
                }
                m_Vertices_indexlist.push_back(vertexIndex[0]-1);
                m_Vertices_indexlist.push_back(vertexIndex[1]-1);
                m_Vertices_indexlist.push_back(vertexIndex[2]-1);
                m_UVs_indexlist.push_back(uvIndex[0]-1);
                m_UVs_indexlist.push_back(uvIndex[1]-1);
                m_UVs_indexlist.push_back(uvIndex[2]-1);
                m_Normals_indexlist.push_back(normalIndex[0]-1);
                m_Normals_indexlist.push_back(normalIndex[1]-1);
                m_Normals_indexlist.push_back(normalIndex[2]-1);

            }else if(m_UVs.size()){
                int matches = sscanf(s+2, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
                if (matches != 6){
                    LOG << "File can't be read by our simple parser : ( Try exporting with other options : " << matches;
                    return false;
                }
                m_Vertices_indexlist.push_back(vertexIndex[0]-1);
                m_Vertices_indexlist.push_back(vertexIndex[1]-1);
                m_Vertices_indexlist.push_back(vertexIndex[2]-1);
                m_UVs_indexlist.push_back(uvIndex[0]-1);
                m_UVs_indexlist.push_back(uvIndex[1]-1);
                m_UVs_indexlist.push_back(uvIndex[2]-1);

            }else if (m_Normals.size()) {
                int matches = sscanf(s+2, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
                if (matches != 6){
                    LOG << "File can't be read by our simple parser : ( Try exporting with other options : " << matches;
                    return false;
                }
                m_Vertices_indexlist.push_back(vertexIndex[0]-1);
                m_Vertices_indexlist.push_back(vertexIndex[1]-1);
                m_Vertices_indexlist.push_back(vertexIndex[2]-1);
                m_Normals_indexlist.push_back(normalIndex[0]-1);
                m_Normals_indexlist.push_back(normalIndex[1]-1);
                m_Normals_indexlist.push_back(normalIndex[2]-1);

            }else {
                int matches = sscanf(s+2, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
                if (matches != 3){
                    LOG << "File can't be read by our simple parser : ( Try exporting with other options : " << matches;
                    return false;
                }
                m_Vertices_indexlist.push_back(vertexIndex[0]-1);
                m_Vertices_indexlist.push_back(vertexIndex[1]-1);
                m_Vertices_indexlist.push_back(vertexIndex[2]-1);

            }

        }
        else if (line[0] == '#'){
            /* ignoring this line */
        }
        else{
            /* ignoring this line */
        }
    }
    return true;
}

//Para usar o LOG no Vertex
QDebug operator<<(QDebug dbg, const Vertex &vertex){
    QDebugStateSaver saver(dbg);
    dbg.nospace() << "\n\033[0m\033[32mVertex(\033[0m " << vertex.vertice << ", " << vertex.uv << ", " << vertex.normal << " \033[0m\033[32m)\033[0m";
    return dbg;
}
