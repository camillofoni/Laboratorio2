#include <iostream>
#include "particle.hpp"

int main()
{
    gRandom->SetSeed();
    Particle::AddParticleType("pioni+", 0.13957, 1);
    Particle::AddParticleType("pioni-", 0.13957, -1);
    Particle::AddParticleType("kaoni+", 0.49367, 1);
    Particle::AddParticleType("kaoni-", 0.49367, -1);
    Particle::AddParticleType("prononi+", 0.93827, 1);
    Particle::AddParticleType("prononi-", 0.93827, -1);
    Particle::AddParticleType("k*", 0.89166, 0, 0.050);
    int N=120;
    Particle EventParticles[N];

}
