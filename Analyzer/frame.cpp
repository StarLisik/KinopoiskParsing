#include "frame.h"
#include "./ui_frame.h"

Frame::Frame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Frame)
{
    ui->setupUi(this);
}

void Frame::set(QList<Film> film) {
    setVisible(true);
    bsave = false;
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(9);
    QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
    __qtablewidgetitem->setText("Место в рейтинге");
    ui->tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
    QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
    __qtablewidgetitem1->setText("Название");
    ui->tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
    QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
    __qtablewidgetitem2->setText("Год");
    ui->tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
    QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
    __qtablewidgetitem3->setText("Продолжительность");
    ui->tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
    QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
    __qtablewidgetitem4->setText("Страна");
    ui->tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
    QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
    __qtablewidgetitem5->setText("Жанр");
    ui->tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
    QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
    __qtablewidgetitem6->setText("Режиссёр");
    ui->tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
    QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
    __qtablewidgetitem7->setText("Рейтинг");
    ui->tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
    QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
    __qtablewidgetitem8->setText("Количество оценок");
    ui->tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);

    ui->tableWidget->setRowCount(film.size());
    for (int i = 0; i < film.size(); ++i) {
        QTableWidgetItem *qtablewidgetitem = new QTableWidgetItem();
        ui->tableWidget->setVerticalHeaderItem(i, qtablewidgetitem);

        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText(QString::number(film[i].place));
        ui->tableWidget->setItem(i, 0, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText(film[i].name);
        ui->tableWidget->setItem(i, 1, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem();
        item3->setText(QString::number(film[i].year));
        ui->tableWidget->setItem(i, 2, item3);

        QTableWidgetItem *item4 = new QTableWidgetItem();
        item4->setText(QString::number(film[i].duration));
        ui->tableWidget->setItem(i, 3, item4);

        QTableWidgetItem *item5 = new QTableWidgetItem();
        item5->setText(film[i].country);
        ui->tableWidget->setItem(i, 4, item5);

        QTableWidgetItem *item6 = new QTableWidgetItem();
        item6->setText(film[i].genre);
        ui->tableWidget->setItem(i, 5, item6);

        QTableWidgetItem *item7 = new QTableWidgetItem();
        item7->setText(film[i].director);
        ui->tableWidget->setItem(i, 6, item7);

        QTableWidgetItem *item8 = new QTableWidgetItem();
        item8->setText(QString::number(film[i].rating));
        ui->tableWidget->setItem(i, 7, item8);

        QTableWidgetItem *item9 = new QTableWidgetItem();
        item9->setText(QString::number(film[i].numberRatings));
        ui->tableWidget->setItem(i, 8, item9);
//        if (i == film.size() - 1)
//            qDebug() << "1";
    }
}

void Frame::save() {
ExcelExportHelper helper;
    for (int i = 0; i < ui->tableWidget->columnCount(); ++i) {
        QTableWidgetItem *qtablewidgetitem = ui->tableWidget->horizontalHeaderItem(i);
        helper.SetCellValue(1, i + 2, qtablewidgetitem->text());
        for (int j = 0; j < ui->tableWidget->rowCount(); ++j) {
            if (i == 0) {
                qtablewidgetitem = ui->tableWidget->verticalHeaderItem(j);
                helper.SetCellValue(j + 2, 1, qtablewidgetitem->text());
            }
            QTableWidgetItem *item = ui->tableWidget->item(j, i);
            if (i == 7 && !bsave) {
//                qDebug() << item->text() << item->text().mid(0, item->text().lastIndexOf(QChar('.'))) << item->text().mid(item->text().lastIndexOf(QChar('.')) + 1);
                helper.SetCellValue(j + 2, i + 2, QString("%1,%2")
                                    .arg(item->text().mid(0, item->text().lastIndexOf(QChar('.'))))
                                    .arg(item->text().mid(item->text().lastIndexOf(QChar('.')) + 1)));
            } else
                helper.SetCellValue(j + 2, i + 2, item->text());
        }
    }
//    helper.SetCellValue(1,1,"Test-11");
//    helper.SetCellValue(1,2,"Test-12");

//    helper.SaveAs(fileName);
}

Frame::~Frame()
{
    delete ui;
}

void Frame::setQuantity(QString name, QList<List *> list) {
    setVisible(true);
    bsave = true;
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(2);
    QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
    __qtablewidgetitem->setText(name);
    ui->tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
    QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
    __qtablewidgetitem1->setText("Колличество");
    ui->tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);

    ui->tableWidget->setRowCount(list.size());
    for (int i = 0; i < list.size(); ++i) {
        QTableWidgetItem *qtablewidgetitem = new QTableWidgetItem();
        ui->tableWidget->setVerticalHeaderItem(i, qtablewidgetitem);

        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText(list[i]->name);
        ui->tableWidget->setItem(i, 0, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText(QString::number(list[i]->quantity));
        ui->tableWidget->setItem(i, 1, item2);
    }
}

void Frame::select(QList<ListSelect> list) {
    setVisible(true);
    bsave = true;
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(list.size());
//    for (int i = 0; i < list.size(); ++i) {
////        qDebug() << "------------------" << list[i].name;
//        for (int j = 0; j < list[i].list.size(); ++j) {
//            qDebug() << list[i].list[j]->name << list[i].list[j]->quantity;
//        }
//    }

    for (int i = 0; i < list.size(); ++i) {
        QTableWidgetItem *qtablewidgetitem = new QTableWidgetItem();
        qtablewidgetitem->setText(list[i].name);
        ui->tableWidget->setHorizontalHeaderItem(i, qtablewidgetitem);
        for (int j = 0; j < list[i].list.size(); ++j) {
            if (i == 0) {
                ui->tableWidget->setRowCount(list[i].list.size());
                QTableWidgetItem *qtablewidgetitem = new QTableWidgetItem();
                qtablewidgetitem->setText(list[i].list[j]->name);
                ui->tableWidget->setVerticalHeaderItem(j, qtablewidgetitem);
            }
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(QString::number(list[i].list[j]->quantity));
            ui->tableWidget->setItem(j, i, item);
            if (i == 27) {
//                qDebug() << list[i].list[j]->name << list[i].list[j]->quantity;
            }
        }
    }
}
