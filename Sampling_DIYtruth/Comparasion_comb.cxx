#include "TMath.h"
//#include "fstream.h"
#include "string"
using namespace std;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
TString FileName1()
{
  TString f1="sample.root";
  return f1;
}
TString FileName2()
{
  TString f2="sample.root";
  return f2;
}
TString FileName3()
{
  TString f3="sample.root";
  return f3;
}
TString CutName1()
{
  TString f1="";
  return f1;
}
TString CutName2()
{
  TString f1="";
  return f1;
}
TString TreeName1()
{
  TString f1="final";
  return f1;
}
void plotdata(TH1F *h1,const char *name1,const char *name2)
{
  //h1->GetXaxis()->SetTickLength(0.04);
  //h1->GetXaxis()->SetLabelSize(0.04);
  //h1->GetXaxis()->SetTitleOffset(1.5);
  h1->GetXaxis()->SetTitle(name1);
  h1->GetXaxis()->CenterTitle();
  //h1->GetYaxis()->SetTickLength(0.04);
  //h1->GetYaxis()->SetLabelSize(0.04);
  //h1->GetYaxis()->SetTitleOffset(1.5);
  h1->GetYaxis()->SetTitle(name2);
  h1->GetYaxis()->CenterTitle();
  h1->SetMarkerStyle(20);
  //h1->SetMarkerSize(0.7);
  h1->SetMarkerColor(2.);
  //h1->GetYaxis()->SetRangeUser(0,1.2*h1->GetMaximum());
  h1->Draw("e");
}
void plotincl(TH1F *h1)
{
  //h1->GetXaxis()->SetTickLength(0.04);
  //h1->GetXaxis()->SetLabelSize(0.04);
  //h1->GetXaxis()->SetTitleOffset(1.1);
  //h1->GetYaxis()->SetTickLength(0.04);
  //h1->GetYaxis()->SetLabelSize(0.04);
  //h1->GetYaxis()->SetTitleOffset(1.8);
  //h1->GetYaxis()->SetTitle("EVENTS");
  h1->SetLineWidth(5);
  h1->SetLineStyle(3);
  h1->SetLineColor(3);
  //h1->GetYaxis()->SetRangeUser(0,1.2*h1->GetMaximum());
  h1->Draw("same");
}
void plotphsp(TH1F *h1)
{
  //h1->GetXaxis()->SetTickLength(0.04);
  //h1->GetXaxis()->SetLabelSize(0.04);
  //h1->GetXaxis()->SetTitleOffset(1.1);
  //h1->GetYaxis()->SetTickLength(0.04);
  //h1->GetYaxis()->SetLabelSize(0.04);
  //h1->GetYaxis()->SetTitleOffset(1.8);
  //h1->GetYaxis()->SetTitle("EVENTS");
  h1->SetLineWidth(5);
  h1->SetLineStyle(3);
  h1->SetLineColor(6);
  //h1->GetYaxis()->SetRangeUser(0,1.2*h1->GetMaximum());
  h1->Draw("same");
}
double max(double a,double b,double c)
{
  double maxup1 =a>b?a:b;
  double int maxup2 =c>maxup1?c:maxup1;
  return maxup2;
}
void plot3(TString name,const char *namex,const char *namey,int Nbin,double low,double up)
{
   TFile  *f1 = new TFile(FileName1());
   TFile  *f2 = new TFile(FileName2());
   TFile  *f3 = new TFile(FileName3());
   TTree *chain1 = (TTree*)f1->Get(TreeName1());
   TTree *chain2 = (TTree*)f2->Get(TreeName1());
   TTree *chain3 = (TTree*)f3->Get(TreeName1());
   TH1F *data= new TH1F("data","",Nbin,low,up);
   TH1F *incl= new TH1F("incl","",Nbin,low,up);
   TH1F *phsp= new TH1F("phsp","",Nbin,low,up);

   TString hisname=name+ " >> data";
   TString hisname1=name+ " >> incl";
   TString hisname2=name+ " >> phsp";
   chain1->Draw(hisname, CutName1());
   chain2->Draw(hisname1,CutName1());
   chain3->Draw(hisname2,CutName1());

   cout<<"Total="<<data->Integral()<<endl;
   incl->Scale(1310.6/1225);
   //phsp->Scale(data->Integral(0,60)/phsp->Integral());//etap
   phsp->Scale(data->Integral()/phsp->Integral());
   plotdata(data,namex,namey);
   data->GetYaxis()->SetRangeUser(0,1.2*max(data->GetMaximum(),incl->GetMaximum(),phsp->GetMaximum()));
   plotincl(incl);
   plotphsp(phsp);
   TLegend *leg = new TLegend(.73,.74,.88,.88,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetTextSize(0.06);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetShadowColor(0);
   leg->AddEntry(data,"data","p");
   leg->AddEntry(incl,"incl","l");
   leg->AddEntry(phsp,"phsp","l");
   leg->Draw();
   TPaveText *pt = new TPaveText(0.1796482,0.8409091,0.4032663,0.8811189,"BRNDC");
   pt->SetFillStyle(0);
   pt->SetBorderSize(0);
   pt->SetTextAlign(10);
	 pt->SetTextSize(0.06);
	 text = pt->AddText("J/#psi->#gamma#eta'#eta#eta (#eta'->#eta#pi^{+}#pi^{-},#eta->#gamma#gamma)");
   pt->Draw();
   TString printname="graph/"+name+".eps";
   canvas->Print(printname);
   //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
}
void plot2D(TString name1,TString name2,const char *namex,const char *namey,int Nbin2,double low2,double up2,int Nbin1,double low1,double up1)
{
  TFile  *f1 = new TFile(FileName1());
  TFile  *f2 = new TFile(FileName2());
  TFile  *f3 = new TFile(FileName3());
  TTree *chain1 = (TTree*)f1->Get(TreeName1());
  TTree *chain2 = (TTree*)f2->Get(TreeName1());
  TTree *chain3 = (TTree*)f3->Get(TreeName1());
  TH2F *h2= new TH2F(name2,name2,Nbin1,low1,up1,Nbin2,low2,up2);
  TString hisname=name1+":"+name2+">>"+name2; 
  chain1->Draw(hisname,CutName1());
  const Int_t colNum = 40;
  int colors[colNum];
  for(int i=0;i<colNum;i++)
  {
    TColor *color = new TColor(45+i,
        (1+i/((colNum)*0.5)),
        (1+i/((colNum)*0.5)),
        (1+i/((colNum)*0.5)),"");
    colors[i]=i*1.5+45;
    colors[0]=0;
    colors[1]=0;
  }
  gStyle->SetPalette(colNum,colors);
  //h2->Draw("colz");
  h2->Draw("cont4z"); 
  h2->GetYaxis()->SetTitle(namex);
  h2->GetYaxis()->CenterTitle();
  h2->GetXaxis()->SetTitle(namey);
  h2->GetXaxis()->CenterTitle();
  TString printname="graph/"+name1+"_"+name2+".eps";
  TFile *f_new = new TFile("data_output.root","UPDATE");
  h2->Write();
  f_new->Close();
  canvas->Print(printname);
}
void AddPlot(const int num,char *str[],const char *namex,const char *namey,int Nbin,double low,double up);
void AddPlot(const int num,char *str[],const char *namex,const char *namey,int Nbin,double low,double up)
{
   TH1F* data1[num],*incl1[num],*phsp1[num];
   TFile  *f1 = new TFile(FileName1());
   TFile  *f2 = new TFile(FileName2());
   TFile  *f3 = new TFile(FileName3());
   TTree *chain1 = (TTree*)f1->Get(TreeName1());
   TTree *chain2 = (TTree*)f2->Get(TreeName1());
   TTree *chain3 = (TTree*)f3->Get(TreeName1());
   TH1F *data= new TH1F("data","",Nbin,low,up);
   TH1F *incl= new TH1F("incl","",Nbin,low,up);
   TH1F *phsp= new TH1F("phsp","",Nbin,low,up);
   for (int i=1; i<num;i++)
   {
     //cout<<"str="<<str[i]<<endl;
     TString name=str[i];
     TString hisname1=name + "_data";
     data1[i]= new TH1F(hisname1,"",Nbin,low,up);
     TString hisname=name + ">>" + hisname1;
     //cout<<"hisname="<<hisname<<endl;
     chain1->Draw(hisname,CutName1());
     data->Add(data1[i],1);
   }
   for (int i=1; i<num;i++)
   {
     TString name=str[i];
     TString hisname1=name + "_incl";
     incl1[i]= new TH1F(hisname1,"",Nbin,low,up);
     TString hisname=name + ">>" + hisname1;
     chain2->Draw(hisname,CutName1());
     incl->Add(incl1[i],1);
   }
   for (int i=1; i<num;i++)
   {
     TString name=str[i];
     TString hisname1=name + "_phsp";
     phsp1[i]= new TH1F(hisname1,"",Nbin,low,up);
     TString hisname=name + ">>" + hisname1;
     chain3->Draw(hisname,CutName1());
     phsp->Add(phsp1[i],1);
   }

   incl->Scale(1310.6/1225);
   phsp->Scale(data->Integral()/phsp->Integral());
   plotdata(data,namex,namey);
   data->GetYaxis()->SetRangeUser(0,1.2*max(data->GetMaximum(),incl->GetMaximum(),phsp->GetMaximum()));
   plotincl(incl);
   plotphsp(phsp);
   TLegend *leg = new TLegend(.73,.74,.88,.88,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetTextSize(0.06);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetShadowColor(0);
   leg->AddEntry(data,"data","p");
   leg->AddEntry(incl,"incl","l");
   leg->AddEntry(phsp,"phsp","l");
   leg->Draw();
   TPaveText *pt = new TPaveText(0.1796482,0.8409091,0.4032663,0.8811189,"BRNDC");
   pt->SetFillStyle(0);
   pt->SetBorderSize(0);
   pt->SetTextAlign(10);
	 pt->SetTextSize(0.06);
	 text = pt->AddText("J/#psi->#gamma#eta'#eta#eta (#eta'->#eta#pi^{+}#pi^{-},#eta->#gamma#gamma)");
   pt->Draw();
   TString name=str[2];
   TString printname="graph/"+name+"_total.eps";
   canvas->Print(printname);
   //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void Comparasion_comb()
{
   TCanvas *canvas = new TCanvas("canvas","canvas",800,600); 
   canvas->SetFillColor(0);
   canvas->SetBorderSize(2);
   canvas->SetLeftMargin(0.15);
   canvas->SetRightMargin(0.15);
   canvas->SetTopMargin(0.05);
   canvas->SetBottomMargin(0.23);
   canvas->SetFrameFillStyle(0);
   canvas->SetFrameBorderMode(0);
   gStyle->SetLegendBorderSize(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetPadBorderSize(0);
   gStyle->SetPadTopMargin(0.05);
   gStyle->SetPadBottomMargin(0.12);
   gStyle->SetPadLeftMargin(0.05); //0.21
   gStyle->SetPadRightMargin(0.05); //0.05
   //gPad->SetLogy();
   gStyle->SetOptStat(0000);
   gStyle->SetOptTitle(0000);
   //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
   plot2D("Mpi01pi02","Metapi01pi02","M(#pi^{0}#pi^{0})/(GeV/c^{2})","M(#eta#pi^{0}#pi^{0})/(GeV/c^{2})",50,0,2.5,50,2,2.8);
   plot2D("Metapi01","Metapi01pi02","M(#eta#pi^{0})/(GeV/c^{2})","M(#eta#pi^{0}#pi^{0})/(GeV/c^{2})",50,0.5,2.6,50,2,2.8);
   plot2D("Metapi02","Metapi01pi02","M(#eta#pi^{0})/(GeV/c^{2})","M(#eta#pi^{0}#pi^{0})/(GeV/c^{2})",50,0.5,2.6,50,2,2.8);
   plot2D("Metapi01","Metapi02","M(#eta#pi^{0})/(GeV/c^{2})","M(#eta#pi^{0})/(GeV/c^{2})",50,0.5,2.6,50,0.5,2);
   //plot2D("epp_metaeta*epp_metaeta","epp_meta1etap*epp_meta1etap","M^{2}(#eta#eta)/(GeV/c^{2})^{2}","M^{2}(#eta'#eta)/(GeV/c^{2})^{2}",20,1,4,20,1.96,5.76);
   //plot2D("epp_metaeta*epp_metaeta","epp_meta2etap*epp_meta2etap","M^{2}(#eta#eta)/(GeV/c^{2})^{2}","M^{2}(#eta'#eta)/(GeV/c^{2})^{2}",20,1,4,20,1.96,5.76);
   //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
   canvas->SetRightMargin(0.05);
   //plot3("epp_metaetaetap","M(#eta'#eta#eta)","Events/(0.02GeV/c^{2})",55,2.05,3.15);
   ////plot3("epp_metaetaetap","M(#eta'#eta#eta)","Events/(0.02GeV/c^{2})",40,2.05,2.85);
   //plot3("epp_chisq","#chi^{2}","Events",100,0,200);
   //plot3("epp_mpipi","M(#pi^{+}#pi^{-})","Events/(GeV/c^{2})",50,0,1.2);
   //plot3("epp_metaetaeta","M(#eta#eta#eta)","Events/(GeV/c^{2})",50,0,3.1);
   //plot3("epp_metap","M(#eta')","Events/(0.005GeV/c^{2})",60,0.8,1.1);
   ////plot3("epp_metaeta","M(#eta_{1}#eta_{2})","Events/(GeV/c^{2})",50,0,3.1);
   //plot3("epp_metaeta","M(#eta_{1}#eta_{2})","Events/(GeV/c^{2})",50,1,2.1);
   //plot3("epp_mgametap","M(#gamma#eta')","Events/(GeV/c^{2})",50,0,3.1);
   //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
   //char *temp_etaeta[4]={"","epp_metaeta12","epp_metaeta13","epp_metaeta23"};
   //AddPlot(4,temp_etaeta,"M(#eta#eta)","Events/(0.04GeV/c^{2})",50,0.5,2.5);
   //char *temp_geta[4]={"","epp_mgameta1","epp_mgameta2","epp_mgameta3"};
   //AddPlot(4,temp_geta,"M(#gamma#eta)","Events/(GeV/c^{2})",50,0,2);
   //char *temp_etaetap[3]={"","epp_meta1etap","epp_meta2etap"};
   //AddPlot(3,temp_etaetap,"M(#eta#eta')","Events/(0.02GeV/c^{2})",50,1.5,2.5);
   //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
}
