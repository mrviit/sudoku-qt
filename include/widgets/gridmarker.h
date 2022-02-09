/**
 * @file gridmarker.h
 * @brief Contains widget used to highlight mouse enter event.
 * @author Joe chen <joechenrh@gmail.com>
 */

#ifndef GRIDMARKER_H
#define GRIDMARKER_H

#include <QLabel>
#include <QPainter>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>

class GridMarker : public QLabel
{
    Q_OBJECT

public:
    explicit GridMarker(int size, QWidget *parent = nullptr);

    void hide();
    void show();

    void setDuration(const int &duration);
    void setMarkerColor(const QColor &color);

    void setShadowColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent*);

private:
    QColor m_markerColor;
    QColor m_shadowColor;

    int m_maxSize;
    int m_indent;

    QPropertyAnimation *m_hideAnimation;
    QPropertyAnimation *m_showAnimation;

};

#endif // GRIDMARKER_H
