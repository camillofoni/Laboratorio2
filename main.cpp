#include <iostream>
#include <cmath>
#include "particle.hpp"
// prova github
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
    TCanvas *prova = new TCanvas("prova","Istogrammi fino ad ora");
    prova->Divide(3,3);
    
    TH1F *h1 = new TH1F("h1", "Tipi di particelle generate", 7, 0, 7 ); 
    TH1F *h2 = new TH1F("h2", "Distribuzione angolo azimutale", 1000, 0, 2 * M_PI);
    TH1F *h3 = new TH1F("h3", "Distribuzione angolo polare", 1000, 0, M_PI);
    TH1F *h4 = new TH1F("h4", "Distribuzione impulso",500, 0, 7);
    TH1F *h5 = new TH1F("h5", "Distribuzione impulso trasverso", 500, 0, 5);
    TH1F *h6 = new TH1F("h6", "Distribuzione della energia delle particelle", 500, 0, 7);
    TH1F *h11 = new TH1F("h11", "Massa invariante per k*", 500, 0.6, 1.2);
    h11->Sumw2();
    for (int j = 0; j < 1e5; ++j)
    {
        for (int i = 0; i < 100; ++i)
        {
            Double_t type = gRandom->Rndm();
            Double_t phi = gRandom->Uniform(0, 2 * M_PI);
            Double_t theta = gRandom->Uniform(0, M_PI);
            Double_t p = gRandom->Exp(1);
            int decaycounter = 0;
            if (type < 0.4) // pioni+
            {
                EventParticles[i].SetIndex(0);
            }
            else if (type < 0.8) // pioni-
            {
                EventParticles[i].SetIndex(1);
            }

            else if (type < 0.85) // kaoni+
            {
                EventParticles[i].SetIndex(2);
            }
            else if (type < 0.9) // kaoni-
            {
                EventParticles[i].SetIndex(3);
            }
            else if (type < 0.945) // protoni+
            {
                EventParticles[i].SetIndex(4);
            }
            else if (type < 0.99) // protoni-
            {
                EventParticles[i].SetIndex(5);
            }
            else // k*
            {
                EventParticles[i].SetIndex(6);
                if (gRandom->Rndm() < 0.5)
                {
                    EventParticles[100 + decaycounter].SetIndex(0);
                    EventParticles[101 + decaycounter].SetIndex(3);
                }
                else
                {
                    EventParticles[100 + decaycounter].SetIndex(1);
                    EventParticles[101 + decaycounter].SetIndex(2);
                }
                EventParticles[i].Decay2body(EventParticles[100 + decaycounter], EventParticles[101 + decaycounter]);
                h11->Fill(EventParticles[100+ decaycounter].InvMass(EventParticles[101+ decaycounter]));
                decaycounter++;
            }
            EventParticles[i].SetP(p * sin(theta) * cos(phi), p * sin(theta) * sin(phi), p * cos(theta));
            h1->Fill(EventParticles[i].GetIndex());
            h2->Fill(phi);
            h3->Fill(theta);
            h4->Fill(p);
            h5->Fill(p*sin(theta));
            h6->Fill(EventParticles[i].GetEnergy());
        }
    }
     

}
