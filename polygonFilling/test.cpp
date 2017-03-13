#include <iostream>
#include <graphics.h>
// #include <dos.h>
using namespace std;
void ffill(int x,int y,int fill,int old)
{
	if((getpixel(x,y)!=old)&&(getpixel(x,y)!=fill))
	{
    cout<<x<<"  "<<y<<endl;
		delay(8);
		putpixel(x,y,fill);
		ffill(x+1,y,fill,old);
		ffill(x-1,y,fill,old);
		ffill(x,y+1,fill,old);
		ffill(x,y-1,fill,old);
	}
}
int main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\Tc\\BGI");
	rectangle(10,50,50,10);
	ffill(15,30,MAGENTA,WHITE);
	getch();
	closegraph();
}
