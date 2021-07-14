#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QWidget>
#include <QAudioOutput>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
#include <QStandardItemModel>
#include <QMediaPlaylist>
#include <QMediaPlayer>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionPlay_triggered();

    void on_actionPause_triggered();

    void on_actionStop_triggered();

    void on_volume_valueChanged(int value);

    void on_mute_pressed();

    void on_actionNext_triggered();

    void on_actionPrevious_triggered();

    void on_actionRepeat_triggered();

    void on_actionShuffle_triggered();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QMediaPlaylist* playlist;
    QSlider* slider;
    QSlider* volumeslider;
    QStandardItemModel* playListModel;

};

#endif // MAINWINDOW_H
