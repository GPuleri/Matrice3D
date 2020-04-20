#include "Matrice3D.h"

template <typename T>
struct punto {
	T x; ///< coordinata x del punto
	T y; ///< coordinata y del punto
	punto() : x(), y() {}
	punto(T xy) : x(xy), y(xy) {}
	punto(T x1, T y1) : x(x1), y(y1) {}
	
	T get_x() const { return x; }
	T get_y() const { return y; }
	
	punto operator+(const T &val) {
		punto tmp(get_x() + val, get_y() + val);
		return tmp;
	}
	
	template <typename Q>
	punto(const punto<Q> &other) {
		this->x = static_cast<T>(other.x);
		this->y = static_cast<T>(other.y);
	}
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const punto<T> &p) {
	std::cout<<"("<<p.x<<" , "<<p.y<<")";
	return os;
}

template <typename T>
struct add_42 {
	T operator() (T &x) const {
		return x + 42; 
	}
};

void test_2d_primitivi(int y, int x);

void test_2d_custom(int y, int x);

void test_3d_primitivi(int z, int y, int x);

void test_3d_custom(int z, int y, int x);

int main() {

	int z = 2;
	int y = 2;
	int x = 2;
	
	test_2d_primitivi(y,x);
	
	std::cout<<std::endl<<std::endl;
	
	test_2d_custom(y,x);
	
	std::cout<<std::endl<<std::endl;
	
	test_3d_primitivi(z,y,x);
	
	std::cout<<std::endl<<std::endl;
	
	test_3d_custom(z,y,x);
	
	return 0;
}

void test_2d_primitivi(int y, int x) {
	
	std::cout<<"****TEST 2D PRIMITIVI****"<<std::endl<<std::endl;
	//costruttore default
	Matrice2D<int> m1();
	
	//costruttore secondario
	Matrice2D<int> m2(y, x);
	m2(0,0)=1;
	m2(0,1)=2;
	//m2(1,0)=3;
	m2(1,1)=4;
	
	//stampa size
	std::cout<<"size m2: "<<m2.get_size()<<std::endl;
	
	std::cout<<std::endl;
	
	//stampa m2
	std::cout<<"stampa m2: "<<m2;
	
	std::cout<<std::endl;
	
	//scrittura cella
	m2(0,0)=m2(1,1);
	std::cout<<"cella (0,0) sovrascritta con cella (1,1)";
	
	std::cout<<std::endl<<std::endl;
	
	std::cout<<"stampa m2 (1->4): "<<m2;
	m2(0,0)=1;
	
	std::cout<<std::endl;
	
	//costruttore secondario
	Matrice2D<int> m3(y, x, 9);
	std::cout<<"stampa m3: "<<m3;
	
	std::cout<<std::endl;
	
	//costruttore copia
	Matrice2D<int> m4(m2);
	std::cout<<"stampa m4: "<<m4;
	
	std::cout<<std::endl;
	
	//operator =
	Matrice2D<int> m5;
	m5 = m2;
	std::cout<<"stampa m5: "<<m5;
	
	std::cout<<std::endl;
	
	//iteratore 
	Matrice2D<int>::iterator i,ie;
	std::cout<<"stampa m5 (iteratore):"<<std::endl;
	for(i = m5.begin(), ie = m5.end(); i != ie; ++i)
		if(i.is_filled())
			std::cout << *i << std::endl;
	
	std::cout<<std::endl<<std::endl;
			
	//iteratore const
	Matrice2D<int>::const_iterator f,fe;
	std::cout<<"stampa m5 (iteratore const):"<<std::endl;
	for(f = m5.cbegin(), fe = m5.cend(); f != fe; ++f)
		if(f.is_filled())
			std::cout << *f << std::endl;

	std::cout<<std::endl<<std::endl;
	
	//conversione
	Matrice2D<double> m6(y,x);	
	m6(0,0)=18.3;
	m6(0,1)=7.2;
	m6(1,0)=4.6;
	m6(1,1)=2.9;

	Matrice2D<int> m7(m6);
	//m6=(Matrice2D<int>)m6;  //in alternativa
	std::cout<<"stampa m6 (double): ";
	std::cout<<m6;
	
	std::cout<<std::endl;

	//stampa conversione
	std::cout<<"stampa m7 (m6 convertito in int): ";
	std::cout<<m7;
	
	std::cout<<std::endl;
	
	//funtore
	add_42<double> fun;
	Matrice2D<int> m8;
	m8=trasforma<int>(m6, fun); 
	
	std::cout<<"stampa m8 (m6 con funtore (+42) e convertito in int): ";
	std::cout<<m8;
	
	std::cout<<std::endl;
}

