// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:

#ifndef DUNE_GEOMETRY_QUADRATURERULES_HH
#define DUNE_GEOMETRY_QUADRATURERULES_HH

#include <algorithm>
#include <limits>
#include <map>
#include <utility>
#include <vector>

#include <dune/common/concurrentcache.hh>
#include <dune/common/fvector.hh>
#include <dune/common/exceptions.hh>
#include <dune/common/visibility.hh>

#include <dune/geometry/type.hh>
#include <dune/geometry/typeindex.hh>

/**
   \file
   Interface for quadrature points and rules
 */

namespace Dune {

  /** \brief Exception thrown if a desired QuadratureRule is not available,
     because the requested order is to high
     \ingroup Quadrature
   */
  class QuadratureOrderOutOfRange : public NotImplemented {};

  /// \brief Single evaluation point in a quadrature rule
  /**
   * \ingroup Quadrature
   * \tparam ct   Number type used for both coordinates and the weights
   * \tparam dim  Dimension of the integration domain
   **/
  template<typename ct, int dim>
  class QuadraturePoint
  {
  public:
    //! Dimension of the integration domain
    enum { dimension = dim };

    //! Number type used for coordinates and quadrature weights
    using Field = ct;

    //! Type used for the position of a quadrature point
    using Vector = Dune::FieldVector<ct,dim>;

    //! Default constructor
    QuadraturePoint () = default;

    //! Set up quadrature of given order in d dimensions
    QuadraturePoint (const Vector& local, Field weight)
      : local_(local)
      , weight_(weight)
    {}

    //! Return local coordinates of integration point
    const Vector& position () const
    {
      return local_;
    }

    //! Return weight associated with integration point
    const Field& weight () const
    {
      return weight_;
    }

  protected:
    Vector local_;
    Field weight_;
  };

  /** \brief Defines an \p enum for currently available quadrature rules.
      \ingroup Quadrature
   */
  namespace QuadratureType {
    enum Enum {
      /** \brief Gauss-Legendre rules (default)
      *
      *  -1D: Gauss-Jacobi rule with parameters \f$\alpha = \beta =0 \f$, i.e. for integrals with a constant weight function.
      *       The quadrature points do not include interval endpoints.
      *       Polynomials of order 2n - 1 can be integrated exactly.
      *  -higher dimension: For the 2D/3D case efficient rules for certain geometries may be used if available.
      *                     Higher dimensional quadrature rules are constructed via \p TensorProductQuadratureRule.
      *                     In this case the 1D rules eventually need higher order to compensate occuring weight functions(i.e. simplices).
      */
      GaussLegendre = 0,

      /** \brief Gauss-Jacobi rules with \f$\alpha =1\f$
      *
      *  -1D Gauss-Jacobi rule with parameters \f$\alpha =1,\ \beta =0 \f$
      *  -Is used to construct efficient simplex quadrature rules of higher order
      */
      GaussJacobi_1_0 = 1,

      /** \brief Gauss-Legendre rules with \f$\alpha =2\f$
      *
      *  -1D Gauss-Jacobi rule with parameters \f$\alpha =2,\ \beta =0 \f$
      *  -Is used to construct efficient simplex quadrature rules of higher order
      */
      GaussJacobi_2_0 = 2,

      /** \brief Gauss-Legendre rules with \f$\alpha =n\f$
      *
      *  -1D: Gauss-Jacobi rule with parameters \f$\alpha = n,\ \beta =0 \f$
      *  -higher dimension: For the 2D/3D case efficient rules for certain geometries may be used if available.
      *                     Higher dimensional quadrature rules are constructed via \p TensorProductQuadratureRule.
      *                     In this case the 1D rules respect eventually occuring weight functions(i.e. simplices).
      *  -The rules for high dimension or order are computed at run time and only floating point number types are supported.(LAPACK is needed for this case)
      *  -Most efficient quadrature type for simplices.
      *
      *   \note For details please use the book "Approximate Calculation of Multiple Integrals" by A.H. Stroud published in 1971.
      */
      GaussJacobi_n_0 = 3,

