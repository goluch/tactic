//#pragma once
//#include "PerformanceCounter.h"
//#include "ProofNumberSearch.h"
//
//namespace gameSolver
//{
//	template<typename N>
//	class ProofNumberSearchWrapped : public ProofNumberSearch<N>
//	{
//
//	public:
//
//		static bool* isItAWinner;
//
//		ProofNumberSearchWrapped();
//		~ProofNumberSearchWrapped();
//		bool Solve(N, bool, bool, PerformanceCounter * = nullptr);
//
//	protected:
//		void SetProofAndDisproofNumbers(N*);
//		void ExpandNode(N* node, PerformanceCounter* pc);
//		N* SelectMostProving(N*);
//		N* UpdateAncestors(N*);
//	};
//
//}