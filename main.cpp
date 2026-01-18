#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define qtt 170
void Scambio(int *a, int *b)
{
	*a += *b;
	*b = *a - *b;
	*a -= *b;
}
void CardName(int card)
{
	cout<<"\033[1;"<<31+((card % 100 - card % 10)/10)<<"m ";
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
			cout<<endl<<"\033[1;31m errore nel 2 switch della funzione CardName \033[0m ";
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
		cout<<" verde";
		break;
	case 2:
		cout<<" giallo";
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
		cout<<endl<<"\033[1;31m errore nel 1 switch in function CardName";
		break;
	}
	cout<<"\033[0m";
}
//ac = active card
//pc = card(s) being played
//cu = amount of cards
//ps= plus
bool SubVerify(int ac, int pc, int ps)
{
	//se tem cartas de + na mesa
	if((ps>0)/*&&(((ac-(ac%100)+ac%10)==101)||((ac-(ac%100)+ac%10)==104))*/)
	{
		//se a carta for do mesmo tipo q a active card
		if((ac-(ac%100)+ac%10)==(pc-(pc%100)+pc%10))
			return 1;
		else
			return 0;

	}
	else
	{
		//se for a mesma cor
		if(((ac%100)-(ac%10))==((pc%100)-(pc%10)))
			return 1;
		//se for a mesma carta
		else if((ac-((ac%100)-(ac%10)))==(pc-((pc%100)-(pc%10))))
			return 1;
		//se a carta q a pessoa ta jogando C) preta
		else if(((pc%100)-(pc%10))==4)
			return 1;
		else
			return 0;
	}
}
bool Verify(int ac, int pc[],int cu, int ps)
{
	int i;
	//ve se todas as cartas na lista sao a mesma
	for(i = 0; (i<cu-1)&&((pc[i]-pc[i]%100+pc[i]%10)==(pc[i+1]-pc[i+1]%100+pc[i+1]%10)); i++);
	//se sao a mesma carta(chega no fim da array)
	if(i==cu-1||cu==1)
	{
		return SubVerify(ac,pc[0],ps);
	}
	else
	{
		if(ps==0&&cu==0)
			return 1;
		else
			return false;
	}
}
int Amount(int c[])
{
	int i;
	for(i = 0; (i<qtt&&(c[i] != 444)); i++);
	return i;
}
//bubble sort
void Organize(int cartas[])
{
	bool v = 1;
	while(v)
	{
		v = 0;
		for(int i =0; i<Amount(cartas); i++)
		{
			if(cartas[i+1]<cartas[i])
			{
				Scambio(&cartas[i],&cartas[i+1]);
				v = 1;
			}
		}
	}
}
void Randomize(int cartas[qtt], int qb, int pcartas[][qtt], int ac, int *cont)
{
	*cont = 0;
	int k;
	for(int i = 0; i<qb; i++)
	{
		for(int j=0; j<Amount(pcartas[i]); j++)
		{
			for(k=0; cartas[k]!=pcartas[i][j]; k++);
			Scambio(&cartas[k],&cartas[*cont]);
			cont++;
		}
	}
	if(ac!=444)
	{
		for(k = 0; cartas[k]!=ac; k++);
		Scambio(&cartas[k],&cartas[*cont]);
		cont++;
	}
	for(int i = *cont; i<qtt; i++)
	{
		int r = (rand() % (qtt-*cont))+*cont;
		Scambio(&cartas[i],&cartas[r]);
	}
}
void Cont(int *cont, int cards[],int qb,int pc[][qtt], int ac)
{
    *cont++;
	if(*cont == qtt)
	{
		Randomize(cards,qb,pc,ac,cont);
	}
}
int ChoseColor(int cartas[qtt])
{
	int r[] = {0,0,0,0};
	for(int i = 0; i<Amount(cartas); i++)
		r[(cartas[i]%100-cartas[i]%10)/10]++;
	int s = 0;
	for(int i = 0; i<4; i++)
		s+=r[i];
	int random = (rand() % s )+ 1;
	for(int i = 0; i<4; i++)
	{
		if(random<=r[i])
			return i;
		else
			random -= r[i];
	}
	return 444;
}
void Turn(int *trn, int qb, int v)
{
	*trn = (*trn == qb||*trn == 0) ? qb-*trn : *trn + v;
}
int main()
{
	int cards[qtt];
	srand(time(NULL));
	int cont = 0;
	//numeri
	for(int i = 0; i<4; i++)
	{
		cards[cont] = i*10;
		for(int j = 1; j<10; j++)
		{
			for(int k = 0; k<4; k++)
			{
				cards[cont] = i*10 + j;
				cont++;
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
				cards[cont] = 100 + i*10 + j;
				cont++;
			}
		}
	}
	//wild cards
	for(int i = 0; i<2; i++)
	{
		cards[cont] = 143 + i;
		cont++;
	}
	cont=0;
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
	int actcard = 444;
	Randomize(cards, qbot, pcards, actcard, &cont);
	do {
		actcard = cards[cont];
		Cont(&cont, cards, qbot, pcards, actcard);
	} while(actcard-actcard%100>0);
	for(int i = 0; i<=qbot; i++)
	{
		for(int j = 0; j<7; j++)
		{
			pcards[i][j] = cards[cont];
			Cont(&cont, cards, qbot, pcards, actcard);
		}
		Organize(pcards[i]);
	}
	int turn,plus=0, verso=1, block=0;
	turn = rand() % (qbot+1);
	//v quando qualcuno ha vinto
	int v = -1;
	cout<<endl<<"Inizia il player "<<turn+1;
	while(v == -1)
	{
		//mostrar as cartas!!!!!!!!!!!!!
		//tutto questo pezzo vai embora dps e troca p um melhor
		for(int i = qbot; i>=0; i--)
		{
			cout<<endl<<"player "<<i+1;
			for(int j = 0; j<Amount(pcards[i]); j++)
			{
				cout<<endl<<"id carta: "<<pcards[i][j];
				cout<<endl<<"carta "<<j+1<<": ";
				CardName(pcards[i][j]);
			}
			cout<<endl;
		}
		cout<<endl<<"active card: ";
		CardName(actcard);
		//ate aqui
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
					cout<<endl<<"player "<<turn+1<<" ha dovuto pescare "<<plus<<" carte";
					pcards[turn][Amount(pcards[turn])] = cards[cont];
					Cont(&cont, cards, qbot, pcards, actcard);
				}
				plus = 0;
				Turn(&turn,qbot,verso);
			}
		}
		bool w=0;
		do {
			for(int i = 0; i<Amount(pcards[turn]); i++)
			{
				w = SubVerify(actcard, pcards[turn][i],plus) ? 1 : w;
				cout<<endl<<"w"<<w;
			}
			if(!w)
			{
				cout<<endl<<"player "<<turn+1<<" ha dovuto pescare 1 carta";
				pcards[turn][Amount(pcards[turn])] = cards[cont];
				Turn(&turn,qbot,verso);
			}
			cout<<endl<<"w"<<w<<" turn"<<turn;
		} while(!w);
		int choice[9], ncartas=0;
		bool bol;
		for(int i = 0; i<9; i++)
			choice[i] = 444;
		do {
			//player's turn
			if(turn == 0)
			{
				cout<<endl<<"Quante carte vuoi giocare?(0 se vuoi saltare il turno)"<<endl;
				cin>>ncartas;
				for(int i = 0; i<ncartas; i++)
				{
					cout<<endl<<"Digita il numero della carta"<<endl;
					cin>>choice[i];
					choice[i] = pcards[0][choice[i]-1];
				}
			}
			//bot's turn
			else
			{
				cout<<endl<<"gioca il bot"<<turn;
				for(choice[0] = 0; !SubVerify(actcard, pcards[turn][choice[0]],plus); choice[0]++);
				cout<<endl<<"Ha trovato la carta numero "<<choice[0]<<" ossia "<<pcards[turn][choice[0]];
				choice[0] = pcards[turn][choice[0]];
				cout<<endl;
				CardName(choice[0]);
				for(int i = 0; i<Amount(pcards[turn]); i++)
				{
					cout<<endl<<(choice[0]-choice[0]%100+choice[0]%10)<<"=="<<(pcards[turn][i]-pcards[turn][i]%100+pcards[turn][i]%10);
					if((choice[0]-choice[0]%100+choice[0]%10)==(pcards[turn][i]-pcards[turn][i]%100+pcards[turn][i]%10))
					{
						cout<<endl<<"siiim";
						choice[ncartas] = pcards[turn][i];
						cout<<endl<<"choice["<<ncartas<<"]="<<pcards[turn][i];
						ncartas++;
					}
				}
			}
			bol = Verify(actcard, choice,ncartas,plus);
		} while(!bol);
		actcard = choice[ncartas-1];
