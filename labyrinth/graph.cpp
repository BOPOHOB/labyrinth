#include "graph.h"
#include <QDebug>
#include <QTime>
#include "types.h"

Graph::Graph()
{
}

Graph::Graph(int size)
    : QVector<Edges>(size)
{ }

bool Graph::isConnected(const int n1, const int n2) const{
    const Edges& e(operator[](n1));
    return e.find(n2) != e.end();
}


void Graph::addEdge(const int n1, const int n2) {
    if (!isConnected(n1, n2)) {
        operator[](n1).insert(n2);
    }
    if (!isConnected(n2, n1)) {
        operator[](n2).insert(n1);
    }
}

void Graph::rendEdge(const int n1, const int n2) {

    operator[](n1).erase(operator[](n1).find(n2));
    operator[](n2).erase(operator[](n2).find(n1));
}

bool Graph::isComplete() const {
    const int queriedSize(size() - 1);
    for (const_iterator it(begin()), end(end()); it != end; ++it)
        if (it->size() != queriedSize)
            return false;
    return true;
}

int Graph::nodeDegree(const int i) const { return operator[](i).size(); }
