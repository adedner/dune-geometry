// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#include "config.h"

#define DUNE_NO_EXTERN_QUADRATURERULES
#include "../quadraturerules.hh"
#undef DUNE_NO_EXTERN_QUADRATURERULES

namespace Dune {

  // explicit template instatiation
  template class GaussLobattoQuadratureRule<double, 1>;
  template class GaussQuadratureRule<double, 1>;
  template class GaussRadauLeftQuadratureRule<double, 1>;
  template class GaussRadauRightQuadratureRule<double, 1>;
  template class Jacobi1QuadratureRule<double, 1>;
  template class Jacobi2QuadratureRule<double, 1>;
  template class JacobiNQuadratureRule<double, 1>;
  template class PrismQuadratureRule<double, 3>;
  template class SimplexQuadratureRule<double, 2>;
  template class SimplexQuadratureRule<double, 3>;

} // namespace
