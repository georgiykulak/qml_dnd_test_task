/* Author: Remy van Elst, https://raymii.org
 * License: GNU AGPLv3
 */

#include "Thingie.h"

#include <random>

Thingie::Thingie(const QString& name, QObject* parent) : QObject(parent), _name(name)
{

}

const QString &Thingie::name() const
{
    return _name;
}

void Thingie::setName(const QString &newName)
{
    if (_name == newName)
        return;
    _name = newName;
    emit nameChanged(_name);
}

const QColor &Thingie::color() const
{
    return _color;
}

void Thingie::setColor(const QColor &newColor)
{
    if (_color == newColor)
        return;
    _color = newColor;
    emit colorChanged(_color);
}


QString Thingie::randomHexString(unsigned int length)
{
    QString result;
    static std::mt19937 generator {std::random_device {}()};
    std::string hex_characters = "0123456789abcdef";
    std::uniform_int_distribution<int> dist(0, hex_characters.length() - 1);
    for (unsigned int i = 0; i < length; i++)
    {
        result += hex_characters[dist(generator)];
    }
    return result;
}


QColor Thingie::randomColor()
{
    QString result = "#";
    result.append(randomHexString(6));
    return QColor(result);
}
