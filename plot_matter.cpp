#include <TCanvas.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TAxis.h>
#include <vector>
#include <cmath>
#include "PlotStyle.h"
#include "Oscillation.h"

int main() {
    SetElegantStyle();
    double L = 1300.0;
    double rho = 3.0;
    double Ye = 0.5;
    double dm2 = 2.5e-3;
    double th = 0.148;
    int N = 200;
    TGraph g_vac(N), g_mat(N);
    for (int i = 0; i < N; ++i) {
        double E = 0.2 + 0.03 * i;
        double x = 1.267 * dm2 * L / E;
        double pvac = std::pow(std::sin(2 * th), 2) * std::pow(std::sin(x), 2);
        g_vac.SetPoint(i, E, pvac);
        double A = 1.52e-4 * rho * Ye * E;
        double cos2 = std::cos(2 * th);
        double sin2 = std::sin(2 * th);
        double denom = std::sqrt(std::pow(cos2 - A / dm2, 2) + sin2 * sin2);
        double thm = 0.5 * std::atan2(sin2, cos2 - A / dm2);
        double dm2m = dm2 * denom;
        double xm = 1.267 * dm2m * L / E;
        double pm = std::pow(std::sin(2 * thm), 2) * std::pow(std::sin(xm), 2);
        g_mat.SetPoint(i, E, pm);
    }
    TCanvas c("matter", "", 800, 600);
    g_vac.SetLineWidth(2);
    g_mat.SetLineWidth(2);
    g_vac.SetLineColor(kBlue + 1);
    g_mat.SetLineColor(kRed + 1);
    g_mat.SetLineStyle(2);
    g_vac.GetXaxis()->SetTitle("E [GeV]");
    g_vac.GetYaxis()->SetTitle("P_{2flavor}(#nu_{e}#rightarrow#nu_{#mu})");
    g_vac.GetYaxis()->SetRangeUser(0.0, 0.2);
    g_vac.Draw("AL");
    g_mat.Draw("L SAME");
    TLegend leg(0.55, 0.65, 0.88, 0.85);
    leg.SetBorderSize(0);
    leg.SetFillStyle(0);
    leg.AddEntry(&g_vac, "Vacuum", "l");
    leg.AddEntry(&g_mat, "Matter", "l");
    leg.Draw();
    c.SaveAs("matter_effect.pdf");
    return 0;
}

