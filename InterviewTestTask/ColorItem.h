#ifndef COLORITEM_H
#define COLORITEM_H

#include <QColor>
#include <QObject>

class ColorItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit ColorItem(QColor color = QColor(), QObject *parent = nullptr);
    const QColor& color() const;

public slots:
    void setColor(const QColor& newColor);

signals:
    void colorChanged(const QColor& color);

private:
    QColor m_color;
};

#endif // COLORITEM_H
