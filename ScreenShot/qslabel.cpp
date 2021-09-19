#include "qslabel.h"
#include"controlwidget.h"
#include<QPalette>
#include"screen.h"
using namespace Qt;
QSLabel::QSLabel(QWidget* parent):DotNum(0)
  ,TextNum(0)
{
    setMouseTracking(true);
    ispressed=false;
    isdrawline=false;
    isdrawrectangle=false;
    isdrawround=false;
    istextedit=false;
    isdrawarrow=false;
    m_plaintextedit=new QTextEdit(this);
    m_plaintextedit->hide();
    m_plaintextedit->resize(240,60);


    QPalette p1 = m_plaintextedit->palette();
    p1.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    p1.setColor(QPalette::Text, Qt::red);
    m_plaintextedit->setPalette(p1);
    m_plaintextedit->setFont(QFont("微软雅黑",14));
    connect(m_plaintextedit,SIGNAL(textChanged()),this,SLOT(ontextchanged()));
//    m_plaintextedit->setStyleSheet("QTextEdit{ border: 1px solid #dadada; }"
//                                   "QTextEdit{font-family:'Microsoft YaHei'; font-size:20px;color:#ff0000;}"
//                                   ""
//                                   );
}

void QSLabel::ontextchanged()
{
     m_plaintextedit->resize(m_plaintextedit->toPlainText().size()*15+100,m_plaintextedit->document()->size().rheight()+10);
}

void QSLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(isdrawline||isdrawrectangle||isdrawround||istextedit||isdrawarrow)
    {
        setCursor(CrossCursor);
    }
    if(ispressed)
    {
        if(isdrawline)
        {
            endPoint=event->pos();
            unique_ptr<DrawGraph>Line = make_unique<DrawLine>(startPoint,endPoint);
            Line->Setnum(++DotNum);
            DrawVec.push_back(std::move(Line));
            startPoint=endPoint;
        }
        else if(isdrawrectangle||isdrawround||isdrawarrow)
        {
            endPoint=event->pos();
        }
        update();
    }
}

void QSLabel::mousePressEvent(QMouseEvent *event)
{
        startPoint=event->pos();
        endPoint=event->pos();
        ispressed=true;
        if(istextedit && (event->buttons() & Qt::LeftButton))
        {
            if(TextNum++)
            {
                unique_ptr<DrawGraph>Text = make_unique<DrawText>(startPoint,endPoint);
                QRect rect = QRect(QPoint(m_plaintextedit->x(),m_plaintextedit->y()),QSize(m_plaintextedit->width(),m_plaintextedit->height()));
                QString str = m_plaintextedit->toPlainText();
                Text->SetAttri(rect,str);
                DrawVec.push_back(std::move(Text));
                update();

                TextNum = 0;
                m_plaintextedit->clear();
                m_plaintextedit->hide();
                return;
            }
            else
            {
                m_plaintextedit->setFocus();
                m_plaintextedit->move(startPoint);
                m_plaintextedit->show();
                m_plaintextedit->clear();
            }

        }
        else
        {
            m_plaintextedit->hide();
        }
}

void QSLabel::mouseReleaseEvent(QMouseEvent *event)
{
    setCursor(ArrowCursor);
    ispressed=false;
    DotNum = 0;
    if(isdrawrectangle)
    {
        endPoint=event->pos();
        unique_ptr<DrawGraph>Rect = make_unique<DrawRect>(startPoint,endPoint);
        DrawVec.push_back(std::move(Rect));
        update();
    }
    else if(isdrawround)
    {
        endPoint=event->pos();
        unique_ptr<DrawGraph>Rect = make_unique<DrawRound>(startPoint,endPoint);
        DrawVec.push_back(std::move(Rect));
        update();
    }
    else if(isdrawarrow)
    {
        endPoint=event->pos();
        unique_ptr<DrawGraph>Arrow = make_unique<DrawArrow>(startPoint,endPoint);
        DrawVec.push_back(std::move(Arrow));
        update();
    }

}


void QSLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0,0,selectimage); //表示是在selectimage上面做编辑
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;
    pen.setColor(red);
    pen.setWidth(2);
    painter.setPen(pen);
    for(int i=0;i<DrawVec.size();i++)
    {
        DrawVec.at(i)->Drwaing(painter);
    }
    if (isdrawrectangle)
    {
        unique_ptr<DrawGraph>Rect = make_unique<DrawRect>(startPoint,endPoint);
        Rect->Drwaing(painter);
    }
    else if (isdrawround)
    {
        unique_ptr<DrawGraph>Rect = make_unique<DrawRound>(startPoint,endPoint);
        Rect->Drwaing(painter);
    }
    else if(isdrawarrow)
    {
        unique_ptr<DrawGraph>Rect = make_unique<DrawArrow>(startPoint,endPoint);
        Rect->Drwaing(painter);
    }
    else if(istextedit)
    {
        unique_ptr<DrawGraph>Rect = make_unique<DrawText>(startPoint,endPoint);
        Rect->Drwaing(painter);
    }
}

void QSLabel::setPaste()
{
    if(DrawVec.size()>0)
    {
        int num = DrawVec.back()->Getnum();
        if(num>DrawVec.size()) return;
        for(int i =0;i<num;i++)
        {
            DrawVec.pop_back();
        }
        update();
    }

}


void QSLabel::setimagetolabel(const QImage &image)
{
    selectimage=image;

    endPoint=QPoint(0,0);
    startPoint=QPoint(0,0);
}


void QSLabel::setdrawlineenable()
{

        isdrawline=true;
        isdrawrectangle=false;
        isdrawround=false;
        istextedit=false;
        isdrawarrow=false;
        m_plaintextedit->hide();
}

void QSLabel::setrectangleenable()
{
        isdrawline=false;
        isdrawrectangle=true;
        isdrawround=false;
        istextedit=false;
        isdrawarrow=false;

        m_plaintextedit->hide();
}

void QSLabel::setdrawarrowenable()
{
       isdrawline=false;
       isdrawarrow=true;
       isdrawrectangle=false;
       isdrawround=false;
       istextedit=false;
       m_plaintextedit->hide();
}

void QSLabel::setroundenable()
{
       isdrawline=false;
       isdrawrectangle=false;
       isdrawround=true;
       isdrawarrow=false;
       istextedit=false;
       m_plaintextedit->hide();
}

void QSLabel::settexteditenable()
{
       isdrawline=false;
       isdrawrectangle=false;
       isdrawround=false;
       isdrawarrow=false;
       istextedit=true;

       m_plaintextedit->hide();
}

void QSLabel::settextedittovector()
{
//    if (istextedit&&m_plaintextedit->toPlainText().size())
//    {
//        myText *text = new myText;
//        text->mRect = QRect(QPoint(m_plaintextedit->x(), m_plaintextedit->y()), QSize(m_plaintextedit->width(), m_plaintextedit->height()));
//        text->mText = m_plaintextedit->toPlainText();
//        texts.push_back(text);
//        update();
//    }
}

QImage QSLabel::resultimage()
{
    //return QImage(QPixmap::grabWidget(this).toImage());
    return QImage(QWidget::grab().toImage());
}
