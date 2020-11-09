import ROOT
from ROOT import TFile, gDirectory
from ROOT import TH1D, TCanvas, TH2D, TH2F

f = TFile('experiment.root')

mychain = gDirectory.Get('tree1')
entries = mychain.GetEntries()

fsave = TFile('histograms_py.root','RECREATE') ###Arquivo onde esta sendo salvo os histogramas

### The Set-up code goes here.
###


#chi2 histogram
chi2Hist = TH1D("chi2","Histogram of Chi2", 100, 0, 20)
chi2Hist.GetXaxis().SetTitle("chi2")
chi2Hist.GetYaxis().SetTitle("number of events")

#ebeam histogram
ebeamHist = TH1D("ebeam","Histogram of ebeam",100,149.0,151.0)
ebeamHist.GetXaxis().SetTitle("ebeam")
ebeamHist.GetYaxis().SetTitle("number of events")

#Scatterplot chi2 x ebeam
scatter = TH2F("Scatter","Scatterplot chi2 x ebeam",100,149.0,151.0,100,0,20)
scatter.GetXaxis().SetTitle("ebeam")
scatter.GetYaxis().SetTitle("chi2")

#Histogram pt
ptHist = TH1D("pt","Histogram of pt",100,0,30)
ptHist.GetXaxis().SetTitle("pt = sqrt(px*px+py*py)")


for jentry in range( entries ):
   
   ientry = mychain.LoadTree( jentry )
   if ientry < 0:
      break      
   nb = mychain.GetEntry( jentry )
   if nb <= 0:
      continue  
### The Loop code goes here.
   #chi2 = mychain.chi2
   #chi2Hist.Fill(chi2)
   #ebeam = mychain.ebeam
   #ebeamHist.Fill(ebeam)
   #scatter.Fill(ebeam,chi2)
     
### The Wrap-up code goes here
canvas = TCanvas()
#chi2Hist.Draw()
#ebeamHist.Fit("gaus")
#ebeamHist.Draw()
#scatter.Draw()

canvas.Draw()
fsave.Write()