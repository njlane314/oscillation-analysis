#include "Oscillation.h"
#include "PlotStyle.h"
#include <TAxis.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <cmath>
#include <vector>

int main() {
  SetOscillationPlotStyle();
  double L = 1300.0;
  double E = 2.5;
  PMNSParams base{0.5843, 0.830, 0.0, 7.42e-5, 2.517e-3, 0.0};
  int N = 180;
  TGraph g(N);
  for (int i = 0; i < N; ++i) {
    double th13 = i * M_PI / (2.0 * N);
    PMNSVacuum pmns(
        {base.th12, base.th23, th13, base.dm21, base.dm31, base.delta});
    double p = pmns.prob(1, 0, L, E);
    g.SetPoint(i, th13, p);
  }
  TCanvas c("mix", "", 800, 600);
  g.SetLineWidth(2);
  g.GetXaxis()->SetTitle("#theta_{13} [rad]");
  g.GetYaxis()->SetTitle("P(#nu_{#mu}#rightarrow#nu_{e})");
  g.GetYaxis()->SetRangeUser(0.0, 0.2);
  g.Draw("AL");
  c.SaveAs("mixing_angle_scan.pdf");
  return 0;
}
