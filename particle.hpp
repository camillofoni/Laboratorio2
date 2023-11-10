#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "resonancetype.hpp"

class Particle
{
public:
    // Particle(const char *name);
    Particle();
    Particle(const char *name, double px = 0, double py = 0, double pz = 0);

    const int GetIndex() const;
    void SetIndex(int index);
    void SetIndex(const char *name);
    double GetPx() const;
    double GetPy() const;
    double GetPz() const;
    void SetP(double px, double py, double pz);
    double GetMass() const;
    double GetEnergy() const;
    double InvMass(Particle &p) const;

    static void AddParticleType(const char *name, const double mass, const int charge, const double width = 0);

    static void PrintArray();

    void ParticleInfo() const;

    int Decay2body(Particle &dau1, Particle &dau2) const;

private:
    static const int MaxNumParticleType = 10;

    static ParticleType *fParticleType[MaxNumParticleType]; // Array di puntatori a istanze di ParticleType, static perchè comune a tutte le istanze di Particle

    int fIndex; // indice che permette di identificare a che ParticleType/ResonanceType appartiene l'istanza di Particle e attribuirle nome, massa, carica e larghezza
    double fPx; // quantità di moto di ogni particella
    double fPy;
    double fPz;

    static int fNParticleType; // numero di ParticleType presenti nell'array

    static int FindParticle(const char *nomeParticella);

    void Boost(double bx, double by, double bz);
};

#endif