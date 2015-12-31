//
//  Transform.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Transform.h"
#include "PaintEngine.h"

DE_BEGIN

Transform::Transform()
:m_needFlush(false)
,m_ignoreAnchorPoint(false)
{
    init();
}

Transform::~Transform()
{
}

void Transform::assign(DE::Transform *src)
{
    m_x = src->m_x;
    m_y = src->m_y;
    m_anchorX = src->m_anchorX;
    m_anchorY = src->m_anchorY;
    m_scaleX = src->m_scaleX;
    m_scaleY = src->m_scaleY;
    m_rotationX = src->m_rotationX;
    m_rotationY = src->m_rotationY;
    m_rotationZ = src->m_rotationZ;
    m_width = src->m_width;
    m_height = src->m_height;
    m_matrix = src->m_matrix;
    m_scissorRect = src->m_scissorRect;
    m_needFlush = true;
}

void Transform::transform(DE::Transform *v)
{
    kmMat4Multiply(&m_matrix,&m_matrix,&v->m_matrix);
}

void Transform::setScissor(int x,int y,int w,int h)
{
    m_scissorRect.set(x,y,w,h);
}

void Transform::scissorBegin()
{
    glEnable(GL_SCISSOR_TEST);
    float x = m_matrix.mat[];
    glScissor(m_scissorRect.x,m_scissorRect.y,m_scissorRect.width,m_scissorRect.height);
}

void Transform::scissorEnd()
{
    glDisable(GL_SCISSOR_TEST);
}

void Transform::init()
{
    m_x = 0;
    m_y = 0;
    m_anchorX = 0;
    m_anchorY = 0;
    m_scaleX = 1;
    m_scaleY = 1;
    m_rotationX = 0;
    m_rotationY = 0;
    m_rotationZ = 0;
    m_width = 0;
    m_height = 0;
    m_needFlush = true;
    flush();
}

void Transform::transTo(float inx, float iny, GLV2F* outValue)
{
    kmVec3 inpos;
    kmVec3Fill(&inpos,inx,iny,0);
    kmVec3 outpos;
    kmVec3Transform(&outpos, &inpos, &m_matrix);
    outValue->v1 = outpos.x;
    outValue->v2 = outpos.y;
}

void Transform::flush()
{
    if (m_needFlush)
    {
        m_needFlush=false;
        kmMat4Identity(&m_matrix);
        kmMat4 t_mat;
        
        //position
        kmMat4Identity(&t_mat);
        kmMat4Translation(&t_mat,m_x,m_y,0);
        kmMat4Multiply(&m_matrix, &m_matrix, &t_mat);
        
        //rotation
        kmMat4Identity(&t_mat);
        kmMat4RotationZ(&t_mat, -m_rotationZ*PI/180.0f);
        kmMat4Multiply(&m_matrix, &m_matrix, &t_mat);
        
        //scale
        kmMat4Identity(&t_mat);
        kmMat4Scaling(&t_mat, m_scaleX, m_scaleY, 1);
        kmMat4Multiply(&m_matrix, &m_matrix, &t_mat);
        
        //anchorPoint
        kmMat4Identity(&t_mat);
        kmMat4Translation(&t_mat,(-m_anchorX*m_width),(-m_anchorY*m_height),0);
        kmMat4Multiply(&m_matrix, &m_matrix, &t_mat);
        
        
    }
}

bool Transform::pointInside(float x,float y,float& ox,float& oy)
{
    kmMat4 i_mat;
    kmMat4Inverse(&i_mat, &m_matrix);
    kmVec3 outpos;
    kmVec3 inpos;
    float nx = x;
    float ny = y;
    kmVec3Fill(&inpos,nx,ny,0);
    kmVec3Transform(&outpos,&inpos,&i_mat);
    ox = outpos.x;
    oy = outpos.y;
    if (outpos.x >= 0 &&
        outpos.y >= 0 &&
        outpos.x < m_width&&
        outpos.y < m_height)
    {
        return true;
    }
    return false;
}

DE_END
