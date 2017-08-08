// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_GEOMETRY_REFINEMENT_HCUBE_CC
#define DUNE_GEOMETRY_REFINEMENT_HCUBE_CC

/*!
 * \file
 * \brief This file contains the \ref Refinement implementation for
 *        hypercubes (quadrilaterals, hexahedrons, etc.).
 *
 * See \ref HCubeRefinement.
 */

/*!
 * \defgroup HCubeRefinement Refinement implementation for hypercubes
 *  \ingroup Refinement
 *
 * \section Iterators The Iterators
 * <!--=========================-->
 *
 * For the iterators we have to hack around a bit.  The problem is as
 * follows:
 * \code
 * template<int A>
 * class outer
 * {
 *   template<int B>
 *   class inner;
 * };
 * \endcode
 * C++ does not allow specialisation of the inner class when the outer
 * class is not specialized.
 *
 * So I had to create a baseclass for the iterators which is not inside
 * another class.  This base class can then be specialized, and the
 * real Iterator class inherits from it.  I gave it the somewhat clumsy
 * name RefinementSubEntityIteratorSpecial.
 */

#include <cassert>

#include <dune/common/fvector.hh>
#include <dune/common/iteratorfacades.hh>
#include <dune/common/power.hh>

#include <dune/geometry/referenceelements.hh>
#include <dune/geometry/axisalignedcubegeometry.hh>

#include "base.cc" // for RefinementTraits

namespace Dune
{
  namespace RefinementImp
  {
    /*!
     * \brief This namespace contains the \ref Refinement implementation
     * for hypercubes (GeometryType::cube).
     *
     * See \ref HCubeRefinement.
     */
    namespace HCubeArbitraryRefinement
    {
      /*!
       * \brief \ref Refinement implementation for hypercubes
       *
       * \param dimension_ Dimension of the refined hypercube
       * \param CoordType  Coordinate type of the refined hypercube
       *
       *  The interface is the same as for \ref Dune::StaticRefinement (apart
       * from the template parameters).
       */
      template<int dimension_, class CoordType>
      class RefinementImp
      {
      public:
        enum { dimension = dimension_ /*!< Know your own dimension \hideinitializer */ };
        //- Know yourself
        typedef RefinementImp<dimension, CoordType> Refinement;

        template<int codimension>
        struct Codim;
        typedef typename Codim<dimension>::SubEntityIterator VertexIterator;
        typedef FieldVector<CoordType, dimension> CoordVector;
        typedef typename Codim<0>::SubEntityIterator ElementIterator;
        typedef FieldVector<int, (1<<dimension)> IndexVector;

        static unsigned nVertices(unsigned nhypercubes);
        static VertexIterator vBegin(unsigned nhypercubes);
        static VertexIterator vEnd(unsigned nhypercubes);

        static unsigned nElements(unsigned nhypercubes);
        static ElementIterator eBegin(unsigned nhypercubes);
        static ElementIterator eEnd(unsigned nhypercubes);
      };

      template<int dimension, class CoordType>
      template<int codimension>
      struct RefinementImp<dimension, CoordType>::Codim
      {
        class SubEntityIterator;
        typedef Dune::AxisAlignedCubeGeometry<CoordType,dimension-codimension,dimension> Geometry;
      };

      template<int dimension, class CoordType>
      unsigned
      RefinementImp<dimension, CoordType>::
      nVertices(unsigned nhypercubes)
      {
        // return (nhypercubes + 1)^dim
        return Power<dimension>::eval(nhypercubes+1u);
      }

      template<int dimension, class CoordType>
      typename RefinementImp<dimension, CoordType>::VertexIterator
      RefinementImp<dimension, CoordType>::
      vBegin(unsigned nhypercubes)
      {
        return VertexIterator(0,nhypercubes);
      }

      template<int dimension, class CoordType>
      typename RefinementImp<dimension, CoordType>::VertexIterator
      RefinementImp<dimension, CoordType>::
      vEnd(unsigned nhypercubes)
      {
        return VertexIterator(nVertices(nhypercubes),nhypercubes);
      }

      template<int dimension, class CoordType>
      unsigned
      RefinementImp<dimension, CoordType>::
      nElements(unsigned nhypercubes)
      {
        static_assert(dimension >= 0,
                      "Negative dimension given, what the heck is that supposed to mean?");
        // return nhypercubes^dim
        return Power<dimension>::eval(nhypercubes);
      }

      template<int dimension, class CoordType>
      typename RefinementImp<dimension, CoordType>::ElementIterator
      RefinementImp<dimension, CoordType>::
      eBegin(unsigned nhypercubes)
      {
        return ElementIterator(0,nhypercubes);
      }

