#include "mainscene.h"
#include "ui_mainscene.h"
#include "config.h"
#include<ctime>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    initScene();

}

MainScene::~MainScene()
{
    delete ui;
}
void MainScene::initScene()
{
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);

    setWindowIcon(QIcon(":/app.ico"));

    //定时器设置
    m_Timer.setInterval(GAME_RATE);
    srand((unsigned int)time(NULL));
    m_recorder=0;
    playGame();


}
void MainScene::playGame()
{
    m_Timer.start();
    connect(&m_Timer,&QTimer::timeout,[=](){
        enemyToScene();
        updatePosition();
        update();
        collisionDetection();
    });
}
void MainScene::updatePosition()
{
    m_map.mapPositon();

    //建了4个飞机
    m_hero.shoot();
    for(int i = 0 ;i < BULLET_NUM;i++)
    { //如果子弹状态为非空闲，计算发射位置
        if(!m_hero.m_bullets[i].m_Free)
        { m_hero.m_bullets[i].updatePosition(); }
    }
    m_hero1.shoot();
    for(int i = 0 ;i < BULLET_NUM;i++)
    { //如果子弹状态为非空闲，计算发射位置
        if(!m_hero1.m_bullets[i].m_Free)
        { m_hero1.m_bullets[i].updatePosition(); }
    }
    m_hero2.shoot();
    for(int i = 0 ;i < BULLET_NUM;i++)
    { //如果子弹状态为非空闲，计算发射位置
        if(!m_hero2.m_bullets[i].m_Free)
        { m_hero2.m_bullets[i].updatePosition(); }
    }
    m_hero3.shoot();
    for(int i = 0 ;i < BULLET_NUM;i++)
    { //如果子弹状态为非空闲，计算发射位置
        if(!m_hero3.m_bullets[i].m_Free)
        { m_hero3.m_bullets[i].updatePosition(); }
    }

    //更新敌机坐标
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free==false)
        {
            m_enemys[i].updatePosition();
        }
    }
}
void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);
    //画4架飞机
    painter.drawPixmap(m_hero.m_x,m_hero.m_y,m_hero.m_plane);
    painter.drawPixmap(m_hero1.m_x+128,m_hero1.m_y,m_hero1.m_plane);
    painter.drawPixmap(m_hero2.m_x+256,m_hero2.m_y,m_hero2.m_plane);
    painter.drawPixmap(m_hero3.m_x+384,m_hero3.m_y,m_hero3.m_plane);

    for(int i = 0 ;i < BULLET_NUM;i++)
    { //如果子弹状态为非空闲，计算发射位置
        if(!m_hero.m_bullets[i].m_Free)
        { painter.drawPixmap(m_hero.m_bullets[i].m_X,m_hero.m_bullets[i].m_Y,m_hero.m_bullets[i].m_Bullet );
          painter.drawPixmap(m_hero1.m_bullets[i].m_X+128,m_hero1.m_bullets[i].m_Y,m_hero.m_bullets[i].m_Bullet );
          painter.drawPixmap(m_hero2.m_bullets[i].m_X+256,m_hero2.m_bullets[i].m_Y,m_hero.m_bullets[i].m_Bullet );
          painter.drawPixmap(m_hero3.m_bullets[i].m_X+384,m_hero3.m_bullets[i].m_Y,m_hero.m_bullets[i].m_Bullet );
        }
    }


    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free==false)
        {
            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enermy);
        }
    }
}

/*void MainScene::mouseMoveEvent(QMouseEvent * event)
{
    int x=event->x()-m_hero.m_Rect.width()*0.5;
    int y=event->y()-m_hero.m_Rect.height()*0.5;

    if(x <= 0 )
    { x = 0; }

    if(x >= GAME_WIDTH - m_hero.m_Rect.width())
    { x = GAME_WIDTH - m_hero.m_Rect.width(); }

    if(y <= 0) { y = 0; }

    if(y >= GAME_HEIGHT - m_hero.m_Rect.height())
    { y = GAME_HEIGHT - m_hero.m_Rect.height(); }

    m_hero.setPosition(x,y);
}
*/

void MainScene::enemyToScene()
{
  m_recorder++;
  if(m_recorder < ENEMY_INTERVAL)
  { return; }
  m_recorder = 0;
  for(int i = 0 ; i< ENEMY_NUM;i++)
  { if(m_enemys[i].m_Free)
      {         m_enemys[i].m_Free=false;
                m_enemys[i].m_X = rand() % (GAME_WIDTH - m_enemys[i].m_Rect.width());
                m_enemys[i].m_Y = -m_enemys[i].m_Rect.height();
                break;
      }
  }
}
void MainScene::collisionDetection()
{
    //遍历所有非空闲的敌机
    for(int i = 0 ;i < ENEMY_NUM;i++)
    { if(m_enemys[i].m_Free)
        { //空闲飞机 跳转下一次循环
            continue;
        }
        //遍历所有 非空闲的子弹
        for(int j = 0 ; j < BULLET_NUM;j++)
        { if(m_hero.m_bullets[j].m_Free)
            { //空闲子弹 跳转下一次循环
                continue;
            }
                //如果子弹矩形框和敌机矩形框相交，发生碰撞，同时变为空闲状态即可
    if(m_enemys[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect))
    { m_enemys[i].m_Free = true;
    m_hero.m_bullets[j].m_Free = true;
    }
    else if(m_enemys[i].m_Rect.intersects(m_hero1.m_bullets[j].m_Rect))
    { m_enemys[i].m_Free = true;
    m_hero1.m_bullets[j].m_Free = true;
    }
    else if(m_enemys[i].m_Rect.intersects(m_hero2.m_bullets[j].m_Rect))
    { m_enemys[i].m_Free = true;
    m_hero2.m_bullets[j].m_Free = true;
    }
    else if(m_enemys[i].m_Rect.intersects(m_hero3.m_bullets[j].m_Rect))
    { m_enemys[i].m_Free = true;
    m_hero3.m_bullets[j].m_Free = true;
    }

        }
    }
}

