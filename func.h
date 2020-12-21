#pragma once
//
// Created by Andrey on 20.12.2020.
//

#ifndef NEURAL_NETWORK_SEARCH_FUNC_H
#define NEURAL_NETWORK_SEARCH_FUNC_H

#include <random>
#include <utility>
#include <map>
#include <algorithm>

const double a = -1;
const double b = 2;
const double c = -4;
const double d = 2;
const int    n = 12;
const double Amp = 5;

auto MakeRange(double rmin, double rmax) {
    std::vector<double> range;
    double step = (rmax - rmin) / (n - 1);

    for (int i = 0; i < n; ++i) {
        range.push_back(rmin + i * step);
    }

    return range;
}

// declared for creation of noise
auto MakeRandGen(double min, double max) {
    std::random_device rd;
    return  std::make_pair(std::uniform_real_distribution<double>(min, max), std::mt19937(rd()));
}

std::map<double, double> GetValues(double ci, double di, double A, bool log) {
    std::map<double, double> values;
    auto xRange = MakeRange(a, b);

    if (A != 0) {
        auto [dis, gen] = MakeRandGen(-0.5, 0.5);
        for (int i = 0; i < n; ++i) {
            auto noise = dis(gen) * A;
            auto val = ci * xRange[i] + di + noise;
            values[xRange[i]] = val;
            if (log) {
                std::cout << "(" << xRange[i] << ";" << val << ") ";
            }
        }
        if (log) {
            std::cout << "\n";
        }
    } else {
        for (int i = 0; i < n; ++i) {
            auto val = ci * xRange[i] + di;
            values[xRange[i]] = val;
            if (log) {
                std::cout << "(" << xRange[i] << ";" << val << ") ";
            }
        }
        if (log) {
            std::cout << "\n";
        }
    }

    return values;
}

std::pair<double, double> FindCRangeBorders(double A) {
    std::map<double, double> linVals = GetValues(c, 0, A, false);
    auto cmin = linVals.begin()->second / linVals.begin()->first;
    auto cmax = cmin;

    for (const auto& [x, y] : linVals) {
        auto ci = y / x;
        if (ci > cmax) {
            cmax = ci;
        }
        if (ci < cmin) {
            cmin = ci;
        }
    }

    if (cmin > cmax) {
        std::swap(cmin, cmax);
    }
     return std::make_pair(cmin, cmax);
}

#endif //NEURAL_NETWORK_SEARCH_FUNC_H
