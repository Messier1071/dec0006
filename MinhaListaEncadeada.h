#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 *
 * @tparam T O tipo dos dados armazenados na lista.
 */
template <typename T>
class MinhaListaEncadeada : public ListaEncadeadaAbstrata<T>
{

public:
    /**
     * @brief Destrutor. Destroi todos os elementos da lista
     */
    virtual ~MinhaListaEncadeada()
    {
        // escreva o algoritmo esperado
    }

    /**
     * @brief Obtém a quantidade de itens na lista.
     *
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t tamanho() const
    {
        return this->_tamanho;
    };

    /**
     * @brief Indica se há algum item na lista ou não.
     *
     * @return false se houver algum item na lista; true caso contrário.
     */
    virtual bool vazia() const
    {
        if (this->_tamanho == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
        return true;
    };

    /**
     * @brief Obtém a posição de um item na lista. Lança
     * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     *
     * @param dado O item cuja posição deseja-se obter.
     * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
     * item na lista, a posição da primeira ocorrência.
     */
    virtual std::size_t posicao(T dado) const
    {
        if (this->_tamanho == 0)
        {
            throw(ExcecaoListaEncadeadaVazia());
        }

        std::size_t Pos = 0;
        Elemento<T> *Seekptr = this->_primeiro;

        do
        {

            if (Seekptr->dado == dado)
            {
                return Pos;
            }

            Seekptr = Seekptr->proximo;
            Pos += 1;
        } while (Seekptr != nullptr);

        throw(ExcecaoDadoInexistente());
    };

    /**
     * @brief Indica se um dado item está contido na lista ou não.
     *
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    virtual bool contem(T dado) const
    {

        if (this->_tamanho == 0)
        {
            return false;
        }
        std::size_t Pos = 0;
        Elemento<T> *Seekptr = this->_primeiro;

        do
        {

            if (Seekptr->dado == dado)
            {
                return true;
            }

            Seekptr = Seekptr->proximo;
            Pos += 1;
        } while (Seekptr != nullptr);

        throw(ExcecaoDadoInexistente());

        return false;
    };

    /**
     * @brief Insere um item no início da lista.
     *
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado)
    {
        Elemento<T> *TemporaryPtr = nullptr;
        Elemento<T> *Classptr = nullptr;
        Elemento<T> *Selector = nullptr;

        if (this->_primeiro == nullptr)
        {
            Classptr = new Elemento<T>(dado);

            this->_primeiro = Classptr;

            this->_tamanho += 1;
            return;
        }
        else
        {
            Classptr = new Elemento<T>(dado);

            Classptr->proximo = this->_primeiro;

            this->_primeiro = Classptr;
            this->_tamanho += 1;
        }

        return;
    };

    /**
     * @brief Insere um item em uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa
     * [0, tamanho].
     *
     * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
     * uma posição já ocupada, a posição do item que já estava naquela posição
     * será posicao + 1; inserir-se na posicao tamanho significa inserir-se no
     * fim da lista.
     * @param dado O item sendo inserido.
     */
    virtual void inserir(std::size_t posicao, T dado)
    {

        if (posicao < 0 || posicao > this->_tamanho)
        {
            throw(ExcecaoPosicaoInvalida());
        }

        if (posicao == this->_tamanho)
        {
            inserirNoFim(dado);
        }
        Elemento<T> *Classptr = nullptr;
        std::size_t Pos = 1;
        Elemento<T> *Seekptr = this->_primeiro;

        Elemento<T> *Temp = nullptr;

        do
        {
            if (Pos == posicao - 1)
            {
                break;
            }
            Seekptr = Seekptr->proximo;
            Pos += 1;
        } while (Seekptr != nullptr);
        Temp = Seekptr->proximo;
        Classptr = new Elemento<T>(dado);
        Classptr->proximo = Temp;
        Seekptr->proximo = Classptr;

        // TODO FINISH THIS
    };

    /**
     * @brief Insere um item no fim da lista.
     *
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado)
    {
        Elemento<T> *TemporaryPtr = nullptr;
        Elemento<T> *Classptr = nullptr;
        Elemento<T> *Selector = nullptr;
        Classptr = new Elemento<T>(dado);

        if (this->_primeiro == nullptr)
        {

            this->_primeiro = Classptr;

            this->_tamanho += 1;
            return;
        }
        else
        {
            Selector = this->_primeiro;
            while (Selector->proximo != nullptr)
            {
                Selector = Selector->proximo;
            }
            Selector->proximo = Classptr;
            this->_tamanho += 1;
        }

        return;
    };

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     *
     * @return O item removido.
     */
    virtual T removerDoInicio()
    {
        // substitua a linha abaixo pelo algoritmo esperado
        return 0;
    };

    /**
     * @brief Remove um item de uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
     *
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    virtual T removerDe(std::size_t posicao)
    {
        // substitua a linha abaixo pelo algoritmo esperado
        return 0;
    };

    /**
     * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     *
     * @return O item removido.
     */
    virtual T removerDoFim()
    {
        // substitua a linha abaixo pelo algoritmo esperado
        return 0;
    };

    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     *
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */
    virtual void remover(T dado) {
        // escreva o algoritmo esperado
    };
};

#endif