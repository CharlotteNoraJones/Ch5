// #include <iostream>

// 5.1 Introduction
// ch.5 presents the necessary info to create concrete classes, abstract
// classes, and class hierarchies

// 5.1.1 Classes
// class: user defined-type used to represent an entity
// three kinds of classes
// concrete classes
// abstract classes
// classes in class hierarchies
// these are the basis for most classes

// 5.2 Concrete Types
// behave "just like built in types"
// std::vector and std::string are examples
// representation part of definition
// this allows:
// concrete objects can be placed in the stack, in statically allocated memory,
// and in other objects refer to objects directly, instead of through pointers
// or references initialize objects immediatly and completely (with
// constructors) copy and move objects
// representation is often private and accessible only through member functions
// (like std::vector) if the representations changes in a big way, must
// recompile use a concrete type when:
// types that don't change very often
// where local variables provide clarity + efficiency
// concrete types can keep big parts of their representation on the free store

// 5.2.1 An Arithmetic Type

// class complex {
//     double re, im; //representation: two doubles
// public:
//     complex(double r, double i): re{r}, im{i} {} // construct complex from
//     two scalars complex(double r, double i): re{r}, im{0} {} // construct
//     complex from one scalar complex() :re{0}, im{0} {} // default complex:
//     {0,0} complex(complex& z) :re{z.re}, im{z.im} {} // copy constructor

//     double real() const {return re;}
//     void real(double d) {re=d;}
//     double imag() const {return im;}
//     void imag(double d) {im=d;}

//     complex& operator+=(complex z)
//     {
//         re+=z.re; // add to re and im
//         im+=z.im; //
//         return *this; // return the result
//     }

//     complex& operator-=(complex z)
//     {
//         re-=z.re;
//         im-=z.im;
//         return *this;
//     }

//     complex& operator*=(complex); // defined out-of-class somewhere
//     complex& operator/=(complex); // defined out-of-class somewhere
// };

// // functions defined in a class are inlined by default.
// // inline keyword explicitly request a function be inlined by the compiler
// // std::complex is carefully designed to implement appropriate inlining

// //default constructor: construct that can be invoked without an arguement.
// // eliminates possibility of initialized variables of the type.

// // const specifiers indicate these functions do not modify the object for
// which they are called.
// // const member functions be invoked for both const and non-const objects,
// but a non-const member function
// // can only be invoked for non-const objects.

// complex z {1,0};
// const complex cz {1,3};
// z = cz; //Ok: assignment to a non=const variable.
// cz = z; // Error: assignment to a const
// double x = z.real(); // Ok: complex::real() is const

// // some useful operations can be defined seperatly from the class definition
// complex operator+(complex a, complex b) {return a+=b;}
// complex operator-(complex a, complex b) {return a-=b;}
// complex operator-(complex a) {return {-a.real(), -a.imag()}}; // unary minus
// complex operator*(complex a, complex b) {return a*=b;}
// complex operator/(complex a, complex b) {return a/=b;}

// // arguement passed by value is copied, so we can modify the an arguement
// with affecting the
// // value of the caller and then use that as the return value

// bool operator==(complex a, complex b) {return a.real()==b.real() && a.imag()
// == b.imag();} //equal bool operator!=(complex a, complex b) {return !(a==b);}
// //not equal

// void f(complex z)
// {
//     complex a {2.3}; // construct {2.3, 0.0} from 2.3
//     complex b {1/a};
//     complex c {a+z*complex{1, 2.3}};
//     if (c != b)
//         c = -(b/a)+2*b;
// }

// // the compiler converts operators invovling complex numbers into the
// appropriate function calls.
// // c!=b means operator!=(c,b) and 1/a means operator/(complex{1},a)

// use overloaded operators with caution

// //5.2.2 A Container
// // container:: class holding a collection of objects
// // std::vector is a container

// // destructor: mechanism for deallocating memory allocated by a destructor

// class Vector {
//     public:
//         Vector(int s): elem{new double[s]}, sz{s} //constructor: acquires
//         resources
//         {
//             for (int i=0;i!=s; ++i) //initialize elements
//                 elem[i]=0;
//         }

//         ~Vector() {delete[] elem;} //destructor: release resources

