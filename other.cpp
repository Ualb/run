#include <iostream>

using namespace std;

class Square {
    private:
        int side_;
    
    public:
        Square(int side_length) :side_(side_length) {};
        int getArea() const {return side_*side_;};
};

int main () {
    Square square(5);
    cout << "Area: " << square.getArea() << endl;
    return 0;
}