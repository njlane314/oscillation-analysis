# Oscillation Analysis Plots

## Build and Run

To build and run any of the plotting executables (for example, `plot_survival`), execute:

```bash
cmake -S . -B build
cmake --build build --target plot_survival
./build/plot_survival
```

Replace `plot_survival` with another target such as `plot_mixing`, `plot_cp`, or `plot_matter` to generate different plots.

## plot_survival
Two-flavor survival probability versus $L/E$ inspired by Pontecorvo (1957) and Maki–Nakagawa–Sakata (1962).

## plot_mixing
Appearance probability scan in $\theta_{13}$ following early mixing studies after Cabibbo (1963).

## plot_cp
Appearance probability as a function of $\delta_{CP}$ echoing CP violation work by Kobayashi and Maskawa (1973).

## plot_baseline
Energy-dependent appearance probabilities for T2K, NOνA, and DUNE baselines highlighted in their design papers.

## plot_matter
Vacuum and matter probabilities showcasing the MSW effect formulated by Wolfenstein (1978) and Mikheyev–Smirnov (1985).

