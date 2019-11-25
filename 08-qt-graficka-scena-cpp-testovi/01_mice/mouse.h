#ifndef MOUSE_H
#define MOUSE_H

#include <QGraphicsItem>

class Mouse : public QGraphicsItem
{
public:
    Mouse();

    // U pitanju je cisto virtualan metod u natklasi QGraphicsItem.
    // Sluzi za definisanje pravougaone povrsine ekrana
    // u cijim okvirima ce element scene biti iscrtan.
    // Koristi se kako bi Qt proverio da li QGraphicsItem zahteva
    // ponovno iscrtavanje.
    QRectF boundingRect() const override;

    // Sluzi za definisanje "preciznog" oblika elementa scene.
    // Koristi se pri detekciji kolizija.
    QPainterPath shape() const override;

    // U pitanju je cisto virtualan metod u natklasi QGraphicsItem.
    // Definise proceduru za iscrtavanje elementa scene.
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    // Metod koji se poziva kada se kliktaj misa dogodi nad elementom scene
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;

protected:
    // Za svaki frejm u animaciji,
    // scena poziva advance nad elementima scene.
    void advance(int step) override;

private:
    qreal angle_;
    qreal speed_;
    qreal mouseEyeDirection_;

    QColor color_;
};

#endif
