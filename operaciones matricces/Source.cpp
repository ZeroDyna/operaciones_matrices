#include<iostream>
#include<vector>
struct node_a {
	int a;
	node_a* nodes[2];
	node_a(int v) {
		a = v;
		nodes[0] = 0;
		nodes[1] = 0;
	}
};
struct arbol {
	node_a* root = 0;
	void find(int v) {

	}
	void insert(){

	}
};
template <class T>
struct node {
	node<T>* nodes[2];
	T value;
	T pos_x;
	T pos_y;
	node(T val,node* down = 0,node*  right = 0, T x = 0, T y = 0) {
		pos_x = x;
		pos_y = y;
		value = val;
		nodes[0] = down;
		nodes[1] = right;
	}
};

class SMatrix {
public:
	int x;
	int y;
	node<int>** arrx;
	node<int>** arry;
	SMatrix(int s1, int s2) {
		x = s1;
		y = s2;
		arrx = new node<int>* [x];
		arry = new node<int>* [y];
		for (int i = 0; i < x; i++) {
			arrx[i] = nullptr;
		}
		for (int i = 0; i < y; i++) {
			arry[i] = nullptr;
		}
	}
	bool find_x(node<int>**& rec, int x_1, int y_1) {
		rec = &(arrx[x_1 - 1]);
		while (*rec && (*rec)->pos_y < y_1) {
			rec = &(*rec)->nodes[0];
		}
		return (*rec) && (*rec)->pos_y == y_1;
	}

	bool find_y(node<int>**& rec, int x_1, int y_1) {
		rec = &(arry[y_1 - 1]);
		while (*rec && (*rec)->pos_x < x_1) {
			rec = &(*rec)->nodes[1];
		}
		return (*rec) && (*rec)->pos_x == x_1;
	}
	
	bool insert(int v, int x , int y) {
		node<int>** p;
		node<int>** q;
		if (!find_x(p, x, y) && !find_y(q, x, y))
		{
			node<int>* r = new node<int>(v,0,0, x, y);
			r->nodes[1] = *p;
			r->nodes[0] = *q;
			*p = r;
			*q = r;
			return 1;
		}
		else{
			(*p)->value = v;
		}
	}
	int get(int x, int y) {
		node<int>** p;
		if (find_x(p, x, y)) return (*p)->value;
		return 0;
	}
	void remove(int x , int y) {
		node<int>** p;
		node<int>** q;
		if (find_x(p, x, y) && find_y(q, x , y)) {
			node<int>* aux = *p;
			*p = aux->nodes[0];
			*q = aux->nodes[1];
			delete aux;
		}
	}
	void set(int z, int x, int y) {
		node<int>** p;

		if (find_x(p, x, y)) {
			if (z == 0) {
				remove(x, y);
			}
			else {
				(*p)->value = z;
			}
		}
		else if(!find_x(p,x,y)) {
			insert(z, x, y);
		}
	}
	struct obj
	{
		int x;
		int y;
		SMatrix* m;
		obj(int x_, int y_, SMatrix l) {
			x = x_;
			y = y_;
			m = &l;
		}
		operator int() {
			return m->get(x, y);
		}
	};
	obj operator()(int x , int y) {
		obj a (x, y, *this);
		return a;
	}
};
void multiplicar(SMatrix* a, SMatrix* b, SMatrix* r) {
	if (a->y != b->x)
		return;
	else {
		node<int>** c = a->arry;
		node<int>** d = b->arrx;
		for (int i = 1; i <= a->x; i++) { // iterar sobre filas de a
			for (int j = 1; j <= b->y; j++) { // iterar sobre columnas de b
				int sum = 0;
				for (int k = 1; k <= a->y; k++) { // iterar sobre columnas de `a` y filas de `b`
					sum += a->get(i, k) * b->get(k, j);
				}
				r->insert(sum, i, j);
			}
		}


	}
}
void sumar(SMatrix* a, SMatrix* b, SMatrix* r) {
	if (a->x != b->x || a->y != b->y) {
		return;
	}
	else {
		for (int i = 1; i <= a->x; i++) {
			for (int j = 1; j <= a->y; j++) {
				int suma = a->get(i, j) + b->get(i, j);
				r->set(suma, i, j);
			}
		}
	}
}
int main() {
	// Create two matrices
	SMatrix matrix1(3, 3);
	SMatrix matrix2(3, 3);

	// Set values for the first matrix
	matrix1.set(1, 1, 1);
	matrix1.set(2, 1, 2);
	matrix1.set(3, 1, 3);
	matrix1.set(4, 2, 1);
	matrix1.set(5, 2, 2);
	matrix1.set(6, 2, 3);
	matrix1.set(7, 3, 1);
	matrix1.set(8, 3, 2);
	matrix1.set(9, 3, 3);

	// Set values for the second matrix
	matrix2.set(9, 1, 1);
	matrix2.set(8, 1, 2);
	matrix2.set(7, 1, 3);
	matrix2.set(6, 2, 1);
	matrix2.set(5, 2, 2);
	matrix2.set(4, 2, 3);
	matrix2.set(3, 3, 1);
	matrix2.set(2, 3, 2);
	matrix2.set(1, 3, 3);

	// Create a result matrix
	SMatrix result(3, 3);

	// Multiply the two matrices
	multiplicar(&matrix1, &matrix2, &result);

	// Print the resulting matrix
	std::cout << "Resulting matrix after multiplication:" << std::endl;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			std::cout << result.get(i, j) << " ";
		}
		std::cout << std::endl;
	}
	// Create a result matrix
	SMatrix suma(3, 3);

	// Multiply the two matrices
	sumar(&matrix1, &matrix2, &suma);
	std::cout << "Resulting matrix after suma:" << std::endl;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			std::cout << suma.get(i, j) << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}