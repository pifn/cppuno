#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define Mx 2 //tamanho do mapa na horizontal
#define My 2 //tamanho do mapa na vertical
const float QCx = (Mx-Mx%5)/5;
const float QCy = (My-My%5)/5;
/*
cards names:
start:
    0 for number
    1 for special card
middle:
    0 for red
    1 for yellow
    2 for green
    3 for blue
    4 for wild
end:
    number itself or id
    ids:
        0 for skip
        1 for draw two
        2 for reverse

        0 for wild card
        1 for wild draw four

empty is 444
*/
/*Uno includes 108 cards:
 25 in each of four color suits (red, yellow, green, blue),
  each suit consisting of one zero, two each of 1 through 9,
 and two each of the action cards "Skip", "Draw Two", and "Reverse".
 The deck also attains four "Wild" cards and four "Wild Draw Four"*/
//quando si gioca un card nero chiede il colore e cambia l'id della active card in base alla scelta
void CardName(int card)
{
	if((card - card%100)/100==1&&card%100-card%10!=40)
	{
		switch(card %10)
		{
		case 0:
			cout<<"skip";
			break;
		case 1:
			cout<<"+2";
			break;
		case 2:
			cout<<"cambia giro";
			break;
		default:
			cout<<"errore nel 2 switch della funzione CardName";
			cout<<card%100 - card%10;
			break;
		}
	}
	if((card - card%100)/100==0&&card%100-card%10!=40)
	{
		cout<<card % 10;
	}
	switch((card % 100 - card % 10)/10)
	{
	case 0:
		cout<<" rosso";
		break;
	case 1:
		cout<<" giallo";
		break;
	case 2:
		cout<<" verde";
		break;
	case 3:
		cout<<" blu";
		break;
	case 4:
		//Wild
		if(card == 143)
			cout<<"sceglie colore";
		else
		{
			cout<<"+4";
		}
		break;
	default:
		cout<<"errore nel 1 switch in function CardName";
		break;
	}
}
void RandomCards(int N,int cartas[192])
{
	int temp;
	for(int i = 0; i<N; i++)
	{
		int pos= rand() % N, temp = cartas[i];
		cartas[i] = cartas[pos];
		cartas[pos] = temp;
	}
}
//ac = active card
//pc = card(s) being played
//cu = amount of cards
//ps= plus
//errore:dice sempre si per i numeri e no per i +4
bool Verify(int ac, int pc[],int cu, int ps)
{
	int i;
	for(i = 0; (i<cu-1)&&((pc[i]-pc[i]%100)==(pc[i+1]-pc[i+1]%100)); i++);
	if(i==cu-1)
	{
		if((ps>0)&&(((ac-(ac%100)+ac%10)==101)||((ac-(ac%100)+ac%10)==104)))
		{
			if((ac-(ac%100)+ac%10)==(pc[0]-(pc[0]%100)+pc[0]%10))
				return 1;
			else
				return 0;

		}
		else
		{
			if(((ac%100)-(ac%10))==((pc[0]%100)-(pc[0]%10)))
				return 1;
			else if((ac-((ac%100)-(ac%10)))==(pc[0]-((pc[0]%100)-(pc[0]%10))))
				return 1;
			else if(((pc[0]%100)-(pc[0]%10))==4)
				return 1;
			else
				return 0;
		}
	}
	else
		return false;
}
int Amount(int c[])
{
	int i;
	for(i = 0; c[i] != 444; i++);
	return i;
}

