#include "PixmapItem.h"

#include <QPainter>

PixmapItem::PixmapItem(const QString& fileName, QGraphicsItem* parent)
    : QGraphicsObject(parent)
{
    pix = QPixmap(fileName);
}

PixmapItem::PixmapItem(const QString& fileName, QGraphicsScene* scene)
    : QGraphicsObject(), pix(fileName)
{
    scene->addItem(this);
}

QSizeF PixmapItem::size() const
{
    return pix.size();
}

QRectF PixmapItem::boundingRect() const
{
    return QRectF(QPointF(0, 0), pix.size());
}

void PixmapItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawPixmap(0, 0, pix);
}