//se cambia colore
		if(actcard-actcard%10==140)
		{
			if(turn==0)
			{
				cout<<endl<<"Quale colore vuoi?";
				cout<<endl<<"\033[1;31m 1-rosso"<<endl<<"\033[1;32m 2-verde"<<endl<<"\033[1;33m 3-giallo"<<endl<<"\033[1;34m 4-blu \033[0m"<<endl;
				int colour;
				cin>>colour;
				actcard-=40;
				actcard+=(colour-1)*10;
			}
			else
			{
				actcard-=40;
				actcard+=(ChoseColor(pcards[turn]))*10;
			}
		}
		Cont(&cont, cards,qbot, pcards, actcard);
		//+2
		if(actcard-actcard%100+actcard%10==101)
			plus+=ncartas*2;
		//+4
		else if(actcard-actcard%100+actcard%10==104)
			plus+=ncartas*4;
		//reverso
		if(actcard-actcard%100+actcard%10==102)
		{
			verso *= (ncartas%2)?-1 : 1;
			if(qbot==1)
				Turn(&turn, qbot, verso);
		}
		//blocco
		for(int i = 0; i<block; i++)
		{
			Turn(&turn,qbot,verso);
			cout<<"player "<<turn+1<<" bloccato"<<endl;
		}
		Turn(&turn, qbot, verso);
		//checa se alguem ta sem cartas e ganhou
		for(int i = 0; i<=qbot; i++)
		{
			int j;
			for(j = 0; pcards[i][j]!=444; j++);
			v = j == 0 ? i : v;
		}
	}
	return 0;
}
