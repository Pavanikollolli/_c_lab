#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <stdexcept>

// 1. Base Class & Polymorphism
class SensorNode {
protected:
    int id;
    double x, y;
    double battery;
    double sensingRadius;

public:
    SensorNode(int id, double x, double y, double battery, double radius)
        : id(id), x(x), y(y), battery(battery), sensingRadius(radius) {
        if (battery <= 0 || radius <= 0) {
            throw std::invalid_argument("Battery and radius must be positive.");
        }
    }
    virtual ~SensorNode() = default;

    // Pure virtual function for polymorphic behavior
    virtual void step(double dt) = 0;

    bool isAlive() const { return battery > 0.0; }
    int getId() const { return id; }
    double getBattery() const { return std::max(0.0, battery); }

    bool coversPoint(double px, double py) const {
        if (!isAlive()) return false;
        double dist = std::hypot(x - px, y - py);
        return dist <= sensingRadius;
    }
};

// 2. Derived Node Types
class TempSensor : public SensorNode {
public:
    TempSensor(int id, double x, double y)
        : SensorNode(id, x, y, 100.0, 15.0) {}

    void step(double dt) override {
        if (isAlive()) battery -= 0.5 * dt; // Low power drain
    }
};

class CameraSensor : public SensorNode {
public:
    CameraSensor(int id, double x, double y)
        : SensorNode(id, x, y, 100.0, 25.0) {}

    void step(double dt) override {
        if (isAlive()) battery -= 2.2 * dt; // High power drain
    }
};

// 3. Network & Simulation Manager
class WSNSimulator {
private:
    std::vector<std::unique_ptr<SensorNode>> nodes;
    std::map<int, double> coverageLog; // Tick -> Coverage %
    int gridWidth, gridHeight;

public:
    WSNSimulator(int w, int h) : gridWidth(w), gridHeight(h) {}

    void addNode(std::unique_ptr<SensorNode> node) {
        nodes.push_back(std::move(node));
    }

    double calculateCoverage() const {
        int coveredPoints = 0;
        int totalPoints = gridWidth * gridHeight;

        for (int x = 0; x < gridWidth; ++x) {
            for (int y = 0; y < gridHeight; ++y) {
                // STL Algorithm: check if ANY alive node covers (x, y)
                bool covered = std::any_of(nodes.begin(), nodes.end(),
                    [x, y](const auto& node) { return node->coversPoint(x, y); });
                if (covered) coveredPoints++;
            }
        }
        return (static_cast<double>(coveredPoints) / totalPoints) * 100.0;
    }

    void run(int maxTicks, const std::string& logFile) {
        std::ofstream out(logFile);
        if (!out.is_open()) {
            throw std::runtime_error("Failed to open output log file.");
        }
        out << "Tick,ActiveNodes,CoveragePercent\n";

        for (int tick = 1; tick <= maxTicks; ++tick) {
            for (auto& node : nodes) {
                node->step(1.0); // Polymorphic call
            }

            // STL Algorithm: count active nodes
            int aliveCount = std::count_if(nodes.begin(), nodes.end(),
                [](const auto& n) { return n->isAlive(); });

            double cov = calculateCoverage();
            coverageLog[tick] = cov;
            out << tick << "," << aliveCount << "," << cov << "\n";

            if (aliveCount == 0) break; // End early if network dies
        }
    }
};

int main() {
    try {
        WSNSimulator sim(50, 50);
        sim.addNode(std::make_unique<TempSensor>(1, 10.0, 10.0));
        sim.addNode(std::make_unique<CameraSensor>(2, 30.0, 30.0));

        sim.run(100, "wsn_results.csv");
        std::cout << "Simulation complete. Results saved to wsn_results.csv\n";
    } catch (const std::exception& e) {
        std::cerr << "Simulation Error: " << e.what() << "\n";
    }
    return 0;
}