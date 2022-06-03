#ifndef SEECOURSEDOC_H
#define SEECOURSEDOC_H

#include <QDialog>

namespace Ui {
class SeeCourseDoc;
}

class SeeCourseDoc : public QDialog
{
    Q_OBJECT

public:
    explicit SeeCourseDoc(QWidget *parent = nullptr);
    ~SeeCourseDoc();

private:
    Ui::SeeCourseDoc *ui;
};

#endif // SEECOURSEDOC_H
