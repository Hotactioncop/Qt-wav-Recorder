#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaRecorder>
#include <QAudioRecorder>
#include <QAudioProbe>
#include <QUrl>
#include <QFileDialog>
#include <QMediaRecorder>
#include <QStandardPaths>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QAudioRecorder *m_audioRecorder = nullptr;
    int number;
    bool alreadyInRun;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public slots:
    void startrecord();
    void stoprecord();
};

#endif // MAINWINDOW_H
