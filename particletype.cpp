#include <iostream>

#include "particletype.hpp"

ParticleType::ParticleType(const char *name, const double mass, const int charge)
    : fName(name), fMass(mass), fCharge(charge)
{
}

void ParticleType::Print() const
{
    std::cout << "\n\tName: " << GetName()
              << "\n\tMass: " << GetMass()
              << "\n\tCharge: " << GetCharge();
}

const char *ParticleType::GetName() const { return fName; }
const double ParticleType::GetMass() const { return fMass; }
const int ParticleType::GetCharge() const { return fCharge; }
double ParticleType::GetWidth() const { return 0; }
