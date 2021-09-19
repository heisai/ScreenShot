#include"DrawGraph.h"
DrawGraph::DrawGraph(QPoint start,QPoint end)
    :startPoint(start)
    ,endPoint(end)
    ,num(1)
{

}






void DrawLine::Drwaing(QPainter &painter)
{
    painter.drawLine(startPoint,endPoint);
}


void DrawArrow::Drwaing(QPainter &painter)
{
    painter.setBrush(QBrush(Qt::red));
    double par=15.0;
    double slopy=atan2((endPoint.y()-startPoint.y()),(endPoint.x()-startPoint.x()));
    double cosy=cos(slopy);
    double siny=sin(slopy);
    QPoint point1 = QPoint(endPoint.x() + int(-par*cosy - (par / 2.0*siny)), endPoint.y() + int(-par*siny + (par / 2.0*cosy)));
    QPoint point2 = QPoint(endPoint.x() + int(-par*cosy + (par / 2.0*siny)), endPoint.y() - int(par / 2.0*cosy + par*siny));
    QPoint points[3]={endPoint,point1,point2};
    painter.setRenderHint(QPainter::Antialiasing,true);
    QPen drawtrianglepen;
    drawtrianglepen.setColor(Qt::red);
    drawtrianglepen.setWidth(1);
    painter.setPen(drawtrianglepen);
    painter.drawPolygon(points,3);
    int offsetx=int(par*siny/3);
    int offsety=int(par*cosy/3);
    QPoint point3,point4;
    point3 = QPoint(endPoint.x() + int(-par*cosy - (par / 2.0*siny)) + offsetx, endPoint.y() + int(-par*siny + (par / 2.0*cosy)) - offsety);
    point4 = QPoint(endPoint.x() + int(-par*cosy + (par / 2.0*siny) - offsetx), endPoint.y() - int(par / 2.0*cosy + par*siny) + offsety);
    QPoint arrbodypoints[3]={startPoint,point3,point4};
    painter.drawPolygon(arrbodypoints,3);
    painter.setBrush(Qt::NoBrush);
}



void DrawRound::Drwaing(QPainter &painter)
{
    int x2 = startPoint.x() < endPoint.x() ? startPoint.x() : endPoint.x();
    int y2 = startPoint.y() < endPoint.y() ? startPoint.y() : endPoint.y();
    painter.drawEllipse(x2, y2, abs(endPoint.x() - startPoint.x()), abs(endPoint.y() - startPoint.y()));
}


void DrawRect::Drwaing(QPainter &painter)
{
    int x1 = startPoint.x() < endPoint.x() ? startPoint.x() : endPoint.x();
    int y1 = startPoint.y() < endPoint.y() ? startPoint.y() : endPoint.y();
    painter.drawRect(x1, y1, abs(endPoint.x() - startPoint.x()), abs(endPoint.y() - startPoint.y()));
}



void DrawText::Drwaing(QPainter &painter)
{
    painter.setFont(QFont("微软雅黑",textsize));
    painter.drawText(rect, Qt::TextWrapAnywhere, str);
}
