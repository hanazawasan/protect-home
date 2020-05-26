#include "enemyplane.h"
#include<config.h>
EnemyPlane::EnemyPlane()
{
     m_enermy.load(":/img-plane_5.png");
     m_X=0;
     m_Y=0;
     m_speed=ENEMY_SPEED;
     m_Free=true;
     m_Rect.setWidth(m_enermy.width());
     m_Rect.setHeight(m_enermy.height());
     m_Rect.moveTo(m_X,m_Y);

}
void EnemyPlane::updatePosition()
{
    //¿ÕÏÐ×´Ì¬£¬²»¼ÆËã×ø±ê
    if(m_Free)
    { return; }
    m_Y += m_speed;
    m_Rect.moveTo(m_X,m_Y);
    if(m_Y >= GAME_HEIGHT)
    { m_Free = true; }
}
