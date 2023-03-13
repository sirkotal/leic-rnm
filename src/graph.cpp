#include "graph.h"

Vertex* Graph::findVertex(const int &id) const {
    for (auto v: vertexSet) {
        if (v->getId() == id) {
            return v;
        }
    }

    return nullptr;
}

int Graph::findVertexIdx(const int &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id) {
            return i;
        }
    return -1;
}

bool Graph::addVertex(const int &id, Station &station) {
    if (findVertex(id) != nullptr) {
        return false;
    }

    vertexSet.push_back(new Vertex(id, station));
    return true;
}

bool Graph::addEdge(const int &source, const int &dest, double weight) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    v1->addEdge(v2, weight);
    return true;
}

bool Graph::addBidirectionalEdge(const int &source, const int &dest, double weight) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    auto e1 = v1->addEdge(v2, weight);
    auto e2 = v2->addEdge(v1, weight);

    e1->setReverse(e2);
    e2->setReverse(e1);

    return true;
}

int Graph::getNumVertex() const {
    return this->vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return this->vertexSet;
}