void test_2d_custom(int y, int x) {
	
	std::cout<<"****TEST 2D CUSTOM****"<<std::endl<<std::endl;
	//costruttore default
	Matrice2D< punto<int> > m1();
	
	//costruttore secondario
	Matrice2D< punto<int> > m2(y, x);
	m2(0,0) = punto<int>(1,1);
	//m2(0,1) = punto<int>(2,2);
	m2(1,0) = punto<int>(3,3);
	m2(1,1) = punto<int>(4,4);
	
	//stampa size
	std::cout<<"size m2: "<<m2.get_size()<<std::endl;
	
	std::cout<<std::endl;
	
	//stampa m2
	std::cout<<"stampa m2: "<<m2;
	
	std::cout<<std::endl;
	
	//scrittura cella
	m2(0,0) = m2(1,1);
	std::cout<<"cella (0,0) sovrascritta con cella (1,1)";
	
	std::cout<<std::endl<<std::endl;
	
	std::cout<<"stampa m2 (1->4): "<<m2;
	m2(0,0) = punto<int>(1,1);
	
	std::cout<<std::endl;
	
	//costruttore secondario
	Matrice2D< punto<int> > m3(y, x, punto<int>(9,9));
	std::cout<<"stampa m3: "<<m3;
	
	std::cout<<std::endl;
	
	//costruttore copia
	Matrice2D< punto<int> > m4(m2);
	std::cout<<"stampa m4: "<<m4;
	
	std::cout<<std::endl;
	
	//operator =
	Matrice2D< punto<int> > m5;
	m5 = m2;
	std::cout<<"stampa m5: "<<m5;
	
	std::cout<<std::endl;
	
	//iteratore 
	Matrice2D< punto<int> >::iterator i,ie;
	std::cout<<"stampa m5 (iteratore):"<<std::endl;
	for(i = m5.begin(), ie = m5.end(); i != ie; ++i)
		if(i.is_filled())
			std::cout << *i << std::endl;
	
	std::cout<<std::endl<<std::endl;
			
	//iteratore const
	Matrice2D< punto<int> >::const_iterator f,fe;
	std::cout<<"stampa m5 (iteratore const):"<<std::endl;
	for(f = m5.cbegin(), fe = m5.cend(); f != fe; ++f)
		if(f.is_filled())
			std::cout << *f << std::endl;

	std::cout<<std::endl<<std::endl;
	
	//conversione
	Matrice2D< punto<double> > m6(y,x);	
	m6(0,0) = punto<double>(18.3 , 11.3);
	m6(0,1) = punto<double>(7.2 , 0.2);
	m6(1,0) = punto<double>(4.6 , -3.6);
	m6(1,1) = punto<double>(2.9 , -5.9);

	Matrice2D< punto<int> > m7(m6);
	std::cout<<"stampa m6 (double): ";
	std::cout<<m6;
	
	std::cout<<std::endl;

	//stampa conversione
	std::cout<<"stampa m7 (m6 convertito in int): ";
	std::cout<< m7;
	
	std::cout<<std::endl;
	
	//funtore
	add_42< punto<double> > fun;
	Matrice2D< punto<int> > m8;
	m8 = trasforma< punto<int> >(m6, fun); 
	
	std::cout<<"stampa m8 (m6 con funtore (+42) e convertito in int): ";
	std::cout<<m8;
	
	std::cout<<std::endl;
}

