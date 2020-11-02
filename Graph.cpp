#include "Graph.h"

#include "Graph.h"

Graph::Graph(size_t vertexAmount)
{
	this->m_VertexCount = vertexAmount;
	m_NextLink = new std::list<Edge>[vertexAmount];
}

Graph::~Graph()
{
	delete[] m_NextLink;
}

void Graph::addEdge(size_t vertex, size_t link, size_t capacity) const
{
	m_NextLink[vertex].emplace_back(Edge(vertex, link, capacity, NULL, true));
}

size_t Graph::getVertexCount() const
{
	return m_VertexCount;
}

std::list<Edge>* Graph::getGraph() const
{
	return m_NextLink;
}

ResidualGraph::ResidualGraph(std::list<Edge> originalGraph[], size_t vertexCount) : Graph(vertexCount)
{
	m_ResidualGraph = new std::list<Edge>[vertexCount];
	for (size_t i = 0; i < vertexCount; i++)
	{
		for (auto j = originalGraph[i].begin(); j != originalGraph[i].end(); j++)
		{
			m_ResidualGraph[i].emplace_back(Edge(j->vertex, j->link, j->capacity, NULL, true));
		}
	}
}

ResidualGraph::~ResidualGraph()
{
	delete[] m_ResidualGraph;
}

std::list<Edge>* ResidualGraph::getGraph() const
{
	return m_ResidualGraph;
}