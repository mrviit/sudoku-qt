﻿#include "gridwidget.h"

#include <QDebug>
#include <QFontDatabase>
#include <QGraphicsDropShadowEffect>

const int duration = 200;

GridWidget::GridWidget(int row, int col, int size, QWidget *parent)
    : QWidget(parent), m_multiValue(0), m_value(0), m_numConflict(0)
{   
    this->setUpdatesEnabled(false);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(2, 2);
    shadow->setBlurRadius(2);
    this->setGraphicsEffect(shadow);
    this->setFixedSize(size, size);

    m_backgroundStyle = QString("background-color:%1;border:1px solid %2;");
    if ((row == 0 || row == 8) && (col == 0 || col == 8))
    {
        m_backgroundStyle += QString("border-%1-%2-radius:%3px;")
                                .arg(row ? "bottom" : "top")
                                .arg(col ? "right" : "left" )
                                .arg(size / 5);
    }

    m_background = new QLabel(this);
    m_background->setFixedSize(size, size);

    m_foreground = new BaseWidget(this);
    m_foreground->setFixedSize(size, size);

    m_marker = new GridMarker(size, this);
    m_marker->setDuration(duration);
    m_marker->setGeometry(QRect(size / 2, size / 2, 1, 1));

    int labelMargin = size / 5 - 5;
    int labelSize = size - 2 * labelMargin;

    int nIndex = QFontDatabase::addApplicationFont(":/fonts/ARLRDBD.TTF");
    QStringList strList(QFontDatabase::applicationFontFamilies(nIndex));

    m_singleGrid = new QLabel(this);
    m_singleGrid->setAlignment(Qt::AlignCenter);
    m_singleGrid->setObjectName("buttonText");
    m_singleGrid->setFont(QFont(strList.at(0), size / 4));
    m_singleGrid->setFixedSize(labelSize, labelSize);
    m_singleGrid->move(labelMargin, labelMargin);
    setStyleSheet(QString("#buttonText{border-radius:%1px;background-color:transparent;}").arg(labelSize / 2));

    QWidget *container = new QWidget(this);
    container->setFixedSize(75, 75);
    for (int i = 0; i < 9; i++)
    {
        QLabel *multiGrid = new QLabel(container);
        multiGrid->setAlignment(Qt::AlignCenter);
        multiGrid->setFont(QFont(strList.at(0), size / 6));
        multiGrid->setText(QString::number(i + 1));
        multiGrid->setFixedSize(size / 3, size / 3);
        multiGrid->move((size / 3) * (i % 3), (size / 3) * (i / 3));
        multiGrid->hide();
        m_multiGrids.push_back(multiGrid);
    }

    m_button = new BaseWidget(this);
    m_button->setFixedSize(size, size);
    m_button->setStyleSheet("background-color:transparent;");
    connect(m_button, SIGNAL(clicked()),      this, SLOT(buttonClicked()));
    connect(m_button, SIGNAL(rightClicked()), this, SLOT(buttonRightClicked()));

    this->setUpdatesEnabled(true);
}

void GridWidget::setColorStyle(QJsonObject json)
{
    this->setUpdatesEnabled(false);

    m_style.border_color[0] = json.value("font_color_unabled").toString();
    m_style.border_color[1] = json.value("font_color_normal").toString();

    m_style.border_radius[0] = json.value("border_radius_conflict").toString();
    m_style.border_radius[1] = "0";

    m_style.font_color[0] = json.value("font_color_unabled").toString();
    m_style.font_color[1] = json.value("font_color_normal").toString();
    m_style.font_color[2] = "#FBFBFB";

    m_style.background_color_hovered = json.value("background_color_hovered").toString();
    m_style.background_color_unhovered = json.value("background_color_unhovered").toString();
    m_style.background_shadow_color = json.value("background_shadow_color").toString();

    m_style.spacing_color = json.value("spacing_color").toString();

    for (auto grid : m_multiGrids)
    {
        grid->setStyleSheet(QString("color:%1").arg(m_style.font_color[1]));
    }

    (static_cast<QGraphicsDropShadowEffect*>(graphicsEffect()))->setColor(m_style.background_shadow_color);
    m_marker->setMarkerColor(json.value("font_color_normal").toString());
    m_marker->setShadowColor(json.value("marker_color_shadow").toString());

    m_foreground->setStyleSheet(m_backgroundStyle.arg(m_style.background_color_unhovered).arg(m_style.spacing_color));
    m_background->setStyleSheet(m_backgroundStyle.arg(m_style.background_color_hovered).arg(m_style.spacing_color));

    //QPalette p = m_foreground->palette();
    //p.setColor(QPalette::Window, m_style.background_color_hovered);
    //m_foreground->setPalette(p);

    //QPalette p = m_foreground->palette();
    //p.setColor(QPalette::Base, m_style.background_color_unhovered);
    //m_foreground->setPalette(p);

    setButtonStyle(false);
    //m_borderRadius = m_style.border_radius[m_numConflict == 0];
    //m_borderColor  = m_style.border_color[m_button->isEnabled()];
    //m_fontColor    = m_style.font_color[m_button->isEnabled()];
    //m_buttonStyle  = QString("border:%1px solid %2;color:%3;");
    //m_singleGrid->setStyleSheet(m_buttonStyle.arg(m_borderRadius, m_borderColor, m_fontColor));

    this->setUpdatesEnabled(true);
}

