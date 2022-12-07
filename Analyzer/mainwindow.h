#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QList>
#include <frame.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Frame *frame;
    QList<Film> film;
    QList<List *> listYear,
                  listCountry,
                  listDirector,
                  listGenre;
    QList<int> year;

    bool changed[4], check[3];

    void upDate();
    void upDateCheck();
    void select(QList<List *> sel1, QList<List *> sel2);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_year_currentIndexChanged(int index);
    void on_country_currentIndexChanged(int index);
    void on_director_currentIndexChanged(int index);
    void on_genre_currentIndexChanged(int index);
    void on_checkBox_clicked();
    void on_checkBox_2_clicked();
    void on_checkBox_3_clicked();
};
#endif // MAINWINDOW_H
