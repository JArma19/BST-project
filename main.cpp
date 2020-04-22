#include <iostream>
#include "bst.h"
using namespace std;

/**
 * Funtore per il confronto tra interi
 * @brief Funtore per il confronto tra interi
 */
struct compare_int
{
	bool operator()(int a, int b) const
	{
		return a < b;
	}
};

/**
 * Funtore per l'uguaglianza tra interi 
 * @brief Funtore per l'uguaglianza tra interi
 */
struct equal_int
{
	bool operator()(int a, int b) const
	{
		return a == b;
	}
};

/**
 * Funtore predicato per verificare se un intero è dispari. 
 * Usato come predicato per la funzione printIF
 * @brief Funtore per verificare se un intero è dispari
 */
struct pred_odd
{
	bool operator()(int a) const
	{
		return a%2 == 1;
	}
};

/**
 * Struct che implementa un punto in uno spazio 2D. 
 * Usato come tipo custom per testare la classe binary_search_tree
 * @brief punto in spazio 2D
 */
struct point 
{
	int x; ///< coordinata x del punto
	int y; ///< coordinata y del punto
	point(int xx, int yy) : x(xx), y(yy) {}
};

/**
 * Funtore per il confronto di due punti 
 * Ritorna true se p1.x < p2.x
 * @brief Funtore per il confronto di due punti
*/
struct compare_point 
{
	bool operator()(const point &p1, const point &p2) const 
	{
		return p1.x < p2.x;
	} 
};

/**
 * Funtore per il confronto di uguaglianza tra due punti
 * Ritorna true se p1 e p2 hanno entrambe le coordinate uguali
 * @brief Funtore per il confronto di due punti
*/
struct equal_point 
{
	bool operator()(const point &p1, const point &p2) const 
	{
		return (p1.x == p2.x) && (p1.y == p2.y);
	} 
};

/**
 * Funtore predicato che verificare se un punto giace su uno dei due assi
 * Usato come predicato per la funzione printIF
 * @brief Funtore per verificare se un punto giace su uno dei due assi
 */
struct axis_zero
{
	bool operator()(const point &p)
	{
		return p.x == 0 || p.y == 0;
	}
};

/**
 * Ridefinizione dell'operatore di stream << per un point
*/
ostream &operator<<(ostream &os, const point &p) 
{
	cout << "(" << p.x << "," << p.y << ")";
	return os;
};

typedef binary_search_tree<int,compare_int,equal_int> bst_int;
typedef binary_search_tree<point,compare_point,equal_point> bst_point;

//Prototipi
void test_metodi_fondamentali_int();
void test_uso_int(bst_int &other);
void test_uso_const_int(const bst_int &other);
void test_metodi_fondamentali_point();
void test_uso_point(bst_point &other);
void test_uso_const_point(const bst_point &other);

int main() 
{	
	test_metodi_fondamentali_int();
	bst_int a;
	test_uso_int(a);
	test_uso_const_int(a);

	test_metodi_fondamentali_point();
	bst_point b;
	test_uso_point(b);
	test_uso_const_point(b);
	
	return 0;
}

void test_metodi_fondamentali_int()
{
	cout << "***********TEST METODI FONDAMENTALI SU BST DI INT***********" << endl;
	//Costruttore
	bst_int bst;
	bst.insert(10);
	bst.insert(3);
	bst.insert(2);
	bst.insert(5);
	bst.insert(17);
	cout << "bst: " << endl << bst << endl;

	//Costruttore di copia
	bst_int bst2(bst);
	cout << "bst2: " << endl << bst2 << endl;

	//Operatore =
	bst_int bst3;
	bst3 = bst;
	cout << "bst3: " << endl << bst3 << endl;
}

void test_uso_int(bst_int &other)
{
	cout << "***********TEST USO BST DI INT***********" << endl;

	cout << "Inserimento valori 10,15,11,5,17" << endl;
	other.insert(10);
	other.insert(15);
	other.insert(11);
	other.insert(5);
	other.insert(17);
	cout << endl;

	cout << "Inserimento duplicato" << endl;
	other.insert(17);
	cout << endl;

	cout << "Dimensione albero: " << other.size() << endl;

	cout << "Controllo esistenza valore 11: " << other.contains(11) << endl;

	cout << "Stampa con iteratori: " << endl;
	bst_int::const_iterator it, it_end;
	it = other.begin();
	it_end = other.end();	
	while(it != it_end)
	{
		cout << *it << endl;
		++it;
	}

	cout << endl << "Stampa con operator<<: " << endl;
	cout << other << endl;

	cout << "Stampa con print(): " << endl;
	other.print();

	cout << endl << "Subtree(15): " << endl;
	bst_int tmp = other.subtree(15);
	cout << tmp << endl;

	cout << "PrintIF numeri dispari: " << endl;
	printIF<pred_odd>(other);
}

