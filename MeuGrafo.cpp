#include "MeuGrafo.h"
// MeuGrafo

#include <cstddef>
// std::size_t
#include <iterator>
// std::empty
// std::size
#include <queue>
// std::priority_queue
#include <vector>
// std::vector

#include "excecoes.h"
// ExcecaoMatrizAdjacenciaVazia
// ExcecaoMatrizAdjacenciaNaoQuadrada
// ExcecaoCustoNegativo
// ExcecaoVerticeComLaco
// ExcecaoVerticeInvalido

// implente aqui
struct Node
{
    std::size_t id;     // pos em matrizadjacencia
    std::size_t rating; // estimativa
    int previd;

    Node(std::size_t tid, std::size_t rtng = std::numeric_limits<double>::infinity(), int prev = -1) : id(tid), rating(rtng), previd(prev) {}

    bool operator<(const Node &tmp) const
    {
        return rating > tmp.rating;
    }
};

MeuGrafo::MeuGrafo(MatrizAdjacencia const &matrizAdjacencia) : GrafoAbstrato(matrizAdjacencia)
{
    if (matrizAdjacencia.size() == 0)
    {
        throw(ExcecaoMatrizAdjacenciaVazia());
    }
    for (size_t i = 0; i < matrizAdjacencia.size(); i++)
    {
        if (matrizAdjacencia.at(i).size() != matrizAdjacencia.size())
        {
            throw(ExcecaoMatrizAdjacenciaNaoQuadrada());
        }
    }

    for (size_t i = 0; i < matrizAdjacencia.size(); i++)
    {
        for (size_t j = 0; j < matrizAdjacencia.at(i).size(); j++)
        {
            if (matrizAdjacencia.at(i).at(j) < 0)
            {
                throw(ExcecaoCustoNegativo());
            }
        }
    }

    for (size_t i = 0; i < matrizAdjacencia.size(); i++)
    {

        if (matrizAdjacencia.at(i).at(i) != inf)
        {
            throw(ExcecaoVerticeComLaco());
        }
    }
};
std::size_t MeuGrafo::quantidadeVertices() const
{
    return this->_matrizAdjacencia.size();
};
std::size_t MeuGrafo::quantidadeArestas(std::size_t vertice) const
{
    if (vertice >= this->_matrizAdjacencia.size())
    {
        throw(ExcecaoVerticeInvalido());
        return -1;
    }

    std::size_t count = 0;
    for (size_t j = 0; j < this->_matrizAdjacencia.size(); j++)
    {
        if (this->_matrizAdjacencia.at(vertice).at(j) != inf)
        {
            count++;
        }
    };
    return count;
};
std::size_t MeuGrafo::quantidadeArestas() const
{
    std::size_t count = 0;

    for (size_t i = 0; i < this->_matrizAdjacencia.size(); i++)
    {
        for (size_t j = 0; j < this->_matrizAdjacencia.size(); j++)
        {
            if ((i - j) > 0)
            {
                if (this->_matrizAdjacencia.at(i).at(j) != inf)
                {
                    count++;
                }
            }
        }
    }

    return count;
};
double MeuGrafo::custo(std::size_t origem, std::size_t destino) const
{
    if (origem >= this->_matrizAdjacencia.size())
    {
        throw(ExcecaoVerticeInvalido());
        return -1;
    }
    if (destino >= this->_matrizAdjacencia.size())
    {
        throw(ExcecaoVerticeInvalido());
        return -1;
    }

    return this->_matrizAdjacencia.at(origem).at(destino);
};
std::vector<double> MeuGrafo::menoresDistancias(std::size_t origem) const
{
    std::priority_queue<Node> Prioq;
    for (size_t i = 0; i < this->_matrizAdjacencia.size(); i++)
    {
        if (i == origem)
        {
            Prioq.emplace(Node(i, 0));
        }
        else
        {
            Prioq.emplace(Node(i));
        }
    } // initialize queue

    return std::vector<double>{1};
};

void Relax(Node current, Node neighbor)
{
}

/*
std::priority_queue<Task> task_queue;

    // Add tasks to the priority queue
    task_queue.emplace(3, "Write report");
    task_queue.emplace(1, "Fix critical bug");
    task_queue.emplace(2, "Prepare presentation");

    // Process tasks in priority order
    while (!task_queue.empty()) {
        const Task& task = task_queue.top();
        std::cout << "Priority: " << task.priority << ", Task: " << task.name << std::endl;
        task_queue.pop();
    }
*/