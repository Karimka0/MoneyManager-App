#ifndef AUTHTORIZATIONSYSTEM_H
#define AUTHTORIZATIONSYSTEM_H

#include <QDialog>

namespace Ui {
class authtorizationSystem;
}

class authtorizationSystem : public QDialog
{
    Q_OBJECT

public:
    explicit authtorizationSystem(QWidget *parent = nullptr);
    ~authtorizationSystem();

private:
    Ui::authtorizationSystem *ui;
};

#endif // AUTHTORIZATIONSYSTEM_H
