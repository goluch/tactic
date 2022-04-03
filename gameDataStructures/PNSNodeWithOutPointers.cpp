#pragma once
#include <windows.h>
#include "../gameEngines/CaptureGoEngine.h"
#include "PNSNodeWithoutPointers.h"

using namespace gameEngines;

// pozwala na alokacjê x razy mniej pamiêci ni¿ dostêpna w systemie
// w celu optymalnego wykorzystania pamiêci powinien byæ ustawiony na 1
#ifdef _DEBUG
#define MEMORY_USAGE_COEFFICIENT 10
#else
#define MEMORY_USAGE_COEFFICIENT 1
#endif

using namespace gameDataStructures;

template<typename E, typename T, typename I>
bool PNSNodeWithoutPointers<E, T, I>::currentNodeIsOfTypeOr;

template<typename E, typename T, typename I>
bool PNSNodeWithoutPointers<E, T, I>::currentIsFirstPlayer;

template<typename E, typename T, typename I>
bool PNSNodeWithoutPointers<E, T, I>::checkWinForFirstPlayer;

template<typename E, typename T, typename I>
T PNSNodeWithoutPointers<E, T, I>::oldProof;

template<typename E, typename T, typename I>
T PNSNodeWithoutPointers<E, T, I>::oldDisproof;

template<typename E, typename T, typename I>
T PNSNodeWithoutPointers<E, T, I>::min;

template<typename E, typename T, typename I>
T PNSNodeWithoutPointers<E, T, I>::sum;

template<typename E, typename T, typename I>
E* PNSNodeWithoutPointers<E, T, I>::possibleMoves;

template<typename E, typename T, typename I>
PNSNodeWithoutPointers<E, T, I>* PNSNodeWithoutPointers<E, T, I>::gameTree;

template<typename E, typename T, typename I>
I PNSNodeWithoutPointers<E, T, I>::gameTreeCount;

template<typename E, typename T, typename I>
I PNSNodeWithoutPointers<E, T, I>::gameTreeIndex;

template<typename E, typename T, typename I>
void PNSNodeWithoutPointers<E, T, I>::Initialize()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	PNSNodeWithoutPointers<E, T, I>::gameTreeIndex = 0;
	PNSNodeWithoutPointers<E, T, I>::possibleMoves = new E[E::maxPossibleMoves];
	PNSNodeWithoutPointers<E, T, I>::gameTreeCount = statex.ullAvailPhys / (sizeof(PNSNodeWithoutPointers) * MEMORY_USAGE_COEFFICIENT);
	PNSNodeWithoutPointers<E, T, I>::gameTree = new PNSNodeWithoutPointers<E, T, I>[PNSNodeWithoutPointers<E, T, I>::gameTreeCount];
	
}

template<typename E, typename T, typename I>
int PNSNodeWithoutPointers<E, T, I>::GenerateAllChildren(bool isFirstPlayerTurn, PNSNodeWithoutPointers<E, T, I> *parent)
{

	this->gameEngine.GeneratePossibleMoves(possibleMoves, isFirstPlayerTurn);
	childrenCount = this->gameEngine.numberOfPossibleMoves(isFirstPlayerTurn);
	this->children = new I[childrenCount];
	for (unsigned int i = 0; i < childrenCount; i++)
	{
		this->children[i] = PNSNodeWithoutPointers<E, T, I>::gameTreeIndex++;
		/*gameTree[this->children[i]].gameEngine = this->gameEngine;
		gameTree[this->children[i]].proof = 1;
		gameTree[this->children[i]].disproof = 1;
		gameTree[this->children[i]].parent = parent;
		gameTree[this->children[i]].children = nullptr;
		gameTree[this->children[i]].childrenCount = 0;*/
	}
	return 0;
};

template<typename E, typename T, typename I>
PNSNodeWithoutPointers<E, T, I>* PNSNodeWithoutPointers<E, T, I>::getChild(int i)
{
	return nullptr;
};

template<typename E, typename T, typename I>
PNSNodeWithoutPointers<E, T, I>* PNSNodeWithoutPointers<E, T, I>::getParent()
{
	return nullptr;
};
