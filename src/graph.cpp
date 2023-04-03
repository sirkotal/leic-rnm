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

double Graph::edmondsKarp(const string source, const string target) {
    Vertex* s = findVertex(source);
    Vertex* t = findVertex(target);
    if (s == nullptr || t == nullptr) {
        std::cerr << "Not a valid path" << std::endl;
        return -1;
    }

    if (s == t) {
        return -1;
    }

    double flow_max = 0;

    // flux reset
    for (auto v : vertexSet) {
        for (auto e : v->getAdj()) {
            e->setFlow(0);
        }
    }

    double f;
    // find paths in which flux increases
    while (findAugmentingPath(s,t)) {
        f = findMinResidualAlongPath(s,t);
        augmentFlowAlongPath(s,t,f);
        flow_max += f;
    }
    return flow_max;
}

bool Graph::findAugmentingPath(Vertex* src, Vertex* dst) {
    for (auto v: vertexSet) {
        v->setVisited(false);
    }
    src->setVisited(true);
    std::queue<Vertex*> q;
    q.push(src);
    while (!q.empty() && !dst->isVisited()) {
        Vertex* v = q.front();
        q.pop();
        for (auto e : v->getAdj()) {
            testAndVisit(q,e,e->getDest(), e->getWeight() - e->getFlow());
        }
        for (auto e : v->getIncoming()) {
            testAndVisit(q,e,e->getOrig(), e->getFlow());
        }
    }
    return dst->isVisited();
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

vector<pair<string,string>> Graph::maxTrainsPairs() {
    int max_trains = INT_MIN;
    vector<pair<string,string>> max_pairs;

    for (auto &source: vertexSet) {
        for (auto &sink: vertexSet) {
            int trains_num = edmondsKarp(source->getStation().getName(), sink->getStation().getName());
            if (trains_num > max_trains) {
                max_pairs.clear();
                max_pairs.push_back(make_pair(source->getStation().getName(), sink->getStation().getName()));
                max_trains = trains_num;
            }
            else if (trains_num == max_trains && find(max_pairs.begin(), max_pairs.end(), make_pair(sink->getStation().getName(), source->getStation().getName())) == max_pairs.end()) {
                max_pairs.push_back(make_pair(source->getStation().getName(), sink->getStation().getName()));
            }
        }
    }

    return max_pairs;
}

bool cmpFunc(pair<string, double>& x, pair<string, double>& y) {
    return x.second > y.second;
}

vector<pair<string, double>> mapSort(map<string, double> &m) {
    vector<pair<string, double>> vct;

    for (auto& itr : m) {
        vct.push_back(itr);
    }

    sort(vct.begin(), vct.end(), cmpFunc);

    return vct;
}

vector<pair<string, double>> Graph::topFlowMunicipalities() {
    map<string, double> muns;

    for (auto &src: vertexSet) {
        for (auto &dst: vertexSet) {
            int trains_num = edmondsKarp(src->getStation().getName(), dst->getStation().getName());

            if (trains_num != -1) {
                if (muns.find(src->getStation().getMunicipality()) == muns.end()) {
                    muns.insert({src->getStation().getMunicipality(), 0});
                }

                muns[src->getStation().getMunicipality()] += trains_num;
            }
        }
    }
    vector<pair<string, double>> final = mapSort(muns);
    return final;
}