void Organize(int cartas[])
{
	bool v = 1;
	while(v)
	{
		v = 0;
		for(int i =0; i<191; i++)
		{
			if(cartas[i+1]<cartas[i])
			{
				cartas[i] += cartas[i+1];
				cartas[i+1] = cartas[i] - cartas[i+1];
				cartas[i] = cartas[i] - cartas[i+1];
				v = 1;
			}
		}
	}
}
int main()
{
	int cards[192];
	int qtt=0;
	srand(time(NULL));
	//numeri
	for(int i = 0; i<4; i++)
	{
		cards[qtt] = i*10;
		qtt++;
		for(int j = 1; j<10; j++)
		{
			for(int k = 0; k<4; k++)
			{
				cards[qtt] = i*10 + j;
				qtt++;
			}
		}
	}
	//special cards (coloured)
	for(int i = 0; i<4; i++)
	{
		for(int j = 0; j<3; j++)
		{
			for(int k = 0; k<2; k++)
			{
				cards[qtt] = 100 + i*10 + j;
				qtt++;
			}
		}
	}
	//wild cards
	for(int i = 0; i<2; i++)
	{
		for(int j = 0; j<4; j++)
		{
			cards[qtt] = 140 + i;
			qtt++;
		}
	}
	RandomCards(qtt,cards);
	int qbot;
	do {
		cout<<"Con quanti bot vuoi giocare? (1-3)";
		cin>>qbot;
	} while(qbot<1||qbot>3);
	int pcards[qbot+1][qtt];
	for(int i = 0; i<=qbot; i++)
	{
		for(int j = 0; j<qtt; j++)
		{
			pcards[i][j] = 444;
		}
	}
	int cont = 0;
	for(int j = 0; j<=qbot; j++)
	{
		for(int i = 0; i<7; i++)
		{
			pcards[j][i] = cards[cont];
			cont++;
		}
	}
	int turn, actcard = cards[cont],plus=0,block=0;
	cont++;
	bool repeat = 0;;
	turn = rand() % (qbot+1);
	int v = -1;
	while(v == -1)
	{

		//mostrar as cartas!!!!!!!!!!!!!
		for(int i = 0; i<=qbot; i++)
		{
			cout<<endl<<"player "<<i+1<<endl;
			for(int j = 0; j<7; j++)
			{
				cout<<"id carta "<<j+1<<" :"<<pcards[i][j]<<endl;
				cout<<"carta: ";
				CardName(pcards[i][j]);
				cout<<endl;
			}
		}
		if(plus>0)
		{
			bool pus=0;
			for(int i = 0; (i<Amount(pcards[turn])||pus); i++)
			{
				if((((pcards[turn][i] - (pcards[turn][i]%100) + (pcards[turn][i]%10))==101)&&((actcard - (actcard%100) + (actcard%10))==101))||(((pcards[turn][i] - (pcards[turn][i]%100) + (pcards[turn][i]%10))==104)&&((actcard - (actcard%100) + (actcard%10))==104)))
					pus = 1;
			}
			if(!pus)
			{
				for(int i = 0; i<plus; i++)
				{
					pcards[turn][Amount(pcards[turn])] = cards[cont];
					cont++;
				}
				plus = 0;
				turn = turn == qbot ? turn + 1 : 0;
			}
		}
		int choice[15], ncartas;
		//player's turn
		if(turn ==0)
		{
			int ncartas;
			bool b;
			do {
				cout<<endl<<"Quante carte vuoi giocare?"<<endl;
				cin>>ncartas;
				for(int i = 0; i<ncartas; i++)
				{
					cout<<"Carta no"<<i+1<<": ";
					cin>>choice[i];
					choice[i] = pcards[turn][choice[i]];
				}
				b = Verify(actcard, choice,ncartas,plus);
			} while(!b);
		}
		//bot's turn
		else
		{
			bool bol;
			do {
				int r = rand() % Amount(pcards[turn]);
				for(int i = 0; i<Amount(pcards[turn]); i++)
				{
					if((pcards[turn][i]-pcards[turn][i]%100)==(pcards[turn][r]-pcards[turn][r]%100))
					{
						choice[ncartas] = pcards[turn][i];
						ncartas++;
					}
				}
				bol = Verify(actcard, choice,ncartas,plus);
			} while(!bol);
		}




		turn = turn == qbot ? 0 : turn + 1;
		for(int i = 0; i<qbot; i++)
		{
			int j;
			for(j = 0; pcards[i][j]!=444; j++);
			v = j == 0 ? i : v;
		}
	}
	return 0;
}


/*devo cambiare la randomcards per far che tenha um numero inicial (ou seja randomiza as cartas a partir da 14)
p dps quando tiver q randomizar no meio da partida eu coloco as cartas dos players + actcard no inicio do baralho assim elas nn se repetem
*/
