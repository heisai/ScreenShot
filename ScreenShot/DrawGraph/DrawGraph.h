#ifndef DRAWGRAPH_H
#define DRAWGRAPH_H
#include<QPoint>
#include<tuple>
#include<QPainter>
#include<math.h>
//绘画抽象基类
class DrawGraph
{
public:
    DrawGraph(QPoint start,QPoint end);
    void SetAttri(const QRect &mrect,const QString &mstr)
    {
        rect = mrect;
        str = mstr;
    }
    int Getnum()const
    {
        return num;
    }
    void Setnum(int mnum)
    {
        num = mnum;
    }
    virtual void Drwaing(QPainter &painter) = 0;
protected:
    QPoint startPoint;
    QPoint endPoint;
    QRect rect;
    QString str;
    int num;
    static const int textsize = 14;
};

// 绘画线条
class DrawLine:public DrawGraph
{
public:
    explicit DrawLine(QPoint start,QPoint end):DrawGraph(start,end){};
    void Drwaing(QPainter &painter)override;

};

//绘画箭头
class DrawArrow:public DrawGraph
{
public:
    explicit DrawArrow(QPoint start,QPoint end):DrawGraph(start,end){};
    void Drwaing(QPainter &painter)override;
};
//绘画椭圆
class DrawRound:public DrawGraph
{
public:
    explicit DrawRound(QPoint start,QPoint end):DrawGraph(start,end){};
    void Drwaing(QPainter &painter)override;
};
//绘画矩形
class DrawRect:public DrawGraph
{
public:
    explicit DrawRect(QPoint start,QPoint end):DrawGraph(start,end){};
    void Drwaing(QPainter &painter)override;
};
//绘画文字
class DrawText:public DrawGraph
{
public:
    explicit DrawText(QPoint start,QPoint end):DrawGraph(start,end){};
    void Drwaing(QPainter &painter)override;

};
#endif // DRAWGRAPH_H
