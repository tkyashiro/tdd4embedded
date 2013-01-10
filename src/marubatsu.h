/* 八代武大 SE/開発部開発12課 A 課題5 */
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
 * CBoard クラス(抽象クラス)
 *========================================*/
class CBoard {
protected:
		uint m_nRow, m_nCol;
		MARUBATSU **m_pBoard; //TY@refine
public:
		CBoard(uint w, uint h);
		virtual ~CBoard();
		virtual BOOL Put(uint w, uint h, MARUBATSU koma) = 0;
		// 勝者を返す / 勝敗がついていない時にはEMPTYを返す
		virtual MARUBATSU Winner() = 0;
		void Print();
		const uint Row(){ return m_nRow; } //TY@A-5
		const uint Col(){ return m_nCol; } //TY@A-5
};

/*========================================*
 * CMaruBatsuBoard クラス
 *========================================*/
class CMaruBatsuBoard : public CBoard {
	private:
		const static int NUM_WIN = 3;
		const static int DEFAULT_BOARD_SIZE = 3; //TY@refine

		int nEmpty;
		MARUBATSU m_eWinner;
		
		BOOL InBoard(uint w, uint h);
		BOOL InBoard( int w,  int h);
		// w,h にコマが置かれた時に、w,hが関連する勝ち負けをチェックする。
		void CheckWinner(uint w, uint h);
		BOOL IsPuttable(){ return nEmpty; }
	public:
		CMaruBatsuBoard( uint w = DEFAULT_BOARD_SIZE, uint h = DEFAULT_BOARD_SIZE );//TY@refine
		virtual ~CMaruBatsuBoard(); //TY@refine
		virtual BOOL Put(uint w, uint h, MARUBATSU koma);
		// 勝敗がついていない時にはEMPTYを返す
		virtual MARUBATSU Winner(){ return m_eWinner; }
		
		BOOL IsGameOver(){ return Winner() != EMPTY || !IsPuttable(); }

};

/*========================================*
 * CMaruBatsuPlayer クラス (抽象クラス)
 *========================================*/
class CMaruBatsuPlayer {
	protected: //TY@A-5
		const MARUBATSU m_hand;
	public:
		CMaruBatsuPlayer(MARUBATSU hand) : m_hand(hand){}
		virtual ~CMaruBatsuPlayer(){} //TY@refine
		virtual void Put( CMaruBatsuBoard &Board ) = 0; //TY@A-5 抽象クラスに変更
};

//TY@A-5 ->
/*========================================*
 * CMaruBatsuPlayerHuman クラス
 *========================================*/
class CMaruBatsuPlayerHuman : public CMaruBatsuPlayer {
	public:
		CMaruBatsuPlayerHuman(MARUBATSU hand) : CMaruBatsuPlayer(hand) {}
		void Put( CMaruBatsuBoard &Board ); //TY@A-5
};

/*========================================*
 * CMaruBatsuPlayerCPU クラス
 *========================================*/
class CMaruBatsuPlayerCPU : public CMaruBatsuPlayer {
	public:
		CMaruBatsuPlayerCPU(MARUBATSU hand) : CMaruBatsuPlayer(hand) {}
		void Put( CMaruBatsuBoard &Board ); //TY@A-5
};
//TY@A-5 <-

/*========================================*
 * CMaruBatsuGame クラス
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

