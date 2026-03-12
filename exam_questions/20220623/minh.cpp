#include <iostream>

using std::cout;
using std::endl;

class Shape {
    private:
        size_t id_;
        static size_t counter;
    public:
        Shape() : id_{++counter} {}
        Shape(const Shape& other) : Shape() {}
        
        Shape& operator= (const Shape& other) = delete;
        
        size_t getID () const { return id_; }
        virtual double area () const = 0;
        virtual void print() const {
            cout << "Shape with ID " << id_ << " is " << this->area() << " units large.\n" ;
        }
        double operator+ (const Shape& other) {
            return this->area() + other.area();
        }
};

size_t Shape::counter = 0;

class Rectangle : public Shape {
    private:
        double width_;
        double length_;
    public:
        Rectangle(double wid, double len) : Shape(), width_{wid}, length_{len} {}
        Rectangle(const Rectangle& other) : Shape(), width_{other.width_}, length_{other.length_} {}
        
        Rectangle& operator= (const Rectangle& other) = delete;
        
        virtual double area () const override {
            return width_ * length_;
        }
        virtual void print() const override {
            cout << "Rectangle with ID " << getID() << " is " << this->area() << " units large.\n" ;
        }
        
};

int main()
{
  Rectangle rec1(2.0,2.0);
  rec1.print();  

  Rectangle rec2(3.0,2.0);
  rec2.print();
  
  Rectangle rec3(2.0,3.0);
  rec3.print();
  
  // Summe zweier Rechtecke
  std::cout << "Summe von rec1 und rec2: "<< rec1 + rec2 << std::endl;
  
  // Test Polymorphie
  Shape* rec4 = new Rectangle(2.0, 4.0);
  rec4->print();
  
  // Test CopyConstructor
  Rectangle rec5(rec1);
  rec5.print();

  
  
  delete rec4;
  return 0;
}
