#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("数字图像处理");
    this->setWindowIcon(QIcon(":/rsc/SEUIcon.png"));
    this->resize(1200, 800);
}

MainWindow::~MainWindow()
{
    if(image) delete image;
    delete ui;
}


//读取图片
void MainWindow::on_pushButton_pressed()
{
    QString file = QFileDialog::getOpenFileName(
                        this,
                        tr("选择一张图片"),
                        "D:\\SEU DOCUMENTS\\数字图像处理\\src", //默认路径，只考虑本地
                        tr("Image Files (*.png *.jpg *.bmp *.raw)")
                        );
    if(file == NULL || file == ""){
        return;
    }
    QString suffix = file.split(".")[1];

    if(suffix != "raw"){ //读取非raw格式文件
        QImage img = QImage(file);

        QGraphicsScene* scene = new QGraphicsScene();
        scene->addPixmap(QPixmap::fromImage(img));
        ui->graphicsView1->setScene(scene);


        this->image = new MyImage(img.bits(), img.width(), img.height()); //根据图像数据加载到MyImage类中
        qDebug() << img;



        uchar* tmp = img.bits();
        int w = img.width();
        int h = img.height();
        int line = img.bytesPerLine();
        qDebug() << line;
        for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                tmp[i * line + j] = 255 - tmp[i * line + j];
            }
        }

        QImage tmp_img(tmp, img.width(), img.height(), img.format());
        QGraphicsScene* scene2 = new QGraphicsScene();
        scene2->addPixmap(QPixmap::fromImage(tmp_img));
        ui->graphicsView2->setScene(scene2);
        qDebug() << tmp_img;

    }
    else{ //读取raw格式文件
        this->image = new MyImage(file); //直接根据raw文件加载类

        //完善显示图片的代码
    }

}

void MainWindow::on_geo_trans_triggered()
{
    qDebug() << "几何变换调用";
    QImage img = this->image->covertColor();
    qDebug() << img;
    QGraphicsScene* scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(img));
    ui->graphicsView2->setScene(scene);
    //MyImage img = image->geoTrans(0);
    //ui->img2->setPixmap(QPixmap::fromImage(img.toQImage()));
}

//保存图片
void MainWindow::on_pushButton_2_pressed()
{

}
