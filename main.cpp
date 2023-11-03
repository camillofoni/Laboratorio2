#include <iostream>
#include "particle.hpp"

int main()
{
    /*
    ParticleType particletype1("e", 4.2, 1);
    ResonanceType resonancetype1("n", 2.3, 2, 5.6);

    ParticleType *types[2];
    types[0] = &particletype1;
    types[1] = &resonancetype1;

    for (int i = 0; i < 2; ++i)
    {
        (*types[i]).Print();
    }
    */

    Particle::AddParticleType("elettrone", 9.11, -1);
    Particle::AddParticleType("neutrone", 24.5, 0.);
    Particle::AddParticleType("protone", 2.5, 1.);
    Particle::AddParticleType("neutrino", 2.5, 0., 1.12);    

    Particle::PrintArray();

    Particle p1("elettrone", 1.1, 2.3, -2.5);
    Particle p2("elettrone", 0.2, 1, 2.4);
    Particle p3("protone", 15.6, 2, 3.5);
    Particle p4("neutrone", 2.43, 1, 3.5);
    Particle p5("neutrone");
    std::cout << "\nEnergy of p1: " << p1.GetEnergy();
    std::cout << "\nInvariant Mass p1 & p2: " << p1.InvMass(p2);
    std::cout<<"\n";
}
