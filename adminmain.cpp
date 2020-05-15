#include "adminmain.h"
#include "ui_adminmain.h"


AdminMain::AdminMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminMain)
{
    ui->setupUi(this);
    //this->resize(800, 600);

    //connect(ui->pushButton_ExportDoc, SIGNAL(clicked()), this, SLOT(slotPushButtonExportDoc_clicked()));

    //connect(ui->commandLinkButton_AddNewDB, SIGNAL(clicked()), this, SLOT(slotAddNewDB()));
}

AdminMain::~AdminMain()
{
    delete ui;
}


bool AdminMain::takeConnect(QSqlDatabase d)
{
    db = d;
    qDebug() << db.userName();

    this->setWindowTitle(db.userName()+"::Админ");

    if(db.open())
    {
        qDebug() << "Connect to database!";
        //        QSqlQuery query;
        //        query.prepare("SELECT database_name FROM study.user_database WHERE user_name = :user");
        //        query.bindValue(":user", db.userName());
        //        query.exec();

        ui->stackedWidget_WorkSpace->setCurrentIndex(0);
        db_buffer.setDB(&db);

        //        while (query.next())
        //        {
        //            ui->listWidget_Databases->addItem(query.value(0).toString());

        //            qDebug() << query.value(0).toString() << endl;
        //        }

        return true;
    }

    return false;
}

void AdminMain::on_pushButton_clicked()
{
    mydb.Calculate(ui->spinBox_hours->value(), ui->doubleSpinBox_coeff->value());

    ui->listWidget_Temu->clear();
    ui->tableWidget_Zachet->setRowCount(0);


    if(ui->checkBox_Visble_Predmet->isChecked())
    {
        ui->groupBox_Zachet->setVisible(true);

        qDebug() << "1/3";

        vector <QString> predmet;
        vector <int> kredit;

        for(int i = 0; i < mydb.result_mod.size(); i++)
        {
            bool flag = false;
            int number;

            for(int j = 0; j < predmet.size(); j++)
                if(predmet[j] == mydb.result_mod[i].discipline)
                {
                    flag = true;
                    number = j;
                }
            qDebug() << "1.1/3";

            if(!flag)
            {
                predmet.push_back(mydb.result_mod[i].discipline);
                kredit.push_back(mydb.result_mod[i].hours);
            }
            else
                kredit[number] = kredit[number] + mydb.result_mod[i].hours;

            qDebug() << "1.2/3";
        }

        qDebug() << "2/3";


        for(int i = 0; i < predmet.size(); i++)
        {
            ui->tableWidget_Zachet->insertRow(ui->tableWidget_Zachet->rowCount());
            ui->tableWidget_Zachet->setItem(ui->tableWidget_Zachet->rowCount()-1, 0, new QTableWidgetItem(predmet[i]));
            ui->tableWidget_Zachet->setItem(ui->tableWidget_Zachet->rowCount()-1, 1, new QTableWidgetItem((QVariant(kredit[i]/30)).toString()));
        }

    }
    else
        ui->groupBox_Zachet->setVisible(false);

    if(ui->groupBox_ChekModule->isChecked())
    {
        ui->groupBox_Temu->setVisible(true);

        if(ui->radioButton_All->isChecked())
        {
            for(int i = 0; i < mydb.result_mod.size(); i++)
                ui->listWidget_Temu->addItem(mydb.result_mod[i].name);
        }
    }
    else
        ui->groupBox_Temu->setVisible(false);

    qDebug() << "3/3";

    if(ui->checkBox_Form_Quest->isChecked())
    {
        ui->groupBox_Tests->setVisible(true);
        ui->label_Tests->setText("");

        for(int i = 0; i < mydb.result_question.size(); i++)
        {
            ui->label_Tests->setText(ui->label_Tests->text() + "\n" + QVariant(i+1).toString() + ". " + mydb.result_question[i].text + "\na) " + mydb.result_question[i].a + "\nb) " + mydb.result_question[i].b + "\nc) " + mydb.result_question[i].c + "\nd) " + mydb.result_question[i].d + "\n");
        }
    }
    else
    {
        ui->groupBox_Tests->setVisible(false);
    }

    ui->stackedWidget_MainWidget->setCurrentIndex(2);
}

void AdminMain::on_pushButton_2_clicked()
{
    ui->stackedWidget_MainWidget->setCurrentIndex(0);
}

void AdminMain::on_pushButton_Return_clicked()
{
    ui->stackedWidget_MainWidget->setCurrentIndex(1);
}