void test_3d_primitivi(int z, int y, int x) {
	
	std::cout<<"****TEST 3D PRIMITIVI****"<<std::endl<<std::endl;
	//costruttore default
	Matrice3D<int> m1();
	
	//costruttore secondario
	Matrice3D<int> m2(z, y, x);
	m2(0,0,0)=1;
	m2(0,0,1)=2;
	m2(0,1,0)=3;
	//m2(0,1,1)=4;
	m2(1,0,0)=5;
	//m2(1,0,1)=6;
	m2(1,1,0)=7;
	m2(1,1,1)=8;
	
	//stampa size
	std::cout<<"size m2: "<<m2.get_size()<<std::endl;
	
	std::cout<<std::endl;
	
	//stampa m2
	std::cout<<"stampa m2: "<<m2;
	
	std::cout<<std::endl;
	
	//scrittura cella
	m2(0,0,0)=m2(1,1,1);
	std::cout<<"cella (0,0,0) sovrascritta con cella (1,1,1)";
	
	std::cout<<std::endl<<std::endl;
	
	std::cout<<"stampa m2 (1->8): "<<m2;
	m2(0,0,0)=1;
	
	std::cout<<std::endl;
	
	//costruttore secondario
	Matrice3D<int> m3(z, y, x, 9);
	std::cout<<"stampa m3: "<<m3;
	
	std::cout<<std::endl;
	
	//costruttore copia
	Matrice3D<int> m4(m2);
	std::cout<<"stampa m4: "<<m4;
	
	std::cout<<std::endl;
	
	//operator =
	Matrice3D<int> m5;
	m5 = m2;
	
	std::cout<<"stampa m5: "<<m5;
	
	std::cout<<std::endl;
	
	//iteratore 
	Matrice3D<int>::iterator i,ie;
	std::cout<<"stampa m5 (iteratore):"<<std::endl;
	for(i = m5.begin(), ie = m5.end(); i != ie; ++i)
		if(i.is_filled())
			std::cout << *i << std::endl;
	
	std::cout<<std::endl<<std::endl;
			
	//iteratore const
	Matrice3D<int>::const_iterator f,fe;
	std::cout<<"stampa m5 (iteratore const):"<<std::endl;
	for(f = m5.cbegin(), fe = m5.cend(); f != fe; ++f)
		if(f.is_filled())
			std::cout << *f << std::endl;

	std::cout<<std::endl<<std::endl;
	
	//conversione
	Matrice3D<double> m6(z,y,x);	
	m6(0,0,0)=18.3;
	m6(0,0,1)=7.2;
	m6(0,1,0)=4.6;
	m6(0,1,1)=2.9;
	m6(1,0,0)=19.3;
	m6(1,0,1)=8.2;
	m6(1,1,0)=5.6;
	m6(1,1,1)=3.9;

	Matrice3D<int> m7(m6);
	//m6=(Matrice3D<int>)m6;  //in alternativa
	std::cout<<"stampa m6 (double): ";
	std::cout<<m6;
	
	std::cout<<std::endl;

	//stampa conversione
	std::cout<<"stampa m7 (m6 convertito in int): ";
	std::cout<<m7;
	
	std::cout<<std::endl;
	
	//funtore
	add_42<double> fun;
	Matrice3D<int> m8;
	m8=trasforma<int>(m6, fun); 
	
	std::cout<<"stampa m8 (m6 con funtore (+42) e convertito in int): ";
	std::cout<<m8;
	
	std::cout<<std::endl;
	
	//slice
	std::cout<<"stampa m8 (metodo slice z=0): ";
	std::cout<<m8.slice(0);
	
	std::cout<<std::endl;
}

