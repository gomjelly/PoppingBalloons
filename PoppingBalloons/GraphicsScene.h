#pragma once

#include <QGraphicsScene>
#include <QSet>

//class Boat;
//class SubMarine;
//class Torpedo;
//class Bomb;
//class PixmapItem;
//class ProgressItem;
//class TextInformationItem;
QT_BEGIN_NAMESPACE
class QAction;
QT_END_NAMESPACE

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode {
        Big = 0,
        Small
    };

    struct SubmarineDescription {
        int type = 0;
        int points = 0;
        QString name;
    };

    struct LevelDescription {
        int id = 0;
        QString name;
        QVector<QPair<int, int>> submarines;
    };

    GraphicsScene(int x, int y, int width, int height, Mode mode, QObject* parent = nullptr);
    //qreal sealLevel() const;
    //void setupScene(QAction* newAction, QAction* quitAction);
    //void addItem(Bomb* bomb);
    //void addItem(Torpedo* torpedo);
    //void addItem(SubMarine* submarine);
    //void addItem(QGraphicsItem* item);
    //void clearScene();

signals:
    //void subMarineDestroyed(int);
    //void allSubMarineDestroyed(int);

private slots:
    //void onBombExecutionFinished();
    //void onTorpedoExecutionFinished();
    //void onSubMarineExecutionFinished();

private:
    //Mode mode;
    //ProgressItem* progressItem;
    //TextInformationItem* textInformationItem;
    //Boat* boat;
    //QSet<SubMarine*> submarines;
    //QSet<Bomb*> bombs;
    //QSet<Torpedo*> torpedos;
    //QVector<SubmarineDescription> submarinesData;
    //QHash<int, LevelDescription> levelsData;

    //friend class PauseState;
    //friend class PlayState;
    //friend class LevelState;
    //friend class LostState;
    //friend class WinState;
    //friend class WinTransition;
    //friend class UpdateScoreTransition;
};

