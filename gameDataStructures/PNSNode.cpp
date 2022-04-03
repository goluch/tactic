#pragma once
#include "PNSNode.h"

using namespace gameDataStructures;

template<typename E, typename T>
bool PNSNode<E, T>::currentNodeIsOfTypeOr;

template<typename E, typename T>
bool PNSNode<E, T>::currentIsFirstPlayer;

template<typename E, typename T>
bool PNSNode<E, T>::checkWinForFirstPlayer;

template<typename E, typename T>
T PNSNode<E, T>::oldProof;

template<typename E, typename T>
T PNSNode<E, T>::oldDisproof;

template<typename E, typename T>
T PNSNode<E, T>::min;

template<typename E, typename T>
T PNSNode<E, T>::sum;

template<typename E, typename T>
E* PNSNode<E, T>::possibleMoves;

template<typename E, typename T>
void PNSNode<E, T>::Initialize()
{
	PNSNode<E, T>::possibleMoves = new CaptureGoEngine[GameEngine::maxPossibleMoves];
}

template<typename E, typename T>
int PNSNode<E, T>::GenerateAllChildren(bool isFirstPlayerTurn, PNSNode<E, T> *parent)
{

	this->gameEngine.GeneratePossibleMoves(possibleMoves, isFirstPlayerTurn);
	childrenCount = this->gameEngine.numberOfPossibleMoves(isFirstPlayerTurn);
	this->children = new PNSNode*[childrenCount];
	for (unsigned int i = 0; i < childrenCount; i++)
	{
		this->children[i] = new PNSNode<E, T>(possibleMoves[i], parent);
	}
#ifdef _DEBUG
	int childrenTablesize = sizeof(children);
	int pnsnodeSize = sizeof(PNSNode);
	return childrenCount * (sizeof(children) + sizeof(PNSNode));
#else
	return 0;
#endif
};

template<typename E, typename T>
PNSNode<E, T>* PNSNode<E, T>::getChild(int i)
{
	return nullptr;
};

template<typename E, typename T>
PNSNode<E, T>* PNSNode<E, T>::getParent()
{
	return nullptr;
};

