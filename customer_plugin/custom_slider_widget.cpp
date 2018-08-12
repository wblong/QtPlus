#include <QPainter>
#include <QMouseEvent>
#include "custom_slider_widget.h"

custom_slider_widget::custom_slider_widget(QWidget *parent) : QWidget(parent)
{

}

void custom_slider_widget::slider_set_widget_resize(int width, int height)
{
    this->w_width=width;
    this->w_height=height;

    resize(QSize(width,height));
    setFixedSize(QSize(width,height));
    this->slider_ypos=0;
    this->slider_width=24;
    this->slider_height=16;
}

void custom_slider_widget::slider_set_max_value(float value)
{
    this->max_value=value;
}

void custom_slider_widget::slider_set_min_value(float value)
{
    this->min_value=value;
}

void custom_slider_widget::slider_set_current_value(float value)
{
    this->current_value=value;
    float percent2=(100/this->max_value);
    this->slider_ypos=percent2*value;
    this->slider_ypos=abs(this->slider_ypos-this->slider_height)-(this->slider_height/2);
}

int custom_slider_widget::slider_get_current_value()
{
    return this->current_value;
}

void custom_slider_widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setPen(QColor(255,255,255));
    painter.setBrush(QColor(255,255,255));
    painter.drawRect(12,0,0,this->w_height);

    QImage image(":/res/slider-handle.png");
    painter.drawImage(0,this->slider_ypos,image);
}

void custom_slider_widget::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons()&Qt::LeftButton)){
        if(event->pos().x()>=0&&event->pos().x()<=this->w_width&&
           event->pos().y()>=0&&event->pos().y()<=this->w_height){
            if((event->pos().y()-(this->slider_height/2))>=0&&
                    (event->pos().y()+(this->slider_height/2))<=this->w_height){
                this->slider_ypos=event->pos().y()-(this->slider_height/2);
                float percent1=this->slider_ypos/84*100;
                float percent2=(100/this->max_value);
                int percent3=percent1/percent2;
                percent3=abs(percent3-this->max_value);
                emit this->valuechanged(percent3);
                this->repaint();
            }
        }// end for if
    }
}