void AdminMain::on_pushButton_Open_clicked()
{
    db.setDatabaseName(ui->listWidget_Databases->item(ui->listWidget_Databases->currentRow())->text());
    qDebug() << ui->listWidget_Databases->item(ui->listWidget_Databases->currentRow())->text();

    Database d;
    mydb = d;

    if(mydb.LoadData(&db))
        ui->stackedWidget_MainWidget->setCurrentIndex(1);
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Невозможно извлечь информаию из базы данных!\n");
        msgBox.exec();
    }
}

void AdminMain::on_pushButton_Gotovo_clicked()
{
    ui->stackedWidget_MainWidget->setCurrentIndex(0);
}

//void AdminMain::on_tableWidget_Zachet_itemClicked(QTableWidgetItem *item)
//{
//    ui->listWidget_Temu->clear();

//    for(int i = 0; i < mydb.result_mod.size(); i++)
//    {
//        if(mydb.result_mod[i].discipline == ui->tableWidget_Zachet->selectedItems()[0]->text())
//            ui->listWidget_Temu->addItem(mydb.result_mod[i].name);
//    }
//}

void AdminMain::on_tableWidget_Zachet_cellClicked(int row, int column)
{
    if(ui->radioButton_Otdelno->isChecked())
    {
        ui->listWidget_Temu->clear();

        for(int i = 0; i < mydb.result_mod.size(); i++)
        {
            if(mydb.result_mod[i].discipline == ui->tableWidget_Zachet->selectedItems()[0]->text())
                ui->listWidget_Temu->addItem(mydb.result_mod[i].name);
        }
    }
}

void AdminMain::slotPushButtonExportDoc_clicked()
{
    //    QAxObject *pword = new QAxObject("Word.Application");
    //    QAxObject *pdoc = pword->querySubObject("Documents");
    //    pdoc = pdoc->querySubObject("Add()");

    //    QAxObject *prange = pdoc->querySubObject("Range()");
    //    prange->dynamicCall("SetRange(int, int)", 0, 100);
    //    prange->setProperty("Text", ui->label_Tests->text());

    //    QAxObject *pfont = prange->querySubObject("Font");
    //    pfont->setProperty("Size", 14);
    //    pfont->setProperty("Name", "Times New Roman");

    //    pword->setProperty("Visible", true);

    //pdoc->dynamicCall("SaveAs()", "tests", "doc");
}

void AdminMain::on_pushButton_ExportPdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "%HOMEPATH%\\test", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName); // устанавливаем путь к pdf файлу

    QTextDocument doc;
    //doc.setHtml("<h1>" + ui->label_Tests->text() + "</h1>");
    doc.setPlainText(ui->label_Tests->text());
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);

    //    // работаем с отрисовкой pdf через QPainter
    //    QPainter p(&printer);
    //    // выполняем действия с p
    //    p.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    //    p.drawText(0, 0, ui->label_Tests->text());
    //    p.end();
}

void AdminMain::slotAddNewDB()
{};

void AdminMain::on_commandLinkButton_AddNewDB_clicked()
{
    db_buffer.DownloadUsers();
    db_buffer.DownloadDatabaseName();
    ui->stackedWidget_WorkSpace->setCurrentIndex(1);
}

void AdminMain::on_commandLinkButton_ViewDBs_clicked()
{
    ui->stackedWidget_WorkSpace->setCurrentIndex(3);
}

void AdminMain::on_commandLinkButton_AddNewUser_clicked()
{
    ui->stackedWidget_WorkSpace->setCurrentIndex(4);
}

void AdminMain::on_commandLinkButton_ViewUsers_clicked()
{
    ui->stackedWidget_WorkSpace->setCurrentIndex(6);
}

void AdminMain::on_lineEdit_NameDB_editingFinished()
{
    if(db_buffer.FindDatabaseName(ui->lineEdit_NameDB->text()))
    {
        if(ui->lineEdit_NameDB->text().size() != 0)
            ui->label_WarningsNameDB->setText("База данных с таким названием уже существует!");
        else
            ui->label_WarningsNameDB->setText("Название не введено!");

        ui->pushButton_AddNewDB_Next_1->setEnabled(false);
    }
    else
    {
        ui->label_WarningsNameDB->setText("Название базы данных введено верно!");

        if(!ui->plainTextEdit_InformationDB->toPlainText().size())
            ui->label_WarningsMoreInformation->setText("Дополнительная информация не введена.\nРекомендуется внести данные, которые помогут пользователю работать с ней.");
        else
            ui->label_WarningsMoreInformation->setText("Дополнительная информация введена!");

        if(!ui->tableWidget_Users->rowCount())
            ui->label_WarningsUsers->setText("Не назначены пользователи, которые могут редактировать БД.\nРекомендуется сразу внести эту информацию, чтобы пользователи могли сразу приступить к работе.");
        else
            ui->label_WarningsUsers->setText("Редакторы назначены!");

        ui->pushButton_AddNewDB_Next_1->setEnabled(true);
    }
}

