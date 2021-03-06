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
    m_needFlush = true;
}

void Transform::transform(DE::Transform *v)
{
    kmMat4Multiply(&m_matrix,&m_matrix,&v->m_matrix);
}

void Transform::setScissor(int x,int y,int w,int h)
{
    GLV2F out;
    transTo(x,y, &out);
    GLV2F out2;
    transTo(x+w,y+h, &out2);
    m_scissorRect.set(out.v1,out.v2,out2.v1-out.v1,out2.v2-out.v2);
}

void Transform::scissorBegin()
{
    float x = m_scissorRect.x* PaintEngine::GetInstance()->getLayerZoom() + PaintEngine::GetInstance()->getLayerX();
    float y = m_scissorRect.y* PaintEngine::GetInstance()->getLayerZoom() + PaintEngine::GetInstance()->getLayerY();
    float w = m_scissorRect.width * PaintEngine::GetInstance()->getLayerZoom();
    float h = m_scissorRect.height * PaintEngine::GetInstance()->getLayerZoom();
//    float x = m_matrix.mat[];
    PaintEngine::GetInstance()->scissorBegin(x,y,w,h);
}

void Transform::scissorEnd()
{
    PaintEngine::GetInstance()->scissorEnd();
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