void test_3d_custom(int z, int y, int x) {
	
	std::cout<<"****TEST 3D CUSTOM****"<<std::endl<<std::endl;
	//costruttore default
	Matrice3D< punto<int> > m1();
	
	//costruttore secondario
	Matrice3D< punto<int> > m2(z, y, x);
	m2(0,0,0) = punto<int>(1,1);
	m2(0,0,1) = punto<int>(2,2);
	m2(0,1,0) = punto<int>(3,3);
	m2(0,1,1) = punto<int>(4,4);
	m2(1,0,0) = punto<int>(5,5);
	m2(1,0,1) = punto<int>(6,6);
	m2(1,1,0) = punto<int>(7,7);
	m2(1,1,1) = punto<int>(8,8);
	
	//stampa size
	std::cout<<"size m2: "<<m2.get_size()<<std::endl;
	
	std::cout<<std::endl;
	
	//stampa m2
	std::cout<<"stampa m2: "<<m2;
	
	std::cout<<std::endl;
	
	//scrittura cella
	m2(0,0,0) = m2(1,1,1);
	std::cout<<"cella (0,0,0) sovrascritta con cella (1,1,1)";
	
	std::cout<<std::endl<<std::endl;
	
	std::cout<<"stampa m2 (1->8): "<<m2;
	m2(0,0,0) = punto<int>(1,1);
	
	std::cout<<std::endl;
	
	//costruttore secondario
	Matrice3D< punto<int> > m3(z, y, x, punto<int>(9,9));
	std::cout<<"stampa m3: "<<m3;
	
	std::cout<<std::endl;
	
	//costruttore copia
	Matrice3D< punto<int> > m4(m2);
	std::cout<<"stampa m4: "<<m4;
	
	std::cout<<std::endl;
	
	//operator =
	Matrice3D< punto<int> > m5;
	m5 = m2;
	std::cout<<"stampa m5: "<<m5;
	
	std::cout<<std::endl;
	
	//iteratore 
	Matrice3D< punto<int> >::iterator i,ie;
	std::cout<<"stampa m5 (iteratore):"<<std::endl;
	for(i = m5.begin(), ie = m5.end(); i != ie; ++i)
		if(i.is_filled())
			std::cout << *i << std::endl;
	
	std::cout<<std::endl<<std::endl;
			
	//iteratore const
	Matrice3D< punto<int> >::const_iterator f,fe;
	std::cout<<"stampa m5 (iteratore const):"<<std::endl;
	for(f = m5.cbegin(), fe = m5.cend(); f != fe; ++f)
		if(f.is_filled())
			std::cout << *f << std::endl;

	std::cout<<std::endl<<std::endl;
	
	//conversione
	Matrice3D< punto<double> > m6(z,y,x);	
	m6(0,0,0) = punto<double>(18.3 , 11.3);
	m6(0,0,1) = punto<double>(7.2 , 0.2);
	m6(0,1,0) = punto<double>(4.6 , -3.6);
	m6(0,1,1) = punto<double>(2.9 , -5.9);
	m6(1,0,0) = punto<double>(17.3 , 10.3);
	m6(1,0,1) = punto<double>(6.2 , -1.2);
	m6(1,1,0) = punto<double>(3.6 , -4.6);
	m6(1,1,1) = punto<double>(1.9 , -6.9);

	Matrice3D< punto<int> > m7(m6);
	std::cout<<"stampa m6 (double): ";
	std::cout<<m6;
	
	std::cout<<std::endl;

	//stampa conversione
	std::cout<<"stampa m7 (m6 convertito in int): ";
	std::cout<< m7;
	
	std::cout<<std::endl;
	
	//funtore
	add_42< punto<double> > fun;
	Matrice3D< punto<int> > m8;
	m8 = trasforma< punto<int> >(m6, fun); 
	
	std::cout<<"stampa m8 (m6 con funtore (+42) e convertito in int): ";
	std::cout<<m8;
	
	std::cout<<std::endl;
	
	//slice
	std::cout<<"stampa m8 (metodo slice z=1): ";
	std::cout<<m8.slice(1);
	
	std::cout<<std::endl;
}