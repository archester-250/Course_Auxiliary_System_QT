#ifndef OUTOFCLASS_H
#define OUTOFCLASS_H

#include <QDialog>

namespace Ui {
class OutOfClass;
}

class OutOfClass : public QDialog
{
    Q_OBJECT

public:
    explicit OutOfClass(QWidget *parent = nullptr);
    ~OutOfClass();

private slots:
    void receiveName(QString name);

private:
    Ui::OutOfClass *ui;
    QString name;
};

#endif // OUTOFCLASS_H
