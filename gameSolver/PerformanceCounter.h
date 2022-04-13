#pragma once
class PerformanceCounter
{
public:
	PerformanceCounter();
	~PerformanceCounter();

	unsigned long long allExpandedNodes;
	unsigned long long maxExpandedNodesInMemory;
	unsigned long long maxProofNumberInRoot;
	unsigned long long maxDisProofNumberInRoot;
	unsigned long long maxMemoryUsageCount;

	void SetMaxProofAndDisproof(unsigned long long, unsigned long long);
	void IncreaseAllExpandedNodes(unsigned long long);
	void DecreaseMaxExpandedNodesInMemory(unsigned long long);
	void IncreaseAllUsedMemory(unsigned long long);
};