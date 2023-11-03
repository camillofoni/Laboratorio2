#include <iostream>
#include <cmath>
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
    int N = 120;
    Particle EventParticles[N];
    TH1F *h = new TH1F("h", "abundancies", 7, 0, 1);
    for (int i = 0; i < 1e5; ++i)
    {
        Double_t type = gRandom->Rndm();
        Double_t phi = gRandom->Uniform(0, 2 * TMath::Pi());
        Double_t theta = gRandom->Uniform(0, TMath::Pi());
        Double_t p = gRandom->Exp(1);

        if (type < 0.4)
        {
            EventParticles[i].SetIndex(0);
        }
        else if (type < 0.8)
        {
            EventParticles[i].SetIndex(1);
        }

        else if (type < 0.85)
        {
            EventParticles[i].SetIndex(2);
        }
        else if (type < 0.9)
        {
            EventParticles[i].SetIndex(3);
        }
        else if (type < 0.945)
        {
            EventParticles[i].SetIndex(4);
        }
        else if (type < 0.99)
        {
            EventParticles[i].SetIndex(5);
        }
        else
        {
            EventParticles[i].SetIndex(6);
        }
        EventParticles[i].SetP(p * sin(theta) * cos(phi), p * sin(theta) * sin(phi), p * cos(theta));
        }
}
