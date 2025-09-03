#include <TCanvas.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TAxis.h>
#include <vector>
#include <cmath>
#include <string>
#include "PlotStyle.h"
#include "Oscillation.h"

int main() {
    SetElegantStyle();
    std::vector<double> baselines = {295.0, 810.0, 1300.0};
    std::vector<std::string> labels = {"T2K", "NO#nuA", "DUNE"};
    PMNSParams nh{0.5843, 0.830, 0.148, 7.42e-5, 2.517e-3, 0.0};
    int N = 200;
    std::vector<TGraph> graphs;
    for (size_t j = 0; j < baselines.size(); ++j) {
        graphs.emplace_back(N);
        for (int i = 0; i < N; ++i) {
            double E = 0.2 + 0.03 * i;
            PMNSVacuum pmns(nh);
            double p = pmns.prob(1, 0, baselines[j], E);
            graphs.back().SetPoint(i, E, p);
        }
    }
    TCanvas c("base", "", 800, 600);
    int colors[3] = {kBlue + 1, kRed + 1, kGreen + 2};
    TLegend leg(0.55, 0.65, 0.88, 0.85);
    leg.SetBorderSize(0);
    leg.SetFillStyle(0);
    for (size_t j = 0; j < graphs.size(); ++j) {
        graphs[j].SetLineWidth(2);
        graphs[j].SetLineColor(colors[j]);
        if (j == 0) {
            graphs[j].GetXaxis()->SetTitle("E [GeV]");
            graphs[j].GetYaxis()->SetTitle("P(#nu_{#mu}#rightarrow#nu_{e})");
            graphs[j].GetYaxis()->SetRangeUser(0.0, 0.2);
            graphs[j].Draw("AL");
        } else {
            graphs[j].Draw("L SAME");
        }
        leg.AddEntry(&graphs[j], labels[j].c_str(), "l");
    }
    leg.Draw();
    c.SaveAs("baseline_scan.pdf");
    return 0;
}

