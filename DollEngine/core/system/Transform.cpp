#include "Transform.h"
#include "Device.h"

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

void Transform::set(Transform* a,Transform* b)
{
    set(a);
    m_matrix = b->m_matrix * a->m_matrix;
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
    m_matrix.reset();
}

void Transform::flush()
{
    if (m_needFlush)
    {
        m_needFlush=false;
        m_matrix.reset();
        
        //position
        m_matrix.translate(m_x,m_y);
        
        //rotation
        m_matrix.rotate(m_rotationZ);
        
        //scale
        m_matrix.scale(m_scaleX,m_scaleY);
        
        //anchorPoint
        if(!m_ignoreAnchorPoint) {
            m_matrix.translate((-m_anchorX*m_width),(-m_anchorY*m_height));
        }
    }
}

bool Transform::isPointInside(float x,float y,double& ox,double& oy)
{
//    x=256,y=384/2;
    bool invertible = true;
    QMatrix baseMax = m_matrix.inverted(&invertible);
    if(!invertible) {
        throw Debug::throwMsg("矩阵不可逆");
    }
    float nx = x*2/Device::GetInstance()->getWinWidth()-1;
    float ny = 1-y*2/Device::GetInstance()->getWinHeight();
//    nx=0,ny=0;
    baseMax.map(nx,ny,&ox,&oy);
    qDebug()<<x<<y<<ox<<oy;
    if (ox >= 0 &&
        oy >= 0 &&
        ox < m_width&&
        oy < m_height)
    {
        return true;
    }
    return false;
}

DE_END
