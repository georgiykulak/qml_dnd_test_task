#include "ColorItem.h"

#include <QDebug>

ColorItem::ColorItem(QColor color, QObject *parent)
    : QObject{parent}
    , m_color(color)
{}

const QColor& ColorItem::color() const
{
    return m_color;
}

void ColorItem::setColor(const QColor& newColor)
{
    qDebug() << "ColorItem setColor: new color ->" << newColor;

    if (m_color == newColor)
        return;

    m_color = newColor;

    emit colorChanged(m_color);
}
