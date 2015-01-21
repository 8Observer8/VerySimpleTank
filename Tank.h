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

#ifndef TANK_H
#define TANK_H

#include <vector>
#include "MeshLoader.h"
#include <QOpenGLShaderProgram>

class Tank
{
public:
    Tank( QOpenGLShaderProgram *program, int vertexAttrLoc,
          int colorAttrLoc, int normalAttrLoc );
    ~Tank();

    void fill( const MeshLoader *loader );

    void draw();

    std::vector<float> planeVertices;
    std::vector<float> gunTubeVertices;
    std::vector<float> turretVertices;
    std::vector<float> bodyVertices;
    std::vector<float> trackRightFrontVertices;
    std::vector<float> trackRightBackVertices;
    std::vector<float> trackLeftFrontVertices;
    std::vector<float> trackLeftBackVertices;
    std::vector<float> trackLeftMiddleVertices;
    std::vector<float> trackRightMiddleVertices;

    std::vector<float> planeColors;
    std::vector<float> gunTubeColors;
    std::vector<float> turretColors;
    std::vector<float> bodyColors;
    std::vector<float> trackRightFrontColors;
    std::vector<float> trackRightBackColors;
    std::vector<float> trackLeftFrontColors;
    std::vector<float> trackLeftBackColors;
    std::vector<float> trackLeftMiddleColors;
    std::vector<float> trackRightMiddleColors;

    std::vector<float> planeNormals;
    std::vector<float> gunTubeNormals;
    std::vector<float> turretNormals;
    std::vector<float> bodyNormals;
    std::vector<float> trackRightFrontNormals;
    std::vector<float> trackRightBackNormals;
    std::vector<float> trackLeftFrontNormals;
    std::vector<float> trackLeftBackNormals;
    std::vector<float> trackLeftMiddleNormals;
    std::vector<float> trackRightMiddleNormals;

private:
    void draw( const std::vector<float> &vertices,
               const std::vector<float> &colors,
               const std::vector<float> &normals );

    QOpenGLShaderProgram *m_program;
    int m_vertexAttrLoc;
    int m_colorAttrLoc;
    int m_normalAttrLoc;
};

#endif // TANK_H
