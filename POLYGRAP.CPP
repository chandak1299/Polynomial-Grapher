#include<stdlib.h>
#include<string.h>
#include<iostream.h>
#include<conio.h>
#include<math.h>
#include<dos.h>
#include<graphics.h>
int COLOR=RED, SCROLL_RATE=0,n;
double a[11];
void derivative(double pol[],double der[],int deg);
void range(double &unit,double pol[],int deg);
void points(double unit,double dy,double dx,double uf,long int pix[][2]);
void plot(long int pix[][2]);
void axis(double dx,double dy);
void scale(double unitx,double unity,long int pix[][2]);
void scroll(char c,double &dx, double &dy);
void zoom(char c,double &uf);
void homescreen();
void settings();
void input();
void help();
void scale(double,double);
void main()
{
 clrscr();
 double i,max,min,unit,dx=0,dy=0,uf=1;
 long int pix[640][2];
 int gd=DETECT,gm;
 char c;
 initgraph(&gd,&gm,"C:\\TC\\BGI");
 setbkcolor(15);
 homescreen();
 range(unit,a,n);
 points(unit,dy,dx,uf,pix);
 axis(dx,dy);
 scale(unit,uf);
 plot(pix);
 do
  {
  c=getch();
  cleardevice();
  switch(c)
   {
    case 'a':
    case 's':
    case 'd':
    case 'w':scroll(c,dx,dy);
    break;
    case 'o':
    case 'i':zoom(c,uf);
    break;
    case 'e':
    dx=dy=0;
    homescreen();
   }
   axis(dy,dx);
   points(unit,dy,dx,uf,pix);
   scale(unit,uf);
   plot(pix);
  }while(c!='e');
 getch();
 closegraph();
}
void derivative(double pol[],double der[],int deg)  //to find derivative of polynomial
 {
  int i;
  for(i=0;i<=deg-1;i++)
  {
   der[i]=pol[i+1]*(i+1);
  }
 }
void range(double &unit,double pol[],int deg) //to find unit for first display of graph
 {
  double i,x,derroot[100];
  double maxx,minx;
  x=poly(-1000.0,deg,pol);
  for(i=-1000;poly(i,deg,pol)*x>0&&i<1000;i++);
  minx=i;
  x=poly(1000.0,deg,pol);
  for(i=1000;poly(i,deg,pol)*x>0&&i>-1000;i--);
  maxx=i;
  for(i=50;i-maxx<0;i+=50);
  maxx=i;
  for(i=50;minx+i<0;i+=50);
  minx=i;             // to accommodate all the roots
  if(maxx>=minx)
   minx=-maxx;
  else
   {
    maxx=minx;
    minx=-minx;
   }
  double maxy,miny,j=0;
  double deri[100],a,b;
  derivative(pol,deri,deg);
  a=poly(-1000,deg-1,deri);
  for(i=-1000;i<=1000;i++)
   {
    b=poly(i,deg-1 ,deri);
    if(a*b<=0)
     {
      derroot[j]=poly(i,deg,pol);
      j++;
     }
    a=b;
   }
  miny=100000;
  maxy=-100000;
  for(i=0;i<j;i++)
   {
    if(derroot[i]>maxy)
     maxy=derroot[i];
    if(derroot[i]<miny)
     miny=derroot[i];
   }
  for(i=50;i-maxy<0;i+=50);
   maxy=i;
  for(i=50;miny+i<0;i+=50);
   miny=i;
  if(maxy>=miny)
   miny=-maxy;
  else
   {
    maxy=miny;
    miny=-miny;
   }
  if(maxy/240.0>maxx/320.0)      //to accommodate all maxima and minima
   {
    unit=maxy/240.0;
   }
  else
   {
    unit=maxx/320.0;     //unit for the graph(no of variables in one pixel
   }
 }
void points(double unit,double dy,double dx,double uf,long int pix[][2])  //to find (x,y)
 {
  long int j,i;
  double x,y;
  for(j=0,i=-320;i<=320;i++,j++)   //i is the pixel
   {
    x=(i+dx)*unit*uf;           //value of x for respective pixel
    y=poly(x,n,a);              //value of y for respective x
    pix[j][0]=i+320;                        //pixels for plotting
    pix[j][1]=240-(y/(unit*uf))-dy;
   }
 }
void plot(long int pix[][2])
 {
  int i=0;
  setcolor(COLOR);
  setlinestyle(SOLID_LINE,1,1);
  for(;i<639;i++)
   {
    moveto(pix[i][0],pix[i][1]);
    if(pix[i][1]>=0&&pix[i+1][1]<=480)         //to complete line if pix goes out of range
     lineto(pix[i+1][0],pix[i+1][1]);          //to plot the lines
   }
 }
void axis(double dx,double dy)
 {
  cleardevice();
  int i;
  for(i=0;i<=640;i+=10)
   {
    setlinestyle(SOLID_LINE,2,1);
    setcolor(7);
    line(i,0,i,480);        //grid
    setcolor(8);
    line(i,235-dx,i,245-dx);      //dashes
   }
  for(i=0;i<480;i+=10)
   {
    setlinestyle(SOLID_LINE,2,1);
    setcolor(7);
    line(0,i,640,i);         //grid
    setcolor(8);
    line(325-dy,i,315-dy,i);       //dashes
   }
  setcolor(8);
  setlinestyle(SOLID_LINE,1,3);
  line(320-dy,0,320-dy,480);//y axis
  line(0,240-dx,640,240-dx);//x axis
 }
void zoom(char c,double &uf)
 {
  switch(c)
   {
    case 'i':             //zoomin
     uf=uf/2;
     break;
    case 'o':             //zoomout
     uf=uf*2;
     break;
   }
  }
