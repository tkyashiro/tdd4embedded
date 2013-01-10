/* ���㕐�� SE/�J�����J��12�� A �ۑ�5 */
#ifndef ___TAKEHIROYASHIRO_A_5_H___
#define ___TAKEHIROYASHIRO_A_5_H___

typedef unsigned int uint;
typedef int BOOL;

//TY@refine
const static int TRUE  = 1;
const static int FALSE = 0;

const static int X = 0;
const static int Y = 1;

//TY@refine
typedef enum {MARU=0, BATSU, EMPTY} MARUBATSU;

/*========================================*
 * CBoard �N���X(���ۃN���X)
 *========================================*/
class CBoard {
protected:
		uint m_nRow, m_nCol;
		MARUBATSU **m_pBoard; //TY@refine
public:
		CBoard(uint w, uint h);
		virtual ~CBoard();
		virtual BOOL Put(uint w, uint h, MARUBATSU koma) = 0;
		// ���҂�Ԃ� / ���s�����Ă��Ȃ����ɂ�EMPTY��Ԃ�
		virtual MARUBATSU Winner() = 0;
		void Print();
		const uint Row(){ return m_nRow; } //TY@A-5
		const uint Col(){ return m_nCol; } //TY@A-5
};

/*========================================*
 * CMaruBatsuBoard �N���X
 *========================================*/
class CMaruBatsuBoard : public CBoard {
	private:
		const static int NUM_WIN = 3;
		const static int DEFAULT_BOARD_SIZE = 3; //TY@refine

		int nEmpty;
		MARUBATSU m_eWinner;
		
		BOOL InBoard(uint w, uint h);
		BOOL InBoard( int w,  int h);
		// w,h �ɃR�}���u���ꂽ���ɁAw,h���֘A���鏟���������`�F�b�N����B
		void CheckWinner(uint w, uint h);
		BOOL IsPuttable(){ return nEmpty; }
	public:
		CMaruBatsuBoard( uint w = DEFAULT_BOARD_SIZE, uint h = DEFAULT_BOARD_SIZE );//TY@refine
		virtual ~CMaruBatsuBoard(); //TY@refine
		virtual BOOL Put(uint w, uint h, MARUBATSU koma);
		// ���s�����Ă��Ȃ����ɂ�EMPTY��Ԃ�
		virtual MARUBATSU Winner(){ return m_eWinner; }
		
		BOOL IsGameOver(){ return Winner() != EMPTY || !IsPuttable(); }

};

/*========================================*
 * CMaruBatsuPlayer �N���X (���ۃN���X)
 *========================================*/
class CMaruBatsuPlayer {
	protected: //TY@A-5
		const MARUBATSU m_hand;
	public:
		CMaruBatsuPlayer(MARUBATSU hand) : m_hand(hand){}
		virtual ~CMaruBatsuPlayer(){} //TY@refine
		virtual void Put( CMaruBatsuBoard &Board ) = 0; //TY@A-5 ���ۃN���X�ɕύX
};

//TY@A-5 ->
/*========================================*
 * CMaruBatsuPlayerHuman �N���X
 *========================================*/
class CMaruBatsuPlayerHuman : public CMaruBatsuPlayer {
	public:
		CMaruBatsuPlayerHuman(MARUBATSU hand) : CMaruBatsuPlayer(hand) {}
		void Put( CMaruBatsuBoard &Board ); //TY@A-5
};

/*========================================*
 * CMaruBatsuPlayerCPU �N���X
 *========================================*/
class CMaruBatsuPlayerCPU : public CMaruBatsuPlayer {
	public:
		CMaruBatsuPlayerCPU(MARUBATSU hand) : CMaruBatsuPlayer(hand) {}
		void Put( CMaruBatsuBoard &Board ); //TY@A-5
};
//TY@A-5 <-

/*========================================*
 * CMaruBatsuGame �N���X
 *========================================*/
class CMaruBatsuGame
{
	private:
		CMaruBatsuBoard m_Board;
		CMaruBatsuPlayer *m_pPlayer1;
		CMaruBatsuPlayer *m_pPlayer2;

		CMaruBatsuPlayer *OppositePlayer(CMaruBatsuPlayer *player){
			if(player == m_pPlayer1) return m_pPlayer2;
			else return m_pPlayer1;
		}
	public:
		CMaruBatsuGame(uint w = 3, uint h = 3);
		~CMaruBatsuGame();
		void Exec();
};

#endif