//         double& operator[](int i);
//         int size() const;
//     private:
//         double* elem; // elem points to an array of sz doubles
//         int sz;
// };

// // destructor is ~ followed the name of the variable.

// // new operator allocates memory on the free store
// // free store is also called heap or dynamic memory
// // delete removes an individual object, delete[] deletes an array

// Vector gv(10); // global variable; gv is destroyed at the end of the program

// Vector* gp = new Vector(100); // Vector on the free store; never implicitly
// destryoed

// void fct(int n)
// {
//     Vector v(n);
//     // ... use v ...
//     {
//         Vector v2(2*n);
//         // ... use v and v2 ...
//     } // v2 is destroyed here
//     // ... use v ...
// } // v is destroyed here

// // our vector obeys the same rules for naming, scope, allocation, lifetime,
// etc as
// // a built in type, like int or char. This is what makes it a concrete type

// //handle-to-date model: when the constructor allocates the elements and the
// destructor deallocates them
// // used to handle data that can vary in size during the lifetime of the
// object.

// // Resource Acquisition is Initialization: that technique.
// // avoid allocations and destructions in general code; keep them buried in
// well-defined abstractions.
// // this means avoid naked new and delete operators.

// // 5.2.3 Initializing Containers
// // multiple ways to get elements into a container
// // initializer-list constructor: initialize with a list of elements
// // push_back(): add a new element at the end(at the back of) the sequence

// class Vector {
//     public:
//         Vector(); // default initalize to "empty"; that is, to no elements
//         Vector(std::initializer_list<double>); // initialize with a list of
//         doubles
//         // ...
//         void push_back(double); // add element at end, increasing the size by
//         one.
//         // ...
// };

// //push_back() is use for input of arbitarty numbers of elements

// Vector read(istream& is)
// {
//     Vector v;
//     for (double d; is>>d;) // read floating-point values into d
//         v.push_back(d); // add d to v
//     return v;
// }

// // reading a lot o data from read() can be expensive.
// // providing Vector with a move constructor makes returning it cheaper.

// Vector v = read(cin); // no copy of Vector elements here

// // std::initializer_list is a standard library type. The compiler knows it,
// uses it for
// // {} list

// Vector v1 {1, 2, 3, 4, 5}; // v1 has 5 elements
// Vector v2 {1.23, 3.14, 6.7, 8}; // v2 has 4 elements

// // example of how vector's list constructor might be defined
// Vector::Vector(std::initializer_list<double> lst) // initialize with a list
//     :elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())}
// {
//     copy(lst.begin(),lst.end(),elem); // copy from lst into elem
// }

// // static cast is necessary because the standard library uses unsigned
// integers for sizes and subscripts.
// // explicit type conversions (cast) are best avoided
// // user cast include reinterpret_cast and bit_cast and const_cast
// // best to use type system and libraries to eliminate unchecked casts in
// higher-level software.

// // 5.3 Abstract Types
// //  abstract type: totally obscure implementation details from users.
// //  must be allocated on the free store and accessed through references or
// //  pointers. to make an abstract type, decouble interface from representation
// //  and give up real local variables.

// // more abstract version of Vector
// class Container {
//     public:
//     virtual double& operator[](int) = 0;  // pure virtual function
//     virtual int size() const = 0;         // const member function
//     virtual ~Container() {}               // destructor
//     };

// // virtual function: be may later redefined in a class derived from this one.
// // =0 means the function is pure virtual, it must be redefined later.
// // it's not possible to define an object that's just Container.

// Container c;  // error: there can be no objects of an abstract class
// Container* p = new Vector_container(
//     10);  // Ok: Container is an interface for Vector_container

// // abstract class: a class with a pure virtual function
// // container can only serve as an interface to a class that implements its
// // operator[] and size() functions

// void use(Container& c) {
//     const int sz = c.size();

//     for (int i = 0; i != sz; ++i) std::cout << c[i] << '\n';
//     }

// // container can be used without knowing the implementation details.

// // polymorpic type: provides the interface to a variety of other classes.

// // abstract classes usually don't have a constructor
// // it's common to define a destructor for an abstract class though.

// // defining  a class that implements the Container infterface

// class Vector_container
//     : public Container {  // Vector_container implements Container
//     public:
//     Vector_container(int s) : v(s) {}  // Vector of s elements
//     ~Vector_container() {}

