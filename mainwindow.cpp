#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QApplication>
#include <QFileInfoList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    number=0;
    m_audioRecorder = new QAudioRecorder;
    alreadyInRun=false;

    connect(ui->pushButton,&QPushButton::pressed,[=]{
        startrecord();
    });
    connect(ui->pushButton_2,&QPushButton::pressed,[=]{
        stoprecord();
    });

    QAudioEncoderSettings settings;
    QAudioEncoderSettings audioSettings;
    settings.setCodec("audio/PCM");
    settings.setSampleRate(16000);
    settings.setBitRate(320);
    settings.setChannelCount(1);
    settings.setQuality(QMultimedia::EncodingQuality(4));
    settings.setEncodingMode(QMultimedia::ConstantQualityEncoding);

    m_audioRecorder->setEncodingSettings(settings, QVideoEncoderSettings(), "audio/x-wav");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startrecord()
{
    //Если программа уже запускалась, то инкрементируем существующий номер и добавляем к имени файла.
   if(alreadyInRun){
       number++;
       m_audioRecorder->setOutputLocation(QUrl::fromLocalFile(QApplication::applicationDirPath()+QString("/AudioFiles/audio_clip_%1.wav").arg(QString::number(number))));
       m_audioRecorder->record();
       ui->label_3->setText("Record is ON");
       ui->label_2->setText(QApplication::applicationDirPath()+"/AudioFiles/audio_clip.wav");
       return;
   }

    //Проверяем, есть ли папка в корневом каталоге. Если нет, то создаем.
    QDir dir = QApplication::applicationDirPath()+"/AudioFiles";
    if(!dir.exists()){
        dir.mkpath(QApplication::applicationDirPath()+"/AudioFiles");
    }

    //Проверяем, есть ли файл уже с таким же именем. Если есть, то инкрементируем номер и добавляем в конец названия файла и снова проверяем, пока не найдем.
    QFile file(QApplication::applicationDirPath()+"/AudioFiles/audio_clip.wav");
    if(!file.exists()){
        m_audioRecorder->setOutputLocation(QUrl::fromLocalFile(QApplication::applicationDirPath()+"/AudioFiles/audio_clip.wav"));
        m_audioRecorder->record();
        ui->label_3->setText("Record is ON");
        ui->label_2->setText(QApplication::applicationDirPath()+"/AudioFiles/audio_clip.wav");
        alreadyInRun=true;
    }else{
        while(true){
            file.setFileName(QApplication::applicationDirPath()+QString("/AudioFiles/audio_clip_%1.wav").arg(QString::number(number)));
            if(file.exists()){
                number++;
            }else break;
        }
        m_audioRecorder->setOutputLocation(QUrl::fromLocalFile(QApplication::applicationDirPath()+QString("/AudioFiles/audio_clip_%1.wav").arg(QString::number(number))));
        m_audioRecorder->record();
        ui->label_3->setText("Record is ON");
        ui->label_2->setText(QApplication::applicationDirPath()+"/AudioFiles/audio_clip.wav");
        alreadyInRun=true;
    }
}

void MainWindow::stoprecord()
{
    m_audioRecorder->stop();
    ui->label_3->setText("Record is OFF");
}
