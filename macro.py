import ROOT
from ROOT import TMath, TFile, TH1F, gDirectory, TCanvas, TH1D

f = TFile("experiment.root")
tree1 = ROOT.gROOT.FindObject("tree1")

mychain = gDirectory.Get('tree1')
entries = mychain.GetEntries()

c1 = TCanvas( 'c1', 'Canvas', 800, 600 )

chi2 = mychain.chi2

