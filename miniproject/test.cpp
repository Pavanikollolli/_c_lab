#define main wsn_main
#include "main.cpp"
#undef main
#include <sstream>
#include <iomanip>

struct BadNode : SensorNode {            // test helper to trigger validation
    BadNode(double b, double r) : SensorNode(99, 0, 0, b, r) {}
    void step(double) override {}
};
static int lines(const std::string& f){ std::ifstream i(f); std::string s; int n=0; while(getline(i,s)) n++; return n; }
static std::string row(const std::string& f,int n){ std::ifstream i(f); std::string s; for(int k=0;k<=n&&getline(i,s);k++); return s; }

int main() {
    // TC-01 default scenario
    { WSNSimulator s(50,50); s.addNode(std::make_unique<TempSensor>(1,10,10)); s.addNode(std::make_unique<CameraSensor>(2,30,30));
      s.run(100,"t1.csv"); std::cout<<"TC-01 rows="<<lines("t1.csv")<<" tick1=["<<row("t1.csv",1)<<"] tick45=["<<row("t1.csv",45)<<"] tick46=["<<row("t1.csv",46)<<"] tick100=["<<row("t1.csv",100)<<"]\n"; }
    // TC-02 camera-only network dies and run stops early
    { WSNSimulator s(50,50); s.addNode(std::make_unique<CameraSensor>(1,30,30));
      s.run(100,"t2.csv"); std::cout<<"TC-02 rows="<<lines("t2.csv")<<" last=["<<row("t2.csv",lines("t2.csv")-1)<<"]\n"; }
    // TC-03 empty network
    { WSNSimulator s(50,50); std::cout<<"TC-03 coverage="<<s.calculateCoverage()<<"\n"; }
    
}
