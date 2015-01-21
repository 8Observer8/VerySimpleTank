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

#include "Scene.h"
#include "MeshLoader.h"
#include <QDir>
#include <QVector3D>
#include <QDebug>

Scene::Scene( QWidget *parent ) :
    QOpenGLWidget( parent ),
    m_xRot( 0 ),
    m_yRot( 0 ),
    m_zRot( 0 )
{

}

Scene::~Scene()
{
    delete m_tank;
}

void Scene::initializeGL()
{
    glClearColor( 0.1f, 0.1f, 0.2f, 1.0f );

    MeshLoader loader( QDir::currentPath() + QString( "/Models/Tank.obj" ) );

    QOpenGLShader vShader( QOpenGLShader::Vertex );
    vShader.compileSourceFile( ":/Shaders/vShader.glsl" );

    QOpenGLShader fShader( QOpenGLShader::Fragment );
    fShader.compileSourceFile( ":/Shaders/fShader.glsl" );

    m_program.addShader( &vShader );
    m_program.addShader( &fShader );
    m_program.link();

    m_vertexAttrLoc = m_program.attributeLocation( "vertexAttr" );
    m_colorAttrLoc = m_program.attributeLocation( "colorAttr" );
    m_normalAttrLoc = m_program.attributeLocation( "normalAttr" );

    m_mvMatrixLoc = m_program.uniformLocation( "mvMatrix" );
    m_projMatrixLoc = m_program.uniformLocation( "projMatrix" );
    m_normalMatrixLoc = m_program.uniformLocation( "normalMatrix" );

    m_lightPosLoc = m_program.uniformLocation( "lightPos" );
    m_program.setUniformValue( m_lightPosLoc, QVector3D( 0.0f, 20.f, 10.0f ) );

    m_tank = new Tank( &m_program, m_vertexAttrLoc, m_colorAttrLoc, m_normalAttrLoc );
    m_tank->fill( &loader );

    m_camera.setToIdentity();
    m_camera.lookAt( QVector3D( 0.0f, 10.0f, 20.0f ),
                     QVector3D( 0.0f, 0.0f, 0.0f ),
                     QVector3D( 0.0f, 1.0f, 0.0f ) );

    glEnable( GL_DEPTH_TEST );
}

void Scene::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if ( !m_program.bind() )
        return;

    m_world.setToIdentity();
    m_world.rotate( 180.0f - ( m_xRot / 16.0f ), 1, 0, 0 );
    m_world.rotate( m_yRot / 16.0f, 0, 1, 0 );
    m_world.rotate( m_zRot / 16.0f, 0, 0, 1 );
    m_program.setUniformValue( m_mvMatrixLoc, m_camera * m_world );
    m_program.setUniformValue( m_projMatrixLoc, m_proj );

    QMatrix3x3 normalMatrix = m_world.normalMatrix();
    m_program.setUniformValue( m_normalMatrixLoc, normalMatrix );

    m_tank->draw();

    m_program.release();
}

void Scene::resizeGL( int w, int h )
{
    if ( h == 0 )
        h = 1;

    glViewport( 0, 0, w, h );

    m_proj.setToIdentity();
    m_proj.perspective( 45.0f, float( w ) / float( h ), 0.01f, 500.0f );
}

void Scene::mousePressEvent( QMouseEvent *event )
{
    m_lastPos = event->pos();
}

void Scene::mouseMoveEvent( QMouseEvent *event )
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation( m_xRot + 8 * dy );
        setYRotation( m_yRot + 8 * dx );
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation( m_xRot + 8 * dy );
        setZRotation( m_zRot + 8 * dx );
    }
    m_lastPos = event->pos();
}

static void qNormalizeAngle( int &angle )
{
    while ( angle < 0 )
        angle += 360 * 16;
    while ( angle > 360 * 16 )
        angle -= 360 * 16;
}

void Scene::setXRotation( int angle )
{
    qNormalizeAngle( angle );
    if (angle != m_xRot)
    {
        m_xRot = angle;
        update();
    }
}

void Scene::setYRotation( int angle )
{
    qNormalizeAngle( angle );
    if (angle != m_yRot)
    {
        m_yRot = angle;
        update();
    }
}

void Scene::setZRotation(int angle)
{
    qNormalizeAngle( angle );
    if (angle != m_zRot)
    {
        m_zRot = angle;
        update();
    }
}
