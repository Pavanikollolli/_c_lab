#include<iostream>
 #include<cstring>
 using namespace std;
 class MyString {
char*data;
public:
MyString(const char*s){
data=new char[strlen(s)+1];
strcpy(data,s);
}
MyString(const MyString&o){
data =new char[strlen(o.data)+1];
strcpy(data,o.data);
}
~MyString(){delete[]data;}
void print()const{cout <<data <<endl;}
 };
 int main(){
MyString a("hardware");
MyString b=a;
a.print( );
b.print( );
return 0;
 }


#include <iostream>
#include <string>
#include <cctype>
using namespace std;
int main(){
string s = "verification";
cout << "First 4: " << s.substr(0,4) << endl;
cout << "From 4: " << s.substr(4) << endl;
int c = s.compare("verify");
cout << "compare vs 'verify': " << (c<0 ? "<" : c>0 ? ">" : "==") << endl;
int freq[26] = {0};
for(char ch:s) if(isalpha((unsigned char)ch)) freq[(ch-'a')]++;
cout << "letter counts: ";
for(int i=0; i<26; i++) if(freq[i]) cout << char('a'+i) << ":" << freq[i] << " ";
cout << endl;
return 0;
}



#include<iostream>
using namespace std;
inline int square(int x){return x*x;}
double area(double r){return 3.1419*r*r;}
int area(int l,int b){return l*b;}
double area(double b,double h){return 0.5*b*h;}
int main(){
    cout <<"square(6) ="<<square(6)<<endl;
    cout <<"circle r=2 = "<<area(2.0)<<endl;
    cout <<"rectangle 4*5="<<area(4,5)<<endl;
    cout <<"triangle b=3,h=8="<<area(3.0,8.0)<<endl;
    return 0;

}

#include<iostream>
using namespace std;
class Register{
private:
unsigned char value;
public:
void write(unsigned char v){value =v;}
unsigned char read()const{return value;}
void reset(){value=0;}
};
int main(){
    Register file[4];
    for(int i=0;i<4;++i)file[i].reset();
    file[0].write (0XAB);
    file[3].write(0x10);
    for(int i=0;i<4;++i)
    cout<<"R"<<i<<"="<<(int)file[i].read()<<endl;
    return 0;
}


#include <iostream>
using namespace std;

class Point {
    int x, y;

public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    Point add(const Point& p) const {
        return Point(x + p.x, y + p.y);
    }

    Point& setX(int v) {
        this->x = v;
        return *this;
    }

    Point& setY(int v) {
        this->y = v;
        return *this;
    }

    void show() const {
        cout << "(" << x << "," << y << ")\n";
    }
};

void shift(Point& p) {
    p.setX(99);
}

void tryShift(Point p) {
    p.setX(-1);
}

int main() {
    Point a(1, 2), b(3, 4);

    Point c = a.add(b);
    c.show();

    Point d;
    d.setX(7).setY(8);
    d.show();

    shift(a);
    a.show();

    tryShift(b);
    b.show();

    return 0;
}



#include<iostream>
using namespace std;
class Tracer{
int id;
public:
Tracer(int i):id(i){cout<<"construct #"<<id<<endl;}
~Tracer(){cout<<"destruct #"<<id<<endl;}
};
int main(){
cout <<"enter block\n";
{Tracer a(1),b(2);cout <<"...working..\n";}
cout<<"left block\n";
return 0;
}