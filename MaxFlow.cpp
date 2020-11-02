#include "MaxFlow.h"
#include <algorithm>
#include <iostream>

int MaxFlow::calculateBackFLowWithStack(std::stack<Edge*>& pathChecker, std::list<Edge>* residualGraph, int backFlowCapacity)
{
	for (auto j = residualGraph[pathChecker.top()->vertex].begin(); j != residualGraph[pathChecker.top()->vertex].end(); j++)
	{
		if (pathChecker.top()->vertex == j->vertex && pathChecker.top()->link == j->link)
		{
			backFlowCapacity = (int)j->capacity - (int)pathChecker.top()->capacity;
			break;
		}
	}
	return backFlowCapacity;
}

size_t MaxFlow::calculateBottleNeck(size_t currentFlow, std::stack<Edge*> pathChecker, std::list<Edge> residualGraph[])
{
	size_t size = pathChecker.size();
	for (size_t i = 0; i < size; i++)
	{
		if (pathChecker.top()->backFlowEdge)
		{
			int backFlowCapacity = 0;
			currentFlow = std::min(currentFlow, (size_t)calculateBackFLowWithStack(pathChecker, residualGraph, backFlowCapacity));
		}
		else
		{
			currentFlow = std::min(currentFlow, pathChecker.top()->capacity);
		}
		pathChecker.pop();
	}
	return currentFlow;
}

void MaxFlow::frontFlow(std::list<Edge>* graph, std::stack<Edge*>& pathChecker, bool* visited, bool& foundFrontFlow)
{
	for (auto i = graph[pathChecker.empty() ? 0 : (pathChecker.top()->backFlowEdge ? pathChecker.top()->vertex : pathChecker.top()->link)].begin(); i != graph[pathChecker.empty() ? 0 : (pathChecker.top()->backFlowEdge ? pathChecker.top()->vertex : pathChecker.top()->link)].end(); ++i)
	{
		if (!visited[i->link] && i->capacity > 0)
		{
			visited[i->link] = true;
			i->backFlowEdge = false;
			foundFrontFlow = true;
			pathChecker.emplace(&(*i));
			break;
		}
	}
}

int MaxFlow::calculateBackFlowCapacity(std::list<Edge>* residualGraph, int backFlowCapacity, std::list<Edge>::iterator k)
{
	for (auto h = residualGraph[k->vertex].begin(); h != residualGraph[k->vertex].end(); h++)
	{
		if (k->vertex == h->vertex && k->link == h->link)
		{
			backFlowCapacity = (int)h->capacity - (int)k->capacity;
			break;
		}
	}
	return backFlowCapacity;
}

bool MaxFlow::emplaceBackflow(std::stack<Edge*>& pathChecker, int backFlowCapacity, bool* visited, std::list<Edge>::iterator k)
{
	if (backFlowCapacity > 0)
	{
		visited[k->vertex] = true;
		k->backFlowEdge = true;
		pathChecker.emplace(&(*k));
		return true;
	}
	return false;
}

void MaxFlow::backFlow(const size_t vertexCount, std::list<Edge>* graph, std::list<Edge>* residualGraph, std::stack<Edge*>& pathChecker, int backFlowCapacity, bool* visited)
{
	for (size_t j = 0; j < vertexCount; j++)
	{
		for (auto k = graph[j].begin(); k != graph[j].end(); k++)
		{
			if (!visited[k->vertex] && k->link == pathChecker.top()->link)
			{
				if (emplaceBackflow(pathChecker, calculateBackFlowCapacity(residualGraph, backFlowCapacity, k), visited, k)) break;
				backFlowCapacity = 0;
			}
		}
	}
}

bool MaxFlow::checkForVisitedLink(std::list<Edge>* graph, bool* visited, bool foundUnvisitedLink)
{
	for (auto i = graph[0].begin(); i != graph[0].end(); ++i)
	{
		if (!visited[i->link] && i->capacity > 0)
		{
			foundUnvisitedLink = true;
			break;
		}
	}
	return foundUnvisitedLink;
}

bool MaxFlow::checkForValidPath(std::list<Edge>* graph, std::stack<Edge*>& pathChecker, bool* visited, const size_t previousTop)
{
	if (pathChecker.empty() || previousTop == (pathChecker.top()->backFlowEdge ? pathChecker.top()->vertex : pathChecker.top()->link))
	{
		if (!pathChecker.empty())
		{
			pathChecker.pop();
		}

		if (pathChecker.empty())
		{
			bool foundUnvisitedLink = false;

			if (!checkForVisitedLink(graph, visited, foundUnvisitedLink))
			{
				return true;
			}
		}
	}
	return false;
}

void MaxFlow::calculateNewCapacities(size_t& currentFlow, std::stack<Edge*>& pathChecker)
{
	size_t size = pathChecker.size();
	for (size_t i = 0; i < size; i++)
	{
		if (pathChecker.top()->backFlowEdge == false)
		{
			pathChecker.top()->capacity -= currentFlow;
		}
		if (pathChecker.top()->backFlowEdge == true)
		{
			pathChecker.top()->capacity += currentFlow;
		}
		pathChecker.pop();
	}
}

size_t MaxFlow::returnMaxFlow(const size_t source, const size_t sink, const size_t vertexCount, std::list<Edge> graph[], std::list<Edge> residualGraph[], std::stack<std::stack<Edge*>>& pathStorage, size_t& currentFlow)
{
	std::stack<Edge*> pathChecker;
	size_t maxFlow = 0;
	currentFlow = SIZE_MAX;
	int backFlowCapacity = 0;

	bool* visited = new bool[vertexCount];
	memset(visited, 0, sizeof(bool) * vertexCount);
	visited[source] = true;

	while (pathChecker.empty() || pathChecker.top()->link != sink)
	{
		bool foundFrontFlow = false;
		const size_t previousTop = !pathChecker.empty() ? (pathChecker.top()->backFlowEdge ? pathChecker.top()->vertex : pathChecker.top()->link) : NULL; pathChecker.empty() ? 0 : (pathChecker.top()->backFlowEdge ? pathChecker.top()->vertex : pathChecker.top()->link);
		frontFlow(graph, pathChecker, visited, foundFrontFlow);

		if (!foundFrontFlow)
		{
			backFlow(vertexCount, graph, residualGraph, pathChecker, backFlowCapacity, visited);
		}

		if (checkForValidPath(graph, pathChecker, visited, previousTop)) break;
	}

	currentFlow = calculateBottleNeck(currentFlow, pathChecker, residualGraph);
	pathStorage.emplace(pathChecker);

	if (!pathChecker.empty())
	{
		maxFlow += currentFlow;
	}

	calculateNewCapacities(currentFlow, pathChecker);
	delete[] visited;
	return maxFlow;
}