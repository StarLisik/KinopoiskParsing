#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QList>

bool increasing(const List *p1, const List *p2) {
    return p1->name > p2->name;
}

bool decreasing(const List *p1, const List *p2) {
    return p1->name < p2->name;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    frame = new Frame();
    frame->setVisible(false);
    changed[0] = changed[1] = changed[2] = changed[3] =
            check[0] = check[1] = check[2] = false;
//    connect(ui->menu, SIGNAL(highlighted(int), this,SLOT(doMenuItem(int))));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() {
int pos;
bool b;
QString line, name;
QStringList stList;
QTextStream stream(&line);
struct Film film;
QFile fileName(QFileDialog::getOpenFileName(this, "Выберите файл", "D:/", "Файлы (*.txt)"));
    this->film.clear();
    qDebug() << fileName.fileName();
    fileName.open(QIODevice::ReadOnly);
    ui->year->clear();
    ui->country->clear();
    ui->director->clear();
    ui->genre->clear();
    listYear.clear();
    listCountry.clear();
    listDirector.clear();
    listGenre.clear();
    while (!fileName.atEnd()) {
        fileName.readLine();

        line = fileName.readLine();
        pos = QString("Место в рейтинге: ").size();
        stream.seek(pos);
        stream >> film.place;

        line = fileName.readLine();
        pos = QString("Название: ").size();
        film.name = line.mid(pos, line.lastIndexOf(QChar('\r')) - pos);

        line = fileName.readLine();
        int counterOfvalues = 0;
        for (int i = line.size() - 1; (i = line.lastIndexOf(" ", i)) != -1; --i) {
            ++counterOfvalues;
            if (counterOfvalues == 1) {
                stream.seek(i + 1);
                stream >> film.duration;
            }
            if (counterOfvalues == 2) {
                stream.seek(i + 1);
                stream >> film.year;
                break;
            }
        }
        b = true;
        if (!listYear.isEmpty())
            for (int i = 0; i < listYear.size(); ++i) {
                if (listYear[i]->name == QString::number(film.year)) {
                    ++listYear[i]->quantity;
                    b = false;
                    break;
                }
            }
        if (b) {
            listYear.append(new List());
            listYear[listYear.size() - 1]->name = QString::number(film.year);
            listYear[listYear.size() - 1]->quantity = 1;
            qSort(listYear.begin(), listYear.end(), decreasing);
        }
//        addList(listYear, QString::number(film.year));


        line = fileName.readLine();
        pos = QString("Страна и режиссер: ").size();
        stream.seek(pos);
        stream >> film.country;

        pos = line.indexOf(" • ", Qt::CaseInsensitive) + 3;
        stream.seek(pos);
        stream >> film.genre;

        pos = line.indexOf("Режиссёр: ", Qt::CaseInsensitive);
        if (pos != -1) {
        pos += QString("Режиссёр: ").size();
//        stream.seek(pos);
        film.director = line.mid(pos, line.lastIndexOf(QChar('\r')) - pos - 1);
        }
//        stream >> film.director;

//        counterOfvalues = 0;
//        int n = 0;
//        for (int i = line.size() - 1; (i = line.lastIndexOf(" ", i)) != -1; --i) {
//            ++counterOfvalues;
//            if ((line.lastIndexOf(", ", i - 2)) != -1)
////            if (counterOfvalues == 2) {
//                n = counterOfvalues;
//                film.director = line.mid(i + 1, line.lastIndexOf(QChar('\r')) - i - 1);
////            }
//            if (counterOfvalues == 3 + n) {
//                stream.seek(i + 1);
//                stream >> film.genre;
//            }
//            if (counterOfvalues == 5 + n) {
//                stream.seek(i + 1);
//                stream >> film.country;
//            }
//        }
        b = true;
        if (!listCountry.isEmpty())
            for (int i = 0; i < listCountry.size(); ++i) {
                if (listCountry[i]->name == film.country) {
                    ++listCountry[i]->quantity;
                    b = false;
                    break;
                }
            }
        if (b) {
            listCountry.append(new List());
            listCountry[listCountry.size() - 1]->name = film.country;
            listCountry[listCountry.size() - 1]->quantity = 1;
            qSort(listCountry.begin(), listCountry.end(), decreasing);
        }
//        addList(listCountry, film.country);
        b = true;
        if (!listDirector.isEmpty())
            for (int i = 0; i < listDirector.size(); ++i) {
                if (listDirector[i]->name == film.director) {
                    ++listDirector[i]->quantity;
                    b = false;
                    break;
                }
            }
        if (b) {
            listDirector.append(new List());
            listDirector[listDirector.size() - 1]->name = film.director;
            listDirector[listDirector.size() - 1]->quantity = 1;
            qSort(listDirector.begin(), listDirector.end(), decreasing);
        }
//        addList(listDirector, film.director);
        b = true;
        if (!listGenre.isEmpty())
            for (int i = 0; i < listGenre.size(); ++i) {
                if (listGenre[i]->name == film.genre) {
                    ++listGenre[i]->quantity;
                    b = false;
                    break;
                }
            }
        if (b) {
            listGenre.append(new List());
            listGenre[listGenre.size() - 1]->name = film.genre;
            listGenre[listGenre.size() - 1]->quantity = 1;
            qSort(listGenre.begin(), listGenre.end(), decreasing);
        }
//        addList(listGenre, film.genre);

        line = fileName.readLine();
        pos = QString("Рейтинг: ").size();
        stream.seek(pos);
        stream >> film.rating;

        line = fileName.readLine();
        pos = QString("Количество оценок: ").size();
        QString str = line.mid(pos, line.lastIndexOf(QChar('\r')) - pos);
        QTextStream stream1(&str);
        int n = 0, t = 0;
        if (str.indexOf(" ", Qt::CaseInsensitive) > -1)
            stream1 >> n >> t;
        else
            stream1 >> t;
        film.numberRatings = n * 1000 + t;

        this->film.append(film);

        fileName.readLine();
//        qDebug() << QString("%1 | %2 | %3 | %4 | %5 | %6 | %7 | %8 | %9")
//                    .arg(film.place)
//                    .arg(film.name)
//                    .arg(film.year)
//                    .arg(film.duration)
//                    .arg(film.director)
//                    .arg(film.genre)
//                    .arg(film.country)
//                    .arg(film.rating)
//                    .arg(film.numberRatings);
//        break;
    }
    fileName.close();
    ui->size->setText(QString::number(this->film.size()));
//    qDebug() << this->film.size();

    stList << "Все";
    for (int i = 0; i < listYear.size(); ++i) {
        stList << listYear[i]->name;
    }
    ui->year->insertItems(0, stList);
    stList.clear();
    stList << "Все";
    for (int i = 0; i < listCountry.size(); ++i) {
        stList << listCountry[i]->name;
    }
    ui->country->insertItems(0, stList);
    stList.clear();
    stList << "Все";
    for (int i = 0; i < listDirector.size(); ++i) {
        stList << listDirector[i]->name;
    }
    ui->director->insertItems(0, stList);
    stList.clear();
    stList << "Все";
    for (int i = 0; i < listGenre.size(); ++i) {
        stList << listGenre[i]->name;
    }
    ui->genre->insertItems(0, stList);

    frame->set(this->film);
}

