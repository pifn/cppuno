#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
#Define Mx 2 //tamanho do mapa na horizontal
#Define My 2 //tamanho do mapa na vertical
const QCx = (Mx-Mx%5)/5;
const QCy = (My-My%5)/5;
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
//pc = card being played
//dice sempre si per i numeri e no per i +4
bool Verify(int ac, int pc)
{
	if((ac-(ac%100-ac%10))==pc-(pc%100-pc%10)) //se 'e la stessa carta ma di colore diverso
		return 1;
	else if(ac%100-ac%10==pc%100-pc%10&&ac-(ac%100-ac%10)!=101&&ac-(ac%100-ac%10)!=104) //se 'e della stessa colore e la carta non 'e un +2 o +4
		return 1;
	else if(pc-(pc%100-pc%10)==104) //se ha giocato un +4
		return 1;
	else
		return 0;
}
void Repeat(char txt[], int D, int A)
{
	for(int i = 0;i<A;i++)
		{
			for(int j = 0;j<D;j++)
					cout<<txt[j];
		}
}
//pcd = pcards
//qb = quantità di bot da 1 a 3
void ShowCards(int pcd[4], int qb)
{
	int MD[qb], SV[qb];
	switch(qb)
		{
			case 1:
				//trova la carta con il bot 1 
				break;
			case 2:
				
				break;
			case 3:
				//trova la carta con il bot 1 
				break;
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
	/*cout<<qtt<<endl;
	for(int i = 0;i<qtt;i++)
	{
	    cout<<cards[i]<<endl;
	}
	cout<<"random:"<<endl;*/

	//randomizare le carte
	RandomCards(qtt,cards);
	/*for(int i = 0;i<qtt;i++)
	{
	    cout<<cards[i]<<endl;
	}*/
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
	for(int i = 0; i<=qbot; i++)
	{
		cout<<"player "<<i+1<<endl;
		for(int j = 0; j<7; j++)
		{
			cout<<"id carta "<<j+1<<" :"<<pcards[i][j]<<endl;
			cout<<"carta: ";
			CardName(pcards[i][j]);
			cout<<endl;
		}
	}
	int v = 0, carta, c,actcard;
	bool reverse = 0;
	while(v == 0)
	{
		int i;
		for((!reverse) ? (i = 0) : (i = qbot); (i<=qbot&&!reverse)||(i>=0&&reverse); reverse ? (i--) : (i++))
		{
			if(/*pode jogar a carta*/)
			{
				//cout<<endl<<"reverse"<<reverse<<endl<<i;
				if(i==0)
				{
					for(c = 0; pcards[0][c]!=444; c++);
					do {
						cout<<"Sceglie una carta da 1 a "<<c;
						cin>>carta;
						carta--;
					} while(!Verify(actcard,pcards[0][carta]))
						//joga a carta
					}
				else
				{
					for(c = 0; pcards[i][c]!=444; c++);
					do {
						carta = rand() % c;
					} while(!Verify(actcard,pcards[i][carta]))
						//joga a carta
					}
				actcard = pcards[i][carta];
			}
			else
			{
			    //pescar uma carta
			}
		}
	}
	return 0;
}


