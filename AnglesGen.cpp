TH2F *h =new TH2F("h","",10000,0,Tmath::Pi(),10000,0,2*TMath::Pi());

double_t phi, theta=0;
for(Int_t i=0; i<nGen; i++){
     theta=gRandom->Rndm()*TMath::Pi();
     phi=gRandom->Rndm()*2*TMath::Pi();
     h->Fill(theta,phi);
};
