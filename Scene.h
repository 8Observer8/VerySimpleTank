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

#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QMouseEvent>
#include "Tank.h"

class Scene : public QOpenGLWidget
{
public:
    Scene( QWidget *parent = 0 );
    ~Scene();

private:
    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );

    void mousePressEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );

    void setXRotation( int angle );
    void setYRotation( int angle );
    void setZRotation( int angle );

    int m_xRot;
    int m_yRot;
    int m_zRot;

    QPoint m_lastPos;

    Tank *m_tank;

    QOpenGLShaderProgram m_program;
    int m_vertexAttrLoc;
    int m_colorAttrLoc;
    int m_normalAttrLoc;

    int m_mvMatrixLoc;
    int m_projMatrixLoc;
    int m_normalMatrixLoc;

    int m_lightPosLoc;

    QMatrix4x4 m_world;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_proj;
};

#endif // SCENE_H
