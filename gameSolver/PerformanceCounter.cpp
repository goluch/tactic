#include "PerformanceCounter.h"


PerformanceCounter::PerformanceCounter()
{
	allExpandedNodes = 0;
	maxExpandedNodesInMemory = 0;
	maxProofNumberInRoot = 0;
	maxDisProofNumberInRoot = 0;
	maxMemoryUsageCount = 0;
}


PerformanceCounter::~PerformanceCounter()
{
}

void PerformanceCounter::SetMaxProofAndDisproof(unsigned long long newProof, unsigned long long newDisproof)
{
	if (this->maxProofNumberInRoot < newProof)
	{
		this->maxProofNumberInRoot = newProof;
	}
	if (this->maxDisProofNumberInRoot < newDisproof)
	{
		this->maxDisProofNumberInRoot = newDisproof;
	}
}

void PerformanceCounter::IncreaseAllExpandedNodes(unsigned long long newNodesCount)
{
	this->allExpandedNodes += newNodesCount;
	this->maxExpandedNodesInMemory += newNodesCount;
}

void PerformanceCounter::DecreaseMaxExpandedNodesInMemory(unsigned long long newNodesCount)
{
	this->maxExpandedNodesInMemory -= newNodesCount;
}

void PerformanceCounter::IncreaseAllUsedMemory(unsigned long long newMemoryUsageCount)
{
	this->maxMemoryUsageCount += newMemoryUsageCount;
}