void scroll(char c,double &dx, double &dy)
 {
  switch(c)
   {
    case 'w':                       //graph moves up
     dy=dy+(50+SCROLL_RATE)*4/5;
     break;
    case 'a':                       //left
     dx=dx+(50+SCROLL_RATE)*4/5;
     break;
    case 's':                       //right
     dy=dy-(50+SCROLL_RATE)*4/5;
     break;
    case 'd':                       //down
     dx=dx-(50+SCROLL_RATE)*4/5;
     break;
    }
   }
void homescreen()
 {
  cleardevice();
  axis(0,0);
  settextstyle(5,HORIZ_DIR,5);
  setcolor(RED);
  outtextxy(410,100,"PolyGraph");
  settextstyle(5,HORIZ_DIR,1);
  setcolor(BLUE);
  outtextxy(50,380,"For Settings, press 's'.");
  outtextxy(50,400, "For help press 'h.'");
  outtextxy(50,420,"To begin plotting, press 'g'");
  outtextxy(50,440,"To exit, press 'e'");
  settextstyle(1,HORIZ_DIR,2);
  setcolor(COLOR);
  char c;
  again:
  c=getch();
  switch(c)
   {
    case 's':
     settings();
     break;
    case 'h':
     help();
     break;
    case 'g':
     input();
     outtextxy(10,50,"PLOTTING...");
     delay(1000);
     break;
    case 'e':
     cleardevice();
     outtextxy(200,220,"Another Successful Run By");
     outtextxy(220,260,"Siddharth Chandak");
     outtextxy(280,280," and");
     outtextxy(240,300,"Anshul Nasery");
     delay(1000);
     exit(0);
    default:
     goto again;
   }
  }
void settings()
 {
  set:
  cleardevice();
  outtextxy(10,20,"For color settings, press 'c'");
  outtextxy(10,50,"For scrolling speed, press 's'");
  outtextxy(10,80,"To go back to the previous menu, press 'b'");
  char c=getch();
  char c2;
  switch(c)
   {
    case 's':
    do{
     cleardevice();
     char scr[10];
     itoa(SCROLL_RATE+50,scr,10);
     outtextxy(10,50,"The current scroll rate is");
     outtextxy(280,50,scr);
     outtextxy(10,80,"To change it to 50, press 1.");
     outtextxy(10,110," To change it to 100, press 2.");
     outtextxy(10,140," To change it to 150, press 3");
     outtextxy(10,170,"To go back, press 'b'");
     ips:
     c2=getch();
     if(c2=='1')
     SCROLL_RATE=0;
     if(c2=='2')
     SCROLL_RATE=50;
     if(c2=='3')
     SCROLL_RATE=100;
     if(c2=='b')
     goto set;
     else
     goto ips;
    }while(c2!='b');
    break;
     case 'c':
    do{
     cleardevice();
     setcolor(COLOR);
     outtextxy(10,50,"The current color is");
     char col[10];
     if(COLOR==RED)
     strcpy(col,"Red");
     if(COLOR==BLUE)
     strcpy(col,"Blue");
     if(COLOR==GREEN)
     strcpy(col,"Green");
     outtextxy(250,50,col);
     outtextxy(10,80,"To change it, enter 'r','b' or 'g'");
     outtextxy(10,110,"To go back, press 's'");
     ipc:
     c2=getch();
     if(c2=='r')
     COLOR=RED;
     else if(c2=='b')
     COLOR=BLUE;
     else if(c2=='g')
     COLOR=GREEN;
     else if(c2=='s')
     goto set;
     else
     goto ipc;
    }while(c2!='s');
    break;
    case 'b':
     homescreen();
     break;
    default:
     goto set;
   }
 }
void input()
 {
  cleardevice();
  outtextxy(10,20,"Enter the degree of the polynomial");
  gotoxy(10,40);
  cin>>n;
  outtextxy(10,60,"Enter the coefficients of the powers starting from the");
  outtextxy(10,80,"constant term");
  int j;
  gotoxy(10,80);
  char str[30][30];
  for(j=0;j<=n;j++)
   {
    cin>>a[j];
    gotoxy(10,85+j);
   }
  cleardevice();
 }
void help()
 {
  cleardevice();
  setcolor(COLOR);
  outtextxy(10,20,"Welcome to Polygraph.");
  outtextxy(10,80,"To begin,select the input option in the main menu");
  outtextxy(10,40,"This graphing tool allows you to plot accurate graphs upto");
  outtextxy(10,60,"5th degree polynomials");
  outtextxy(10,100,"Begin by entering the degree of the polynomial, and then");
  outtextxy(10,120,"the coefficients starting from the constant term");
  outtextxy(10,140,"You can zoom in and out of the graph by pressing 'o' or 'i'");
  outtextxy(10,160,"For scrolling, use 'w','a','s',and 'd'");
  outtextxy(10,180,"Press any key to go back");
  getch();
  homescreen();
 }
void scale(double unit,double uf)
 {
  setcolor(8);
  rectangle(500,10,620,80);
  settextstyle(4,0,2);
  setcolor(COLOR+2);
  outtextxy(523,15,"SCALE");
  int ui=unit*uf*10;
  int ud=(unit*uf*10-ui)*1000;
  char sui[15],suf[4];
  itoa(ui,sui,10);
  itoa(ud,suf,10);
  if(suf[2]=='\0')
   {
    if(suf[1]=='\0')
     {
      suf[2]=suf[0];
      suf[0]='0';
      suf[1]='0';
      suf[3]='\0';
     }
    suf[2]=suf[1];
    suf[1]=suf[0];
    suf[0]='0';
    suf[3]='\0';
   }
  strcat(sui,".");
  strcat(sui,suf);
  settextstyle(2,0,4);
  outtextxy(510,50,"1 Unit is");
  outtextxy(580,50,sui);
 }