//     double& operator[](int i) override { return v[i]; }
//     int size() const override { return v.size(); }

//     private:
//     Vector v;
//     };

// // :public means "is derived from" or "is a subtype of"
// // inheritance: use of base of derived classes

// // in the above case, operator[] and size() override the corresponding members
// // in the base clas Container override specifier makes it clear what's intended
// // override is optional, but helps the compiler catch mistakes.
// // Vector_container overrides container's destructor
// // calling a destructor for a class implicitly calls it for the classes's
// // members

// // for a function like use(Container&) to use Container without knowledge of
// // implementation details, other functions will have to make an object it can
// // operate on

// void g() {
//     Vector_container vc(10);  // Vector of ten elements
//     // ... fill vc ...
//     use(vc);
//     }
// // this function will work just as well for other implementations of container

// class List_container : public Container {  // List_container implements
//     // Container
//     public:
//     List_container() {}  // empty List
//     List_container(std::initializer_list<double> il) : Id{ il } {}
//     ~List_container() {}

//     double& operator[](int i) override;
//     int size() const override { return Id.size(); }

//     private:
//     std::list<double> ld;  // (standard-library) list of doubles (§12.3)
//     };
// double& List_container::operator[](int i) {
//     for (auto& x : ld) {
//         if (i == 0) return x;
//         --i;
//         }
//     throw out_of_range{ "List container" };
//     }
// // the performance of std::vector is a lot better than std::list

// // this also works
// void h() {
//     List_container lc{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//     use(lc);
// }

// // use(Container&) doesn't need to be recompiled if the implementation of List_container changes
// // but, objects must be manipulated through pointers or references. 

// // 5.4 Virtual Function 

// void use(Container& c)
// {
//     const int sz = c.size();

//     for (int u = 0; i != sz; ++i)
//         std::cout << c[i] << '\n';
// }

// // virtual function table; vtbl, table used by a class with virtual functions to identify the correct function to call. 
// // this has a pretty small overhead over non-virtual functions

// // 5.5 Class Hierarchies
// // set of classes ordered by derivation

// // example

// class Shape
// {
//     public:
//     virtual Point center() const = 0 //pure virtual
//         virtual void move(Point to) = 0;

//     virtual void draw() const = 0; //draw on current "Canvas"
//     virtual void rotate(int angle) = 0;

//     virtual ~Shape() {} //destructor
//     // ...
// };
// // this is an abstract class
// // nothing except the pointer to the vtbl is common for every Shape. 

// // example of a general function manipulating vectors to pointers of shapes:

// void rotate_all(vector<Shape*>& v, int angle) // rotate v's elements by angle degrees
// {
//     for (auto p : v)
//         p->rotate(angle);
// }

// class Circle : public Shape 
// {
//     public:
//         Circle(Point p, int rad) :x{p}. r{rad} {} // constructor

//         Point center() const override {return x;}
//         void move(Point to) override {x=to;}
//         void draw() const override;
//         void rotate(int) override {} // nice simple algorithm
//     private:
//         Point x; // center
//         int r; // radius
// };

// class Smiley : public Circle { // use the circle as the base for a face
//     public:
//         Smiley(Point p, int rad) : Circle{p, rad}, mouth{nullptr} {}
//         ~Smiley()
//         {
//             delete mouth;
//             for (auto p : eyes)
//                 delete p;
//         }

//         void move(Point to) override;
//         void draw() const override;
//         void rotate(int) override;

//         void add_eye(Shape* s)
//         {
//             eyes.push_back(s);
//         }

//         void set_mouth(Shape* s);
//         virtual void wink(int i); // wind eye number i

//         // ..
//     private: 
//         vector<Shape*> eyes; // usually two eyes
//         Shape* mouth;
// };

// void Smiley::draw() const
// {
//     Circle::draw();
//     for( auto p : eyes)
//         p->draw();
//     mouth->draw();
// }

// // 5.5.1 Benefits from Hierarchies
// // interface inheritance: an object of a derived class can be used whenver an object of base class is required. 
// // base classes thus act as interfaces for the dervied class. 
// //implementation inheritance: derived classes inherit members from parent classes, making them simpler to inherit. 