      /** \brief Gauss-Lobatto rules
       *
       * 1D: Gauss-Lobatto rules for a constant weight function.
       * These are optimal rules under the constraint that both interval endpoints are quadrature points.
       * Polynomials of order 2n - 3 can be integrated exactly.
       */
      GaussLobatto = 4,

      /** \brief Gauss-Radau rules including the left endpoint
       *
       * 1D: Gauss-Radau rules for a constant weight function.
       * These are optimal rules under the constraint that the left endpoint of the integration interval is a quadrature point.
       * Polynomials of order 2n - 2 can be integrated exactly.
       */
      GaussRadauLeft = 5,

      /** \brief Gauss-Radau rules including the right endpoint
       *
       * 1D: Gauss-Radau rules for a constant weight function.
       * These are optimal rules under the constraint that the right endpoint of the integration interval is a quadrature point.
       * Polynomials of order 2n - 2 can be integrated exactly.
       * The right Gauss-Radau rules are the just the mirrored left Gauss-Radau rules.
       */
      GaussRadauRight = 6,
      size
    };
  }

  /** \brief Abstract base class for quadrature rules
      \ingroup Quadrature
   */
  template<typename ct, int dim>
  class QuadratureRule : public std::vector<QuadraturePoint<ct,dim> >
  {
  public:
    //! The space dimension
    enum { d = dim };

    //! The type used for coordinates
    using CoordType = ct;

    // This container is always a const container,
    // therefore iterator is the same as const_iterator
    using iterator = typename std::vector<QuadraturePoint<ct,dim> >::const_iterator;

  public:
    /** \brief Default constructor
     *
     * Create an invalid empty quadrature rule.  This must be initialized
     * later by copying another quadraturerule before it can be used.
     */
    QuadratureRule () = default;

  protected:
    //! Constructor for a given geometry type. Leaves the quadrature order invalid
    QuadratureRule (const GeometryType& type)
      : type_(type) {}

    //! Constructor for a given geometry type and a given quadrature order
    QuadratureRule (const GeometryType& type, int order)
      : type_(type), order_(order) {}

  public:
    //! Return order
    virtual int order () const { return order_; }

    //! Return type of element
    virtual GeometryType type () const { return type_; }

    //! Virtual destructor
    virtual ~QuadratureRule () = default;

  protected:
    GeometryType type_;
    int order_ = -1;
  };

  // Forward declaration of the factory class,
  // needed internally by the QuadratureRules container class.
  template<typename ctype, int dim> class QuadratureRuleFactory;

  /** \brief A container for all quadrature rules of dimension <tt>dim</tt>
      \ingroup Quadrature
   */
  template<typename ctype, int dim>
  class QuadratureRules
  {
  public:
    //! type of quadrature rule provided by this cache
    using QuadratureRule = Dune::QuadratureRule<ctype, dim>;

    //! identifier for quadrature rules, used in the cache container
    struct QuadratureKey
    {
      unsigned int id; // topologyId
      int p;  // order
      QuadratureType qt; // quadrature type

      friend bool operator< (const QuadratureKey& lhs, const QuadratureKey& rhs)
      {
        return std::tie(lhs.id,lhs.p,lhs.qt) < std::tie(rhs.id,rhs.p,rhs.qt);
      }
    };

  private:
    //! private constructor
    QuadratureRules () = default;

  public:
    //! maximum quadrature order for given geometry type and quadrature type
    static unsigned maxOrder (const GeometryType& t, QuadratureType qt = QuadratureType::GaussLegendre)
    {
      return QuadratureRuleFactory<ctype,dim>::maxOrder(t,qt);
    }

    //! select the appropriate QuadratureRule for GeometryType t and order p
    static const QuadratureRule& rule (const GeometryType& t, int p, QuadratureType qt = QuadratureType::GaussLegendre)
    {
      return QuadratureRuleCache::get(QuadratureKey{t.id(),p,qt}, [&](const QuadratureKey&) {
        return QuadratureRuleFactory<ctype,dim>::rule(t,p,qt);
      });
    }

