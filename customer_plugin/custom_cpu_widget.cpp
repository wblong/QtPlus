#include "custom_cpu_widget.h"
#include<QPainter>
custom_cpu_widget::custom_cpu_widget(QWidget *parent) : QWidget(parent)
{
    this->w_width=80;
    this->w_height=100;
    resize(QSize(this->w_width,this->w_height));
    setFixedSize(QSize(this->w_width,this->w_height));
    this->cpu_used_level=10;
}

void custom_cpu_widget::cpu_set_widget_level(int level)
{
    this->cpu_used_level=level;
    this->repaint();
}

void custom_cpu_widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setPen(QColor(0,0,0));
    painter.setBrush(QColor(0,0,0));
    painter.drawRect(0,0,this->w_width,this->w_height);

    int i;
    for(i=21;i>=0;i--){

        if(this->cpu_used_level>i){
            painter.setBrush(QColor(153,255,0));
        }else{
            painter.setBrush(QColor(51,102,0));
        }
        painter.drawRect(6,(this->w_height-8)-(i*4),30,3);
        painter.drawRect(43,(this->w_height-8)-(i*4),30,3);

    }
}
