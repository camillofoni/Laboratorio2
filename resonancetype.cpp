#include <iostream>

#include "resonancetype.hpp"

ResonanceType::ResonanceType(const char *name, double mass, int charge, double width) : fWidth(width), ParticleType(name, mass, charge) {}
double ResonanceType::GetWidth() const { return fWidth; }

void ResonanceType::Print() const
{
    ParticleType::Print();
    std::cout << "\n\tResonance width: " << GetWidth();
};