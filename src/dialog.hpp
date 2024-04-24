#pragma once
#include <QDate>
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = nullptr);
  ~Dialog();

  void AddAccoutTo(QString name);
  void AddAccoutFrom(QString name);

  void ClearAccChoose();
signals:
  void add_button_clicked(QString type, QString account_to,
                          QString account_from, QString currency,
                          QString description, QString sum, QString category,
                          QDate date);

private slots:

  void on_TypeChoose_activated(int index);

  void on_pushButton_clicked();

private:
  Ui::Dialog *ui;
};
