void proportions(Int_t nGen) {
    TH1F *h =new TH1F("h", "abundancies",5,0,5);
    Double_t x=0;
    for(Int_t i=0;i<nGen;i++) {
        x=gRandom->Rndm();
       if(x<0.4)h->Fill(0);
       else if(x<0.8)h->Fill(1);
       else if(x<0.85)h->Fill(2);
       else if(x<0.9)h->Fill(3);
       else if(x<0.945)h->Fill(4);
       else if(x<0.99)h->Fill(5);
       else h->Fill(6);
    }
}