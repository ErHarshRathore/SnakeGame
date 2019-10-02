#include<dos.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>

void printMessage(void);

void printMessage()
{
  printf("\n%5c Snake Game(v2.0) :\n\n",char(4));
  printf("\t%c  Developed By : Er. Harsh Rathore\n",char(15));
  printf("\t%c  Developed On : 21 December 2018(Fri)\n",char(15));
  printf("\t%c  Tested By    : Gautam ,Navya,Riya and Harsh\n",char(15));
  printf("\n    %c Project Details :\n\n",char(4));
  printf("\t%c  Start  Date : 15 December 2018(Sat) \n",char(15));
  printf("\t%c  Finish Date : 20 December 2018(Thur)\n",char(15));
  printf("\t%c  Last Update : 27 December 2018(Thur)\n",char(15));
  printf("\n%5c Features and Rules :\n\n",char(4));
  printf("\t%c  The Snake Can Overlap it-self\n",char(15));
  printf("\t%c  The Display Limits Shifts the Snake on Other end\n",char(15));
  printf("\t%c  You Have only 3 Total Life Times\n",char(15));
  printf("\t%c  Snake should take food before Timer is Over\n",char(15));
  printf("\t%c  The Maximum Lenght of Snake is 30 \n",char(15));
  printf("\t%c  When you take food 135 times You Will Won\n",char(15));
  printf("\t%c  Use Arrow Keys For Play,SpaceBar for Stop",char(15));
  printf(" and ESC for Force Exit\n");
  printf("\n%5c Enter the Gaming Level from \"1\" to \"5\" : ",char(16));
}

