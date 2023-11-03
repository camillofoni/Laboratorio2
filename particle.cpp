#include <iostream>
#include <cmath>
#include <cstdlib>
#include "particle.hpp"

/*  OVERLOAD DEL COSTRUTTORE DI PARTICLE
    Particle::Particle(const char *name) : fPx(0), fPy(0), fPz(0)
    {
        fIndex = FindParticle(name);
        if (fIndex == -1)
            std::cout << "\n\tParticle name not found\n";
    }
*/
Particle::Particle(){
  fPx=0;
  fPy=0;
  fPz=0;
}

Particle::Particle(const char *name, double px, double py, double pz) : fPx(px), fPy(py), fPz(pz)
{
  fIndex = FindParticle(name);
  if (fIndex == -1)
    std::cout << "\n\tParticle name not found\n";
}

const int Particle::GetIndex() const { return fIndex; }
void Particle::SetIndex(int index) { fIndex = index; }
void Particle::SetIndex(const char *name) { fIndex = FindParticle(name); }

double Particle::GetPx() const { return fPx; }
double Particle::GetPy() const { return fPy; }
double Particle::GetPz() const { return fPz; }
void Particle::SetP(double px, double py, double pz)
{
  fPx = px;
  fPy = py;
  fPz = pz;
}
double Particle::GetMass() const { return fParticleType[fIndex]->GetMass(); }
double Particle::GetEnergy() const { return sqrt(GetMass() * GetMass() + GetPx() * GetPx() + GetPy() * GetPy() + GetPz() * GetPz()); }
double Particle::InvMass(Particle &p) const { return sqrt(pow(GetEnergy() + p.GetEnergy(), 2) - (pow(GetPx() + p.GetPx(), 2) + pow(GetPy() + p.GetPy(), 2) + pow(GetPz() + p.GetPz(), 2))); }

int Particle::Decay2body(Particle &dau1, Particle &dau2) const
{
  if (GetMass() == 0.0)
  {
    std::cout << "Decayment cannot be preformed if mass is zero\n";
    return 1;
  }

  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  if (fIndex > -1)
  { // add width effect

    // gaussian random numbers

    float x1, x2, w, y1;

    double invnum = 1. / RAND_MAX;
    do
    {
      x1 = 2.0 * rand() * invnum - 1.0;
      x2 = 2.0 * rand() * invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while (w >= 1.0);

    w = sqrt((-2.0 * log(w)) / w);
    y1 = x1 * w;

    massMot += fParticleType[fIndex]->GetWidth() * y1;
  }

  if (massMot < massDau1 + massDau2)
  {
    std::cout << "\nDecayment cannot be preformed because mass is too low in this channel\n";
    return 2;
  }

  double pout = sqrt((massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) * (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) / massMot * 0.5;

  double norm = 2 * M_PI / RAND_MAX;

  double phi = rand() * norm;
  double theta = rand() * norm * 0.5 - M_PI / 2.;
  dau1.SetP(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi), pout * cos(theta));
  dau2.SetP(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi), -pout * cos(theta));

  double energy = sqrt(fPx * fPx + fPy * fPy + fPz * fPz + massMot * massMot);

  double bx = fPx / energy;
  double by = fPy / energy;
  double bz = fPz / energy;

  dau1.Boost(bx, by, bz);
  dau2.Boost(bx, by, bz);

  return 0;
}

void Particle::AddParticleType(const char *name, const double mass, const int charge, const double width)
{ // controlla se il ParticleType è presente, se l'array è pieno, altrimenti aggiunge nuovo ParticleType
  if ((FindParticle(name) == -1) && fNParticleType < 10)
  {
    if (width == 0)
      fParticleType[fNParticleType] = new ParticleType(name, mass, charge);
    else
      fParticleType[fNParticleType] = new ResonanceType(name, mass, charge, width);
  }
  fNParticleType++;
}

int Particle::FindParticle(const char *nomeParticella)
{
  for (int i = 0; i < fNParticleType; ++i)
  {
    if (((fParticleType[i])->GetName()) == (nomeParticella))
      return i;
  }
  return -1;
}

void Particle::Boost(double bx, double by, double bz)
{

  double energy = GetEnergy();

  // Boost this Lorentz vector
  double b2 = bx * bx + by * by + bz * bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx * fPx + by * fPy + bz * fPz;
  double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

  fPx += gamma2 * bp * bx + gamma * bx * energy;
  fPy += gamma2 * bp * by + gamma * by * energy;
  fPz += gamma2 * bp * bz + gamma * bz * energy;
}

ParticleType *Particle::fParticleType[MaxNumParticleType];

int Particle::fNParticleType = 0;

void Particle::PrintArray()
{
  for (int i = 0; i < fNParticleType; ++i)
  {
    std::cout << "\n\n\t"
              << i;
    fParticleType[i]->Print();
  }
  std::cout << "\n\n";
}

void Particle::ParticleInfo() const
{
  std::cout << "\n\tIndex: " << fIndex << "\n\tName: " << fParticleType[fIndex]->GetName()
            << "\n\tPx: " << fPx << "\tPy: " << fPy << "\tPz: " << fPz;
}