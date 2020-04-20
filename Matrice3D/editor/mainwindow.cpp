#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextDocument>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextDocumentWriter>
#include <QTextStream>
#include <QTextCodec>
#include <QTextCharFormat>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFileName(QString());
    ui->Dimensione->addItems({"12", "16", "18"});
    ui->Bold->setCheckable(true);
    ui->Italic->setCheckable(true);
    ui->Underline->setCheckable(true);

    ui->textEdit->setAcceptRichText(true);
    setNewFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFileName(const QString &fileName)
{
    this->fileName = fileName;
    ui->textEdit->document()->setModified(false);

    QString name;
    if (fileName.isEmpty())
        name = "Nuovo";
    else
        name = QFileInfo(fileName).fileName();

    setWindowTitle(tr("%1 - %2").arg(QCoreApplication::applicationName(), name));
    setWindowModified(false);
}

void MainWindow::apriFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("Impossibile aprire il file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                                  file.errorString()));
        return;
    }

    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);
    if (Qt::mightBeRichText(str)) {
        ui->textEdit->setHtml(str);
    } else {
        str = QString::fromLocal8Bit(data);
        ui->textEdit->setPlainText(str);
    }
}

void MainWindow::on_Nuovo_clicked()
{
    if(maybeSave()) {
        ui->textEdit->clear();
        setFileName(QString());
        setNewFile();
    }
}

void MainWindow::on_Apri_clicked()
{          
    if (maybeSave()) {
       QFileDialog fileDialog(this, tr("Apri File"));
       fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
       fileDialog.setFileMode(QFileDialog::ExistingFile);
       fileDialog.setMimeTypeFilters(QStringList() << "text/html");
       if (fileDialog.exec() != QDialog::Accepted)
           return;
       const QString fileName = fileDialog.selectedFiles().first();
       if (!fileName.isEmpty()) {
           apriFile(fileName);
           setFileName(fileName);
       }
    }
}

bool MainWindow::on_Salva_clicked()
{
    if (fileName.isEmpty())
        return on_Salva_con_nome_clicked();

    QTextDocumentWriter writer(fileName);
    bool success = writer.write(ui->textEdit->document());
    if (success) {
        ui->textEdit->document()->setModified(false);
        QMessageBox::information(this, QCoreApplication::applicationName(),
                             tr("Salvato \"%1\"")
                             .arg(QDir::toNativeSeparators(fileName)));
    } else {
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("Impossibile salvare il file \"%1\"")
                             .arg(QDir::toNativeSeparators(fileName)));
        setFileName(QString());
    }
    return success;
}

bool MainWindow::on_Salva_con_nome_clicked()
{
    QFileDialog fileDialog(this, tr("Salva come.."));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList mimeTypes;
    mimeTypes << "text/html" ;
    fileDialog.setMimeTypeFilters(mimeTypes);
    if (fileDialog.exec() != QDialog::Accepted)
        return false;
    const QString fileName = fileDialog.selectedFiles().first();
    setFileName(fileName);

    return on_Salva_clicked();
}

void MainWindow::on_Bold_clicked()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(ui->Bold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}

void MainWindow::on_Italic_clicked()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(ui->Italic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void MainWindow::on_Underline_clicked()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(ui->Underline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void MainWindow::on_Dimensione_currentTextChanged(const QString &arg1)
{
    qreal pointSize = arg1.toFloat();
    if (pointSize > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}

void MainWindow::setNewFile()
{
    ui->Dimensione->setCurrentIndex(0);
    ui->Bold->setChecked(false);
    ui->Italic->setChecked(false);
    ui->Underline->setChecked(false);
    on_Bold_clicked();
    on_Italic_clicked();
    on_Underline_clicked();
}

bool MainWindow::maybeSave()
{
    if (!ui->textEdit->document()->isModified())
        return true;

    const QMessageBox::StandardButton ret =
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("Il documento è stato modificato.\n"
                                "Vuoi salvare le modifiche?"),
                             QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)
        return on_Salva_clicked();
    else if (ret == QMessageBox::Cancel)
        return false;
    return true;
}

void MainWindow::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}
