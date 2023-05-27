#pragma once
#include <vector>
#include "Player.h"
#include "GameEngine.h"
#include "GameEngineExceptions.h"

using namespace std;

namespace gameEngines
{
	typedef pair<int, int> Coord;

	enum Direction
	{
		Unknown, E, S, SE, W, N, NW
	};

	class KInRow
	{
	public:
		Direction dir;
		vector<Coord> row;

		KInRow() { }
		KInRow(Direction d) : dir(d) { }
		KInRow(const KInRow& k) : dir(k.dir)
		{
			this->row = k.row;
		}
		~KInRow() { }
	};

    class GIPFEngine
        : public GameEngine
    {
    public:

		GIPFEngine();
		~GIPFEngine();

		virtual int Evaluate(Player);
		virtual GameEngine* GeneratePossibleMoves(int& count, Player activePlayer);
		virtual string SetGameState(istream& newGameState);
		virtual string GetGameState();
		string CheckPawnsNumber();
		string DoMove(string move);
		int CheckKInRow();
		int RemoveKInRows(string& errorInfo);

    private:

		//border is the outer fields of the board intended for pieces added at the beginning of the move
		int s;
		int k;
		int gw;
		int gb;
		int gw_res;
		int gb_res;
		int diag;
		char value;
		Player activePlayer;
		int collisionInKInRowsNumber;
		vector<KInRow> kInRowsIndexes;
		KInRow* kInRowsconflictingRows[3];
		vector<vector<char>> board;
		Coord collisionIndex;
		string info;
		const int border = 1;;
		//always starts white
		static const char firstPlayerField;
		static const char secondPlayerField;
		static const char startField;
		static const char emptyField;
		static const char forbiddenField;

		Direction SpecifyDirection(Coord sour, Coord dest);
		Direction GetOppositeDirection(Direction moveDir);
		Coord SpecifyNextFieldCoord(Coord sour, Direction moveDir);
		Coord ConvertCoordinates(string Coordinates);
		bool MoveWholeRow(Coord sour, Coord dest, Direction moveDir);
		//int CheckKInRow(Coord checkedField);
		bool GetPawnColor(Coord fieldCoord, char& actualColor);
		int CheckHorizontallyOrVertically(Direction iDir, Direction jDir);
		int CheckDiagonally(Direction iDir1, Direction iDir2, Direction jDir);
		int AddToKInRowsAndFindCollision(KInRow possiblekInRowsIndexes);
		bool UpdatePlayersReserves(Coord tmpCoord, char kInRowColor);
		bool RemoveKinRow(KInRow* kInRow);
		void ClearGameState();
    };

}