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
public:
    virtual ~MinhaArvoreAVL() {
        nukeTree(this->raiz);
    };

    void nukeTree(Nodo<T> *rootptr){

        if (rootptr == nullptr)
        {
            return;
        }

        this->nukeTree(rootptr->filhoEsquerda);
        this->nukeTree(rootptr->filhoDireita);
        delete(rootptr);

        return;
    }

    Nodo<T> *getraiz() const
    {
        return this->raiz;
    }

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

        return recursiveCount(this->raiz);
    };

    int recursiveCount(Nodo<T> *rootptr) const
    {

        if (rootptr == nullptr)
        {
            return 0;
        }

        return recursiveCount(rootptr->filhoEsquerda) + recursiveCount(rootptr->filhoDireita) + 1;
    }

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

        return recursiveContains(this->raiz, chave);
    };
    virtual bool recursiveContains(Nodo<T> *rootptr, T chave) const
    {
        if (rootptr == nullptr)
        {
            return false;
        }

        if (rootptr->chave == chave)
        {
            return true;
        }

        return this->recursiveContains(rootptr->filhoEsquerda, chave) || this->recursiveContains(rootptr->filhoDireita, chave);
    }

    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<int> altura(T chave) const
    {
        // substitua a linha abaixo pelo algoritmo esperado
        return recursiveHeight(this->raiz, chave);
    };

    virtual std::optional<int> recursiveHeight(Nodo<T> *rootptr, T chave) const
    {
        if (rootptr == nullptr)
        {
            return std::nullopt;
        }

        if (rootptr->chave == chave)
        {
            return rootptr->altura;
        }

        std::optional<int> temp;
        temp = recursiveHeight(rootptr->filhoEsquerda, chave);
        if (temp != std::nullopt)
        {
            return temp;
        }
        temp = recursiveHeight(rootptr->filhoDireita, chave);
        if (temp != std::nullopt)
        {
            return temp;
        }

        return std::nullopt;
    };

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */
    virtual void inserir(T chave)
    {

        this->recursiveInsert(this->raiz, chave);
        this->recalcHeight();
    };
    /*

    if insertion point is found

      create new vertex

    if value to be inserted < this key

      go left

    else if value to be inserted > this key

      go right



    else increment frequency
    */
    virtual void recursiveInsert(Nodo<T> *&rootptr, T chave = 0, Nodo<T> *insert = nullptr)
    {
        if (rootptr == nullptr)
        {

            rootptr = new Nodo<T>{chave};

            return;
        }
        if (insert != nullptr)
        {
            if (insert->filhoDireita == rootptr)
            {
                insert->filhoDireita = nullptr;
            }
            if (insert->filhoEsquerda == rootptr)
            {
                insert->filhoEsquerda = nullptr;
            }

            if (rootptr->chave >= insert->chave)
            {
                rootptr->filhoEsquerda = insert;
            }
            else
            {
                rootptr->filhoDireita = insert;
            }
        }
        else
        {
            if (rootptr->chave < chave)
            {
                this->recursiveInsert(rootptr->filhoDireita, chave);
            }
            if (rootptr->chave >= chave)
            {
                this->recursiveInsert(rootptr->filhoEsquerda, chave);
            }
        }

        rootptr->altura = 1 + this->max(this->getHeight(rootptr->filhoEsquerda), this->getHeight(rootptr->filhoDireita));

        int balance = this->getBalanceFactor(rootptr);
        int Lbalance = this->getBalanceFactor(rootptr->filhoEsquerda);
        int Rbalance = this->getBalanceFactor(rootptr->filhoDireita);

        if (balance > 1 && Lbalance >= 0) // LL
        {
            this->rotateRight(rootptr);
            return;
        }

        if (balance > 1 && Lbalance < 0) // LR
        {
            rotateLeft(rootptr->filhoEsquerda);
            rotateRight(rootptr);
            return;
        }

        if (balance < -1 && Rbalance <= 0) // RR
        {
            this->rotateLeft(rootptr);
            return;
        }

        if (balance < -1 && Rbalance > 0) // RL
        {
            rotateRight(rootptr->filhoDireita);
            rotateLeft(rootptr);
            return;
        }
    }

    virtual void recalcHeight()
    {
        recursiveRecalcHeight(this->raiz);
    }

    int getHeight(Nodo<T> *rootptr) const
    {
        if (rootptr == nullptr)
        {
            return -1;
        }
        return rootptr->altura;
    }

    virtual int recursiveRecalcHeight(Nodo<T> *&rootptr)
    {
        if (rootptr == nullptr)
        {
            return -1;
        }
        rootptr->altura = this->max(this->recursiveRecalcHeight(rootptr->filhoEsquerda), this->recursiveRecalcHeight(rootptr->filhoDireita)) + 1;
        return rootptr->altura;
    }

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     */
    virtual void remover(T chave)
    {
        recursiveRemove(this->raiz, chave, this->raiz);
        this->recalcHeight();
    };

    void recursiveRemove(Nodo<T> *rootptr, T chave,Nodo<T> *&parentptr)
    {
        if (rootptr == nullptr)
        {
            return;
        }
        
        
        Nodo<T> *temp = nullptr;

        if (rootptr->chave < chave)
        {
            this->recursiveRemove(rootptr->filhoDireita, chave,rootptr->filhoDireita);
        }
        else if (rootptr->chave > chave)
        {
            this->recursiveRemove(rootptr->filhoEsquerda, chave, rootptr->filhoEsquerda);
        }
        else if (rootptr->chave == chave)
        {
            if (this->raiz == rootptr && rootptr->filhoDireita == nullptr && rootptr->filhoEsquerda == nullptr)
            {
                delete(rootptr);
                this->raiz = nullptr;
                return;
            }
            
            
            if (rootptr->filhoEsquerda == nullptr)
            {
                temp = rootptr->filhoDireita;
                if (temp != nullptr)
                {
                    if (temp->filhoDireita == temp)
                    {
                        temp->filhoDireita = nullptr;
                    }
                }
                
                delete(rootptr);

                parentptr = temp;
                return;
            }

            if (rootptr->filhoDireita == nullptr)
            {
                temp = rootptr->filhoEsquerda;
                if (temp != nullptr)
                {
                    if (temp->filhoEsquerda == temp)
                    {
                        temp->filhoEsquerda = nullptr;
                    }
                }

                delete (rootptr);

                parentptr = temp;
                return;
            }

            temp = this->recursiveSmallestChild(rootptr->filhoDireita);
            rootptr->chave = temp->chave;
            this->recursiveRemove(rootptr->filhoDireita, temp->chave, rootptr->filhoDireita);
        }


        ;

        rootptr->altura = 1 + this->max(this->getHeight(rootptr->filhoEsquerda), this->getHeight(rootptr->filhoDireita));

        int balance = this->getBalanceFactor(rootptr);
        int Lbalance = this->getBalanceFactor(rootptr->filhoEsquerda);
        int Rbalance = this->getBalanceFactor(rootptr->filhoDireita);

        if (balance > 1 && Lbalance >= 0) // LL
        {
            this->rotateRight(parentptr);
            return;
        }

        if (balance > 1 && Lbalance < 0) // LR
        {
            rotateLeft(parentptr->filhoEsquerda);
            rotateRight(parentptr);
            return;
        }

        if (balance < -1 && Rbalance <= 0) // RR
        {
            this->rotateLeft(parentptr);
            return;
        }

        if (balance < -1 && Rbalance > 0) // RL
        {
            rotateRight(parentptr->filhoDireita);
            rotateLeft(parentptr);
            return;
        }
    };

    /**
     * @brief finds the smallest child in a tree (including children) returns
     * @param root of the tree
     */
    virtual int smallest()
    {
        Nodo<T> *smallest = recursiveSmallestChild(this->raiz);

        return smallest->chave;
    }

    virtual Nodo<T> *recursiveSmallestChild(Nodo<T> *&rootptr)
    {
        // if (rootptr == nullptr)
        // {
        //     return nullptr;
        // }

        // Nodo<T> *smallest = nullptr;
        // Nodo<T> *temp = nullptr;

        // temp = recursiveSmallestChild(rootptr->filhoEsquerda);
        // smallest = temp;
        // if (temp == nullptr)
        // {

        //     temp = recursiveSmallestChild(rootptr->filhoDireita);
        //     if (temp == nullptr)
        //     {
        //         return rootptr;
        //     }
        //     if (smallest != nullptr)
        //     {
        //         if (smallest->chave > temp->chave)
        //         {
        //             smallest = temp;
        //         }
        //     }
        //     else if (rootptr->filhoDireita)
        //     {
                
        //     }
        


        // }

        // if (rootptr->chave < smallest->chave)
        // {
        //     smallest = rootptr;
        // }

        // return smallest;

        Nodo<T> *smallest = rootptr;
        while (smallest->filhoEsquerda != nullptr)
        {
            smallest = smallest->filhoEsquerda;
        }
        return smallest;

    }

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

        Nodo<T> *temp = recursiveConstFind(this->raiz, chave);
        if (temp->filhoEsquerda == nullptr)
        {
            return std::nullopt;
        }

        return temp->filhoEsquerda->chave;
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

        Nodo<T> *temp = recursiveConstFind(this->raiz, chave);
        if (temp->filhoDireita == nullptr)
        {
            return std::nullopt;
        }
        return temp->filhoDireita->chave;
    };

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *emOrdem() const
    {
        MinhaListaEncadeada<T> *List = new MinhaListaEncadeada<T>();
        this->recursiveInOrder(this->raiz, List);
        return List;
    };

    virtual void recursiveInOrder(Nodo<T> *rootptr, MinhaListaEncadeada<T> *List) const
    {
        if (rootptr == nullptr)
        {
            return;
        }

        this->recursiveInOrder(rootptr->filhoEsquerda, List);
        List->inserirNoFim(rootptr->chave);
        this->recursiveInOrder(rootptr->filhoDireita, List);

        return;
    };

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *preOrdem() const
    {
        MinhaListaEncadeada<T> *List = new MinhaListaEncadeada<T>();
        this->recursivePreOrder(this->raiz, List);
        return List;
    };

    virtual void recursivePreOrder(Nodo<T> *rootptr, MinhaListaEncadeada<T> *List) const
    {
        if (rootptr == nullptr)
        {
            return;
        }

        List->inserirNoFim(rootptr->chave);
        this->recursivePreOrder(rootptr->filhoEsquerda, List);
        this->recursivePreOrder(rootptr->filhoDireita, List);

        return;
    };

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *posOrdem() const
    {
        MinhaListaEncadeada<T> *List = new MinhaListaEncadeada<T>();
        this->recursivePostOrder(this->raiz, List);
        return List;
    };

    virtual void recursivePostOrder(Nodo<T> *rootptr, MinhaListaEncadeada<T> *List) const
    {
        if (rootptr == nullptr)
        {
            return;
        }

        this->recursivePostOrder(rootptr->filhoEsquerda, List);
        this->recursivePostOrder(rootptr->filhoDireita, List);
        List->inserirNoFim(rootptr->chave);

        return;
    };

    virtual int max(int a, int b)
    {
        if (a > b)
        {
            return a;
        }
        return b;
    }

    Nodo<T> *recursiveConstFind(Nodo<T> *rootptr, T chave) const
    {
        if (rootptr == nullptr)
        {
            return nullptr;
        }

        if (rootptr->chave == chave)
        {
            return rootptr;
        }

        Nodo<T> *temp = nullptr;
        temp = this->recursiveConstFind(rootptr->filhoEsquerda, chave);
        if (temp != nullptr)
        {
            return temp;
        }

        temp = this->recursiveConstFind(rootptr->filhoDireita, chave);
        if (temp != nullptr)
        {
            return temp;
        }
        return nullptr;
    }

    int getBalanceFactor(Nodo<T> *&rootptr)
    {
        if (rootptr == nullptr)
        {
            return 0;
        }
        return getHeight(rootptr->filhoEsquerda) - getHeight(rootptr->filhoDireita);
    }
    void rotateRight(Nodo<T> *&rootptr)
    {
        Nodo<T> *&leftnode = rootptr->filhoEsquerda;
        Nodo<T> *T2 = leftnode->filhoDireita;
        Nodo<T> *&T3 = rootptr->filhoEsquerda;

        leftnode->filhoDireita = rootptr;
        rootptr = leftnode;
        T3 = T2;

        return;
    }
    void rotateLeft(Nodo<T> *&rootptr)
    {
        Nodo<T> *&rightnode = rootptr->filhoDireita;
        Nodo<T> *T2 = rightnode->filhoEsquerda;
        Nodo<T> *&T3 = rootptr->filhoDireita;

        rightnode->filhoEsquerda = rootptr;
        rootptr = rightnode;
        T3 = T2;

        return;
    }

};

#endif