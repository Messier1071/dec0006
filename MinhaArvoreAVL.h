#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"

/**
 * @brief Representa uma árvore AVL.
 *
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
    virtual ~MinhaArvoreAVL() {
        // escreva o algoritmo esperado
    };

    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
    virtual bool vazia() const
    {
        if (this->raiz == nullptr)
        {
            return true;
        }

        return false;
    };

    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    virtual int quantidade() const
    {
        if (this->vazia())
        {
            return 0;
        }

        return -1;
    };

    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    virtual bool contem(T chave) const
    {
        if (this->vazia())
        {
            return false;
        }

        return false;
    };

    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<int> altura(T chave) const
    {
        // substitua a linha abaixo pelo algoritmo esperado
        return std::nullopt;
    };

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */
    virtual void inserir(T chave)
    {
        /*

if insertion point is found

  create new vertex

if value to be inserted < this key

  go left

else if value to be inserted > this key

  go right

else increment frequency
*/

        if (this->vazia())
        {
            this->raiz = new Nodo<T>{chave};
            return;
        }
        Nodo<T> *Searchptr = this->raiz;
        Nodo<T> **InsertionPoint = nullptr;
        while (InsertionPoint == nullptr)
        {
            if (Searchptr->chave < chave)
            {
                if (Searchptr->filhoEsquerda == nullptr)
                {
                    InsertionPoint = &Searchptr->filhoEsquerda;
                }
                else
                {
                    Searchptr = Searchptr->filhoEsquerda;
                }
            }
            if (Searchptr->chave >= chave)
            {
                if (Searchptr->filhoDireita == nullptr)
                {
                    InsertionPoint = &Searchptr->filhoDireita;
                }
                else
                {
                    Searchptr = Searchptr->filhoEsquerda;
                }
            }

            if (Searchptr == nullptr)
            {
                break;
            }
        }
        *InsertionPoint = new Nodo<T>{chave};
    };

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     */
    virtual void remover(T chave) {
        // escreva o algoritmo esperado
    };

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<T> filhoEsquerdaDe(T chave) const
    {
        if (this->vazia())
        {
            return std::nullopt;
        }

        return std::nullopt;
    };

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */
    virtual std::optional<T> filhoDireitaDe(T chave) const
    {
        if (this->vazia())
        {
            return std::nullopt;
        }

        return std::nullopt;
    };

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *emOrdem() const
    {
        MinhaListaEncadeada<T> *List = new MinhaListaEncadeada<T>();

        return List;
    };

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *preOrdem() const
    {
        MinhaListaEncadeada<T> *List = new MinhaListaEncadeada<T>();

        return List;
    };

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *posOrdem() const
    {
        MinhaListaEncadeada<T> *List = new MinhaListaEncadeada<T>();

        return List;
    };
};

#endif