  private:
    using QuadratureRuleCache = ConcurrentCache<QuadratureKey, QuadratureRule, ThreadLocalPolicy,
      std::map<QuadratureKey, QuadratureRule>>;
  };

} // end namespace Dune

#define DUNE_INCLUDING_IMPLEMENTATION

// 0d rules
#include "quadraturerules/pointquadrature.hh"
// 1d rules
#include "quadraturerules/gausslobattoquadrature.hh"
#include "quadraturerules/gaussquadrature.hh"
#include "quadraturerules/gaussradauleftquadrature.hh"
#include "quadraturerules/gaussradaurightquadrature.hh"
#include "quadraturerules/jacobi1quadrature.hh"
#include "quadraturerules/jacobi2quadrature.hh"
#include "quadraturerules/jacobiNquadrature.hh"
// 3d rules
#include "quadraturerules/prismquadrature.hh"
// general rules
#include "quadraturerules/simplexquadrature.hh"
#include "quadraturerules/tensorproductquadrature.hh"

#undef DUNE_INCLUDING_IMPLEMENTATION

namespace Dune {

  /** \brief Factory class for creation of quadrature rules,
      depending on GeometryType, order and QuadratureType.

      The whole class is private and can only be accessed
      by the singleton container class QuadratureRules.
   */
  template<typename ctype, int dim>
  class QuadratureRuleFactory
  {
    friend class QuadratureRules<ctype, dim>;

  private:
    static unsigned maxOrder (const GeometryType& t, QuadratureType qt)
    {
      return TensorProductQuadratureRule<ctype,dim>::maxOrder(t.id(), qt);
    }

    static QuadratureRule<ctype, dim> rule (const GeometryType& t, int p, QuadratureType qt)
    {
      return TensorProductQuadratureRule<ctype,dim>(t.id(), p, qt);
    }
  };

  template<typename ctype>
  class QuadratureRuleFactory<ctype, 0>
  {
    enum { dim = 0 };
    friend class QuadratureRules<ctype, dim>;

  private:
    static unsigned maxOrder (const GeometryType& t, QuadratureType qt)
    {
      if (t.isVertex())
        return std::numeric_limits<int>::max();
      DUNE_THROW(Exception, "Unknown GeometryType");
    }

    static QuadratureRule<ctype, dim> rule (const GeometryType& t, int p, QuadratureType qt)
    {
      if (t.isVertex())
        return PointQuadratureRule<ctype>();
      DUNE_THROW(Exception, "Unknown GeometryType");
    }
  };

  template<typename ctype>
  class QuadratureRuleFactory<ctype, 1>
  {
    enum { dim = 1 };
    friend class QuadratureRules<ctype, dim>;

  private:
    static unsigned maxOrder (const GeometryType& t, QuadratureType qt)
    {
      if (t.isLine())
      {
        switch (qt) {
        case QuadratureType::GaussLegendre :
          return GaussQuadratureRule<ctype>::highest_order;
        case QuadratureType::GaussJacobi_1_0 :
          return Jacobi1QuadratureRule<ctype>::highest_order;
        case QuadratureType::GaussJacobi_2_0 :
          return Jacobi2QuadratureRule<ctype>::highest_order;
        case QuadratureType::GaussLobatto :
          return GaussLobattoQuadratureRule1D<ctype>::highest_order;
        case QuadratureType::GaussJacobi_n_0 :
          return JacobiNQuadratureRule1D<ctype>::maxOrder();
        case QuadratureType::GaussRadauLeft :
          return GaussRadauLeftQuadratureRule1D<ctype>::highest_order;
        case QuadratureType::GaussRadauRight :
          return GaussRadauRightQuadratureRule1D<ctype>::highest_order;
        default :
          DUNE_THROW(Exception, "Unknown QuadratureType");
        }
      }
      DUNE_THROW(Exception, "Unknown GeometryType");
    }

