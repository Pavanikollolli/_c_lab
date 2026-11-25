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
    // TC-04 invalid battery / radius
    { try{ BadNode b(0,10); std::cout<<"TC-04a no exception\n"; }catch(const std::exception&e){ std::cout<<"TC-04a "<<e.what()<<"\n"; }
      try{ BadNode b(50,-5); std::cout<<"TC-04b no exception\n"; }catch(const std::exception&e){ std::cout<<"TC-04b "<<e.what()<<"\n"; } }
    // TC-05 unwritable log file
    { WSNSimulator s(10,10); try{ s.run(5,"/nonexistent_dir/out.csv"); std::cout<<"TC-05 no exception\n"; }catch(const std::exception&e){ std::cout<<"TC-05 "<<e.what()<<"\n"; } }
    // TC-06 boundary of sensing radius
    { TempSensor t(1,10,10); std::cout<<"TC-06 d=15:"<<t.coversPoint(25,10)<<" d=15.1:"<<t.coversPoint(25.1,10)<<"\n"; }
    // TC-07 overlapping nodes not double counted
    { WSNSimulator a(50,50), b(50,50); a.addNode(std::make_unique<TempSensor>(1,10,10));
      b.addNode(std::make_unique<TempSensor>(1,10,10)); b.addNode(std::make_unique<TempSensor>(2,10,10));
      std::cout<<"TC-07 single="<<a.calculateCoverage()<<" duplicate="<<b.calculateCoverage()<<"\n"; }
    // TC-08 battery drain per tick
    { TempSensor t(1,0,0); CameraSensor c(2,0,0); for(int i=0;i<10;i++){t.step(1);c.step(1);} std::cout<<"TC-08 temp="<<t.getBattery()<<" camera="<<c.getBattery()<<"\n"; }
    // TC-09 dead node covers nothing / battery clamped
    { CameraSensor c(1,10,10); for(int i=0;i<46;i++) c.step(1); std::cout<<"TC-09 alive="<<c.isAlive()<<" battery="<<c.getBattery()<<" covers="<<c.coversPoint(10,10)<<"\n"; }
}