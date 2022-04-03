#pragma once

#include "Node.h"

namespace gameDataStructures
{
	template<typename E, typename T>
	struct PNSNode 
	{
		PNSNode();
		PNSNode(E, PNSNode * = nullptr);
		~PNSNode();

		E gameEngine;
		T proof;
		T disproof;

		PNSNode *parent;
		PNSNode **children;
		unsigned long long childrenCount;

		static T oldProof;
		static T oldDisproof;
		static T min;
		static T sum;
		static bool currentNodeIsOfTypeOr;
		static bool currentIsFirstPlayer;
		static bool checkWinForFirstPlayer;
		static E* possibleMoves;

		int GenerateAllChildren(bool, PNSNode *);

		static void Initialize();

		PNSNode* getChild(int i);
		PNSNode* getParent();
	};
}