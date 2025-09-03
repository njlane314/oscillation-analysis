#pragma once

#include <array>
#include <complex>
#include <cmath>

struct PMNSParams {
    double th12;
    double th23;
    double th13;
    double dm21;
    double dm31;
    double delta;
};

struct PMNS {
    using C = std::complex<double>;
    using U3 = std::array<std::array<C, 3>, 3>;

    static U3 R12(double t) {
        U3 r{};
        double c = std::cos(t), s = std::sin(t);
        r[0][0] = c;
        r[0][1] = s;
        r[1][0] = -s;
        r[1][1] = c;
        r[2][2] = 1;
        return r;
    }

    static U3 R23(double t) {
        U3 r{};
        double c = std::cos(t), s = std::sin(t);
        r[0][0] = 1;
        r[1][1] = c;
        r[1][2] = s;
        r[2][1] = -s;
        r[2][2] = c;
        return r;
    }

    static U3 U13(double t, double d) {
        U3 r{};
        double c = std::cos(t), s = std::sin(t);
        r[0][0] = c;
        r[0][2] = std::exp(C(0, -d)) * s;
        r[1][1] = 1;
        r[2][0] = -std::exp(C(0, d)) * s;
        r[2][2] = c;
        return r;
    }

    static U3 mul(const U3 &a, const U3 &b) {
        U3 r{};
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                r[i][j] = 0.0;
                for (int k = 0; k < 3; ++k) {
                    r[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return r;
    }

    static U3 build(double th12, double th23, double th13, double d) {
        return mul(R23(th23), mul(U13(th13, d), R12(th12)));
    }
};

struct PMNSVacuum {
    using C = std::complex<double>;
    using U3 = std::array<std::array<C, 3>, 3>;

    explicit PMNSVacuum(PMNSParams p) : p_(p) {
        U_ = PMNS::build(p_.th12, p_.th23, p_.th13, p_.delta);
    }

    double prob(int a, int b, double L, double E) const {
        const double k = 1.267;
        const double dm21 = p_.dm21;
        const double dm31 = p_.dm31;
        const double dm32 = dm31 - dm21;

        const double D21 = k * dm21 * L / E;
        const double D31 = k * dm31 * L / E;
        const double D32 = k * dm32 * L / E;

        auto term = [&](int i, int j) {
            auto A = U_[a][i] * std::conj(U_[b][i]) * std::conj(U_[a][j]) * U_[b][j];
            return std::make_pair(A.real(), A.imag());
        };

        double p = (a == b);

        {
            auto t31 = term(2, 0);
            p += -4.0 * t31.first * std::sin(D31) * std::sin(D31)
                 + 2.0 * t31.second * std::sin(2.0 * D31);

            auto t32 = term(2, 1);
            p += -4.0 * t32.first * std::sin(D32) * std::sin(D32)
                 + 2.0 * t32.second * std::sin(2.0 * D32);

            auto t21 = term(1, 0);
            p += -4.0 * t21.first * std::sin(D21) * std::sin(D21)
                 + 2.0 * t21.second * std::sin(2.0 * D21);
        }

        return p;
    }

    PMNSParams p_;
    U3 U_;
};

