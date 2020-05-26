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
    //������Ϸ ����������ʱ������
    void playGame();
    //��������
    void updatePosition();
    //��ͼ�¼�
    void paintEvent(QPaintEvent *event);

    /*void mouseMoveEvent(QMouseEvent *);*/

    //�л�����
    void enemyToScene();
    //�л�����
    EnemyPlane m_enemys[ENEMY_NUM];
    //�л����������¼
    int m_recorder;
    HeroPlane m_hero;
    HeroPlane m_hero1;
    HeroPlane m_hero2;
    HeroPlane m_hero3;
    //��ͼ����
    Map m_map;

    void collisionDetection();
private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
