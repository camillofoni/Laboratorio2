#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP
#include "particletype.hpp"

class ResonanceType : public ParticleType
{
public:
    ResonanceType(const char *name, const double mass, const int charge, const double width);

    const double GetWidth() const;

    void Print() const;

private:
    const double fWidth;
};

#endif