#include "stdafx.h"
#include "picdata.h"

Picdata::Picdata(int r,int l,int pc,bool se,bool vi)
{
	radio=r;
	linewidth=l;
	pencolor=pc;
	IsSelected=se;
	IsVisible=vi;
}
void Picdata::eraser()
{
	IsVisible=false;
}
bool Picdata::checkin(CPoint mp1,CPoint mp2)
{
	int mx1,mx2,my1,my2,temp;
	mx1=mp1.x;
	mx2=mp2.x;
	my1=mp1.y;
	my2=mp2.y;
	if(mx1>mx2) {temp=mx1;mx1=mx2;mx2=temp;}
	if(my1>my2) {temp=my1;my1=my2;my2=temp;}

	int x1,x2,y1,y2;
	x1=p1.x;
	x2=p2.x;
	y1=p1.y;
	y2=p2.y;
	if(x1>x2) {temp=x1;x1=x2;x2=temp;}
	if(y1>y2) {temp=y1;y1=y2;y2=temp;}

	if(mx1<x1&&x2<mx2&&my1<y1&&y2<my2)
		return true;
	else return false;
}





Line::Line(int r,int l,int pc,bool se,bool vi):Picdata(r,l,pc,se,vi)
{

}

void Line::draw(CDC& dc)
{
	CPen mpen(PS_SOLID,linewidth,pencolor);
	dc.SelectObject(mpen);

	dc.MoveTo(p1);
	dc.LineTo(p2);
	mpen.DeleteObject();

}


Square::Square(int r,int l,int pc,bool se,bool vi):Picdata(r,l,pc,se,vi)
{

}

void Square::draw(CDC& dc)
{
	CPen mpen(PS_SOLID,linewidth,pencolor);
	dc.SelectObject(mpen);

	dc.Rectangle(p1.x,p1.y,p2.x,p2.y);
	mpen.DeleteObject();

}



Circle::Circle(int r,int l,int pc,bool se,bool vi):Picdata(r,l,pc,se,vi)
{

}

void Circle::draw(CDC& dc)
{
	CPen mpen(PS_SOLID,linewidth,pencolor);
	dc.SelectObject(mpen);

	dc.Ellipse(p1.x,p1.y,p2.x,p2.y);
	mpen.DeleteObject();
}


Eraser::Eraser(int r,int l,int pc,bool se,bool vi/* =false */):Square(r,l,pc,se,vi)
{

}

void Eraser::draw(CDC& dc)
{
	CPen mpen(PS_DASH,1,RGB(0,0,0));
	dc.SelectObject(mpen);
	dc.Rectangle(p1.x,p1.y,p2.x,p2.y);
	mpen.DeleteObject();
}