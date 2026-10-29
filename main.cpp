
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

struct Particle {
    double x, y;
    double vx, vy;
};

struct SimulationResult {
    double averageSpeed;
    double checksum;
};

SimulationResult runSimulation(size_t count, size_t steps) {
    vector<Particle> particles;
    particles.reserve(count);

    mt19937_64 rng(42);
    uniform_real_distribution<double> position(-100.0, 100.0);
    uniform_real_distribution<double> velocity(-1.0, 1.0);

    for (size_t i = 0; i < count; ++i) {
        particles.push_back({
            position(rng), position(rng),
            velocity(rng), velocity(rng)
        });
    }

    const double dt = 0.016;
    const double boundary = 100.0;

    // Update particles in place to reduce memory overhead.
    for (size_t step = 0; step < steps; ++step) {
        for (Particle& p : particles) {
            p.x += p.vx * dt;
            p.y += p.vy * dt;

            if (p.x > boundary) {
                p.x = 2 * boundary - p.x;
                p.vx = -abs(p.vx);
            } else if (p.x < -boundary) {
                p.x = -2 * boundary - p.x;
                p.vx = abs(p.vx);
            }

            if (p.y > boundary) {
                p.y = 2 * boundary - p.y;
                p.vy = -abs(p.vy);
            } else if (p.y < -boundary) {
                p.y = -2 * boundary - p.y;
                p.vy = abs(p.vy);
            }
        }
    }

    // Calculate metrics in a single pass.
    double speedSum = 0.0;
    double checksum = 0.0;

    for (const Particle& p : particles) {
        speedSum += sqrt(p.vx * p.vx + p.vy * p.vy);
        checksum += p.x * 0.5 + p.y * 0.25
                  + p.vx + p.vy;
    }

    double averageSpeed = particles.empty()
        ? 0.0
        : speedSum / particles.size();

    return {averageSpeed, checksum};
}

int main(int argc, char* argv[]) {
    size_t particleCount = 200000;
    size_t steps = 500;

    try {
        if (argc > 1)
            particleCount = stoull(argv[1]);
        if (argc > 2)
            steps = stoull(argv[2]);
    } catch (...) {
        cerr << "Usage: " << argv[0]
             << " [particle_count] [steps]\n";
        return 1;
    }

    if (particleCount == 0 || steps == 0) {
        cerr << "Particle count and steps must be greater than zero.\n";
        return 1;
    }

    auto start = chrono::steady_clock::now();

    SimulationResult result =
        runSimulation(particleCount, steps);

    auto end = chrono::steady_clock::now();

    chrono::duration<double> elapsed = end - start;

    cout << fixed << setprecision(6);
    cout << "C++ Particle Simulation\n";
    cout << "Particles: " << particleCount << '\n';
    cout << "Steps: " << steps << '\n';
    cout << "Average speed: " << result.averageSpeed << '\n';
    cout << "Checksum: " << result.checksum << '\n';
    cout << "Elapsed time (seconds): "
         << elapsed.count() << '\n';

    return 0;
}
