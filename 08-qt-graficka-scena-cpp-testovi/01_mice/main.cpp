#include "mouse.h"

#include <QtGui>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <cmath>

static const unsigned mouseCount = 10u;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    qsrand(static_cast<unsigned>(QTime(0,0,0).secsTo(QTime::currentTime())));

    // Inicijalizujemo scenu
    QGraphicsScene scene;
    scene.setSceneRect(-300, -300, 600, 600);

    // Iskljucujemo indeksiranje pozicija elemenata scene
    // Usled ovoga, pretraga elemenata je linearne slozenosti.
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    // Dodajemo miseve
    for (auto i = 0u; i < mouseCount; ++i)
    {
        Mouse * mouse = new Mouse();
        mouse->setPos(sin((i * 6.28) / mouseCount) * 200,
                      cos((i * 6.28) / mouseCount) * 200);
        scene.addItem(mouse);
    }

    // Kreiramo pogled za scenu
    QGraphicsView view(&scene);
    QGraphicsView map(&scene);

    // Ukljucujemo anti-aliasing
    view.setRenderHint(QPainter::Antialiasing);

    // Postavljamo sliku za pozadinu.
    // Primetite karakter : u nazivu resursa - koristimo Qt resource system (.qtc)
    // da se neophodni resursi postave u izvrsivu datoteku naseg programa tako da nismo
    // u obavezi da ih korisniku zasebno isporucujemo.
    view.setBackgroundBrush(QPixmap(":/images/cheese.jpg"));

    // Omogucava se da korisnik misem moze da pomera glavni pogled
    // na scenu (drag and drop akcija).
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle("Misevi");
    view.resize(600, 400);
    view.show();

    map.setWindowTitle("Mapa");
    map.resize(300, 200);
    map.scale(.25, .25);
    map.show();

    // Postavljamo tajmer
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));

    // Postavljamo da se advance poziva na svakih 1000/33 ms sto otprilike daje 30fps.
    timer.start(1000 / 33);

    return app.exec();
}

