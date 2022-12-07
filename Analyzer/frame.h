#ifndef FRAME_H
#define FRAME_H

#include <QFrame>
#include <QList>
#include <QDebug>
#include <QFile>
#include <QFileDialog>

#include "excelexporthelper.h"

namespace Ui {
class Frame;
}

struct Film {
    int place;//Место в рейтинге
    int year;//год
    int duration;//Продолжительность
    int numberRatings;//Количество оценок
    double rating;//Рейтинг
    QString name;//Название
    QString country;//Страна
    QString genre;//жанр
    QString director;//режиссер
};

struct List {
    int quantity;
    QString name;
};

struct ListSelect {
    QList<List *> list;
    QString name;
};

class Frame : public QFrame
{
    Q_OBJECT

public:
    explicit Frame(QWidget *parent = nullptr);
    ~Frame();

    void setQuantity(QString name, QList<List *> list);
    void select(QList<ListSelect> list);
    void set(QList<Film> film);
    void save();
private:
    Ui::Frame *ui;
    bool bsave = false;
};

#endif // FRAME_H
