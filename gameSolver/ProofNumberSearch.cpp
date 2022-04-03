#pragma once

#include <time.h>
#include "ProofNumberSearch.h"
#include "../gameEngines/CaptureGoEngine.h"
#include "../gameDataStructures/PNSNode.h"
#include "../gameDataStructures/PNSNode.cpp"
#include "../gameDataStructures/PNSNodeWithoutPointers.h"
//#include "../gameDataStructures/PNSNodeWithoutPointers.cpp"
#include "limits.h"



using namespace gameSolver;
using namespace gameDataStructures;
using namespace gameEngines;

// KONSTRUKTORU I DESTRUKTORY

template<typename N>
ProofNumberSearch<N>::ProofNumberSearch<N>()
{
	N::Initialize();
	isItAWinner = new bool(false);
};

template<typename N>
ProofNumberSearch<N>::~ProofNumberSearch<N>()
{

};

template<>
ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>>::ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>>()
{
	PNSNode<CaptureGoEngine, unsigned int>::Initialize();
	isItAWinner = new bool(false);
};

template<>
ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>>::~ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>>()
{

};

template<>
PNSNode<CaptureGoEngine, unsigned int>::PNSNode<CaptureGoEngine, unsigned int>()
{

};

template<>
PNSNode<CaptureGoEngine, unsigned int>::~PNSNode<CaptureGoEngine, unsigned int>()
{

};

template<>
PNSNode<CaptureGoEngine, unsigned int>::PNSNode<CaptureGoEngine, unsigned int>(CaptureGoEngine gE, PNSNode *parent)
{
	this->gameEngine = gE;
	this->proof = 1;
	this->disproof = 1;
	this->parent = parent;
	this->children = nullptr;
	this->childrenCount = 0;
};

template<>
PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>::PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>()
{

};

template<>
PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>::~PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>()
{

};

template<>
PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>::PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>(CaptureGoEngine gE, unsigned int parent)
{

	PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>::gameTree[gameTreeIndex].gameEngine = gE;
	PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>::gameTree[gameTreeIndex].proof = 1;
	PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>::gameTree[gameTreeIndex].disproof = 1;
	PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>::gameTree[gameTreeIndex].parent = parent;
	PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>::gameTree[gameTreeIndex].children = nullptr;
	PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>::gameTree[gameTreeIndex].childrenCount = 0;
	gameTreeIndex++;
};

// DEKLARACJE PÓL STATYCZNYCH

template<typename N>
bool* ProofNumberSearch<N>::isItAWinner;

// DEKLARACJE PÓL DYNAMICZNYCH

clock_t start, end;



template<typename N>
void ProofNumberSearch<N>::Evaluate(N* node)
{
	if (node->gameEngine.isGameOver())
	{
		node->gameEngine.checkIsItAWinner(N::checkWinForFirstPlayer, isItAWinner);
		if (*isItAWinner)
		{
			node->proof = 0;
			node->disproof = UINT_MAX;
		}
		else
		{
			node->proof = UINT_MAX;
			node->disproof = 0;
		}
		// stara wersja dla metody checkIsFirstPlayerWinner()
		/*if (checkIsFirstPlayerWinner)
		{
			if (*checkIsFirstPlayerWinner)
			{
				node->proof = 0;
				node->disproof = UINT_MAX;
			}
			else
			{
				node->proof = UINT_MAX;
				node->disproof = 0;
			}
		}*/
	}
	else
	{
		// parametr = 0 poniewa¿ obydwaj w tej grze gracze mog¹ wykonaæ dentyczn¹ liczbê posuniêæ
		short childrenNumber = node->gameEngine.numberOfPossibleMoves(0);
		if (!N::currentNodeIsOfTypeOr)
		{
			node->proof = 1;
			node->disproof = childrenNumber;
		}
		else
		{
			node->proof = childrenNumber;
			node->disproof = 1;
		}
	}
};

template<typename N>
void ProofNumberSearch<N>::SetProofAndDisproofNumbers(N* node)
{
	node->min = UINT_MAX;
	node->sum = 0;
	if (N::currentNodeIsOfTypeOr)
	{
		for (unsigned int i = 0; i < node->childrenCount; i++)
		{
			if (node->children[i]->disproof == UINT_MAX || node->sum == UINT_MAX)
			{
				node->sum = UINT_MAX;
			}
			else
			{
				node->sum += node->children[i]->disproof;
			}
			if (node->min > node->children[i]->proof)
			{
				node->min = node->children[i]->proof;
			}			
		}
		node->proof = node->min;
		node->disproof = node->sum;
	}
	else
	{
		for (unsigned int i = 0; i < node->childrenCount; i++)
		{
			if (node->children[i]->proof == UINT_MAX || node->sum == UINT_MAX)
			{
				node->sum = UINT_MAX;
			}
			else
			{
				node->sum += node->children[i]->proof;
			}
			if (node->min > node->children[i]->disproof)
			{
				node->min = node->children[i]->disproof;
			}
		}
		node->proof = node->sum;
		node->disproof = node->min;
	}
};

