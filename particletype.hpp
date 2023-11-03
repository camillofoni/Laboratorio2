#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

class ParticleType
{
public:
    ParticleType(const char *name, const double mass, const int charge);

    const char *GetName() const;
    const double GetMass() const;
    const int GetCharge() const;
    virtual int ParticleType::GetWidth() const;

    virtual void Print() const;

private:
    const char *fName;
    const double fMass;
    const int fCharge;
};

#endif