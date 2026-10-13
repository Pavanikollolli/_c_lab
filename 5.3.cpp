#include<iostream>
using namespace std;
class car{
    int speed=0;
    friend class Dashboard;
    public:
    void accelerate()
    {
        speed+=10;
    }
};
class Dashboard{
    public:
    void display(const car &c)
    {
      cout<<"speed= "<<c.speed<<"km/h\n";
    }
};
int main()
{
    car c;c.accelerate();c.accelerate();
    Dashboard().display(c);
    return 0;
}