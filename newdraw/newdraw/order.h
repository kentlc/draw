#pragma once
#include "stdafx.h"

class Order
{
private:
	CString ordername;

public:
	Order(CString cs) {ordername=cs;}
	~Order() {}
	int seporder();//����������ֽ⣬������������
	CPoint GetPoint1();
	CPoint GetPoint2();
};