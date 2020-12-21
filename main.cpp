#include "search_methods.h"

int main() {
    GetValues(c, d, Amp, true);
    GetValues(c, d, 0, true);
    auto [cmin, cmax] = FindCRangeBorders(0);
    auto [ncmin, ncmax] = FindCRangeBorders(Amp);
    auto dmin = a;
    auto dmax = b;

    auto [cres,dres] = Passive(cmin, cmax, dmin, dmax, 0);
    std::cout << "Without noise: c = " << cres <<" d = " << dres << "\n";

    auto [ncres,ndres] = Passive(ncmin, ncmax, dmin, dmax, Amp);
    std::cout << "With noise: c = " << ncres <<" d = " << ndres;
    return 0;
}
