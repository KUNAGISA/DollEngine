//
//  de-Transform.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-Transform.h"
#include "de.h"

NAMESPACE_DE_BEGIN

Transform::Transform()
:m_need_refresh(false)
,m_ignoreAnchorPoint(false)
{
    init();
}

Transform::~Transform()
{
}

void Transform::set(Transform* a,Transform* b)
{
    set(a);
    kmMat4Multiply(&m_matrix,&a->m_matrix,&b->m_matrix);
}

void Transform::set(Transform* a)
{
    memcpy((void*)this, (void*)a, sizeof(Transform));
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

void Transform::refresh()
{
    if (m_need_refresh)
    {
        m_need_refresh=false;
        kmMat4Identity(&m_matrix);
        kmMat4 t_mat;
        
        //position
        kmMat4Identity(&t_mat);
        kmMat4Translation(&t_mat,m_x,m_y,0);
        kmMat4Multiply(&m_matrix, &m_matrix, &t_mat);
        
        //rotation
        kmMat4Identity(&t_mat);
        kmMat4RotationZ(&t_mat, m_rotationZ*PI/180.0f);
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

bool Transform::isPointInside(float x,float y)
{
    kmMat4 t_mat;
    kmMat4Inverse(&t_mat, &m_matrix);
    kmVec3 outpos;
    kmVec3 inpos;
    float nx = x/INNER_W-1;
    float ny = 1-y/INNER_H;
    kmVec3Fill(&inpos,nx,ny,0);
    kmVec3Transform(&outpos,&inpos,&t_mat);
    if (outpos.x >= 0 &&
        outpos.y >= 0 &&
        outpos.x < m_width&&
        outpos.y < m_height)
    {
        return true;
    }
    return false;
}

NAMESPACE_DE_END