// // concrete class vc classes in hiearchies
// // concrete classes are similar to built-in types. 
// // can be defined as local variables, access them with names, copy easily. 
// // classes in hiearchies are allocated on the free store with new
// // accessed through pointers or references. 

// // funtion that reads data describing shapes from an input stream.

// enum class Kind {circle, triangle, smiley };

// Shape* read_shape(istream& is) // read shape descriptions from input stream is
// {
//     // ... read shape header from is and find its Kind k ...

//     switch(k) {
//         case Kind::circle:
//             // ...read circle data {Point, int} into p and r ...
//             return new Circle{p, r};
//         case Kind::triangle:
//             // ... read triangle data {Point, Point, Point} into p1, p2, and p3 ...
//             return new Triangle{p1, p2, p3};
//         case Kind::smiley:
//             // ... read smiley data {Point, int, Shape, Shape, Shape} into p, r, e1, e2, and m ...
//             Smiley* ps = new Smiley{p, r};
//             ps->add_eye(e1);
//             ps->add_eye(e2);
//             ps->set_mouth(m);
//             return ps;
//     }
// }

// // the shape reader can be used like so

// void user()
// {
//     std::vector<Shape*> v;

//     while (cin)
//         v.push_back(read_shape(cin));

//     draw_all(v); // call draw() for each element
//     rotate_all(v,45); // call rotate(45) for each element

//     for (auto p: v) // remember to delete elements
//         delete p;
// }

// // in this example, user doens't need to know what kind of shapes its manipulating. 
// // user code can be compiled once and use as more shapes are added. 
// // calling a base class's destructor will call the destructor of whatever dervied class it is. 
// // classes are constructed bottom up and destroyed top down

// // 5.5.2 Hiearchy Navigation
// // dynamic_cast operator checks if a class in a hiearchy is a particular derived class. 

// Shape* ps {read_shape(cin)};
// if (Smiley* p = dynamic_cast<Smiley*>(ps)) // does ps point to a Smiley
// {
//     // a Smiley; use it ...
// }
// else {
//     // ..not a Smiley, try something else ...
// }

// // dynamic_cast returns nullptr if the object is of a different derived class. 

// // when a different type is unacceptable, dynamic_cast to a referene type.
// Shape* ps {read_shape(cin)};
// Smiley& r {dynamic_cast<Smiley&>(*ps)}; // somewhere, catch std::bad_cast

// // it's best to use dynamic_cast with restrain. Try to avoid losing type information, but sometimes its inevitable
// // operations like dynamic_cast are "is kind of" and "is instance of"

// 5.5.3 Avoiding Resource Leaks
// leak: when we aqcuire a resource and fail to release it. This makes the resource unavailable. 

// mistakes in previous examples
// the implementer of Smiley may fail to delete the pointer to mouth
// a user of read_shape() might fail to delete the pointer returned.
// the owner of a container of Shape pointers might fail to delete the objects points to. 

// pointers to objects allocated on the free store are dangerous
// don't use a "plain old pointer" to represent ownership. 

void user(int x)
{
    Shape* p = new Circle{Point{0,0},10};
    // ...
    if (x<0) throw Bad_x{} //potential leak
    if (x==0) return; // potential leak
    // ..
    delete p;
}

// this leaks if x is not positive. 
// don't assign the result of new to a naked pointer

// if delete is required, use the standard-library unique-ptr

#include <memory>
#include <vector>

class Smiley : public Circle {
    //..
    private:
        std::vector<std::unique_ptr<Shape>> eyes; //usually two eyes. 
        unique_ptr<Shape> mouth;
}

// this is a simple, general, and effective technique for resource management. 
// we don't need to define a destructor in this instance because the compiler 
// will implicitly generate one that does the required destruction of unique_ptrs in the vector
// this is just as efficient as using raw pointers. 

std::unique_ptr<Shape> read_shape(istream is) // read shape descriptions from input stream is
{
    // ..read shape header from is and find its Kind k..

    switch(k) {
        case Kind::circle:
            // ...read circle data {Point, int} into p and r ..
            return std::unique_ptr<Shape>{new Circle{p,r}};
    }
}

// unique_ptr will delete the object when it's no longer needed (when the unique_ptr goes out of scope)