#pragma once

#include "GraphicsScene.h"

#include <QGraphicsObject>

class PixmapItem : public QGraphicsObject
{
public:
    PixmapItem(const QString& fileName, QGraphicsItem* parent = nullptr);
    PixmapItem(const QString& fileName, QGraphicsScene* scene);
    QSizeF size() const;
    QRectF boundingRect() const override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;
private:
    QPixmap pix;
};