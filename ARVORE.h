#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

/*
Fazer:
    Buscar um número
    Inserir
    Remover
    Liberar

*/
    typedef struct no_Arv{
        int info;
        no_Arv *esq;
        no_Arv *dir;
    } NoArv;

    typedef struct Arvore_Binaria{
        NoArv *Raiz;
    } Arv;

    int VaziaArvore(Arv *A){
        if(A->Raiz == NULL){
            return 1;
        } else{
            return 0;
        }
    }

    Arv *CriaArvore(){
        Arv* a = (Arv*) malloc(sizeof(Arv));
        a->Raiz = NULL;
        return a;
    }

    //Procedimento = 1 --> Pre-Order
    //Procedimento = 2 --> In-Order
    //Procedimento = 3 --> Pos-Order
    void ImprimirArvore(Arv *A, int procedimento){
        if(procedimento == 1){
            auxPreOrder(A->Raiz);
        } else if(procedimento == 2){
            auxInOrder(A->Raiz);
        } else if(procedimento == 3){
            auxPosOrder(A->Raiz);
        } else{
            printf("Procedimento invalido.");
        }
    }

    void auxPreOrder(NoArv *pai){
        printf("%d, ", pai->info);
        if(pai ->dir != NULL){ auxPreOrder(pai ->dir); }
        if(pai ->esq != NULL){ auxPreOrder(pai ->esq); }
    }

    void auxInOrder(NoArv *pai){
        if(pai ->dir != NULL){ auxPreOrder(pai ->dir); }
        printf("%d, ", pai->info);
        if(pai ->esq != NULL){ auxPreOrder(pai ->esq); }
    }

    void auxPosOrder(NoArv *pai){
        if(pai ->dir != NULL){ auxPreOrder(pai ->dir); }
        if(pai ->esq != NULL){ auxPreOrder(pai ->esq); }
        printf("%d, ", pai->info);
    }

    void buscaNum(Arv *A, int num)

#endif // ARVORE_H_INCLUDED
