#include "vertexedge.h"

/************************* Vertex  **************************/

Vertex::Vertex(const Station &station): station(station) {}

Edge * Vertex::addEdge(Vertex *d, double w, const string &service) {
    auto newEdge = new Edge(this, d, w, service);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(string destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getStation().getName() == destID) {
            it = adj.erase(it);
            // Also remove the corresponding edge from the incoming list
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getStation().getName() == station.getName()) {
                    it2 = dest->incoming.erase(it2);
                }
                else {
                    it2++;
                }
            }
            delete edge;
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

Station Vertex::getStation() const{
    return this->station;
}

std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

int Vertex::getDistance() const {
    return this->dist;
}

bool Vertex::isVisited() const {
    return this->visited;
}

bool Vertex::isProcessing() const {
    return this->processing;
}

unsigned int Vertex::getIndegree() const {
    return this->indegree;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setProcesssing(bool processing) {
    this->processing = processing;
}

void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

void Vertex::setDistance(int num) {
    this->dist = num;
}

/*bool Vertex::operator()(const Vertex* s, const Vertex* t) const {
    return s->getDistance() > t->getDistance();
}*/

Vertex* Vertex::getSRC() {
    return this->src;
}

void Vertex::setSRC(Vertex *v) {
    this->src = v;
}

/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double w, const string &service): orig(orig), dest(dest), weight(w), service(service) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

double Edge::getFlow() const {
    return flow;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}

string Edge::getService() const {
    return this->service;
}