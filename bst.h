#ifndef BST_H
#define BST_H

#include <ostream>
#include <iterator> 
#include <cstddef> 
#include "exceptionbst.h"

/**
 * @file bst.h
 */

/**
 * 
 * @author Armanini Justin
 * 
 * @section Description 
 * Classe che implementa un albero binario di ricerca che contiene dati generici T.
 * 
 * @brief Albero binario di ricerca (bst)
 *  
 * @param T tipo del dato
 * @param C funtore di comparazione (<) di due dati
 * @param E funtore di comparazione (==) di due dati
 */

template <typename T, typename C, typename E>
class binary_search_tree 
{
	/**
	 * Struct che implementa un nodo dell'albero.
	 * 
	 * @brief Nodo dell'albero
	 */
	struct node
	{
		T value;
		node* parent;
		node* left_child;
		node* right_child;

		/**
		 * Costruttore di default
		 */
		node() : parent(nullptr), left_child(nullptr), right_child(nullptr) {}

		/**
		 * Costruttore che inizializza un nodo che contiente il dato x
		 * @param x dato contenuto del nodo inizializzato
		 */
		node(const T &x) : value(x), parent(nullptr), left_child(nullptr), right_child(nullptr) {}

		/**
		 * Distruttore
		 */
		~node()
		{
			parent = nullptr; 
			left_child = nullptr;
			right_child = nullptr;
		}

		// Copy constructor e Operatore di assegnamento di default

	}; //struct node

	node* _root; ///< puntatore alla radice dell'albero
	unsigned int _size; ///< numero di elementi di tipo T che compongono l'albero
	C _cmp; ///< oggetto funtore per relazione di ordinamento di tipo C
	E _eq; ///< oggetto funtore per relazione di uguaglianza di tipo E

	/**
	 * Metodo helper che inserisce ciascun nodo dell'albero radicato nel nodo x in this
	 * @param x radice dell'albero da cui inserire i nodi
	 */
	void helper_copy_tree(const node *x) 
	{
		if(x != nullptr)
		{
			insert(x->value);
			helper_copy_tree(x->left_child);
			helper_copy_tree(x->right_child);
		}
	}

	/**
	 * Metodo helper che rimuove ricorsivamente i nodi dell'albero radicato nel nodo x, compreso x stesso
	 * @param x nodo da rimuovere
	 */
	void remove_helper(node *x)
	{
		if(x != nullptr)
		{
			remove_helper(x->left_child);
			remove_helper(x->right_child);
			delete x;
			x = nullptr;
			_size--;
		}
	}

	/**
	 * Metodo helper che ritorna puntatore al nodo dell'albero che contiene elemento x 
	 * @param x elemento da cercare nell'albero
	 * @return nodo puntatore al nodo che contiene elemento x
	 */
	node* find_helper(const T &x) const
	{
		node *tmp = _root;
		while(tmp != nullptr)
		{
			if(_eq(tmp->value,x))
				return tmp;
			else 
				if(_cmp(tmp->value,x)) // <
					tmp = tmp->right_child;
				else
					tmp = tmp->left_child;
		}
		return nullptr; // x non trovato
	}

	/**
	 * Metodo helper che stampa ricorsivamente in order i nodi dell'albero radicato in x
	 * @param x radice dell'albero da stampare
	 */
	void print_helper(const node* x) const
	{
		if(x != nullptr)
		{
			print_helper(x->left_child);
			std::cout << x->value << std::endl;
			print_helper(x->right_child);
		}
	}

public:
	
	/**
	 * Costruttore di default
	 */
	binary_search_tree() : _root(nullptr), _size(0) {}

	/**
	 * Costruttore di copia
	 * @param other bst da copiare
	 */
	binary_search_tree(const binary_search_tree &other) : _root(nullptr), _size(0)
	{
		helper_copy_tree(other._root);
	}
	
	/**
	 * Operatore di assegnamento
	 * @param other bst da copiare
	 * @return reference a this
	 */
	binary_search_tree &operator=(const binary_search_tree &other)
	{
		if(this != &other) //evito self-assignment
		{
			binary_search_tree tmp(other);
			std::swap(this->_root,tmp._root);
			std::swap(this->_size,tmp._size);
		}
		return *this;
	}

	/**
	 * Distruttore
	 */
	~binary_search_tree()
	{
		remove_helper(_root);
	}

	/**
	 * Metodo che ritorna il numero di elementi (_size)
	 * @return numero elementi in this
	 */
	unsigned int size() const
	{
		return _size;
	}

