#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PoppingBalloons.h"

class PoppingBalloons : public QMainWindow
{
    Q_OBJECT

public:
    PoppingBalloons(QWidget *parent = nullptr);
    ~PoppingBalloons();

private:
    Ui::PoppingBalloonsClass ui;
};
