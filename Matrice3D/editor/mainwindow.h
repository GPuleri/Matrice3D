#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setFileName(const QString &fileName);
    void apriFile(const QString &fileName);

private slots:

    void on_Nuovo_clicked();
    void on_Apri_clicked();
    bool on_Salva_clicked();
    bool on_Salva_con_nome_clicked();

    void on_Bold_clicked();
    void on_Italic_clicked();
    void on_Underline_clicked();
    void on_Dimensione_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    QTextEdit *textEdit;
    QString fileName;

    void setNewFile();
    bool maybeSave();
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
};

#endif // MAINWINDOW_H
