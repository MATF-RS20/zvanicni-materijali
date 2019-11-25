#include "mouse.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <cmath>

static const double PI = 3.14159265358979323846264338327950288419717;
static const double TWO_PI = 2.0 * PI;

// Funkcija koja normalizuje ugao
// da bude u intervalu [0, 2 * Pi]
static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
    {
        angle += TWO_PI;
    }

    while (angle > TWO_PI)
    {
        angle -= TWO_PI;
    }

    return angle;
}

Mouse::Mouse()
  : angle_(0.0)
  , speed_(0.0)
  , mouseEyeDirection_(0.0)
  , color_(qrand() % 256, qrand() % 256, qrand() % 256)
{
    // Metod setRotation je nasledjen iz QGraphicsItem klase.
    // Postavlja rotaciju naseg misa u njegovom lokalnom koordinatnom prostoru.
    setRotation(qrand() % (360 * 16));
}

// Metod koji vraca pravouganik u cijim okvirima
// garantujemo da se mis nalazi (to jest, da ni jedan deo misa ne izlazi van).
// QGraphicsView ovo koristi kako bi proverio
// da li QGraphicsItem zahteva ponovno crtanje.
QRectF Mouse::boundingRect() const
{
    qreal adjust = -0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

// Funkcija koja vraca preciznije granice misa
// radi detekcije kolizije.
QPainterPath Mouse::shape() const
{
    QPainterPath path;
    // Preciznost je definisana detaljnoscu QPainterPath.
    // Ovde kazemo da se kolizije vrse na osnovu pravougaonika.
    path.addRect(-10, -20, 20, 40);
    return path;
}

void Mouse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option)

    // Crtamo telo
    painter->setBrush(color_);
    painter->drawEllipse(-10, -20, 20, 40);

    // Ostale elemente misa crtamo samo ako imamo dovoljno mesta za detalje
    const auto details =
            QStyleOptionGraphicsItem::levelOfDetailFromTransform(painter->worldTransform());
    if (details >= .75)
    {
        // Crtamo oci
        painter->setBrush(Qt::white);
        painter->drawEllipse(-10, -17, 8, 8);
        painter->drawEllipse(2, -17, 8, 8);

        // Crtamo nos
        painter->setBrush(Qt::black);
        painter->drawEllipse(QRectF(-2, -22, 4, 4));

        // Crtamo zenice
        painter->drawEllipse(QRectF(-8.0 + mouseEyeDirection_, -17, 4, 4));
        painter->drawEllipse(QRectF(4.0 + mouseEyeDirection_, -17, 4, 4));

        // Crtamo usi.
        // Ukoliko se mis sudara sa nekim drugim objektom (u nasem slucaju: sa drugim misem)
        // usi mi bojimo u crveno, a inace bojimo u normalnu tamno zutu boju.
        const auto earsColor =
                scene()->collidingItems(this).isEmpty() ? Qt::darkYellow : Qt::red;
        painter->setBrush(earsColor);
        painter->drawEllipse(-17, -12, 16, 16);
        painter->drawEllipse(1, -12, 16, 16);

        // Crtamo rep
        QPainterPath path(QPointF(0, 20));
        path.cubicTo(-5, 22, -5, 22, 0, 25);
        path.cubicTo(5, 27, 5, 32, 0, 30);
        path.cubicTo(-5, 32, -5, 42, 0, 35);
        painter->setBrush(Qt::NoBrush);
        painter->drawPath(path);
    }
}

// QGraphicsScene poziva advance nad svakim elementom scene
// kada se odluci da predje na sledeci frame.
void Mouse::advance(int step)
{
    // Metod advance se poziva dva puta:
    // Ako je step == 0, onda se poziva da informise elemente
    // o tome da ce se desiti advance (korisno da se elementi pripreme za advance).
    // Ako je step == 1, onda se zapravo izvrsava advance na sceni.
    if (!step)
    {
        return;
    }

    // Linija od centra misa do centra scene
    const QLineF lineToCenter(QPointF(0, 0), mapFromScene(0, 0));

    // Ako se previse odaljavamo od centra,
    // bolje da se vracamo nazad.
    if (lineToCenter.length() > 150)
    {
        qreal angleToCenter = acos(lineToCenter.dx() / lineToCenter.length());
        if (lineToCenter.dy() < 0)
        {
            angleToCenter = TWO_PI - angleToCenter;
        }
        angleToCenter = normalizeAngle((PI - angleToCenter) + PI / 2);

        if (angleToCenter < PI && angleToCenter > PI / 4)
        {
            // Rotiramo na levo
            angle_ += (angle_ < -PI / 2) ? 0.25 : -0.25;
        }
        else if (angleToCenter >= PI && angleToCenter < (PI + PI / 2 + PI / 4))
        {
            // Rotiramo na desno
            angle_ += (angle_ < PI / 2) ? 0.25 : -0.25;
        }
    }
    else if (sin(angle_) < 0)
    {
        angle_ += 0.25;
    }
    else if (sin(angle_) > 0)
    {
        angle_ -= 0.25;
    }

    // Trazimo miseve koji su nam u vidokrugu
    const QPolygonF mouseSight({ mapToScene(0, 0), mapToScene(-30, -50), mapToScene(30, -50)});
    const auto dangerMice = scene()->items(mouseSight);

    for (auto item: dangerMice)
    {
        if (item == this)
        {
            continue;
        }

        QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));

        qreal angleToMouse = acos(lineToMouse.dx() / lineToMouse.length());
        if (lineToMouse.dy() < 0)
        {
            angleToMouse = TWO_PI - angleToMouse;
        }
        angleToMouse = normalizeAngle((PI - angleToMouse) + PI / 2);

        if (angleToMouse >= 0 && angleToMouse < PI / 2)
        {
            // Rotiramo na levo
            angle_ += 0.5;
        }
        else if (angleToMouse <= TWO_PI && angleToMouse > (TWO_PI - PI / 2))
        {
            // Rotiramo na desno
            angle_ -= 0.5;
        }
    }

    // Haoticno kretanje
    if (dangerMice.size() > 1 && (qrand() % 10) == 0)
    {
        if (qrand() % 1)
        {
            angle_ += (qrand() % 100) / 500.0;
        }
        else
        {
            angle_ -= (qrand() % 100) / 500.0;
        }
    }

    speed_ += (-50 + qrand() % 100) / 100.0;

    const qreal dx = sin(angle_) * 10;
    mouseEyeDirection_ = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(speed_) * 3)));
}

void Mouse::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    Q_UNUSED(event)

    // Prosledjujemo dogadjaj roditeljskoj klasi.
    // QGraphicsItem::mousePressEvent(event);

    // Uklanjamo misa iz scene.
    // Iz dokumentacije:
    // Removes the item `item` and all its children from the scene.
    // The ownership of `item` is passed on to the caller
    // (i.e., `QGraphicsScene` will no longer delete `item` when destroyed).
    // scene()->removeItem(this);

    // Kompletno unistavamo misa
    delete this;
}
