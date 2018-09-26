#include "TFile.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void sampling_GEN()
{
  for(int i=3;i<10;i++)
  {
    char c[20];
    sprintf(c,"%d",i);
    string tem=c;
    sub_sample(i,c);
  }
}
void sub_sample(int i,string name)
{
  ifstream amp("../xgb_weight_DIY_truth_all.txt");         
  std::vector<double> vamp;
  double myd;
  double max =0;

  while(!amp.eof())
{
  amp >> myd;
  vamp.push_back(myd);
 
  if(myd > max)
  max = myd;
 }

  cout<<max<<endl;  
  int num =   vamp.size() -1;
  cout << "vamp.size()="<<vamp.size() << endl;
  amp.close();
  int rand1=10000+i;
  TRandom3 rg(rand1);
  TString filename="DIY_truth_"+name+".root";

  TFile *nin = new TFile("/home/xiongxa/ML_reweighting/DATA/EtaPi0Pi0/Final/MCtruth_forDIY_all_final.root");
  TTree *ntuple = (TTree *) nin->Get("final");

  TFile *out = new TFile(filename,"recreate");
  TTree *newtree = ntuple->CloneTree(0); 

  TH1D *h1=new TH1D("h1","h1",200,1,3);
 
  float Px_eta,Py_eta,Pz_eta,E_eta,Px_pi01,Py_pi01,Pz_pi01,E_pi01,Px_pi02,Py_pi02,Pz_pi02,E_pi02; 
 
  ntuple->SetBranchAddress("Px_eta",&Px_eta);
  ntuple->SetBranchAddress("Py_eta",&Py_eta);
  ntuple->SetBranchAddress("Pz_eta",&Pz_eta);
  ntuple->SetBranchAddress("E_eta",&E_eta);

  ntuple->SetBranchAddress("Px_pi01",&Px_pi01);
  ntuple->SetBranchAddress("Py_pi01",&Py_pi01);
  ntuple->SetBranchAddress("Pz_pi01",&Pz_pi01);
  ntuple->SetBranchAddress("E_pi01",&E_pi01);

  ntuple->SetBranchAddress("Px_pi02",&Px_pi02);
  ntuple->SetBranchAddress("Py_pi02",&Py_pi02);
  ntuple->SetBranchAddress("Pz_pi02",&Pz_pi02);
  ntuple->SetBranchAddress("E_pi02",&E_pi02);
  Long64_t nevent = ntuple->GetEntries();
  cout <<"nevent total="<<nevent<< endl;
  int acc = 0;

  for(Long64_t j=0; j<nevent; j++ )
 {
   ntuple->GetEntry(j);
   Double_t mx;
   double rand = rg.Rndm();
   //cout<<"rand="<<rand<<endl;
   if(rand < vamp[j]/max)
{
      TLorentzVector L_gam,L_eta,L_pi01,L_pi02,L_tem;
      //L_gam.SetPxPyPzE(Px_gam,Py_gam,Pz_gam,E_gam);
      L_eta.SetPxPyPzE(Px_eta,Py_eta,Pz_eta,E_eta);
      L_pi01.SetPxPyPzE(Px_pi01,Py_pi01,Pz_pi01,E_pi01);
      L_pi02.SetPxPyPzE(Px_pi02,Py_pi02,Pz_pi02,E_pi02);
      L_tem=L_eta+L_pi01+L_pi02;
      mx=L_tem.M();
      //mx=sqrt((E_eta+E_pi01+E_pi02)**2 - (Px_eta+Px_pi01+Px_pi02)**2 - (Py_eta+Py_pi01+Py_pi02)**2 - (Pz_eta+Pz_pi01+Pz_pi02)**2 );
     //if(acc==6000) break;
      h1->Fill(mx);
     newtree->Fill();
     acc=acc+1;
/*
   in<<"3"<<"\n";
   in<<"310"<<" "<<MCPxP2<<" "<<MCPyP2<<" "<<MCPzP2<<" "<<MCEnP2<<"\n";
   in<<"310"<<" "<<MCPxP3<<" "<<MCPyP3<<" "<<MCPzP3<<" "<<MCEnP3<<"\n";
   in<<"22"<<" "<<MCPxP1<<" "<<MCPyP1<<" "<<MCPzP1<<" "<<MCEnP1<<"\n";
   in<<"\n";*/
//   rec++;
}
} 

 cout <<"acc events="<<acc<<endl;
  h1->Write();
  newtree->Write();
  nin->Close();
  out->Write();
  out->Close();

    }