void main()
{
	int gd=DETECT,gm,time,i;
	clrscr();

	printMessage();
	scanf("%d",&i);
	printf(" Loading...");
	delay(1500);

	switch(i) //Select the initial Gaming Level
	{
		case 1 :time=90;  break;
		case 2 :time=80;  break;
		case 3 :time=70;  break;
		case 4 :time=60;  break;
		case 5 :time=50;  break;
		default:time=45;
	}

  initgraph(&gd,&gm,"..\\bgi"); //Initializing the Graphics
  int x=getmaxx(),y=getmaxy(),xh=x/2,yh=y/2,randx,randy;
  int len=4,score=0,timer=1,heart=0,temp_timer;
  int xs[31]={xh,xh,xh,xh},ys[31]={yh,yh,yh,yh},
	  poly[]={0,0 , 35,0 , 35,28 , 0,28};
  char tab='s',eat='y',*str;

  //For Initial Frame Formating
  line(0,29,x,29);line(0,y-20,x,y-20); //Upper and Lower Display Divider
  sprintf(str,"%d             %d           %d",score,len,100-time);
  setcolor(9);outtextxy(10,y-15,"Score :      Length :      Speed :");
  setcolor(14);outtextxy(82,getmaxy()-15,str);
  setcolor(12);outtextxy(x-220,y-15,"Made By Er.Harsh Rathore...");
  settextstyle(0,0,2);sprintf(str,"%c %c %c",char(3),char(3),char(3));
  outtextxy(x-99,8,str);setcolor(14);outtextxy(x-115,8,"| | | |");
  settextstyle(4,0,4); settextjustify(1,0);
  setcolor(13);outtextxy(xh,26,"SNAKE GAME");

  //Game Starts From Here
  while(len<=30) //Exit if Lenght is Greater then 30
  {
	if(eat=='y') //For putting the Food on Random x & y co-ordinates
	{
	  put_food:
	  randx=random((x-20))+10;randy=random((y-67))+37;
	  for(i=1;i<=len;i++)
	   if(abs(xs[i]-randx)<10 && abs(ys[i]-randy)<10)
		 goto put_food;//Change food possition if it is below of Snake
	  setfillstyle(1,random(14)+1);fillellipse(randx,randy,5,5);
	  temp_timer=(500/time);timer=30;eat='n';//set food not Taken Yet
	}
	//Clearing the Snake Footprints from Display
	setcolor(0);setfillstyle(1,0);fillellipse(xs[1],ys[1],7,7);
	fillellipse(xs[len],ys[len],5,5);
	if(temp_timer==0)//For decreament in timer clock
	{	timer--;fillpoly(4,poly);temp_timer=(500/time);}
	if(abs(xs[0]-randx)<13&&abs(ys[0]-randy)<13)//When Snake takes the food
	{
	  fillellipse(randx,randy,5,5);fillpoly(4,poly);settextstyle(0,0,1);
	  score++;sprintf(str," %d",score);fillellipse(87,y-12,15,7);
	  setcolor(14);outtextxy(82,y-7,str);
	  if(score%5==0)//Increases the Lenght
	  {
		len++;sprintf(str," %d",len>30?len-1:len);
		setcolor(0);fillellipse(192,y-12,15,7);
		setcolor(14);outtextxy(188,y-7,str);
	  }
	  if(score%20==0)//Increases the Speed of Snake by 0.7 milisec/pixel
	  {
		time-=7;sprintf(str," %d",100-time);
		setcolor(0);fillellipse(297,y-12,15,7);
		setcolor(14);outtextxy(293,y-7,str);
	  }
	  eat='y'; //Set the food has been taken
	}
	//Puts the Snake again and again
	setcolor(11);setfillstyle(9,timer>10?10:12);fillellipse(xs[0],
	ys[0],7,7);  for(i=1 ;i<len ;i++)fillellipse(xs[i],ys[i],5,5);
	//Writes the Timer value
	if(temp_timer==500/time||temp_timer==500/(time+6))
	{
	  sprintf(str,"%d",timer) ;settextstyle(0,0,2);
	  if(timer<10)setcolor(12);outtextxy(20,22,str);
	}
	if(timer==0) //Reducing the Life when Timer is 0 or Exit the Game
	{
	  setcolor(8);sprintf(str,"%c",char(3));settextstyle(0,0,2);outtextxy
	  (x-(28+heart++*32),24,str);if(heart>2)break;//Ends the loop Game Over
	  tab='s';delay(2000);timer=30;temp_timer=500/time;
	}
	if(kbhit()) //KeyBoard Listener
	{
	  char temp=getch();   if(temp==27)break; if(temp==32)tab='s';
	  if(temp==80&&tab!='u')tab='d';if(temp==72&&tab!='d')tab='u';
	  if(temp==77&&tab!='l')tab='r';if(temp==75&&tab!='r')tab='l';
	}
	//Shifts the Prev Possition upto Next while tail
	for(i=len;i>=1;i--){xs[i]=xs[i-1];ys[i]=ys[i-1];}

	//Move the Head or Snake Ahead
	if(tab=='r') xs[0]+=10; if(tab=='l') xs[0]-=10;
	if(tab=='d') ys[0]+=10; if(tab=='u') ys[0]-=10;
	if(tab=='s') getch();

	//When Display Limit Over Shifts the Snake on other end
	if(xs[0]<7)  xs[0]=x-7;	if(xs[0]>x-7)  xs[0]=7;
	if(ys[0]<37) ys[0]=y-29;if(ys[0]>y-29) ys[0]=37;

	delay(time);temp_timer--;//Delay by which User can see the Snake Clearly
  }
  //When Game Has terminated Shows the Results
  setcolor(4);settextstyle(1,0,10);settextjustify(1,1);
  if(len==31){outtextxy(xh,yh-150,"You");outtextxy(xh,yh,"Won");}
  else     {outtextxy(xh,yh-150,"Game");outtextxy(xh,yh,"Over");}
  settextstyle(4,0,8);setcolor(9);sprintf(str," %d",score);
  outtextxy(xh,y-100,str);delay(3000);getch();closegraph();
}