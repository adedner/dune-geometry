// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_GEOMETRY_QUADRATURE_PRISM_HH
#define DUNE_GEOMETRY_QUADRATURE_PRISM_HH

#ifndef DUNE_INCLUDING_IMPLEMENTATION
#error This is a private header that should not be included directly.
#error Use #include <dune/geometry/quadraturerules.hh> instead.
#endif

namespace Dune {

  /***********************************
   * quadrature for Prism
   **********************************/

  /** \brief Quadrature rules for prisms
      \ingroup Quadrature
   */
  template<typename ct>
  class PrismQuadratureRule : public QuadratureRule<ct,3>
  {
  public:
    /** \brief The highest quadrature order available */
    enum { highest_order = 2 };

    using Field = typename QuadraturePoint<ct,3>::Field;
    using Vector = typename QuadraturePoint<ct,3>::Vector;

  private:
    friend class QuadratureRuleFactory<ct,3>;
    PrismQuadratureRule(int p);
  };


  template<typename ct>
  PrismQuadratureRule<ct>::PrismQuadratureRule(int p)
    : QuadratureRule<ct,3>(GeometryTypes::prism, 2)
  {
    Field w{0.166666666666666666666L / 2.0L};
    switch (p)
    {
      case 0:
      case 1:
      case 2:
        // dim = 3, order = 2, npoints = 6
        this->order_ = 2;
        this->resize(6);
        (*this)[0] = {
          Vector{0.666666666666666666666L, 0.166666666666666666666L, 0.211324865405187117745L}, w};
        (*this)[1] = {
          Vector{0.166666666666666666666L, 0.666666666666666666666L, 0.211324865405187117745L}, w};
        (*this)[2] = {
          Vector{0.166666666666666666666L, 0.166666666666666666666L, 0.211324865405187117745L}, w};
        (*this)[3] = {
          Vector{0.666666666666666666666L, 0.166666666666666666666L, 0.788675134594812882255L}, w};
        (*this)[4] = {
          Vector{0.166666666666666666666L, 0.666666666666666666666L, 0.788675134594812882255L}, w};
        (*this)[5] = {
          Vector{0.166666666666666666666L, 0.166666666666666666666L, 0.788675134594812882255L}, w};
    }
  }

} // namespace Dune

#endif // DUNE_GEOMETRY_QUADRATURE_PRISM_HH
