#ifndef ADMINMENU_H
#define ADMINMENU_H

#include <QDialog>
#include "seeallcourses.h"
#include "seeallstudents.h"
#include "addcourse.h"
#include "addhomework.h"
#include "seecoursedoc.h"
#include "addcoursedoc.h"

namespace Ui {
class AdminMenu;
}

class AdminMenu : public QDialog
{
    Q_OBJECT

public:
    explicit AdminMenu(QWidget *parent = nullptr);
    ~AdminMenu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::AdminMenu *ui;
};

#endif // ADMINMENU_H
