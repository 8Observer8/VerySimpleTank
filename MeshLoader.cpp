/*
    A very simple tank model

    Copyright (C) 2014  Enzhaev Ivan

    Email: 8observer8@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "MeshLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>
#include <QDebug>

MeshLoader::MeshLoader( const QString &fileName )
{
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile( fileName.toStdString(), aiProcess_Triangulate );

    if ( scene == 0 )
    {
        std::cout << "Error: unable to open the file " << fileName.toStdString() << std::endl;
        return;
    }

    if ( ( scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE ) ||
         ( !scene->mRootNode ) )
    {
        std::cout << "Error: the file wasn't successfully opened " << fileName.toStdString();
        return;
    }

    unsigned int numChildren = scene->mRootNode->mNumChildren;
    for( unsigned int i = 0; i < numChildren; ++i )
    {
        aiNode *node = scene->mRootNode->mChildren[i];
        aiMesh *mesh = scene->mMeshes[node->mMeshes[0]];

        if ( std::string( node->mName.C_Str() ) == std::string( "Plane" ) )
        {
            fillContainers( planeVertices, planeColors, planeNormals, mesh, scene );
        }
        else if ( std::string( node->mName.C_Str() ) == std::string( "GunTube_Cube.004" ) )
        {
            fillContainers( gunTubeVertices, gunTubeColors, gunTubeNormals, mesh, scene );
        }
        else if ( std::string( node->mName.C_Str() ) == std::string( "Turret_Cube.003" ) )
        {
            fillContainers( turretVertices, turretColors, turretNormals, mesh, scene );
        }
        else if ( std::string( node->mName.C_Str() ) == std::string( "Body_Cube.002" ) )
        {
            fillContainers( bodyVertices, bodyColors, bodyNormals, mesh, scene );
        }
        else if ( std::string( node->mName.C_Str() ) == std::string( "TrackRightFront_Cylinder.006" ) )
        {
            fillContainers( trackRightFrontVertices, trackRightFrontColors, trackRightFrontNormals, mesh, scene );
        }
        else if ( std::string( node->mName.C_Str() ) == std::string( "TrackRightBack_Cylinder.005" ) )
        {
            fillContainers( trackRightBackVertices, trackRightBackColors, trackRightBackNormals, mesh, scene );
        }
        else if ( std::string( node->mName.C_Str() ) == std::string( "TrackLeftFront_Cylinder.002" ) )
        {
            fillContainers( trackLeftFrontVertices, trackLeftFrontColors, trackLeftFrontNormals, mesh, scene );
        }
        else if ( std::string( node->mName.C_Str() ) == std::string( "TrackLeftBack_Cylinder.001" ) )
        {
            fillContainers( trackLeftBackVertices, trackLeftBackColors, trackLeftBackNormals, mesh, scene );
        }
        else if ( std::string( node->mName.C_Str() ) == std::string( "TrackLeftMiddle_Cube.001" ) )
        {
            fillContainers( trackLeftMiddleVertices, trackLeftMiddleColors, trackLeftMiddleNormals, mesh, scene );
        }
        else if ( std::string( node->mName.C_Str() ) == std::string( "TrackRightMiddle_Cube" ) )
        {
            fillContainers( trackRightMiddleVertices, trackRightMiddleColors, trackRightMiddleNormals, mesh, scene );
        }
    }
}

MeshLoader::~MeshLoader()
{

}

void MeshLoader::fillContainers( std::vector<float> &vertices,
                                 std::vector<float> &colors,
                                 std::vector<float> &normals,
                                 aiMesh *mesh , const aiScene *scene )
{
    unsigned int numVertices = mesh->mNumVertices;

    vertices.resize( numVertices * 3 );
    colors.resize( numVertices * 3 );
    normals.resize( numVertices * 3 );

    aiColor4D col;
    aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
    aiGetMaterialColor( mat, AI_MATKEY_COLOR_DIFFUSE, &col );

    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int d = 0;

    for ( unsigned int i = 0; i < numVertices; ++i )
    {
        vertices[j++] = mesh->mVertices[i].x;
        vertices[j++] = mesh->mVertices[i].y;
        vertices[j++] = mesh->mVertices[i].z;

        colors[k++] = col.r;
        colors[k++] = col.g;
        colors[k++] = col.b;

        normals[d++] = mesh->mNormals[i].x;
        normals[d++] = mesh->mNormals[i].y;
        normals[d++] = mesh->mNormals[i].z;
    }
}

