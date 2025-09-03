#include <TCanvas.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TAxis.h>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "PlotStyle.h"
#include "Oscillation.h"

int main(int argc, char **argv) {
    SetElegantStyle();

    double L = 1300.0;
    double E = 2.5;

    if (argc > 1) {
        L = std::atof(argv[1]);
    }

    if (argc > 2) {
        E = std::atof(argv[2]);
    }

    PMNSParams nh{0.5843, 0.830, 0.148, 7.42e-5, 2.517e-3, 0.0};
    PMNSParams ih{0.5843, 0.830, 0.148, 7.42e-5, -2.498e-3, 0.0};
    PMNSVacuum pmns_nh(nh), pmns_ih(ih);

    int N = 361;
    TGraph g_nh(N), g_ih(N);
    for (int i = 0; i < N; ++i) {
        double d = i * M_PI / 180.0;
        PMNSVacuum A_nh({nh.th12, nh.th23, nh.th13, nh.dm21, nh.dm31, d});
        PMNSVacuum Abar_nh({nh.th12, nh.th23, nh.th13, nh.dm21, nh.dm31, -d});
        double x = A_nh.prob(1, 0, L, E);
        double y = Abar_nh.prob(1, 0, L, E);
        g_nh.SetPoint(i, x, y);

        PMNSVacuum A_ih({ih.th12, ih.th23, ih.th13, ih.dm21, ih.dm31, d});
        PMNSVacuum Abar_ih({ih.th12, ih.th23, ih.th13, ih.dm21, ih.dm31, -d});
        double xi = A_ih.prob(1, 0, L, E);
        double yi = Abar_ih.prob(1, 0, L, E);
        g_ih.SetPoint(i, xi, yi);
    }

    TCanvas c("c", "", 800, 700);
    g_nh.SetLineWidth(3);
    g_nh.SetLineColor(kBlue + 1);

    g_ih.SetLineWidth(3);
    g_ih.SetLineColor(kRed + 1);
    g_ih.SetLineStyle(2);

    g_nh.GetXaxis()->SetTitle("P(\n#nu_{#mu}\\rightarrow\n#nu_{e})");
    g_nh.GetYaxis()->SetTitle("P(\n#bar{#nu}_{#mu}\\rightarrow\n#bar{#nu}_{e})");
    g_nh.GetXaxis()->SetLimits(0.0, 0.6);
    g_nh.GetYaxis()->SetRangeUser(0.0, 0.6);
    g_nh.Draw("AL");
    g_ih.Draw("L SAME");

    TLegend leg(0.58, 0.74, 0.88, 0.89);
    leg.SetBorderSize(0);
    leg.SetFillStyle(0);
    leg.AddEntry(&g_nh, "NH", "l");
    leg.AddEntry(&g_ih, "IH", "l");
    leg.Draw();

    TLatex t;
    t.SetNDC();
    t.SetTextSize(0.045);
    t.DrawLatex(0.14, 0.92, Form("L=%.0f km  E=%.1f GeV", L, E));

    c.SaveAs("biprob.pdf");
    c.SaveAs("biprob.png");
    return 0;
}
