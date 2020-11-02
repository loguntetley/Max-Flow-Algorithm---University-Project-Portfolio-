#pragma once
#include <list>
#include <stack>
#include "Edge.h"


class MaxFlow
{
private:
	static int calculateBackFLowWithStack(std::stack<Edge*>& pathChecker, std::list<Edge>* residualGraph, int backFlowCapacity);
	static size_t calculateBottleNeck(size_t currentFlow, std::stack<Edge*> pathChecker, std::list<Edge> residualGraph[]);
	static void frontFlow(std::list<Edge>* graph, std::stack<Edge*>& pathChecker, bool* visited, bool& foundFrontFlow);
	static int calculateBackFlowCapacity(std::list<Edge>* residualGraph, int backFlowCapacity, std::list<Edge>::iterator k);
	static bool emplaceBackflow(std::stack<Edge*>& pathChecker, int backFlowCapacity, bool* visited, std::list<Edge>::iterator k);
	static void backFlow(size_t vertexCount, std::list<Edge>* graph, std::list<Edge>* residualGraph, std::stack<Edge*>& pathChecker, int backFlowCapacity, bool* visited);
	static bool checkForVisitedLink(std::list<Edge>* graph, bool* visited, bool foundUnvisitedLink);
	static bool checkForValidPath(std::list<Edge>* graph, std::stack<Edge*>& pathChecker, bool* visited, size_t previousTop);
	static void calculateNewCapacities(size_t& currentFlow, std::stack<Edge*>& pathChecker);

public:
	static size_t returnMaxFlow(const size_t source, const size_t sink, const size_t vertexCount, std::list<Edge> graph[], std::list<Edge> residualGraph[], std::stack<std::stack<Edge*>>& pathStorage, size_t& currentFlow);
};