#include "heroplane.h"
#include "config.h"

HeroPlane::HeroPlane()
{
    m_plane.load(":/hero2.png");
    m_x=0;
    m_y=GAME_HEIGHT-m_plane.height();

    m_Rect.setWidth(m_plane.width());
    m_Rect.setHeight(m_plane.height());
    m_Rect.moveTo(m_x,m_y);

    m_recorder=0;
}

void HeroPlane::setPosition(int x, int y)
{
    m_x=x;
    m_y=y;
    m_Rect.moveTo(m_x,m_y);
}

void HeroPlane::shoot()
{
    m_recorder++;
    if(m_recorder<BULLET_INTERVAL)
    {
        return;
    }
    m_recorder=0;

    for(int i=0;i<BULLET_NUM;i++)
    {
        if(m_bullets[i].m_Free)
        {
            m_bullets[i].m_Free=false;
            m_bullets[i].m_X=m_x+m_Rect.width()*0.5-10;
            m_bullets[i].m_Y=m_y-25;
            break;
        }
    }
}
