#include "graph.h"

#define MAX std::numeric_limits<double>::max()

Graph::Graph(Graph& g) {
    for (auto v : g.getVertexSet()) {
        addVertex(v->getStation());
    }

    for (auto v : g.getVertexSet()) {
        auto v_copy = findVertex(v->getStation().getName());
        for (auto e : v->getAdj()) {
            auto w = e->getDest();
            auto w_copy = findVertex(w->getStation().getName());
            addEdge(v_copy->getStation().getName(), w_copy->getStation().getName(), e->getWeight(), e->getService());
        }
    }
}

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

bool Graph::removeVertex(const string &target) {
    Vertex* node = findVertex(target);

    if (node == nullptr) {
        return false;
    }

    for (auto e : node->getAdj()) {
        auto w = e->getDest();
        w->removeEdge(node->getStation().getName());
        node->removeEdge(w->getStation().getName());
    }

    for (auto itr = vertexSet.begin(); itr != vertexSet.end(); itr++) {
        if ((*itr)->getStation().getName() == target) {
            vertexSet.erase(itr);
            itr--;
            break;
        }
    }

    delete node;
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
    map<pair<string,string>, int> matrix;

    for (auto &source: vertexSet) {
        for (auto &sink: vertexSet) {
            int trains_num = INT_MIN;

            if (matrix.find(make_pair(source->getStation().getName(), sink->getStation().getName())) == matrix.end() && matrix.find(make_pair(sink->getStation().getName(), source->getStation().getName())) == matrix.end()) {
                trains_num = edmondsKarp(source->getStation().getName(), sink->getStation().getName());

                matrix[make_pair(source->getStation().getName(), sink->getStation().getName())] = trains_num;
            }
            else {
                trains_num = matrix[make_pair(source->getStation().getName(), sink->getStation().getName())];
            }
            if (trains_num > max_trains) {
                max_pairs.clear();
                max_pairs.push_back(make_pair(source->getStation().getName(), sink->getStation().getName()));
                max_trains = trains_num;
            }
            else if (trains_num == max_trains) {
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

vector<pair<string, double>> Graph::topFlowDistricts() {
    map<string, double> dists;

    for (auto &src: vertexSet) {
        for (auto &dst: vertexSet) {
            int trains_num = edmondsKarp(src->getStation().getName(), dst->getStation().getName());

            if (trains_num != -1) {
                if (dists.find(src->getStation().getDistrict()) == dists.end()) {
                    dists.insert({src->getStation().getDistrict(), 0});
                }

                dists[src->getStation().getDistrict()] += trains_num;
            }
        }
    }
    vector<pair<string, double>> final = mapSort(dists);
    return final;
}

double Graph::maxArrivalTrains(const string dest){
    Station motherSrc = Station("all", "all", "all", "all", "all");

    addVertex(motherSrc);

    for(auto i: this->vertexSet)
        for(auto j: i->getAdj())
            j->setFlow(0);

    for(auto i : this->vertexSet){
        if((!i->getStation().operator==(this->findVertex(dest)->getStation())) && (i->getAdj().size() == 1))
            addEdge(motherSrc.getName(), i->getStation().getName(), MAX, "ALL");
    }

    double maxTrainArrival = edmondsKarp(motherSrc.getName(), dest);

    removeVertex(motherSrc.getName());
    return maxTrainArrival;
}

/**
 * @brief Allows the sorting of the graph's vertexes by descending order of distance
 */
struct PriorityCompare {
    /**
     * @brief Sorts two vertexes by distance
     * @param s The first vertex
     * @param t The second vertex
     * @return True if the first vertex's distance is bigger than the second's; otherwise, it returns false
     */
    bool operator()(const Vertex* s, const Vertex* t) {
        return s->getDistance() > t->getDistance();
    }
};

void Graph::dijkstra(const string &source, const string &target, vector<Vertex*> &path) {
    priority_queue<Vertex*, vector<Vertex*>, PriorityCompare> pq;
    Vertex* src = findVertex(source);
    for (auto node : vertexSet){
        node->setVisited(false);
        node->setDistance(INT_MAX);
    }

    src->setDistance(0);
    pq.push(src);

    while (!pq.empty()) {
        Vertex* t = pq.top();
        //cout << t->getStation().getName() << endl;
        pq.pop();

        t->setVisited(true);

        for (auto e : t->getAdj()) {
            Vertex *v = e->getDest();
            string serv = e->getService();
            int w;
            if (serv == "STANDARD") {
                w = 2;
            }
            else if (serv == "ALFA PENDULAR") {
                w = 4;
            }
            if (!v->isVisited() && t->getDistance() != INT_MAX && (t->getDistance() + w < v->getDistance())) {
                v->setSRC(t);
                v->setDistance(t->getDistance()+w);
                pq.push(v);
            }
        }
    }
    path.clear();
    Vertex* trg = findVertex(target);
    while (trg != nullptr) {
        path.push_back(trg);
        trg = trg->getSRC();
    }
    reverse(path.begin(), path.end());
}

double Graph::findBottleneck(vector<Vertex*> &path) {
    double bottleneck = MAX;
    for (int i = 0; i < path.size() - 1; i++) {
        Vertex* src = path[i];
        Vertex* dst = path[i+1];

        if (src == nullptr || dst == nullptr) {
            return -1;
        }

        double w;

        for (auto e: src->getAdj()) {
            if (e->getDest()->getStation().getName() == dst->getStation().getName()) {
                w = e->getWeight();
                break;
            }
        }


        bottleneck = min(bottleneck, w);
        //cout << "[" << bottleneck << "]";
    }
    //cout << endl << "{" << bottleneck << "}" << endl;
    return bottleneck;
}
