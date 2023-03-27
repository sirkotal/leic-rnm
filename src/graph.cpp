#include "graph.h"

#define MAX std::numeric_limits<double>::max()

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

bool Graph::addVertex(const Station &station) {
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

int Graph::getNumEdges() const {
    int res = 0;
    for (auto v: vertexSet) {
        res += v->getAdj().size();
    }
    return res;
}

void Graph::edmondsKarp(const string source, const string target) {
    Vertex* s = findVertex(source);
    Vertex* t = findVertex(target);
    if (s == nullptr || t == nullptr || s == t) {
        std::cerr << "Error" << std::endl;
        return;
    }

    // flux reset
    for (auto v : vertexSet) {
        for (auto e : v->getAdj()) {
            e->setFlow(0);
        }
    }

    // find paths in which flux increases
    while (findAugmentingPath(s,t)) {
        double f = findMinResidualAlongPath(s,t);
        augmentFlowAlongPath(s,t,f);
    }

    return;
}

bool Graph::findAugmentingPath(Vertex* s, Vertex* t) {
    for (auto v: vertexSet) {
        v->setVisited(false);
    }
    s->setVisited(true);
    std::queue<Vertex*> q;
    q.push(s);
    while (!q.empty() && !t->isVisited()) {
        Vertex* v = q.front();
        q.pop();
        for (auto e : v->getAdj()) {
            testAndVisit(q,e,e->getDest(), e->getWeight() - e->getFlow());
        }
        for (auto e : v->getIncoming()) {
            testAndVisit(q,e,e->getOrig(), e->getFlow());
        }
    }
    return t->isVisited();
}

void Graph::testAndVisit(std::queue<Vertex*> &q, Edge* e, Vertex* w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
    return;
}

double Graph::findMinResidualAlongPath(Vertex* s, Vertex* t) {
    double f = MAX;
    for (auto v = t; v!= s;) {
        Edge* e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

void Graph::augmentFlowAlongPath(Vertex* s, Vertex* t, double f) {
    for (auto v= t; v!=s; ) {
        Edge* e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest()==v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
    return;
}