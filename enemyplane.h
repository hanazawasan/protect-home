#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H
#include<QPixmap>
#include<QRect>
class EnemyPlane
{
public:
    EnemyPlane();

    void updatePosition();
public:
    QPixmap m_enermy;

    int m_X;
    int m_Y;

    QRect m_Rect;

    bool m_Free;

    int m_speed;

};

#endif // ENEMYPLANE_H
