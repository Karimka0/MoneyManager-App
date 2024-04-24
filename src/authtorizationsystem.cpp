#include "authtorizationsystem.h"
#include "ui_authtorizationsystem.h"

authtorizationSystem::authtorizationSystem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authtorizationSystem)
{
    ui->setupUi(this);
}

authtorizationSystem::~authtorizationSystem()
{
    delete ui;
}