void GridWidget::setEnabled(bool enabled)
{  
    m_button->setEnabled(enabled);
    setButtonStyle(false);
    //m_fontColor = m_style.font_color[enabled];
    //m_borderColor = m_style.border_color[enabled];
    //m_singleGrid->setStyleSheet(m_buttonStyle.arg(m_borderRadius, m_borderColor, m_fontColor));
}

bool GridWidget::isEnabled() const
{
    return m_button->isEnabled();
}

void GridWidget::setMultiValue(int value)
{
    m_multiValue = value;

    this->setUpdatesEnabled(false);

    if (value)
    {
        m_singleGrid->hide();
        for (auto &grid : m_multiGrids)
        {
            grid->setVisible(value % 2);
            value /= 2;
        }
    }
    else
    {
        m_singleGrid->show();
        for (auto &grid : m_multiGrids)
        {
            grid->hide();
        }
    }

    this->setUpdatesEnabled(true);
}

int GridWidget::multiValue() const
{
    return m_multiValue;
}

void GridWidget::setValue(int value)
{
    this->setUpdatesEnabled(false);

    if (value && m_multiValue)
    {
        m_singleGrid->show();
        for (auto &grid : m_multiGrids)
        {
            grid->hide();
        }
    }
    m_value = value;
    m_singleGrid->setText(value == 0 ? "" : QString::number(value));

    this->setUpdatesEnabled(true);
}

int GridWidget::value() const
{
    return m_value;
}

void GridWidget::changeConflict(int num)
{
    /*
    if (m_numConflict == 0 && num > 0)
    {
        m_borderRadius = m_style.border_radius[1];
        m_singleGrid->setStyleSheet(m_buttonStyle.arg(m_borderRadius, m_borderColor, m_fontColor));
    }
    else if (m_numConflict > 0 && m_numConflict + num == 0)
    {
        m_borderRadius = m_style.border_radius[0];
        m_singleGrid->setStyleSheet(m_buttonStyle.arg(m_borderRadius, m_borderColor, m_fontColor));
    }
    */
    m_numConflict += num;
    setButtonStyle(false);

}

void GridWidget::clearConflict()
{
    m_numConflict = 0;
    setButtonStyle(false);
    //m_borderRadius = m_style.border_radius[1];
    //m_singleGrid->setStyleSheet(m_buttonStyle.arg(m_borderRadius, m_borderColor, m_fontColor));
}


void GridWidget::buttonClicked()
{
    emit clicked();
}

void GridWidget::buttonRightClicked()
{
    emit rightClicked();
}

void GridWidget::enterEvent(QEvent*)
{
    emit hovered();
}

void GridWidget::leaveEvent(QEvent*)
{
    emit leaved();
}


void GridWidget::showBackground()
{
    m_foreground->hide();
}

void GridWidget::hideBackground()
{
    m_foreground->reveal();
}

void GridWidget::enter()
{
    m_foreground->hide();
    m_marker->show();
    setButtonStyle(true);
    // m_fontColor = m_style.font_color[2];
    // m_singleGrid->setStyleSheet(m_buttonStyle.arg(m_borderRadius).arg(m_borderColor).arg(m_fontColor));
}

void GridWidget::leave()
{
    m_foreground->reveal();
    m_marker->hide();
    setButtonStyle(false);
    // m_fontColor = m_style.font_color[1];
    // m_singleGrid->setStyleSheet(m_buttonStyle.arg(m_borderRadius).arg(m_borderColor).arg(m_fontColor));
}

void GridWidget::setButtonStyle(int entered)
{
    this->setUpdatesEnabled(false);

    if (m_button->isEnabled() && m_value == 0)
    {
        m_multiGrids[4]->setStyleSheet(QString("color:%1;").arg(entered ? "#FBFBBF": m_style.font_color[1]));
    }

    m_singleGrid->setStyleSheet(QString("border:%1px solid %2;color:%3;")
                                .arg(m_style.border_radius[m_numConflict == 0],
                                     m_style.border_color[m_button->isEnabled()],
                                     m_style.font_color[m_button->isEnabled() + entered]));

    this->setUpdatesEnabled(true);
}
