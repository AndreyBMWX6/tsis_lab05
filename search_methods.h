#pragma once
//
// Created by Andrey on 19.12.2020.
//

#ifndef NEURAL_NETWORK_SEARCH_SEARCH_METHODS_H
#define NEURAL_NETWORK_SEARCH_SEARCH_METHODS_H

#include <cmath>
#include <string>
#include <iostream>

#include "func.h"
#include "TextTable.h"

const std::map<double, double> yVals = GetValues(c, d, 0, false);
const std::map<double, double> nyVals = GetValues(c, d, Amp, false);

double GetSquaredErrorsSum(double ci, double di, double A) {
    auto tVals = GetValues(ci, di, A, false);
    double sum = 0;

    if (A != 0) {
        for (const auto& [x, y] : nyVals) {
            sum += (y - tVals[x]) * (y - tVals[x]);
        }
    } else {
        for (const auto& [x, y] : yVals) {
            sum += (y - tVals[x]) * (y - tVals[x]);
        }
    }


    return sum;
}

double GetFibonachiNum(int num) {
    if (num <= 2) {
        return 1;
    } else {
        return GetFibonachiNum(num - 1) + GetFibonachiNum(num - 2);
    }
}

double Fibonachi(double dmin, double dmax, double ci, double A) {
    for (int i = 1; i <= n - 1; ++i) {
        double d1 = dmin + (GetFibonachiNum(n - i)/GetFibonachiNum(n + 1)) * (dmax - dmin);
        double d2 = dmin + (GetFibonachiNum(n + 1 - i)/GetFibonachiNum(n + 1)) * (dmax - dmin);

        if (GetSquaredErrorsSum(ci, d1, A) < GetSquaredErrorsSum(ci, d2, A)) {
            dmax = d2;
        } else {
            dmin = d1;
        }
    }
    return dmin + ((dmax - dmin) / 2);
}

std::pair<double, double> Passive(double cmin, double cmax, double dmin, double dmax, double A) {
    double cres;
    double dres;

    auto cRange = MakeRange(cmin, cmax);
    std::vector<std::pair<double, double>> func_params;

    for (const auto& ci : cRange) {
        func_params.push_back(std::make_pair(ci, Fibonachi(dmin, dmax, ci, A)));
    }

    cres = func_params[0].first;
    dres = func_params[0].second;

    for (const auto& [ci, di] : func_params) {
        if (GetSquaredErrorsSum(ci, di, A) < GetSquaredErrorsSum(cres, dres, A)) {
            cres = ci;
            dres = di;
        }
    }

    return std::make_pair(cres, dres);
}


#endif //NEURAL_NETWORK_SEARCH_SEARCH_METHODS_H
