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

    return std::vector<double>{1};
};