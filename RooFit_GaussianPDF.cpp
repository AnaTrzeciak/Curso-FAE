#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooGaussian.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooPlot.h"

//Exercise 1: Create a Gaussian p.d.f, generate some toy data and fit it.

using namespace RooFit;

void RooFit_GaussianPDF(){


//Observable
RooRealVar x("x","Observable", -10,10);

//Parameters
RooRealVar mean("mean", "BO Mass",0);
RooRealVar sigma("sigma", "BO Mass",3);

//PDF Object
RooGaussian gaus("Gaussian Distribution", "Gaussian Distribution", x, mean, sigma);

//Generate Events
RooDataSet* data = gaus.generate(x,10000);

//Fit
gaus.fitTo(*data);

//Plot PDF
RooPlot* xframe = x.frame();
data->plotOn(xframe);
gaus.plotOn(xframe);
xframe->Draw();
}
