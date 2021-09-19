#include "controlwidget.h"
#include "ui_controlwidget.h"
#include <QPoint>
#include "screen.h"
#include <QDebug>
#include <QApplication>
#include <QClipboard>

ControlWidget::ControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlWidget),
    screen(NULL)
{
    ui->setupUi(this);
//    this->setFixedSize(QSize(500,35));
    connectSignalAndSlot();
    Qt::WindowFlags nType = Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint;
    setWindowFlags(nType);

}

void ControlWidget::connectSignalAndSlot()
{
    connect(ui->rectBtn, SIGNAL(clicked()), this, SLOT(slotrectangleBtnclicked()));
    connect(ui->groundBtn, SIGNAL(clicked()), this, SLOT(slotdrawRoundBtnclicked()));

    connect(ui->arwowBtn, SIGNAL(clicked()), this, SLOT(slotarrowBtnclicked()));
    connect(ui->penBtn, SIGNAL(clicked()), this, SLOT(slotdrawLineBtnclicked()));
    connect(ui->textBtn, SIGNAL(clicked()), this, SLOT(slottextEditBtclicked()));
    connect(ui->retBtn, SIGNAL(clicked()), this, SLOT(slotreturneditBtnclicked()));
    connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(cancelBtn_slot()));
    connect(ui->saveBtn, SIGNAL(clicked()), this, SLOT(saveBtn_slot()));

}
//撤销截图按钮
void ControlWidget::cancelBtn_slot()
{
    if(screen)
    {
        screen->close();
        screen->Exit();
    }
    this->close();

}
//保存截图按钮
void ControlWidget::saveBtn_slot()
{
    screen->savePixmap();
    cancelBtn_slot();
    emit screen->signalclose(screen->getFileName());

}

//完成按钮将截图保存到剪贴板
void ControlWidget::finishBtn_slot()
{
    QClipboard *board = QApplication::clipboard();
    QPixmap pix = screen->getGrabPixmap();
    board->setImage(pix.toImage());
    cancelBtn_slot();
}


//保存Screen类的引用
void ControlWidget::setScreenQuote(Screen *screen)
{
    this->screen = screen;
}

ControlWidget::~ControlWidget()
{
    delete ui;
}

void ControlWidget::slotdrawLineBtnclicked()
{

    screen->drawline();
}



void ControlWidget::slottextEditBtclicked()
{
    screen->textedit();
}

void ControlWidget::slotrectangleBtnclicked()
{
    screen->drawrectang();
}

void ControlWidget::slotdrawRoundBtnclicked()
{
    screen->drawround();
}

void ControlWidget::slotarrowBtnclicked()
{
    screen->drawarrow();
}

void ControlWidget::slotmosaicBtnclicked()
{

}

void ControlWidget::slotreturneditBtnclicked()
{
   screen->drawpaste();
}

