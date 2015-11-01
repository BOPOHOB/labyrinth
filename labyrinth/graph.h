#ifndef GRAPH_H
#define GRAPH_H
#include <QVector>
#include <QSet>

//Edges from signed node
typedef QSet<int> Edges;

//All about the graph edges
class Graph : public  QVector<Edges>
{
public:
    Graph();
    Graph(int size);

    //is graph have edge from n1 to n2
    bool isConnected(const int n1, const int n2) const;
    //add adge from n1 to n2 and from n2 to n1
    void addEdge(const int n1, int n2);
    //rend edge from n1 to n2 and from n2 to n1.
    void rendEdge(const int n1, const int n2);

    bool isComplete() const;
    int nodeDegree(const int i) const;
};

#endif // GRAPH_H
