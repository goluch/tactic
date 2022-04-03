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

	void setMaxProofAndDisproof(unsigned long long, unsigned long long);
	void increaseAllExpandedNodes(unsigned long long);
	void decreaseMaxExpandedNodesInMemory(unsigned long long);
	void increaseAllUsedMemory(unsigned long long);
};