      template<int dimension, class CoordType>
      typename RefinementImp<dimension, CoordType>::ElementIterator
      RefinementImp<dimension, CoordType>::
      eEnd(unsigned nhypercubes)
      {
        return ElementIterator(nElements(nhypercubes),nhypercubes);
      }

      //
      // The iterators
      //

#ifdef DOXYGEN
      /*!
       * \brief SubEntityIterator base class for hypercube refinement
       *
       * \tparam dimension   Dimension of the refined element
       * \tparam CoordType   Coordinate type of the refined element
       * \tparam codimension Codimension of the iterator
       *
       * This is the base class for SubEntityIterators.  We have to use
       * this construct because RefinementImp<...>::%codim<...> cannot
       * be specialized without first specializing RefinementImp.
       */
      template<int dimension, class CoordType, int codimension>
      class RefinementSubEntityIteratorSpecial {};
#else //!DOXYGEN
      template<int dimension, class CoordType, int codimension>
      class RefinementSubEntityIteratorSpecial;
#endif //DOXYGEN

      // for vertices

      template<int dimension, class CoordType>
      class RefinementSubEntityIteratorSpecial<dimension, CoordType, dimension>
      {
      public:
        typedef RefinementImp<dimension, CoordType> Refinement;
        typedef typename Refinement::template Codim<dimension>::SubEntityIterator Common;
        typedef typename Refinement::CoordVector CoordVector;

        CoordVector coords() const;

      private:
        const Common & asCommon() const
        {
          return *static_cast<const Common*>(this);
        }
      };

      template<int dimension, class CoordType>
      typename RefinementSubEntityIteratorSpecial<dimension, CoordType, dimension>::CoordVector
      RefinementSubEntityIteratorSpecial<dimension, CoordType, dimension>::
      coords() const
      {
        std::array<unsigned int, dimension> v(asCommon().vertexCoord());
        CoordVector c;
        for (int d = 0; d < dimension; d++)
        {
          c[d] = v[d]*1.0 / asCommon()._nhypercubes;
        }
        return c;
      }

      // for elements

      template<int dimension, class CoordType>
      class RefinementSubEntityIteratorSpecial<dimension, CoordType, 0>
      {
      public:
        typedef RefinementImp<dimension, CoordType> Refinement;
        typedef typename Refinement::template Codim<0>::SubEntityIterator Common;
        typedef typename Refinement::IndexVector IndexVector;
        typedef typename Refinement::CoordVector CoordVector;

        IndexVector vertexIndices() const;
        CoordVector coords() const;

      private:
        const Common & asCommon() const
        {
          return *static_cast<const Common*>(this);
        }
      };

      template<int dimension, class CoordType>
      typename RefinementSubEntityIteratorSpecial<dimension, CoordType, 0>::IndexVector
      RefinementSubEntityIteratorSpecial<dimension, CoordType, 0>::
      vertexIndices() const
      {
        enum { nIndices = (1 << dimension) };

        // cell index tuple
        std::array<unsigned int, dimension> e(asCommon().cellCoord());

        // vertices
        IndexVector vec;
        std::array<unsigned int, dimension> v;
        for(int i = 0; i < nIndices; ++i)
        {
          std::array<unsigned int, dimension> alpha(asCommon().idx2multiidx(i));
          for (int d = 0; d < dimension; d++)
          {
            vec[i] += (alpha[d]+e[d])*std::pow(asCommon()._nhypercubes+1, d);
          }
          // compute vertex index tuple from cell tuple
//          vec[nIndices-1-i] = asCommon().vertexIdx(v);
        }
        return vec;
      }

      template<int dimension, class CoordType>
      typename RefinementSubEntityIteratorSpecial<dimension, CoordType, 0>::CoordVector
      RefinementSubEntityIteratorSpecial<dimension, CoordType, 0>::
      coords() const
      {
        std::array<unsigned int, dimension> v(asCommon().cellCoord());
        CoordVector c;
        for (int d=0; d<dimension; d++)
        {
          c[d] = (v[d]*1.0 + 0.5) / asCommon()._nhypercubes;
        }
        return c;
      }

