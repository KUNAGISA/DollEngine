//
//  Transform.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Transform.h"
#include "GLCanvas.h"

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

void Transform::copy(DE::Transform *src)
{
    memcpy((void*)this, (void*)src, sizeof(Transform));
}

void Transform::transform(DE::Transform *v)
{
    kmMat4Multiply(&m_matrix,&m_matrix,&v->m_matrix);
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
    kmMat4Identity(&m_matrix);
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
    kmMat4 t_mat;
    kmMat4Inverse(&t_mat, &m_matrix);
    kmVec3 outpos;
    kmVec3 inpos;
    float nx = x*2/GLCanvas::GetInstance()->getLayerWidth()-1;
    float ny = y*2/GLCanvas::GetInstance()->getLayerHeight()-1;
    kmVec3Fill(&inpos,nx,ny,0);
    kmVec3Transform(&outpos,&inpos,&t_mat);
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
