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

#include "Tank.h"

Tank::Tank( QOpenGLShaderProgram *program, int vertexAttrLoc,
            int colorAttrLoc, int normalAttrLoc) :
    m_program( program ),
    m_vertexAttrLoc( vertexAttrLoc ),
    m_colorAttrLoc( colorAttrLoc ),
    m_normalAttrLoc( normalAttrLoc )
{

}

Tank::~Tank()
{

}

void Tank::fill( const MeshLoader *loader )
{
    planeVertices = loader->planeVertices;
    planeColors = loader->planeColors;
    planeNormals = loader->planeNormals;

    gunTubeVertices = loader->gunTubeVertices;
    gunTubeColors = loader->gunTubeColors;
    gunTubeNormals = loader->gunTubeNormals;

    turretVertices = loader->turretVertices;
    turretColors = loader->turretColors;
    turretNormals = loader->turretNormals;

    bodyVertices = loader->bodyVertices;
    bodyColors = loader->bodyColors;
    bodyNormals = loader->bodyNormals;

    trackRightFrontVertices = loader->trackRightFrontVertices;
    trackRightFrontColors = loader->trackRightFrontColors;
    trackRightFrontNormals = loader->trackRightFrontNormals;

    trackRightBackVertices = loader->trackRightBackVertices;
    trackRightBackColors = loader->trackRightBackColors;
    trackRightBackNormals = loader->trackRightBackNormals;

    trackLeftFrontVertices = loader->trackLeftFrontVertices;
    trackLeftFrontColors = loader->trackLeftFrontColors;
    trackLeftFrontNormals = loader->trackLeftFrontNormals;

    trackLeftBackVertices = loader->trackLeftBackVertices;
    trackLeftBackColors = loader->trackLeftBackColors;
    trackLeftBackNormals = loader->trackLeftBackNormals;

    trackLeftMiddleVertices = loader->trackLeftMiddleVertices;
    trackLeftMiddleColors = loader->trackLeftMiddleColors;
    trackLeftMiddleNormals = loader->trackLeftMiddleNormals;

    trackRightMiddleVertices = loader->trackRightMiddleVertices;
    trackRightMiddleColors = loader->trackRightMiddleColors;
    trackRightMiddleNormals = loader->trackRightMiddleNormals;
}

void Tank::draw()
{
    draw( planeVertices, planeColors, planeNormals );
    draw( gunTubeVertices, gunTubeColors, gunTubeNormals );
    draw( turretVertices, turretColors, turretNormals );
    draw( bodyVertices, bodyColors, bodyNormals );
    draw( trackRightFrontVertices, trackRightFrontColors, trackRightFrontNormals );
    draw( trackRightBackVertices, trackRightBackColors, trackRightBackNormals );
    draw( trackLeftFrontVertices, trackLeftFrontColors, trackLeftFrontNormals );
    draw( trackLeftBackVertices, trackLeftBackColors, trackLeftBackNormals );
    draw( trackLeftMiddleVertices, trackLeftMiddleColors, trackLeftMiddleNormals );
    draw( trackRightMiddleVertices, trackRightMiddleColors, trackRightMiddleNormals );
}

void Tank::draw( const std::vector<float> &vertices,
                 const std::vector<float> &colors,
                 const std::vector<float> &normals )
{
    m_program->setAttributeArray( m_vertexAttrLoc, vertices.data(), 3 );
    m_program->setAttributeArray( m_colorAttrLoc, colors.data(), 3 );
    m_program->setAttributeArray( m_normalAttrLoc, normals.data(), 3 );

    m_program->enableAttributeArray( m_vertexAttrLoc );
    m_program->enableAttributeArray( m_colorAttrLoc );
    m_program->enableAttributeArray( m_normalAttrLoc );

    glDrawArrays( GL_TRIANGLES, 0, vertices.size() / 3 );

    m_program->disableAttributeArray( m_vertexAttrLoc );
    m_program->disableAttributeArray( m_colorAttrLoc );
    m_program->disableAttributeArray( m_normalAttrLoc );
}

