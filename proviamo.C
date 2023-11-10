#include <cmath>
#include <cstdlib>
#include <iostream>

#include "particle.hpp"

void proviamo() {
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
  TCanvas *c1 = new TCanvas("c1", "Istogrammi fino ad ora1");
  TCanvas *c2 = new TCanvas("c2", "Istogrammi fino ad ora2");
  TCanvas *c3 = new TCanvas("c3", "Istogrammi fino ad ora3");
  TCanvas *c4 = new TCanvas("c4", "Istogrammi fino ad ora4");
  TCanvas *c5 = new TCanvas("c5", "Istogrammi fino ad ora5");
  TCanvas *c6 = new TCanvas("c6", "Istogrammi fino ad ora6");
  TCanvas *c7 = new TCanvas("c7", "Istogrammi fino ad ora7");
  TCanvas *c8 = new TCanvas("c8", "Istogrammi fino ad ora8");
  TCanvas *c9 = new TCanvas("c9", "Istogrammi fino ad ora9");
  TCanvas *c10 = new TCanvas("c10", "Istogrammi fino ad ora10");
  TCanvas *c11 = new TCanvas("c11", "Istogrammi fino ad ora11");
  TCanvas *c12 = new TCanvas("c12", "Istogrammi fino ad ora12");

  TH1F *h1 = new TH1F("h1", "Tipi di particelle generate", 7, 0, 7);
  TH1F *h2 =
      new TH1F("h2", "Distribuzione angolo azimutale", 1000, 0, 2 * M_PI);
  TH1F *h3 = new TH1F("h3", "Distribuzione angolo polare", 1000, 0, M_PI);
  TH1F *h4 = new TH1F("h4", "Distribuzione impulso", 500, 0, 7);
  TH1F *h5 = new TH1F("h5", "Distribuzione impulso trasverso", 500, 0, 5);
  TH1F *h6 =
      new TH1F("h6", "Distribuzione della energia delle particelle", 500, 0, 7);
  TH1F *h7 =
      new TH1F("h7", "Massa invariante per tutte le particelle", 100, 0, 10);
  h7->Sumw2();
  TH1F *h8 =
      new TH1F("h8", "Massa invariante per cariche discordi", 100, 0, 10);
  h8->Sumw2();
  TH1F *h9 =
      new TH1F("h9", "Massa invariante per cariche concordi", 100, 0, 10);
  h9->Sumw2();
  TH1F *h10 = new TH1F("h10", "Massa invariante per pioni caoni segno discorde",
                       100, 0, 10);
  h10->Sumw2();
  TH1F *h11 = new TH1F(
      "h11", "Massa invariante per pioni e kaoni segno concorde", 100, 0, 10);
  h11->Sumw2();
  TH1F *h12 = new TH1F("h12", "Massa invariante per figlie k*", 100, 0, 3);
  h12->Sumw2();

  for (int j = 0; j < 1e5; ++j) {
    int eventParticlesSize = 0;
    for (int i = 0; i < 100; ++i) {
      Double_t type = gRandom->Rndm();
      Double_t phi = gRandom->Uniform(0, 2 * M_PI);
      Double_t theta = gRandom->Uniform(0, M_PI);
      Double_t p = gRandom->Exp(1);
      int decaycounter = 0;
      if (type < 0.4)  // pioni+
      {
        EventParticles[i].SetIndex(0);

      } else if (type < 0.8)  // pioni-
      {
        EventParticles[i].SetIndex(1);

      }

      else if (type < 0.85)  // kaoni+
      {
        EventParticles[i].SetIndex(2);

      } else if (type < 0.9)  // kaoni-
      {
        EventParticles[i].SetIndex(3);

      } else if (type < 0.945)  // protoni+
      {
        EventParticles[i].SetIndex(4);

      } else if (type < 0.99)  // protoni-
      {
        EventParticles[i].SetIndex(5);

      } else  // k*
      {
        EventParticles[i].SetIndex(6);
        if (gRandom->Rndm() < 0.5) {
          EventParticles[100 + decaycounter].SetIndex(0);
          EventParticles[101 + decaycounter].SetIndex(3);
          ++eventParticlesSize;
          ++eventParticlesSize;

        } else {
          EventParticles[100 + decaycounter].SetIndex(1);
          EventParticles[101 + decaycounter].SetIndex(2);
          ++eventParticlesSize;
          ++eventParticlesSize;
        }
        /*EventParticles[i].Decay2body(EventParticles[100 + decaycounter],
                                     EventParticles[101 + decaycounter]);
        h12->Fill(EventParticles[100 + decaycounter].InvMass(
            EventParticles[101 + decaycounter]));
        decaycounter++;*/
      }
      EventParticles[i].SetP(p * sin(theta) * cos(phi),
                             p * sin(theta) * sin(phi), p * cos(theta));
      if (EventParticles[i].GetIndex() == 6) {
        EventParticles[i].Decay2body(EventParticles[100 + decaycounter],
                                     EventParticles[101 + decaycounter]);
        h12->Fill(EventParticles[100 + decaycounter].InvMass(
            EventParticles[101 + decaycounter]));
        decaycounter++;
      }
      h1->Fill(EventParticles[i].GetIndex());
      h2->Fill(phi);
      h3->Fill(theta);
      h4->Fill(p);
      h5->Fill(p * sin(theta));
      h6->Fill(EventParticles[i].GetEnergy());
      ++eventParticlesSize;
    };

    for (int i = 0; i < eventParticlesSize; ++i) {
      int firstIndex = EventParticles[i].GetIndex();
      if ((firstIndex % 2) == 1)  // particelle negative
      {
        for (int k = 0; k < eventParticlesSize; ++k) {
          int secondIndex = EventParticles[k].GetIndex();
          if (((secondIndex % 2) == 1) &&
              (i != k))  // particelle negative di indice diverso
          {
            h9->Fill(EventParticles[firstIndex].InvMass(
                EventParticles[secondIndex]));
            if (firstIndex == 1 && secondIndex == 3)  // pioni e kaoni negativi
            {
              h11->Fill(EventParticles[firstIndex].InvMass(
                  EventParticles[secondIndex]));
            }
          }
        }
      } else if ((firstIndex % 2) == 0)  // particelle positive
      {
        for (int j = 0; j < eventParticlesSize; ++j) {
          int secondIndex = EventParticles[j].GetIndex();

          if ((secondIndex % 2) == 1)  // particelle negative
          {
            // particelle discordi
            h8->Fill(EventParticles[firstIndex].InvMass(
                EventParticles[secondIndex]));
            if ((firstIndex == 0 && secondIndex == 3) ||
                (firstIndex == 2 &&
                 secondIndex == 1))  // pioni e kaoni discordi
            {
              h10->Fill(EventParticles[firstIndex].InvMass(
                  EventParticles[secondIndex]));
            }

          } else if ((secondIndex % 2) == 0)  // particelle positive
          {
            h9->Fill(EventParticles[firstIndex].InvMass(
                EventParticles[secondIndex]));
            if (firstIndex == 0 && secondIndex == 2) {
              h11->Fill(EventParticles[firstIndex].InvMass(
                  EventParticles[secondIndex]));
            }
          }
        }
      }
    }
  }

  /*TFile *Laboratorio2 = new TFile("Laboratorio2", "CREATE");
  h1->Write();
  h2->Write();
  h3->Write();
  h4->Write();
  h5->Write();
  h6->Write();
  h7->Write();
  h8->Write();
  h9->Write();
  h10->Write();
  h11->Write();
  h12->Write();
  Laboratorio2->Close();*/
  
  
  h7-> Add(h8, h9);
  c1->cd();
  h1->Draw();
  c2->cd();
  h2->Draw();
  c3->cd();
  h3->Draw();
  c4->cd();
  h4->Draw();
  c5->cd();
  h5->Draw();
  c6->cd();
  h6->Draw();
  c7->cd();
  h7->Draw();
  c8->cd();
  h8->Draw();
  c9->cd();
  h9->Draw();
  c10->cd();
  h10->Draw();
  c11->cd();
  h11->Draw();
  c12->cd();
  h12->Draw();
}
