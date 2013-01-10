/* ���㕐�� SE/�J�����J��12�� A �ۑ�5 */

#include <iostream>
#include <time.h>
#include <cstdio>
#include <stdlib.h>
#include <new>
#include "marubatsu.h"

using namespace std;

/*========================================*
 * CBoard �N���X(���ۃN���X)
 *========================================*/

CBoard::CBoard( uint w, uint h ) : m_nRow(w), m_nCol(h)
{
	try{ //TY@A-5refine
		m_pBoard = new MARUBATSU*[m_nRow];
		for( uint i = 0; i < m_nRow; ++i ){
			m_pBoard[i] = new MARUBATSU[m_nCol];
			for( uint j = 0; j < m_nCol; ++j ){
				m_pBoard[i][j] = EMPTY;
			}
		}
	}catch(...){
		throw (-1);
	}
}

CBoard::~CBoard()
{
	for( uint i = 0; i < m_nRow; ++i ){
		delete [] m_pBoard[i];
	}
	delete [] m_pBoard;
}

void CBoard::Print()
{
	uint i, j;
	for( i = 0; i < m_nRow; ++i ){
		for( j = 0; j < m_nCol; ++j ){
			switch( m_pBoard[i][j] ){
				case MARU:  cout << 'o'; break;
				case BATSU: cout << 'x'; break;
				case EMPTY: cout << ' '; break;
			}
			if( j != m_nCol-1 ) cout << '|';
		}
		cout << endl;
		for( j = 0; j < m_nCol-1; ++j ){
			cout << '-' << '+';
		}
		cout << '-' << endl;
	}
}

/*========================================*
 * CMaruBatsuBoard �N���X
 *========================================*/

CMaruBatsuBoard::CMaruBatsuBoard(uint w, uint h) : CBoard(w,h), nEmpty(w*h), m_eWinner(EMPTY)
{
}

CMaruBatsuBoard::~CMaruBatsuBoard()
{
}

BOOL CMaruBatsuBoard::InBoard(int w, int h)
{
	if( w < 0 || h < 0 ) return FALSE;
	return InBoard((uint)w,(uint)h);
}

BOOL CMaruBatsuBoard::InBoard(uint w, uint h)
{
	if( w >= m_nRow || h >= m_nCol ) return FALSE;
	return TRUE;
}

void CMaruBatsuBoard::CheckWinner(uint w, uint h)
{
	static const int dir[8][2] = {
		{-1,-1},{ 0,-1},{ 1,-1},
		{-1, 0},        { 1, 0},
		{-1, 1},{ 0, 1},{ 1, 1},
	};
	int count[8] = {0,0,0,0,0,0,0,0,};
	MARUBATSU yourhand = m_pBoard[w][h];
	int pos[2];

	for( int i = 0; i < 8; ++i ){
		// �e�����̘A�����𐔂���
		pos[X] = w + dir[i][X];
		pos[Y] = h + dir[i][Y];
		while( InBoard(pos[X],pos[Y]) &&
				m_pBoard[pos[X]][pos[Y]] == yourhand )
		{
			count[i]++;
			pos[X] += dir[i][X];
			pos[Y] += dir[i][Y];
			//cout << pos[X] << "," << pos[Y] << endl;
		}
	}
	for( int i = 0; i < 8/2; ++i ){
		count[i] += 1 + count[8-i-1];
		if( count[i] >= NUM_WIN ) m_eWinner = yourhand;
	}
}

BOOL CMaruBatsuBoard::Put(uint w, uint h, MARUBATSU koma)
{
	if( m_eWinner != EMPTY ) return FALSE;
	if( ! InBoard(w,h) ) return FALSE;
	if( m_pBoard[w][h] != EMPTY ) return FALSE;

	m_pBoard[w][h] = koma;
	nEmpty--;
	
	CheckWinner(w, h);

	return TRUE;
}

 //TY@A-5 ->
/*========================================*
 * CMaruBatsuPlayerHuman �N���X
 *========================================*/

void CMaruBatsuPlayerHuman::Put( CMaruBatsuBoard &board )
{
	uint x, y;
	const int size = 256;
	char buf[size];
	while(1){
		x = y = -1;
		cout << (m_hand==MARU ? "��" : "�~")
			<< "�̓��͏ꏊ���w�肵�Ă��������i�s-��j : ";
		cin  >> buf;
		sscanf( buf, "%d-%d", &x, &y );
		if( board.Put(x,y,m_hand) ){
			break;
		}else{
			cerr << "!!! ���̏ꏊ�ɂ͒u���܂��� !!!" << endl;
		}
	}
}

/*========================================*
 * CMaruBatsuPlayerCPU �N���X
 *========================================*/

void CMaruBatsuPlayerCPU::Put( CMaruBatsuBoard &board )
{
	uint x, y;
	srand(time(NULL));
	while(1){
		x = rand() % board.Row();
		y = rand() % board.Col();
		if( board.Put(x,y,m_hand) ){
			cout << (m_hand==MARU ? "��" : "�~" ) << "��"
				 << x << "," << y << "�ɒu���܂����B" << endl;
			break;
		}
	}
}

//TY@A-5 <-

/*========================================*
 * CMaruBatsuGame �N���X
 *========================================*/

CMaruBatsuGame::CMaruBatsuGame(uint w, uint h) : m_Board(w,h)
{
	int hand = -1;
	//TY@A-5 ->
	do{
		cout << "��U��U��I��ł��������i0�F��U�A1�F��U�j: ";
		cin >> hand;
	}while( hand != 0 && hand != 1 );
	try{ //TY@A-5refine
		if( hand == 0 ){
			m_pPlayer1 = new CMaruBatsuPlayerHuman(MARU);
			m_pPlayer2 = new CMaruBatsuPlayerCPU(BATSU);
		}else{
			m_pPlayer1 = new CMaruBatsuPlayerCPU(MARU);
			m_pPlayer2 = new CMaruBatsuPlayerHuman(BATSU);
		}
	}catch(...){
		throw;
	}
	//TY@A-5 <-
}

CMaruBatsuGame::~CMaruBatsuGame()
{
	//TY@refine
	delete m_pPlayer1;
	delete m_pPlayer2;
}

void CMaruBatsuGame::Exec()
{
	cout << "== �悤�����I ���~�Q�[���\�t�g�� ����" << endl;
	CMaruBatsuPlayer *player = m_pPlayer1;
	while( !m_Board.IsGameOver() ){
		player->Put(m_Board);
		m_Board.Print();
		player = OppositePlayer(player);
	}
	//TY@refine
	switch(m_Board.Winner()){
		case MARU:  
			cout << "== ���̏����́��̏����ł� ==" ;
			break;
		case BATSU:
			cout << "== ���̏����́~�̏����ł� ==" ;
			break;
		case EMPTY:
			cout << "== ���̏����͂Ђ��킯�ł� ==" ;
			break;
		default:
			break;
	}
}

//#define ___DEBUG_MAIN___

#ifdef ___DEBUG_MAIN___

int main()
{
	try{
		CMaruBatsuGame game(3,3);
		game.Exec();

	}catch(...){
		cerr << "��O���������܂���";
		return -1;
	}
	return 0;
}

#endif
