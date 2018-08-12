#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "custom_cpu_widget.h"
#include "custom_slider_widget.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:

public slots:
    void mvalueChanged(int value);
private:
    custom_slider_widget *slider_widget;
    custom_cpu_widget *cpu_widget;
private:
    bool m_embedded;
    QPixmap m_device;
protected:
    void update_background();
protected:
    virtual void paintEvent(QPaintEvent*event);
};

#endif // WIDGET_H
