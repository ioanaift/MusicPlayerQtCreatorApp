#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>
#include <QFileDialog>
#include <QDir>
#include <QtMultimedia/QMediaPlayer>
#include <QString>

int value;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    playListModel = new QStandardItemModel(this);
    ui->playlistView->setModel(playListModel);

    playListModel->setHorizontalHeaderLabels(QStringList()  << tr("Audio Track") << tr("File Path"));
    ui->playlistView->hideColumn(1);
    ui->playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);


    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(player);
    player->setPlaylist(playlist);
    //playlist->setPlaybackMode(QMediaPlaylist::Loop);

    slider = new QSlider(this);
    //bar = new QProgressBar(this);
    slider->setOrientation(Qt::Horizontal);

    ui->statusBar->addPermanentWidget(slider);
    //ui->statusBar->addPermanentWidget(bar);

    connect(player,&QMediaPlayer::durationChanged, slider,&QSlider::setMaximum);
    connect(player,&QMediaPlayer::positionChanged, slider,&QSlider::setValue);
    connect(slider,&QSlider::sliderMoved, player,&QMediaPlayer::setPosition);

    ui-> volume ->setRange(0, 100);
    ui-> volume->setFixedWidth(100);
    ui-> volume->setValue(70);

    //connect(ui->volume,&QSlider::sliderMoved, this ,this->on_volume_valueChanged);

    //connect(player,&QMediaPlayer::durationChanged, bar,&QProgressBar::setMaximum);
    // connect(player,&QMediaPlayer::positionChanged, bar,&QProgressBar::setValue);

    connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){
        playlist->setCurrentIndex(index.row());
    });


    connect(playlist, &QMediaPlaylist::currentIndexChanged, [this](int index){
        ui->currentTrack->setText(playListModel->data(playListModel->index(index, 0)).toString());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
//    QString filename = QFileDialog::getOpenFileName(this, "Open File","","Audio File (*.mp3)");
//    on_actionStop_triggered();
//    if (filename.isEmpty()){
//        return;
//    }

//    player->setMedia(QUrl::fromLocalFile(filename));

//    on_actionPlay_triggered();


    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open files"), QString(), tr("Audio Files (*.mp3)"));

    foreach (QString filename, files) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filename).dirName()));
        items.append(new QStandardItem(filename));
        playListModel->appendRow(items);
        playlist->addMedia(QUrl::fromLocalFile(filename));

        on_actionStop_triggered();
        if (filename.isEmpty()){
            return;
        }

        player->playlist();

       on_actionPlay_triggered();
    }
}

void MainWindow::on_actionPlay_triggered()
{
    player->play();
    ui->statusBar->showMessage("Playing");
    printf("palying");
}

void MainWindow::on_actionPause_triggered()
{
    player->pause();
    ui->statusBar->showMessage("Paused");
}

void MainWindow::on_actionStop_triggered()
{
    player->stop();
    ui->statusBar->showMessage("Stoped");
}


void MainWindow::on_volume_valueChanged(int value)
{
    player->setVolume(value);
    //printf("%d\n", value);
}


void MainWindow::on_mute_pressed()
{
    ui-> volume->setValue(0);



}
