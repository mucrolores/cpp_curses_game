#include <iostream>
#include <cstdlib>
#include <ctime>
#include <curses.h>
#include <windows.h>
using namespace std;//monitor space 24(height)*80(length)

char screen[24][80];
void setBound();
void showScreen();
int findBlock();
void clearScreen();
void initialSet();
void cursesShow();

class producer
{
	public:
		producer();
		int get_cor();
		int get_life();
		int get_cycle_Count();
		void place_Cor(int target_Cor);
		void replace(int iniCor);
		void move();
		int copy();
		void clear();
		
		
	private:
		int cor_X;
		int cor_Y;
		int life;
		int cycle_Count;
		char pState1;
		char pState3;
		
	
};

producer::producer()
{
	pState1 = 'p';
	pState3 = 'P';
	cycle_Count = 1;
	life = 0;
	cor_X = 99;
	cor_Y = 99;
}

int producer::get_cor()
{
	return cor_X*100+cor_Y;
}
	
int producer::get_life()
{
	return life;
}
	
int producer::get_cycle_Count()
{
	return cycle_Count;
}

void producer::place_Cor(int target_Cor)
{
	cor_X = target_Cor/100;
	cor_Y = target_Cor%100;
	screen[cor_X][cor_Y] = pState1;
	life = 1;
}
	
void producer::move()
{
	int new_Cor_X,new_Cor_Y;
	if(life>0)
	{
		new_Cor_X = cor_X+rand()%3-1;
		new_Cor_Y = cor_Y+rand()%3-1;
		if(screen[cor_X-1][cor_Y-1]==' '||screen[cor_X-1][cor_Y]==' '||screen[cor_X-1][cor_Y+1]==' '||screen[cor_X][cor_Y-1]==' '||screen[cor_X][cor_Y+1]==' '||screen[cor_X+1][cor_Y-1]==' '||screen[cor_X+1][cor_Y]==' '||screen[cor_X+1][cor_Y+1]==' ')
		{
			while(screen[new_Cor_X][new_Cor_Y]!=' ')
			{
				new_Cor_X = cor_X+rand()%3-1;
				new_Cor_Y = cor_Y+rand()%3-1;	
			}
			screen[new_Cor_X][new_Cor_Y] = pState1;
			screen[cor_X][cor_Y] = ' ';
			cor_X = new_Cor_X;
			cor_Y = new_Cor_Y;
		}
		cycle_Count++;
	}
		
}