void MainWindow::upDate() {
QList<Film> newFilm;
bool b1 = false, b2 = false, b3 = false, b4 = false;
    for (int i = 0; i < film.size(); ++i) {
        b1 = false, b2 = false, b3 = false, b4 = false;
        if (changed[0] || changed[1] || changed[2] || changed[3]) {
            if (changed[0] && film[i].year == ui->year->currentText().toInt()) {
                b1 = true;
            } else if (!changed[0])
                b1 = true;
            if (changed[1] && film[i].country == ui->country->currentText()) {
                b2 = true;
            } if (!changed[1])
                b2 = true;
            if (changed[2] && film[i].director == ui->director->currentText()) {
                b3 = true;
            } if (!changed[2])
                b3 = true;
            if (changed[3] && film[i].genre == ui->genre->currentText()) {
                b4 = true;
            } if (!changed[3])
                b4 = true;
            if (b1 && b2 && b3 && b4) {
               newFilm.append(film[i]);
            }
        } else {
            newFilm.append(film[i]);
        }
    }
    frame->set(newFilm);
}

void MainWindow::upDateCheck() {
    if (!check[0] && !check[1] && !check[2]) {
        upDate();
        return;
    }
    if (check[0] && !check[1] && !check[2]) {
        frame->setQuantity("Год", listYear);
        return;
    }
    if (!check[0] && check[1] && !check[2]) {
        frame->setQuantity("Страна", listCountry);
        return;
    }
    if (!check[0] && !check[1] && check[2]) {
        frame->setQuantity("Жанр", listGenre);
        return;
    }

    if (check[0] && check[1]) {
        QList<ListSelect> listSelect;
        ListSelect select;
        for (int i = 0; i < listCountry.size(); ++i) {
            if (changed[1])
                i = ui->country->currentIndex() - 1;
            select.name = listCountry[i]->name;
            select.list.clear();
            for (int j = 0; j < listYear.size(); ++j) {
                if (changed[0])
                    j = ui->year->currentIndex() - 1;
                List *list = new List();
                list->name = listYear[j]->name;
                list->quantity = 0;
                for (int r = 0; r < film.size(); ++r) {
                    if (film[r].year == listYear[j]->name.toInt() && film[r].country == listCountry[i]->name)
                        ++list->quantity;
                }
                select.list.append(list);
                if (changed[0])
                    break;
            }
            listSelect.append(select);
            if (changed[1])
                break;
        }
        frame->select(listSelect);
    }

    if (check[0] && check[2]) {
//        select(listYear, listGenre);
        QList<ListSelect> listSelect;
        ListSelect select;
        for (int i = 0; i < listGenre.size(); ++i) {
            if (changed[3])
                i = ui->genre->currentIndex() - 1;
            select.name = listGenre[i]->name;
            select.list.clear();
            for (int j = 0; j < listYear.size(); ++j) {
                if (changed[0])
                    j = ui->year->currentIndex() - 1;
                List *list = new List();
                list->name = listYear[j]->name;
                list->quantity = 0;
                for (int r = 0; r < film.size(); ++r) {
                    if (film[r].year == listYear[j]->name.toInt() && film[r].genre == listGenre[i]->name)
                        ++list->quantity;
                }
                select.list.append(list);
                if (changed[0])
                    break;
            }
            listSelect.append(select);
            if (changed[3])
                break;
        }
        frame->select(listSelect);
    }

    if (check[1] && check[2]) {
        select(listCountry, listGenre);
        QList<ListSelect> listSelect;
        ListSelect select;
        for (int i = 0; i < listGenre.size(); ++i) {
            if (changed[3])
                i = ui->genre->currentIndex() - 1;
            select.name = listGenre[i]->name;
            select.list.clear();
            for (int j = 0; j < listCountry.size(); ++j) {
                if (changed[1])
                    i = ui->country->currentIndex() - 1;
                List *list = new List();
                list->name = listCountry[j]->name;
                list->quantity = 0;
                for (int r = 0; r < film.size(); ++r) {
                    if (film[r].country == listCountry[j]->name && film[r].genre == listGenre[i]->name)
                        ++list->quantity;
                }
                select.list.append(list);
                if (changed[1])
                    break;
            }
            listSelect.append(select);
            if (changed[3])
                break;
        }
        frame->select(listSelect);
    }

}