template<typename N>
typename N* ProofNumberSearch<N>::SelectMostProving(N* node)
{
	while (node->children)
	{
		int i = 0;
		if (N::currentNodeIsOfTypeOr)
		{
			while (node->children[i]->proof != node->proof)
			{
				i++;
			}
		}
		else
		{
			while (node->children[i]->disproof != node->disproof)
			{
				i++;
			}
		}
		node = node->children[i];		
		N::currentIsFirstPlayer = !N::currentIsFirstPlayer;
		N::currentNodeIsOfTypeOr = !N::currentNodeIsOfTypeOr;
	}
	return node;
};

template<typename N>
void ProofNumberSearch<N>::ExpandNode(N* node, PerformanceCounter* pc)
{
#ifdef _DEBUG
	if (pc)
	{		
		pc->increaseAllUsedMemory(node->GenerateAllChildren(N::currentIsFirstPlayer, node));
		pc->increaseAllExpandedNodes(node->childrenCount);
	}
#else
	node->GenerateAllChildren(N::currentIsFirstPlayer, node);
#endif
	for (unsigned int i = 0; i < node->childrenCount; i++)
	{
		// na potrzeby DEBUGOWANIA
		//unsigned long long bp = ((CaptureGoEngine*)(node->children[i]->gameEngine))->blackPawns;
		//unsigned long long wp = ((CaptureGoEngine*)(node->children[i]->gameEngine))->whitePawns;
		// todo: poprawiæ Evaluate aby nie potrzebowa³a podwójnej zmiany wartoœci Node::currentNodeIsOfTypeOr
		Evaluate(node->children[i]);		
	}
};

template<typename N>
typename N* ProofNumberSearch<N>::UpdateAncestors(N* node)
{
	bool changed = true;
	N *previousNode;
	while (node && changed)
	{
		node->oldProof = node->proof;
		node->oldDisproof = node->disproof;
		SetProofAndDisproofNumbers(node);
		changed = (node->oldProof != node->proof || node->oldDisproof != node->disproof);
		previousNode = node;
		node = node->parent;
		N::currentIsFirstPlayer = !N::currentIsFirstPlayer;
		N::currentNodeIsOfTypeOr = !N::currentNodeIsOfTypeOr;
	}
	N::currentIsFirstPlayer = !N::currentIsFirstPlayer;
	N::currentNodeIsOfTypeOr = !N::currentNodeIsOfTypeOr;
	return previousNode;
};


template<typename N>
void ProofNumberSearch<N>::startExecutionTimeMeasurement()
{
	start = clock();
}

template<typename N>
void ProofNumberSearch<N>::stopExecutionTimeMeasurement()
{
	end = clock();
}

template<typename N>
bool ProofNumberSearch<N>::Solve(N solvingNode, bool currentPlayerIsFirst, bool winForFirstPlayer, PerformanceCounter* pc)
{
	N root = solvingNode;
	N::currentNodeIsOfTypeOr = winForFirstPlayer;
	N::currentPlayerIsFirst = checkWinForFirstPlayer;
	N::checkWinForFirstPlayer = currentPlayerIsFirst;
	N::Node *currentNode = &root;
	N::Node *mostProvingNode = nullptr;

	startExecutionTimeMeasurement();
  	while (root.proof != 0 && root.disproof != 0)
	{
#ifdef DEBUG
		if (pc)
		{
			pc->setMaxProofAndDisproof(root.proof, root.disproof);
		}
#endif
		mostProvingNode = SelectMostProving(currentNode);
		ExpandNode(mostProvingNode, pc);
		currentNode = UpdateAncestors(mostProvingNode);
	}
	stopExecutionTimeMeasurement();
	if (root.proof == 0) return true;
	else if (root.disproof == 0) return false;
	else throw "unknown value";
};	

template<>
bool ProofNumberSearch<PNSNode<CaptureGoEngine, unsigned int>>::Solve(PNSNode<CaptureGoEngine, unsigned int> solvingNode, bool currentPlayerIsFirst, bool winForFirstPlayer, PerformanceCounter* pc)
{
	PNSNode<CaptureGoEngine, unsigned int> root = solvingNode;
	PNSNode<CaptureGoEngine, unsigned int>::currentNodeIsOfTypeOr = winForFirstPlayer;
	PNSNode<CaptureGoEngine, unsigned int>::currentIsFirstPlayer = currentPlayerIsFirst;
	PNSNode<CaptureGoEngine, unsigned int>::checkWinForFirstPlayer = winForFirstPlayer;
	PNSNode<CaptureGoEngine, unsigned int> *currentNode = &root;
	PNSNode<CaptureGoEngine, unsigned int> *mostProvingNode = nullptr;

	startExecutionTimeMeasurement();
	while (root.proof != 0 && root.disproof != 0)
	{
#ifdef _DEBUG
		if (pc)
		{
			pc->setMaxProofAndDisproof(root.proof, root.disproof);
		}
#endif
		mostProvingNode = SelectMostProving(currentNode);
		ExpandNode(mostProvingNode, pc);
		currentNode = UpdateAncestors(mostProvingNode);
	}
	stopExecutionTimeMeasurement();
	if (root.proof == 0) return true;
	else if (root.disproof == 0) return false;
	else throw "unknown value";
};