	/**
	 * Metodo che inserisce elemento x nel bst, solo se non esiste già un nodo che contiene quell'elemento
	 * @param x elemento da inserire
	 * @throw eccezione nel caso si cerchi di inserire un elemento già presente
	 */
	void insert(const T &x)
	{
		try
		{
			node *tmp = _root;
			node *parent = nullptr;

			while(tmp != nullptr)
			{
				parent = tmp;
				if(_eq(tmp->value,x))
					throw duplicated_value("Elemento già inserito nell'albero");
				
				else
					if(_cmp(tmp->value, x)) // <
						tmp = tmp->right_child;
					else
						tmp = tmp->left_child;
			}

			node *new_node = new node(x);
			//Albero vuoto
			if(parent == nullptr)
				_root = new_node;
			else
			{
				if(_cmp(parent->value,new_node->value)) //parent < new_node
					parent->right_child = new_node;
				else
					parent->left_child = new_node;
				
				new_node->parent = parent;  
			}    
			_size++;
		}
		catch(duplicated_value &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	/**
	 * Metodo che controlla l'esistenza di un elemento nel bst
	 * @param x elemento di cui verificare l'esistenza
	 * @return true se esiste nodo che contiene x
	 */
	bool contains(const T &x) const
	{
		if(find_helper(x) != nullptr) //elemento presente
			return true;
		else
			return false;
	}

	/**
	 * Metodo che dato l'elemento x, restituisce un nuovo albero corrispondente al sottoalbero
	 * radicato nel nodo che contiene l'elemento x
	 * @param x radice del sottoalbero
	 * @return nuovo albero uguale al sottoalbero radicato nel nodo che contiene l'elemento x
	 */
	binary_search_tree subtree(const T &x) const
	{
		binary_search_tree tmp;
		node* pos = find_helper(x); //trovo radice sottoalbero
		tmp.helper_copy_tree(pos); //inserisco i nodi
		return tmp;
	}

	/**
	 * Metodo che stampa il bst in order
	 */
	void print() const
	{
		print_helper(_root);
	}

	/**
	 * Forward iterator di sola lettura
	 * 
	 * @brief forward iterator costante dell'albero
	 */
	class const_iterator 
	{
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;
	
		/**
		 * Costruttore di default
		 */
		const_iterator() : _n(nullptr) {}

		/**
		 * Costruttore di copia
		 */
		const_iterator(const const_iterator &other) : _n(other._n) {}

		/**
		 * Operatore di assegnamento
		 */
		const_iterator& operator=(const const_iterator &other) 
		{
			_n = other._n;
			return *this;
		}

		/**
		 * Distruttore
		 */
		~const_iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const 
		{
			return _n->value;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const 
		{
			return &(_n->value);
		}
		
		// Operatore di iterazione post-incremento
		const_iterator operator++(int) 
		{
			const_iterator tmp(*this);
			next_helper();
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++() 
		{
			next_helper();
			return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const 
		{
			return _n == other._n;
		}
		
		// Diversita'
		bool operator!=(const const_iterator &other) const 
		{
			return _n != other._n;
		}

	private:
		
		const node *_n;

		// Per poter usare il costruttore di inizializzazione nei metodi begin() e end()
		friend class binary_search_tree;

		// Costruttore privato di inizializzazione usato dalla classe container nei metodi begin() e end()
		const_iterator(const node* x) : _n(x) {}

		/**
		 * Metodo helper che visita il bst con visita in order aggiornando di volta in volta l'attributo _n
		 * Si assume che si parta dal nodo più a sx dell'albero
		 */
		void next_helper()
		{
			if(_n != nullptr) //se _n == nullptr o ho finito l'iteratore o l'albero è vuoto, non faccio nulla
			{
				if(_n->parent == nullptr) //nodo radice
					if(_n->right_child != nullptr)
					{
						_n = _n->right_child;
						while(_n->left_child != nullptr)
							_n = _n->left_child;
					}
					else
					{
						_n = nullptr;
					}
				else
				{
					if(_n == _n->parent->left_child)
						if(_n->right_child == nullptr) //non c'è sottoalbero dx, risalgo
						{
							 _n = _n->parent;
						}
						else //visito sottoalbero dx
						{
							_n = _n->right_child;
							while(_n->left_child != nullptr)
								_n = _n->left_child;    
						}

					else if(_n == _n->parent->right_child)
						if(_n->right_child == nullptr) //non c'è sottoalbero dx, risalgo
						{
							while(_n->parent != nullptr && _n == _n->parent->right_child) //shortcut eval
								_n = _n->parent;
							
							_n = _n->parent;
						}
						else //visito sottoalbero dx
						{
							_n = _n->right_child;
							while(_n->left_child != nullptr)
								_n = _n->left_child;
						}     
				}
			}   
		}

		
	}; // class const_iterator
	
	/**
	 * Ritorna l'iteratore al nodo più a sx del bst, in quanto lo si visita in order
	 * @return iteratore al nodo più a sinistra del bst, cioè il minore per elemento contenuto
	 */
	const_iterator begin() const 
	{
		node *tmp = _root;
		if(tmp != nullptr)
			while(tmp->left_child != nullptr)
				tmp = tmp->left_child;

		return const_iterator(tmp);
	}
	
	/**
	 * Ritorna l'iteratore alla fine del bst
	 * @return iteratore alla fine del bst
	 */
	const_iterator end() const 
	{
		return const_iterator(nullptr);
	}
	
}; //class binary search tree


/**
 * Ridefinizione dell'operatore di stream per stampare contenuto dell'albero mediante iteratori
 * @param os oggetto stream di output
 * @param bst albero da stampare
 * @return reference allo stream di output
 */

template <typename T, typename C, typename E> 
std::ostream &operator<<(std::ostream &os, const binary_search_tree<T,C,E> &bst) 
{
	typename binary_search_tree<T,C,E>::const_iterator it,it_end;
	it = bst.begin();
	it_end = bst.end();

	while(it!=it_end) 
	{
		os << *it << std::endl;
		++it;
	}

	return os;
}

/**
 * Funzione globale che stampa tutti i nodi del bst che soddisfano il predicato
 * @param bst albero da stampare
 * @param pred predicato da applicare sui nodi di bst
 */
template < typename P, typename T, typename C, typename E>
void printIF(const binary_search_tree<T,C,E> &bst)
{
	P pred;
	typename binary_search_tree<T,C,E>::const_iterator it,it_end;
	it = bst.begin();
	it_end = bst.end();

	while(it!=it_end) 
	{
		if(pred(*it))
			std::cout << *it << std::endl;
		++it;
	}
} 

#endif