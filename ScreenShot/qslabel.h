#ifndef QSLABEL_H
#define QSLABEL_H
#include<QLabel>
#include <QWidget>
#include<QTextEdit>
#include<QPaintEvent>
#include<QMouseEvent>
#include<QRgb>
#include <math.h>
#include<QFont>
#include"DrawGraph/DrawGraph.h"
#include<iostream>
#include<vector>
#include<memory>
#include<QDebug>
using namespace std;
class Screen;

typedef struct myLine{
    QPoint startPoint;
    QPoint endPoint;
}myLine;
typedef struct myRectangle{
    QPoint startPoint;
    QPoint endPoint;
}myRectangle;

typedef struct myRound{
    QPoint startPoint;
    QPoint endPoint;
}myRound;
typedef struct myArrow{
    QPoint startPoint;
    QPoint endPoint;
}myArrow;
typedef struct myText{
    QString mText;
    QRect mRect;

}myText;
class QSLabel : public QLabel
{
    Q_OBJECT
public:
    using DrawVector = std::vector<unique_ptr<DrawGraph>>;
    QSLabel(QWidget *parent);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void setPaste();
    void setdrawlineenable();
    void setrectangleenable();
    void setdrawarrowenable();
    void setroundenable();
    void settexteditenable();
    void settextedittovector();
    void setimagetolabel(const QImage &image);
    QImage resultimage();
public slots:
    void ontextchanged();
private:
    QPoint startPoint;
    QPoint endPoint;
//    QVector<myLine*> lines;
//    QVector<myRectangle*> rectangles;
//    QVector<myRound*> rounds;
//    QVector<myText*> texts;
//    QVector<myArrow*> arrows;
    QString text;
    QImage selectimage;
    QTextEdit *m_plaintextedit;
    bool ispressed;
    bool isdrawline;
    bool isdrawrectangle;
    bool isdrawround;
    bool istextedit;
    bool isdrawarrow;
    Screen *screen;
    DrawVector DrawVec;
    int DotNum;
    int TextNum;



};

#endif // QSLABEL_H
