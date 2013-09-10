
// stdafx.cpp : 只包括标准包含文件的源文件
// newdraw.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


bool SaveBitmap(HBITMAP hBitmap,char* filename)
{
	BITMAP bitmap;
	GetObject(hBitmap,sizeof(BITMAP),&bitmap);

	LPVOID lp=VirtualAlloc(0,bitmap.bmHeight*bitmap.bmWidthBytes,MEM_COMMIT,PAGE_READWRITE);
	if(lp==0) return false;
	GetBitmapBits(hBitmap,bitmap.bmHeight*bitmap.bmWidthBytes,lp);
	BITMAPFILEHEADER b1={0};
	BITMAPINFOHEADER b2={0};
	b1.bfType=(DWORD)(('M'<<8)|'B');
	b1.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	b1.bfSize=sizeof(BITMAPFILEHEADER)+bitmap.bmHeight*bitmap.bmWidthBytes+sizeof(BITMAPINFOHEADER);

	b2.biSize=sizeof(BITMAPINFOHEADER);
	b2.biWidth=bitmap.bmWidth;
	b2.biHeight=bitmap.bmHeight;
	b2.biPlanes=1;
	b2.biBitCount=bitmap.bmBitsPixel;
	b2.biCompression=BI_RGB;
	b2.biSizeImage=bitmap.bmHeight*bitmap.bmWidthBytes;

	HANDLE hFile=CreateFileA(filename,FILE_ALL_ACCESS,NULL,NULL,CREATE_ALWAYS,NULL,NULL);
	HANDLE hmap=CreateFileMapping(hFile,NULL,PAGE_READWRITE,0,b1.bfSize,0);
	LPVOID l=MapViewOfFile(hmap,FILE_MAP_WRITE,0,0,0);
	if(l==0) return false;
	memcpy(l,&b1,sizeof(BITMAPFILEHEADER));
	memcpy((BYTE*)l+sizeof(b1),&b2,sizeof(BITMAPINFOHEADER));
	for(int i=0;i<bitmap.bmHeight;i++)
		memcpy((BYTE*)l+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+i*bitmap.bmWidthBytes,(BYTE*)lp+(bitmap.bmHeight-1-i)*bitmap.bmWidthBytes,bitmap.bmWidthBytes);
	UnmapViewOfFile(l);
	CloseHandle(hmap);
	CloseHandle(hFile);
	VirtualFree(lp,bitmap.bmHeight*bitmap.bmWidthBytes,MEM_FREE);
	if(GetLastError()) return false;
	return true;
}