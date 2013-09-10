#include "stdafx.h"
#include "order.h"

int Order::seporder()
{
	wchar_t name[30];
	int i;
	for(i=0;i<ordername.GetLength();i++)
		name[i]=ordername.GetAt(i);
	name[i]='\0';
	char str[15];
	for(i=0;name[i]!='(';i++)
	{
		str[i]=name[i];
	}
	str[i]='\0';
	if(strcmp(str,"LINE")==0)
		return 1;
	else if(strcmp(str,"RECTANGLE")==0)
		return 3;
	else if(strcmp(str,"ELLIPSE")==0)
		return 4;
	else return 0;
}

CPoint Order::GetPoint1()
{
	wchar_t name[30];
	CPoint p;
	int i;
	for(i=0;i<ordername.GetLength();i++)
		name[i]=ordername.GetAt(i);
	name[i]='\0';
	char str;
	int x,y;
	x=y=0;
	for(i=0;name[i]!='(';i++);
	for(i=i+1;name[i]!=',';i++)
		x=10*x+name[i]-48;
	for(i=i+1;name[i]!=',';i++)
		y=10*y+name[i]-48;
	p.x=x;p.y=y;
	return(p);
}

CPoint Order::GetPoint2()
{
	CPoint p;
	wchar_t name[30];
	int i;
	for(i=0;i<ordername.GetLength();i++)
		name[i]=ordername.GetAt(i);
	name[i]='\0';
	int x,y;
	x=y=0;
	for(i=i+1;name[i]!=',';i++);
	for(i=i+1;name[i]!=',';i++);
	for(i=i+1;name[i]!=',';i++)
		x=10*x+name[i]-48;
	for(i=i+1;name[i]!=')';i++)
		y=10*y+name[i]-48;
	p.x=x;p.y=y;
	return(p);
}