void test_uso_const_int(const bst_int &other)
{
	cout << "***********TEST USO CONST BST DI INT***********" << endl;

	cout << "Non posso inserire perchè parametro const" << endl;
	
	cout << "Dimensione albero: " << other.size() << endl;

	cout << "Controllo esistenza valore 11: " << other.contains(11) << endl;

	cout << "Stampa con iteratori: " << endl;
	bst_int::const_iterator it, it_end;
	it = other.begin();
	it_end = other.end();
	while(it != it_end)
	{
		cout << *it << endl;
		++it;
	}

	cout << endl << "Stampa con operator<<: " << endl;
	cout << other << endl;

	cout << "Stampa con print(): " << endl;
	other.print();

	cout << endl << "Subtree(15): " << endl;
	bst_int tmp = other.subtree(15);
	cout << tmp << endl;

	cout << "PrintIF numeri dispari: " << endl;
	printIF<pred_odd>(other);

}

void test_metodi_fondamentali_point()
{
	cout << "***********TEST METODI FONDAMENTALI SU BST DI POINT***********" << endl;
	//Costruttore
	bst_point bst;
	bst.insert(point(1,2));
	bst.insert(point(0,3));
	bst.insert(point(7,0));
	bst.insert(point(5,4));
	bst.insert(point(3,8));
	cout << "bst: " << endl << bst << endl;

	//Costruttore di copia
	bst_point bst2(bst);
	cout << "bst2: " << endl << bst2 << endl;

	//Operatore =
	bst_point bst3;
	bst3 = bst;
	cout << "bst3: " << endl << bst3 << endl;

}

void test_uso_point(bst_point &other)
{
	cout << "***********TEST USO BST DI POINT***********" << endl;

	cout << "Inserimento punti (3,11) (0,3) (8,1) (1,4) (7,8)" << endl;
	other.insert(point(3,11));
	other.insert(point(0,3));
	other.insert(point(8,1));
	other.insert(point(1,4));
	other.insert(point(7,8));

	cout << endl;
	cout << "Inserimento duplicato" << endl;
	other.insert(point(1,4));
	cout << endl;
	
	cout << "Dimensione albero: " << other.size() << endl;

	cout << "Controllo esistenza punto(3,2): " << other.contains(point(3,2)) << endl;

	cout << "Stampa con iteratori: " << endl;
	bst_point::const_iterator it, it_end;
	it = other.begin();
	it_end = other.end();
	while(it != it_end)
	{
		cout << *it << endl;
		++it;
	}

	cout << endl << "Stampa con operator<<: " << endl;
	cout << other << endl;

	cout << "Stampa con print(): " << endl;
	other.print();

	cout << endl << "Subtree((0,3)): " << endl;
	bst_point tmp = other.subtree(point(0,3));
	cout << tmp << endl;

	cout << "PrintIF punti che appartengono a uno dei due assi: " << endl;
	printIF<axis_zero>(other);

}

void test_uso_const_point(const bst_point &other)
{
	cout << "***********TEST USO CONST BST DI POINT***********" << endl;

	cout << "Non posso inserire perchè parametro const" << endl;
	
	cout << "Dimensione albero: " << other.size() << endl;

	cout << "Controllo esistenza punto(3,2): " << other.contains(point(3,2)) << endl;

	cout << "Stampa con iteratori: " << endl;
	bst_point::const_iterator it, it_end;
	it = other.begin();
	it_end = other.end();
	while(it != it_end)
	{
		cout << *it << endl;
		++it;
	}

	cout << endl << "Stampa con operator<<: " << endl;
	cout << other << endl;

	cout << "Stampa con print(): " << endl;
	other.print();

	cout << endl << "Subtree((0,3)): " << endl;
	bst_point tmp = other.subtree(point(0,3));
	cout << tmp << endl;

	cout << "PrintIF punti che appartengono a uno dei due assi: " << endl;
	printIF<axis_zero>(other);
}