    static QuadratureRule<ctype, dim> rule (const GeometryType& t, int p, QuadratureType qt)
    {
      if (t.isLine())
      {
        switch (qt) {
        case QuadratureType::GaussLegendre :
          return GaussQuadratureRule<ctype>(p);
        case QuadratureType::GaussJacobi_1_0 :
          return Jacobi1QuadratureRule<ctype>(p);
        case QuadratureType::GaussJacobi_2_0 :
          return Jacobi2QuadratureRule<ctype>(p);
        case QuadratureType::GaussLobatto :
          return GaussLobattoQuadratureRule1D<ctype>(p);
        case QuadratureType::GaussJacobi_n_0 :
          return JacobiNQuadratureRule1D<ctype>(p);
        case QuadratureType::GaussRadauLeft :
          return GaussRadauLeftQuadratureRule1D<ctype>(p);
        case QuadratureType::GaussRadauRight :
          return GaussRadauRightQuadratureRule1D<ctype>(p);
        default :
          DUNE_THROW(Exception, "Unknown QuadratureType");
        }
      }
      DUNE_THROW(Exception, "Unknown GeometryType");
    }
  };

  template<typename ctype>
  class QuadratureRuleFactory<ctype, 2>
  {
    enum { dim = 2 };
    friend class QuadratureRules<ctype, dim>;

  private:
    static unsigned maxOrder (const GeometryType& t, QuadratureType qt)
    {
      unsigned order =
        TensorProductQuadratureRule<ctype,dim>::maxOrder(t.id(), qt);
      if (t.isSimplex())
        order = std::max(order, unsigned(SimplexQuadratureRule<ctype,dim>::highest_order));
      return order;
    }

    static QuadratureRule<ctype, dim> rule (const GeometryType& t, int p, QuadratureType qt)
    {
      if (t.isSimplex()
        && ( qt == QuadratureType::GaussLegendre || qt == QuadratureType::GaussJacobi_n_0 )
        && p <= SimplexQuadratureRule<ctype,dim>::highest_order)
      {
        return SimplexQuadratureRule<ctype,dim>(p);
      }
      return TensorProductQuadratureRule<ctype,dim>(t.id(), p, qt);
    }
  };

  template<typename ctype>
  class QuadratureRuleFactory<ctype, 3>
  {
    enum { dim = 3 };
    friend class QuadratureRules<ctype, dim>;

  private:
    static unsigned maxOrder (const GeometryType& t, QuadratureType qt)
    {
      unsigned order =
        TensorProductQuadratureRule<ctype,dim>::maxOrder(t.id(), qt);
      if (t.isSimplex())
        order = std::max(order, unsigned(SimplexQuadratureRule<ctype,dim>::highest_order));
      if (t.isPrism())
        order = std::max(order, unsigned(PrismQuadratureRule<ctype>::highest_order));
      return order;
    }

    static QuadratureRule<ctype, dim> rule (const GeometryType& t, int p, QuadratureType qt)
    {

      if (t.isSimplex()
        && ( qt == QuadratureType::GaussLegendre || qt == QuadratureType::GaussJacobi_n_0 )
        && p <= SimplexQuadratureRule<ctype,dim>::highest_order)
      {
        return SimplexQuadratureRule<ctype,dim>(p);
      }
      if (t.isPrism()
        && qt == QuadratureType::GaussLegendre
        && p <= PrismQuadratureRule<ctype>::highest_order)
      {
        return PrismQuadratureRule<ctype>(p);
      }
      return TensorProductQuadratureRule<ctype,dim>(t.id(), p, qt);
    }
  };

#ifndef DUNE_NO_EXTERN_QUADRATURERULES
  extern template class GaussLobattoQuadratureRule<double, 1>;
  extern template class GaussQuadratureRule<double, 1>;
  extern template class GaussRadauLeftQuadratureRule<double, 1>;
  extern template class GaussRadauRightQuadratureRule<double, 1>;
  extern template class Jacobi1QuadratureRule<double, 1>;
  extern template class Jacobi2QuadratureRule<double, 1>;
  extern template class JacobiNQuadratureRule<double, 1>;
  extern template class PrismQuadratureRule<double, 3>;
  extern template class SimplexQuadratureRule<double, 2>;
  extern template class SimplexQuadratureRule<double, 3>;
#endif // !DUNE_NO_EXTERN_QUADRATURERULES

} // end namespace

#endif // DUNE_GEOMETRY_QUADRATURERULES_HH
