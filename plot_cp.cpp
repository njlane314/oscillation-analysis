#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <vector>
#include <cmath>
#include "PlotStyle.h"
#include "Oscillation.h"

int main() {
    SetElegantStyle();
    double L = 1300.0;
    double E = 2.5;
    PMNSParams nh{0.5843, 0.830, 0.148, 7.42e-5, 2.517e-3, 0.0};
    int N = 361;
    TGraph g(N);
    for (int i = 0; i < N; ++i) {
        double d = i * M_PI / 180.0;
        PMNSVacuum pmns({nh.th12, nh.th23, nh.th13, nh.dm21, nh.dm31, d});
        double p = pmns.prob(1, 0, L, E);
        g.SetPoint(i, d, p);
    }
    TCanvas c("cp", "", 800, 600);
    g.SetLineWidth(2);
    g.GetXaxis()->SetTitle("#delta_{CP} [rad]");
    g.GetYaxis()->SetTitle("P(#nu_{#mu}#rightarrow#nu_{e})");
    g.GetXaxis()->SetLimits(0, 2 * M_PI);
    g.GetYaxis()->SetRangeUser(0.0, 0.2);
    g.Draw("AL");
    c.SaveAs("cp_phase.pdf");
    return 0;
}