void AdminMain::on_pushButton_AddNewDB_Next_1_clicked()
{
    ui->stackedWidget_WorkSpace->setCurrentIndex(2);
}

void AdminMain::on_pushButton_InMainPage_DB_clicked()
{
    ui->stackedWidget_WorkSpace->setCurrentIndex(0);
}

void AdminMain::on_pushButton_AddMoreDB_clicked()
{
    ui->commandLinkButton_AddNewDB->clicked();
}

void AdminMain::on_pushButton_ChangeUsers_clicked()
{
    UsersSelectionDialog *SelectionDialog = new UsersSelectionDialog;
    SelectionDialog->setTables(db_buffer.getUsersList());
    connect(SelectionDialog, SIGNAL(takeResult(QList <QString>)), this, SLOT(slot_getInfoFrom_UserSelectionDialog(QList <QString>)));
    SelectionDialog->exec();
}

void AdminMain::slot_getInfoFrom_UserSelectionDialog(QList <QString> resultList)
{
    ui->tableWidget_Users->setRowCount(0);

    QList <User> tempList = db_buffer.getUsersList();
    int x = 0;
    bool flag;

    while(x < tempList.size())
    {
        flag = false;

        for(int i = 0; i < resultList.size(); i++)
        {
            if(resultList.at(i) == tempList.at(x).fio)
            {
                flag = true;
                resultList.removeAt(i);
                x++;
                i = resultList.size();
            }
        }

        if(!flag)
        {
            tempList.removeAt(x);
        }
    }


    for(int i = 0; i < tempList.size(); i++)
    {
        ui->tableWidget_Users->insertRow(ui->tableWidget_Users->rowCount());
        ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 0, new QTableWidgetItem(tempList.at(i).fio));

        if(tempList.at(i).role == "Admin")
            ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 1, new QTableWidgetItem("Администратор"));
        else if(tempList.at(i).role == "Oper")
            ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 1, new QTableWidgetItem("Оператор"));
        else if(tempList.at(i).role == "Exp")
            ui->tableWidget_Users->setItem(ui->tableWidget_Users->rowCount()-1, 1, new QTableWidgetItem("Эксперт"));
    }

    if(db_buffer.FindDatabaseName(ui->lineEdit_NameDB->text()))
    {
        if(ui->lineEdit_NameDB->text().size() != 0)
            ui->label_WarningsNameDB->setText("База данных с таким названием уже существует!");
        else
            ui->label_WarningsNameDB->setText("Название не введено!");

        ui->pushButton_AddNewDB_Next_1->setEnabled(false);
    }
    else
    {
        ui->label_WarningsNameDB->setText("Название базы данных введено верно!");

        if(!ui->plainTextEdit_InformationDB->toPlainText().size())
            ui->label_WarningsMoreInformation->setText("Дополнительная информация не введена.\nРекомендуется внести данные, которые помогут пользователю работать с ней.");
        else
            ui->label_WarningsMoreInformation->setText("Дополнительная информация введена!");

        if(!ui->tableWidget_Users->rowCount())
            ui->label_WarningsUsers->setText("Не назначены пользователи, которые могут редактировать БД.\nРекомендуется сразу внести эту информацию, чтобы пользователи могли сразу приступить к работе.");
        else
            ui->label_WarningsUsers->setText("Редакторы назначены!");

        ui->pushButton_AddNewDB_Next_1->setEnabled(true);
    }
}

void AdminMain::on_plainTextEdit_InformationDB_textChanged()
{
    if(db_buffer.FindDatabaseName(ui->lineEdit_NameDB->text()))
    {
        if(ui->lineEdit_NameDB->text().size() != 0)
            ui->label_WarningsNameDB->setText("База данных с таким названием уже существует!");
        else
            ui->label_WarningsNameDB->setText("Название не введено!");

        ui->pushButton_AddNewDB_Next_1->setEnabled(false);
    }
    else
    {
        ui->label_WarningsNameDB->setText("Название базы данных введено верно!");

        if(!ui->plainTextEdit_InformationDB->toPlainText().size())
            ui->label_WarningsMoreInformation->setText("Дополнительная информация не введена.\nРекомендуется внести данные, которые помогут пользователю работать с ней.");
        else
            ui->label_WarningsMoreInformation->setText("Дополнительная информация введена!");

        if(!ui->tableWidget_Users->rowCount())
            ui->label_WarningsUsers->setText("Не назначены пользователи, которые могут редактировать БД.\nРекомендуется сразу внести эту информацию, чтобы пользователи могли сразу приступить к работе.");
        else
            ui->label_WarningsUsers->setText("Редакторы назначены!");

        ui->pushButton_AddNewDB_Next_1->setEnabled(true);
    }
}
