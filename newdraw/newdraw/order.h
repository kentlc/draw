#pragma once
#include "stdafx.h"

class Order
{
private:
	CString ordername;

public:
	Order(CString cs) {ordername=cs;}
	~Order() {}
	int seporder();//将输入命令分解，返回命令类型
	CPoint GetPoint1();
	CPoint GetPoint2();
};