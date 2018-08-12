#include "butterfly.h"
#include <QPainter>
#include <QGraphicsScene>
#include <math.h>
const static double PI=3.1415926;

Butterfly::Butterfly(QObject *parent)
{
    up=true;
    pix_up.load(":/img/up.png");
    pix_down.load(":/img/down.png");
    startTimer(100);
}

void Butterfly::timerEvent(QTimerEvent *event)
{
    qreal edgex=scene()->sceneRect().right()+boundingRect().width()/2;
    qreal edgetop=scene()->sceneRect().top()+boundingRect().height()/2;
    qreal edgebottom=scene()->sceneRect().bottom()+boundingRect().height()/2;

    if(pos().x()>=edgex)
        setPos(scene()->sceneRect().left(),pos().y());
    if(pos().y()<=edgetop)
        setPos(pos().x(),scene()->sceneRect().bottom());
    if(pos().y()>=edgebottom)
        setPos(pos().x(),scene()->sceneRect().top());

    angle+=(qrand()%10)/20.0;

    qreal dx=fabs(sin(angle*PI)*10.0);
    qreal dy=qrand()%20-10.0;

    setPos(mapToParent(dx,dy));
}

QRectF Butterfly::boundingRect() const
{
    qreal adjust=2;
    return QRectF(-pix_up.width()/2-adjust,-pix_up.height()/2-adjust,pix_up.width()+2*adjust
                  ,pix_up.height()+2*adjust);
}

void Butterfly::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(up){
        painter->drawPixmap(boundingRect().topLeft(),pix_up);
        up=!up;
    }else{
        painter->drawPixmap(boundingRect().topLeft(),pix_down);
        up=!up;
    }
}
