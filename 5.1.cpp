#include<iostream>
using namespace std;
class Widget
{
    int id;
    static int count;
    public:
    Widget()
    {
        id=++count;
        cout<<"Created W"<<id<<endl;
    }
    ~Widget()
    {
        --count;
        cout<<"Destroyed W"<<id<<endl;
    }
    static int Alive(){
        return count;
    }
};
int Widget::count=0;
int main()
{
    Widget a,b;
    cout<<"Alive: "<<Widget::Alive()<<endl;
    {
        Widget c;
        cout<<"Alive: "<<Widget::Alive()<<endl;
    }
    cout<<"Alive: "<<Widget::Alive()<<endl;
    return 0;
}