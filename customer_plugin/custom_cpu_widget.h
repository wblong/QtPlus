#ifndef CUSTOM_CPU_WIDGET_H
#define CUSTOM_CPU_WIDGET_H

#include <QWidget>
class custom_cpu_widget : public QWidget
{
    Q_OBJECT
public:
    explicit custom_cpu_widget(QWidget *parent = 0);
    void cpu_set_widget_level(int level);

private:
    int w_width;
    int w_height;
    int cpu_used_level;
protected:
    virtual void paintEvent(QPaintEvent *event);
};

#endif // CUSTOM_CPU_WIDGET_H
