#pragma  once
#include "stdafx.h"

class Picdata
{
protected:
	int radio;
	int linewidth;
	int pencolor;
	bool IsSelected;
	bool IsVisible;

public:
	CPoint p1;
	CPoint p2;
	bool checkin(CPoint mp1,CPoint mp2);
	void SetSelect(bool s) {IsSelected=s;}
	bool GetSelect() {return IsSelected;}
	bool GetVisible() {return IsVisible;}
	void eraser();
	Picdata(int r,int l,int pc,bool se=false,bool vi=true) ;
	~Picdata() {}
    virtual void draw(CDC& dc)=0;
};

class Line:public Picdata
{

public:
	Line(int r,int l,int pc,bool se=false,bool vi=true) ;
	~Line() {}
	void draw(CDC& dc);
};

class Square:public Picdata
{
public:
	Square(int r,int l,int pc,bool se=false,bool vi=true) ;
	~Square() {}
	void draw(CDC& dc);

};

class Circle:public Picdata
{
public:
	Circle(int r,int l,int pc,bool se=false,bool vi=true) ;
	~Circle() {}
	void draw(CDC& dc);
};



class Eraser:public Square
{
public:
	Eraser(int r,int l,int pc,bool se=false,bool vi=false);
	~Eraser();
	void draw(CDC& dc);
};