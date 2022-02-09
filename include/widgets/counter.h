/**
 * @file counter.h
 * @brief Contains widget used to show remain count of certain digit.
 * @author Joe chen <joechenrh@gmail.com>
 */

#ifndef COUNTER_H
#define COUNTER_H

#include <QLabel>
#include <QJsonObject>
#include <QGraphicsOpacityEffect>

class Counter : public QWidget
{
    Q_OBJECT

    struct CounterStyle
    {
        QString cnt_color_hovered;
        QString cnt_font_color_unhovered;
        QString cnt_font_color_hovered;
    };

public:
    Counter(int num, int size, QWidget *parent = nullptr);

    void setCount(int value);
    void modify(int value);
    void setColorStyle(QJsonObject json);

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

signals:
    void hovered();
    void leaved();

private:
    int m_count;
    QLabel *m_cntLabel;
    QLabel *m_numLabel;
    QGraphicsOpacityEffect *m_cntOpacity;
    CounterStyle m_style;
};

#endif // COUNTER_H