      // common
      template<int dimension, class CoordType>
      template<int codimension>
      class RefinementImp<dimension, CoordType>::Codim<codimension>::SubEntityIterator
        : public ForwardIteratorFacade<typename RefinementImp<dimension,
                  CoordType>::template Codim<codimension>::SubEntityIterator, int>,
          public RefinementSubEntityIteratorSpecial<dimension, CoordType, codimension>
      {
      public:
        typedef RefinementImp<dimension, CoordType> Refinement;
        typedef typename Refinement::template Codim<codimension>::SubEntityIterator This;

        SubEntityIterator(unsigned int index, unsigned int nhypercubes);

        bool equals(const This &other) const;
        void increment();

        int index() const;
        Geometry geometry () const;
      private:
        friend class RefinementSubEntityIteratorSpecial<dimension, CoordType, codimension>;
        unsigned int _index;
        unsigned int _nhypercubes;

        std::array<unsigned int, dimension>
        cellCoord(unsigned int idx) const
        {
          return idx2coord(idx, _nhypercubes);
        }

        std::array<unsigned int, dimension>
        vertexCoord(unsigned int idx) const
        {
          return idx2coord(idx, _nhypercubes+1u);
        }

        std::array<unsigned int, dimension>
        cellCoord() const
        {
          return cellCoord(_index);
        }

        std::array<unsigned int, dimension>
        vertexCoord() const
        {
          return vertexCoord(_index);
        }

        std::array<unsigned int, dimension>
        idx2coord(unsigned int idx, unsigned int w) const
        {
          std::array<unsigned int, dimension> c;
          for (unsigned int d = 0; d < dimension; d++)
          {
            c[d] = idx%w;
            idx = idx/w;
          }
          return c;
        }

        unsigned int
        coord2idx(std::array<unsigned int, dimension> c, unsigned int w) const
        {
          unsigned int i = 0;
          for (unsigned int d = dimension; d > 0; d--)
          {
            i *= w;
            i += c[d-1];
          }
          return i;
        }

        std::array<unsigned int, dimension>
        idx2multiidx(unsigned int idx) const
        {
          std::array<unsigned int, dimension> alpha;
          for (unsigned int i = 0; i < dimension; ++i)
            alpha[i] = (idx & (1u<<i))>>i;
          return alpha;
        }

        unsigned int
        vertexIdx(std::array<unsigned int, dimension> c) const
        {
          return coord2idx(c, _nhypercubes+1u);
        }
      };

#ifndef DOXYGEN
      template<int dimension, class CoordType>
      template<int codimension>
      RefinementImp<dimension, CoordType>::Codim<codimension>::SubEntityIterator::
      SubEntityIterator(unsigned int index, unsigned int nhypercubes)
        : _index(index), _nhypercubes(nhypercubes)
      {}

      template<int dimension, class CoordType>
      template<int codimension>
      bool
      RefinementImp<dimension, CoordType>::Codim<codimension>::SubEntityIterator::
      equals(const This &other) const
      {
        return ((_index == other._index) && (_nhypercubes == other._nhypercubes));
      }

      template<int dimension, class CoordType>
      template<int codimension>
      void
      RefinementImp<dimension, CoordType>::Codim<codimension>::SubEntityIterator::
      increment()
      {
        ++_index;
      }

      template<int dimension, class CoordType>
      template<int codimension>
      int
      RefinementImp<dimension, CoordType>::Codim<codimension>::SubEntityIterator::
      index() const
      {
        return _index;
      }

      template<int dimension, class CoordType>
      template<int codimension>
      typename RefinementImp<dimension, CoordType>::template Codim<codimension>::Geometry
      RefinementImp<dimension, CoordType>::Codim<codimension>::SubEntityIterator::geometry () const
      {
        std::array<unsigned int,dimension> intCoords = idx2coord(_index,_nhypercubes);

        Dune::FieldVector<CoordType,dimension> lower;
        Dune::FieldVector<CoordType,dimension> upper;

        assert(codimension == 0 or codimension == dimension);

        if (codimension == 0) {
          for (size_t j = 0; j < dimension; j++)
          {
            lower[j] = double(intCoords[j])     / double(_nhypercubes);
            upper[j] = double(intCoords[j] + 1) / double(_nhypercubes);
          }
        } else {
          for (size_t j = 0; j < dimension; j++)
            lower[j] = upper[j] = double(intCoords[j]) / double(_nhypercubes);
        }

        return typename RefinementImp<dimension,
            CoordType>::template Codim<codimension>::Geometry(lower,upper);
      }

#endif // DOXYGEN

    } // namespace HCube

    // ///////////////////////
    //
    // The refinement traits
    //

#ifndef DOXYGEN
    template<unsigned topologyId, class CoordType, unsigned coerceToId,
        int dim>
    struct Traits<
        topologyId, CoordType, coerceToId, dim,
        typename std::enable_if<
            (dim >= 2 &&
             (Impl::CubeTopology<dim>::type::id >> 1) ==
             (topologyId >> 1) &&
             (Impl::CubeTopology<dim>::type::id >> 1) ==
             (coerceToId >> 1)
            )>::type
        >
    {
      typedef HCubeArbitraryRefinement::RefinementImp<dim, CoordType> Imp;
    };
#endif

  } // namespace RefinementImp

} // namespace Dune

#endif // DUNE_GEOMETRY_REFINEMENT_HCUBE_CC
