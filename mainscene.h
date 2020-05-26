#ifndef MAINSCENE_H
#define MAINSCENE_H
#include<QTimer>
#include<QWidget>
#include <QMainWindow>
#include "map.h"
#include<QPainter>
#include<QMouseEvent>
#include "heroplane.h"
#include "enemyplane.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    void initScene();
    QTimer m_Timer;
    //启动游戏 用于启动定时器对象
    void playGame();
    //更新坐标
    void updatePosition();
    //绘图事件
    void paintEvent(QPaintEvent *event);

    /*void mouseMoveEvent(QMouseEvent *);*/

    //敌机出场
    void enemyToScene();
    //敌机数组
    EnemyPlane m_enemys[ENEMY_NUM];
    //敌机出场间隔记录
    int m_recorder;
    HeroPlane m_hero;
    HeroPlane m_hero1;
    HeroPlane m_hero2;
    HeroPlane m_hero3;
    //地图对象
    Map m_map;

    void collisionDetection();
private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