void MainWindow::select(QList<List *> sel1, QList<List *> sel2) {
QList<ListSelect> listSelect;
ListSelect select;
    for (int i = 0; i < sel1.size(); ++i) {
        select.name = sel1[i]->name;
        qDebug() << select.name << "------------------";
        for (int j = 0; j < sel2.size(); ++j) {
            List *list = new List();
            list->name = sel2[j]->name;
            list->quantity = 0;
            for (int r = 0; r < film.size(); ++r) {
                if (film[r].year == sel1[i]->name.toInt() && film[r].country == sel2[j]->name)
                    ++list->quantity;
            }
            select.list.append(list);
            qDebug() << list->name << list->quantity;
        }
        listSelect.append(select);
    }
    frame->select(listSelect);
}

void MainWindow::on_pushButton_2_clicked() {
    qDebug() << "on_pushButton_2_clicked";
    frame->save();
}

void MainWindow::on_year_currentIndexChanged(int index) {
    if (index > 0)
        changed[0] = true;
    else
        changed[0] = false;
    if (!check[0] && !check[1] && !check[2])
        upDate();
    else
        upDateCheck();
}

void MainWindow::on_country_currentIndexChanged(int index) {
    if (index > 0)
        changed[1] = true;
    else
        changed[1] = false;
    if (!check[0] && !check[1] && !check[2])
        upDate();
    else
        upDateCheck();
}

void MainWindow::on_director_currentIndexChanged(int index) {
    if (index > 0)
        changed[2] = true;
    else
        changed[2] = false;
    if (!check[0] && !check[1] && !check[2])
        upDate();
    else
        upDateCheck();
}

void MainWindow::on_genre_currentIndexChanged(int index) {
    if (index > 0)
        changed[3] = true;
    else
        changed[3] = false;
    if (!check[0] && !check[1] && !check[2])
        upDate();
    else
        upDateCheck();
}

void MainWindow::on_checkBox_clicked() {
    check[0] = ui->checkBox->isChecked();

    ui->checkBox->setEnabled(true);
    ui->checkBox_2->setEnabled(true);
    ui->checkBox_3->setEnabled(true);

    if (check[0] && check[1])
        ui->checkBox_3->setEnabled(false);

    if (check[0] && check[2])
        ui->checkBox_2->setEnabled(false);

    if (check[1] && check[2])
        ui->checkBox->setEnabled(false);

    if (!check[0] && !check[1] && !check[2])
        upDate();
    else
        upDateCheck();
}

void MainWindow::on_checkBox_2_clicked() {
    check[1] = ui->checkBox_2->isChecked();

    ui->checkBox->setEnabled(true);
    ui->checkBox_2->setEnabled(true);
    ui->checkBox_3->setEnabled(true);

    if (check[0] && check[1])
        ui->checkBox_3->setEnabled(false);

    if (check[0] && check[2])
        ui->checkBox_2->setEnabled(false);

    if (check[1] && check[2])
        ui->checkBox->setEnabled(false);

    if (!check[0] && !check[1] && !check[2])
        upDate();
    else
        upDateCheck();
}

void MainWindow::on_checkBox_3_clicked() {
    check[2] = ui->checkBox_3->isChecked();

    ui->checkBox->setEnabled(true);
    ui->checkBox_2->setEnabled(true);
    ui->checkBox_3->setEnabled(true);

    if (check[0] && check[1])
        ui->checkBox_3->setEnabled(false);

    if (check[0] && check[2])
        ui->checkBox_2->setEnabled(false);

    if (check[1] && check[2])
        ui->checkBox->setEnabled(false);

    if (!check[0] && !check[1] && !check[2])
        upDate();
    else
        upDateCheck();
}