int producer::copy()
{
	int new_Cor_X = (cor_X+rand()%3)-1;
	int new_Cor_Y = (cor_Y+rand()%3)-1;
	
	if(life>0)
	{
		if(screen[cor_X-1][cor_Y-1]==' ' || screen[cor_X-1][cor_Y]==' ' || screen[cor_X-1][cor_Y+1]==' '||screen[cor_X][cor_Y-1]==' '||screen[cor_X][cor_Y+1]==' '||screen[cor_X+1][cor_Y-1]==' '||screen[cor_X+1][cor_Y]==' '||screen[cor_X+1][cor_Y+1]==' ')
		{
			while(screen[new_Cor_X][new_Cor_Y]!=' ')
			{
				new_Cor_X = cor_X+rand()%3-1;
				new_Cor_Y = cor_Y+rand()%3-1;
			}
			return new_Cor_X*100+new_Cor_Y;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}

void producer::clear()
{
	screen[cor_X][cor_Y]=' ';
	cor_X = 99;
	cor_Y = 99;
	life = 0;
	cycle_Count = 0;
}

void producer::replace(int iniCor)
{
	screen[cor_X][cor_Y] = pState1;
}

class consumer
{
	public:
		consumer();
		int get_cor();
		int get_life();
		int get_cycle_Count();
		void modify_Cor(int target_Cor);
		void place_Cor(int target_Cor);
		void move();
		int eat();
		void clear();
		
	private:
		int cor_X;
		int cor_Y;
		int life;
		int cycle_Count;
		char CState1;
		char CState2;
};

consumer::consumer()
{
	CState1 = 'C';
	CState2 = 'c';
	cycle_Count = 3;
	life = 0;
	cor_X = 99;
	cor_Y = 99;
}

int consumer::get_cor()
{
	return cor_X*100+cor_Y;
}
	
int consumer::get_life()
{
	return life;
}
	
int consumer::get_cycle_Count()
{
	return cycle_Count;
}

void consumer::modify_Cor(int target_Cor)
{
	cor_X = target_Cor/100;
	cor_Y = target_Cor%100;
	screen[cor_X][cor_Y] = CState1;
}

void consumer::place_Cor(int target_Cor)
{
	cor_X = target_Cor/100;
	cor_Y = target_Cor%100;
	screen[cor_X][cor_Y] = CState1;
	life = 1;
}

void consumer::move()
{
	int new_Cor_X,new_Cor_Y;
	if(life>0)
	{
		new_Cor_X = cor_X+rand()%3-1;
		new_Cor_Y = cor_Y+rand()%3-1;
		
		if(screen[cor_X-1][cor_Y-1]==' '||screen[cor_X-1][cor_Y]==' '||screen[cor_X-1][cor_Y+1]==' '||screen[cor_X][cor_Y-1]==' '||screen[cor_X][cor_Y+1]==' '||screen[cor_X+1][cor_Y-1]==' '||screen[cor_X+1][cor_Y]==' '||screen[cor_X+1][cor_Y+1]==' ')
		{
			while(screen[new_Cor_X][new_Cor_Y]!=' ')
			{
				new_Cor_X = cor_X+rand()%3-1;
				new_Cor_Y = cor_Y+rand()%3-1;	
			}
			screen[new_Cor_X][new_Cor_Y] = CState1;
			screen[cor_X][cor_Y] = ' ';
			cor_X = new_Cor_X;
			cor_Y = new_Cor_Y;
			cycle_Count--;
		}
		
	}
}

int consumer::eat()//returning eating target coordinate
{
	int new_Cor_X,new_Cor_Y;
	new_Cor_X = cor_X+rand()%3-1;
	new_Cor_Y = cor_Y+rand()%3-1;
	if(life==1 && cycle_Count<3)
	{
		if(screen[cor_X-1][cor_Y-1]=='P'||screen[cor_X-1][cor_Y]=='P'||screen[cor_X-1][cor_Y+1]=='P'||screen[cor_X][cor_Y-1]=='P'||screen[cor_X][cor_Y+1]=='P'||screen[cor_X+1][cor_Y-1]=='P'||screen[cor_X+1][cor_Y]=='P'||screen[cor_X+1][cor_Y+1]=='P' || screen[cor_X-1][cor_Y-1]=='p'||screen[cor_X-1][cor_Y]=='p'||screen[cor_X-1][cor_Y+1]=='p'||screen[cor_X][cor_Y-1]=='p'||screen[cor_X][cor_Y+1]=='p'||screen[cor_X+1][cor_Y-1]=='p'||screen[cor_X+1][cor_Y]=='p'||screen[cor_X+1][cor_Y+1]=='p')                               
		{
			while(screen[new_Cor_X][new_Cor_Y]!='P' && screen[new_Cor_X][new_Cor_Y]!='p')
			{
				new_Cor_X = cor_X+rand()%3-1;
				new_Cor_Y = cor_Y+rand()%3-1;
			}
			
			cycle_Count = 3 ;
			return new_Cor_X*100+new_Cor_Y;
		}
		else
		{
			return -1;
		}	
	}
	else
	{
		return -1;
	}
}

void consumer::clear()
{
	screen[cor_X][cor_Y]=' ';
	cor_X = 99;
	cor_Y = 99;
	life = 0;
}

int main()
{
	srand(time(NULL));
	
	setBound();
	
	producer p[1716];
	consumer c[1716];
	
	int producerAmount = 0,consumerAmount = 0;
	int toEatCor;
	int tmpProducerAmount = 0,tmpConsumerAmount = 0;
	
	cout << "how many producer you want:";
	cin >> producerAmount;
	cout << "how many consumer you want:";
	cin >> consumerAmount;
	
	while(producerAmount<0 || consumerAmount<0 || producerAmount+consumerAmount>1716)
	{
		cout << "wrong setting, please retype the number" << endl;
		system("PAUSE");
		system("CLS"); 
		cout << "how many producer you want:";
		cin >> producerAmount;
		cout << "how many consumer you want:";
		cin >> consumerAmount;
	}
	
	for(int i=0;i<producerAmount;i++)
	{
		p[i].place_Cor(findBlock());
	}
	
	for(int i=0;i<consumerAmount;i++)
	{
		c[i].place_Cor(findBlock());
	}
	initialSet();
	//showScreen();
	
	while(true)
	{
		for(int i=0;i<producerAmount;i++)//____________________________________________________________ producer copy and move
		{	
			if((p[i].get_cycle_Count())%3==1 && p[i].get_cycle_Count()>1 && p[i].copy()!=-1)
			{
				p[producerAmount].place_Cor(p[i].copy());
				producerAmount++;
			}
			p[i].move();
		}
		for(int i=0;i<consumerAmount;i++)//____________________________________________________________ consumer move
		{	
			c[i].move();
		}
				
		for(int i=0;i<consumerAmount;i++)//____________________________________________________________ consumer die
		{
			if(c[i].get_cycle_Count()==0)
			{
				c[i].clear();
			}
		}
		
		for(int i=0;i<consumerAmount;i++)//____________________________________________________________ consumer eat
		{
			toEatCor = c[i].eat();
			if(toEatCor!=-1)
			{
				for(int j=0;j<producerAmount;j++)
				{
					if(p[j].get_cor()==toEatCor)
					{
						p[j].clear();
					}
				}
				consumerAmount++;
				c[consumerAmount-1].place_Cor(toEatCor);
			}	
		}
		
		for(int j=0;j<1715;j++)
		{
			for(int i=0;i<1715;i++)
			{
				if(p[i].get_life()==0)
				{
					p[i]=p[i+1];
					p[i+1].clear();
				}
				if(c[i].get_life()==0)
				{
					c[i]=c[i+1];
					c[i+1].clear();
				}
			}
		}
		
		tmpProducerAmount = 0;
		tmpConsumerAmount = 0;
		for(int i=0;i<1716;i++)
		{
			if(p[i].get_life()==1)
			{
				tmpProducerAmount++;
			}
			if(c[i].get_life()==1)
			{
				tmpConsumerAmount++;
			}
		}
		
		producerAmount = tmpProducerAmount;
		consumerAmount = tmpConsumerAmount;
		
		setBound();
		
		for(int i=0;i<producerAmount;i++)
		{
			p[i].place_Cor(p[i].get_cor());
		}
		for(int i=0;i<consumerAmount;i++)
		{
			c[i].place_Cor(c[i].get_cor());
		}
		
		Sleep(500);
		//system("PAUSE");
		cursesShow();
		cout << endl << "producerAmount:"<< producerAmount << endl << "consumerAmount:" << consumerAmount <<endl;
		/*
		for(int i=0;i<200;i++)
		{
			cout << "[" << i << "]:";
			cout << p[i].get_cor() << "."<< p[i].get_life() << "/";
			cout << c[i].get_cor() << "."<< c[i].get_life() << "//__";
			
		}
		*/
		
		if(producerAmount==0 && consumerAmount==0)
		{
			system("CLS");
			cout << "game over" << endl;
			cout << "system message:producer die,consumer die" << endl;
			break;
		}
		else if(producerAmount==0)
		{
			system("CLS");
			cout << "game over" << endl;
			cout << "system message:producer die"<< endl;
			break;
		}
		else if(consumerAmount==0)
		{
			system("CLS");
			cout << "game over" << endl;
			cout << "system message:consumer die"<< endl;
			break;
		}
	}
	
	return 0;
}

void setBound()
{
	for(int i=0;i<24;i++)
	{
		for(int j=0;j<80;j++)
		{
			screen[i][j]=' ';
		}
	}

	for(int i=1;i<80;i++)
	{
		screen[0][i]='#';
		screen[23][i]='#';
	}
	for(int i=1;i<24;i++)
	{
		screen[i][0]='#';
		screen[i][79]='#';
	}
	screen[0][0] = '#';
	screen[0][79] = '#';
	screen[23][0] = '#';
	screen[23][79] = '#';
}

void cursesShow()
{
	for(int i=0;i<24;i++)
	{
		for(int j=0;j<80;j++)
		{
			move(i,j);
			addch(screen[i][j]);
		}
	}
	refresh();
}

void showScreen()
{
	system("CLS");
	for(int i=0;i<24;i++)
	{
		for(int j=0;j<80;j++)
		{
			cout << screen[i][j];
		}
		cout << endl;
	}
}

int findBlock()
{
	int x,y;
	x = rand()%24;
	y = rand()%80;
	
	while(screen[x][y]!=' ')
	{
		x = rand()%24;
		y = rand()%80;
	}
	return x*100+y;
}

void initialSet()
{
	initscr();
    cbreak();
    nonl();
    noecho();
    intrflush(stdscr,FALSE);
    keypad(stdscr,TRUE);
    refresh();
}

