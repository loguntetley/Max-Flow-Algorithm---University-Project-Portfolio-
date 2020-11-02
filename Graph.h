#pragma once
#include <list>
#include "Edge.h"

class Graph
{
private:
    size_t m_VertexCount;
    std::list<Edge>* m_NextLink;

public:

    Graph(size_t vertexAmount);
    virtual ~Graph();
    void addEdge(size_t vertex, size_t link, size_t capacity) const;
    size_t getVertexCount() const;
    virtual std::list<Edge>* getGraph() const;

};

class ResidualGraph : public Graph
{
private:
    std::list<Edge>* m_ResidualGraph;

public:
    ResidualGraph(std::list<Edge> originalGraph[], size_t vertexCount);
    ~ResidualGraph() override;
    std::list<Edge>* getGraph() const override;

};