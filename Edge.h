#pragma once

struct Edge
{
    size_t vertex, link, capacity;
    bool backFlowEdge, isEdge;
    Edge(const size_t vertex, const size_t link, size_t capacity, bool backFlowEdge, bool isEdge) : vertex(vertex), link(link), capacity(capacity), backFlowEdge(backFlowEdge), isEdge(isEdge) {}
};