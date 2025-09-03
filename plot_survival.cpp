#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <vector>
#include <cmath>
#include "PlotStyle.h"
#include "Oscillation.h"

int main() {
    SetElegantStyle();
    double dm2 = 2.5e-3;
    double theta = 0.8;
    double s2 = std::pow(std::sin(2 * theta), 2);
    int N = 500;
    TGraph g(N);
    for (int i = 0; i < N; ++i) {
        double LE = i * 4.0;
        double x = 1.267 * dm2 * LE;
        double p = 1 - s2 * std::pow(std::sin(x), 2);
        g.SetPoint(i, LE, p);
    }
    TCanvas c("surv", "", 800, 600);
    g.SetLineWidth(2);
    g.GetXaxis()->SetTitle("L/E [km/GeV]");
    g.GetYaxis()->SetTitle("P(#nu_{#mu}#rightarrow#nu_{#mu})");
    g.GetYaxis()->SetRangeUser(0.0, 1.0);
    g.Draw("AL");
    c.SaveAs("survival_LE.pdf");
    return 0;
}

