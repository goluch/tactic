#pragma once

#include "Node.h"

namespace gameDataStructures
{
	template<typename E, typename T, typename I>
	struct PNSNodeWithoutPointers
	{
		class Indexer { };

		PNSNodeWithoutPointers();
		//PNSNodeWithoutPointers(E, I = NULL);
		~PNSNodeWithoutPointers();

		//E gameEngine;
		T proof;
		T disproof;

		I parent;
		I *children;
		short childrenCount;

		static T oldProof;
		static T oldDisproof;
		static T min;
		static T sum;
		static bool currentNodeIsOfTypeOr;
		static bool currentIsFirstPlayer;
		static bool checkWinForFirstPlayer;
		static I gameTreeCount;
		static I gameTreeIndex;
		static E* possibleMoves;
		static PNSNodeWithoutPointers<E, T, I>* gameTree;

		int GenerateAllChildren(bool, PNSNodeWithoutPointers *);

		static void Initialize();

		PNSNodeWithoutPointers* getChild(int i);
		PNSNodeWithoutPointers* getParent();

	};
}