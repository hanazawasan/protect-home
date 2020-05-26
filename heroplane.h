#ifndef HEROPLANE_H
#define HEROPLANE_H
#include<QPixmap>
#include<config.h>
#include "bullet.h"

class HeroPlane
{
public:
    HeroPlane();

    void shoot();

    void setPosition(int x,int y);
public:
    QPixmap m_plane;

    int m_x;
    int m_y;

    QRect  m_Rect;

    Bullet m_bullets[BULLET_NUM];
    int m_recorder;
};

#endif // HEROPLANE_H
