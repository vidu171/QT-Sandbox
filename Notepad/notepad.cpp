#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

Notepad::~Notepad()
{
    delete ui;
}



void Notepad::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void Notepad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open then file");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot Open File "+ file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();

}

void Notepad::on_actionSave_triggered()
{
    QString fileName = currentFile;

    if(currentFile.isNull()){
        fileName = QFileDialog::getSaveFileName(this,"Save File");
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QFile::Text )){
        QMessageBox::warning(this,"warning","Can not save file");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.close();

}
