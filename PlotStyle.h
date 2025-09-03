#pragma once

#include <TStyle.h>

inline void SetOscillationPlotStyle() {
  static TStyle *s = nullptr;
  if (s) {
    s->cd();
    return;
  }

  s = new TStyle("elegant", "elegant");
  s->SetCanvasColor(0);
  s->SetPadColor(0);
  s->SetFrameFillColor(0);
  s->SetFrameLineColor(1);
  s->SetOptStat(0);
  s->SetOptTitle(0);
  s->SetPadLeftMargin(0.12);
  s->SetPadRightMargin(0.05);
  s->SetPadBottomMargin(0.12);
  s->SetPadTopMargin(0.08);
  s->SetLabelSize(0.04, "XY");
  s->SetTitleSize(0.05, "XY");
  s->SetTitleOffset(1.10, "X");
  s->SetTitleOffset(1.10, "Y");
  s->cd();
}
