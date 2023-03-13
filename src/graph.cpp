#include "graph.h"

Vertex* Graph::findVertex(const string &id) const {
    for (auto v: vertexSet) {
        if (v->getStation().getName() == id) {
            return v;
        }
    }

    return nullptr;
}

int Graph::findVertexIdx(const string &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getStation().getName() == id) {
            return i;
        }
    return -1;
}

bool Graph::addVertex(Station station) {
    if (findVertex(station.getName()) != nullptr) {
        return false;
    }

    vertexSet.push_back(new Vertex(station));
    return true;
}

bool Graph::addEdge(const string &source, const string &dest, double weight, const string &serv) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    v1->addEdge(v2, weight, serv);
    return true;
}

bool Graph::addBidirectionalEdge(const string &source, const string &dest, double weight, const string &serv) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    auto e1 = v1->addEdge(v2, weight, serv);
    auto e2 = v2->addEdge(v1, weight, serv);

    e1->setReverse(e2);
    e2->setReverse(e1);

    return true;
}

int Graph::getNumVertex() const {
    return this->vertexSet.size();
}

vector<Vertex *> Graph::getVertexSet() const {
    return this->vertexSet;
}