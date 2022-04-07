//#include <time.h>
//#include "ProofNumberSearch.h"
//#include "ProofNumberSearch.cpp"
//#include "ProofNumberSearchWrapped.h"
//#include "../gameEngines/CaptureGoEngine.h"
//#include "../gameDataStructures/PNSNode.h"
//#include "../gameDataStructures/PNSNode.cpp"
//#include "../gameDataStructures/PNSNodeWithoutPointers.h"
//#include "../gameDataStructures/PNSNodeWithoutPointers.cpp"
//#include "limits.h"
//
//
//
//using namespace gameSolver;
//using namespace gameDataStructures;
//using namespace gameEngines;
//
//// KONSTRUKTORU I DESTRUKTORY
//
//template<typename N>
//ProofNumberSearchWrapped<N>::ProofNumberSearchWrapped<N>()
//{
//	N::Initialize();
//	isItAWinner = new bool(false);
//};
//
//template<typename N>
//ProofNumberSearchWrapped<N>::~ProofNumberSearchWrapped<N>()
//{
//
//};
//
//template<>
//ProofNumberSearchWrapped<PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>>::ProofNumberSearchWrapped<PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>>()
//{
//	PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>::Initialize();
//	isItAWinner = new bool(false);
//};
//
//template<>
//ProofNumberSearchWrapped<PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>>::~ProofNumberSearchWrapped<PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>>()
//{
//
//};
//
//// DEKLARACJE PÓL STATYCZNYCH
//
//template<typename N>
//bool* ProofNumberSearchWrapped<N>::isItAWinner;
//
//// DEFINICJE METOD
//
//template<typename N>
//typename N* ProofNumberSearchWrapped<N>::UpdateAncestors(N* node)
//{
//	bool changed = true;
//	N *previousNode;
//	while (node && changed)
//	{
//		node->oldProof = node->proof;
//		node->oldDisproof = node->disproof;
//		SetProofAndDisproofNumbers(node);
//		changed = (node->oldProof != node->proof || node->oldDisproof != node->disproof);
//		previousNode = node;
//		node = node->getParent();
//		N::currentIsFirstPlayer = !N::currentIsFirstPlayer;
//		N::currentNodeIsOfTypeOr = !N::currentNodeIsOfTypeOr;
//	}
//	N::currentIsFirstPlayer = !N::currentIsFirstPlayer;
//	N::currentNodeIsOfTypeOr = !N::currentNodeIsOfTypeOr;
//	return previousNode;
//};
//
//template<typename N>
//void ProofNumberSearchWrapped<N>::SetProofAndDisproofNumbers(N* node)
//{
//	node->min = UINT_MAX;
//	node->sum = 0;
//	if (N::currentNodeIsOfTypeOr)
//	{
//		for (unsigned int i = 0; i < node->childrenCount; i++)
//		{
//			if (node->getChild(i)->disproof == UINT_MAX || node->sum == UINT_MAX)
//			{
//				node->sum = UINT_MAX;
//			}
//			else
//			{
//				node->sum += node->getChild(i)->disproof;
//			}
//			if (node->min > node->getChild(i)->proof)
//			{
//				node->min = node->getChild(i)->proof;
//			}
//		}
//		node->proof = node->min;
//		node->disproof = node->sum;
//	}
//	else
//	{
//		for (unsigned int i = 0; i < node->childrenCount; i++)
//		{
//			if (node->getChild(i)->proof == UINT_MAX || node->sum == UINT_MAX)
//			{
//				node->sum = UINT_MAX;
//			}
//			else
//			{
//				node->sum += node->getChild(i)->proof;
//			}
//			if (node->min > node->getChild(i)->disproof)
//			{
//				node->min = node->getChild(i)->disproof;
//			}
//		}
//		node->proof = node->sum;
//		node->disproof = node->min;
//	}
//};
//
//template<typename N>
//typename N* ProofNumberSearchWrapped<N>::SelectMostProving(N* node)
//{
//	while (node->children)
//	{
//		int i = 0;
//		if (N::currentNodeIsOfTypeOr)
//		{
//			while (node->getChild(i)->proof != node->proof)
//			{
//				i++;
//			}
//		}
//		else
//		{
//			while (node->getChild(i)->disproof != node->disproof)
//			{
//				i++;
//			}
//		}
//		node = node->getChild(i);	
//		N::currentIsFirstPlayer = !N::currentIsFirstPlayer;
//		N::currentNodeIsOfTypeOr = !N::currentNodeIsOfTypeOr;
//	}
//	return node;
//};
//
//template<typename N>
//void ProofNumberSearchWrapped<N>::ExpandNode(N* node, PerformanceCounter* pc)
//{
//#ifdef _DEBUG
//	if (pc)
//	{
//		pc->increaseAllUsedMemory(node->GenerateAllChildren(N::currentIsFirstPlayer, node));
//		pc->increaseAllExpandedNodes(node->childrenCount);
//	}
//#else
//	node->GenerateAllChildren(N::currentIsFirstPlayer, node);
//#endif
//	for (unsigned int i = 0; i < node->childrenCount; i++)
//	{
//		Evaluate(node->getChild(i));
//	}
//};
//
//template<>
//bool ProofNumberSearchWrapped<PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int>>::Solve(
//	PNSNodeWithoutPointers<CaptureGoEngine, unsigned int, unsigned int> solvingNode,
//	bool currentPlayerIsFirst,
//	bool winForFirstPlayer, 
//	PerformanceCounter* pc)
//{
//	unsigned int root = 0;
//	bool currentNodeIsOfTypeOr = winForFirstPlayer;
//	bool currentIsFirstPlayer = currentPlayerIsFirst;
//	bool checkWinForFirstPlayer = winForFirstPlayer;
//	unsigned int currentNode = root;
//	unsigned int mostProvingNode = root;
//
//	/*startExecutionTimeMeasurement();
//	while (root->proof != 0 && root->disproof != 0)
//	{
//#ifdef _DEBUG
//		if (pc)
//		{
//			pc->setMaxProofAndDisproof(root->proof, root->disproof);
//		}
//#endif
//		mostProvingNode = SelectMostProving(currentNode);
//		ExpandNode(mostProvingNode, pc);
//		currentNode = UpdateAncestors(mostProvingNode);
//	}
//	stopExecutionTimeMeasurement();
//	if (root->proof == 0) return true;
//	else if (root->disproof == 0) return false;
//	else throw "unknown value";*/
//
//	//todo: skasowaæ !!!
//	return false;
//};