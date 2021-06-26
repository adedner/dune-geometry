// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_GEOMETRY_QUADRATURE_SIMPLEX_HH
#define DUNE_GEOMETRY_QUADRATURE_SIMPLEX_HH

#ifndef DUNE_INCLUDING_IMPLEMENTATION
#error This is a private header that should not be included directly.
#error Use #include <dune/geometry/quadraturerules.hh> instead.
#endif

namespace Dune {

  /************************************************
   * Quadraturerule for Simplices Triangle/Tetrahedra
   *************************************************/

  /** \brief Quadrature rules for simplices
      \ingroup Quadrature
   */
  template<typename ct, int dim>
  class SimplexQuadratureRule;

  /** \brief Quadrature rules for triangles
      \ingroup Quadrature
   */
  template<typename ct>
  class SimplexQuadratureRule<ct,2> : public QuadratureRule<ct,2>
  {
  public:
    /** \brief The highest quadrature order available */
    enum { highest_order = 12 };

  private:
    friend class QuadratureRuleFactory<ct,2>;
    SimplexQuadratureRule (int p);
  };

  /** \brief Quadrature rules for tetrahedra
      \ingroup Quadrature
   */
  template<typename ct>
  class SimplexQuadratureRule<ct,3> : public QuadratureRule<ct,3>
  {
  public:
    /** \brief The highest quadrature order available */
    enum { highest_order = 5 };

  private:
    friend class QuadratureRuleFactory<ct,3>;
    SimplexQuadratureRule (int p);
  };


  template<typename ct>
  SimplexQuadratureRule<ct,2>::SimplexQuadratureRule(int p)
    : QuadratureRule<ct,2>(GeometryTypes::triangle)
  {
    switch (p)
    {
      // polynom degree 1

      // Rule t2-1-1 of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: Rule 1-1, P. 307, A.H. Stroud, Approximate Calculation of Multiple Integrals

      case 0:
      case 1:
        this->order_ = 1;
        this->resize(1);
        (*this)[0] = {
          {0.333333333333333333333333333333333, 0.333333333333333333333333333333333},
           0.5};
        break;

      // polynom degree 2
      // symmetric

      // Rule t2-2-3a of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: Rule 2-1, P. 307, A.H. Stroud, Approximate Calculation of Multiple Integrals

      case 2:
        this->order_ = 2;
        this->resize(3);
        (*this)[0] = {
          {4.0/6.0, 1.0/6.0},
           0.5/3.0};
        (*this)[1] = {
          {1.0/6.0, 4.0/6.0},
           0.5/3.0};
        (*this)[2] = {
          {1.0/6.0, 1.0/6.0},
           0.5/3.0};
        break;

      // polynom degree 3
      // symmetric

      // Rule t2-3-4a of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: Rule 3-1, P. 308, A.H. Stroud, Approximate Calculation of Multiple Integrals

      case 3:
        this->order_ = 3;
        this->resize(4);
        (*this)[0] = {
          {10.0/30.0, 10.0/30.0},
           0.5 * -27.0/48.0};
        (*this)[1] = {
          {18.0/30.0, 6.0/30.0},
           0.5 * 25.0/48.0};
        (*this)[2] = {
          {6.0/30.0, 18.0/30.0},
           0.5 * 25.0/48.0};
        (*this)[3] = {
          {6.0/30.0, 6.0/30.0},
           0.5 * 25.0/48.0};
        break;

      // polynomial degree 4
      // symmetric points

      // Rule t2-4-6a of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: Appendix II, D.A. Dunavant, High degree efficient symmetrical Gaussian quadrature rules for the triangle

      case 4:
        this->order_ = 4;
        this->resize(6);
        (*this)[0] = {
          {0.81684757298045851308085707319560, 0.091576213509770743459571463402202},
           0.5 * 0.10995174365532186763832632490021};
        (*this)[1] = {
          {0.091576213509770743459571463402202, 0.81684757298045851308085707319560},
           0.5 * 0.10995174365532186763832632490021};
        (*this)[2] = {
          {0.091576213509770743459571463402202, 0.091576213509770743459571463402202},
           0.5 * 0.10995174365532186763832632490021};
        (*this)[3] = {
          {0.10810301816807022736334149223390, 0.44594849091596488631832925388305},
           0.5 * 0.22338158967801146569500700843312};
        (*this)[4] = {
          {0.44594849091596488631832925388305, 0.10810301816807022736334149223390},
           0.5 * 0.22338158967801146569500700843312};
        (*this)[5] = {
          {0.44594849091596488631832925388305, 0.44594849091596488631832925388305},
           0.5 * 0.22338158967801146569500700843312};
        break;

      // polynomial degree 5
      // symmetric points

      // Rule t2-5-7 of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: Rule 5-1, P. 314, A.H. Stroud, Approximate Calculation of Multiple Integrals

      case 5:
        this->order_ = 5;
        this->resize(7);
        (*this)[0] = {
          {0.333333333333333333333333333333333, 0.333333333333333333333333333333333},
           0.5 * 0.225};
        (*this)[1] = {
          {0.79742698535308732239802527616975, 0.1012865073234563388009873619151},
           0.5 * 0.12593918054482715259568394550018};
        (*this)[2] = {
          {0.10128650732345633880098736191512, 0.79742698535308732239802527616975},
           0.5 * 0.12593918054482715259568394550018};
        (*this)[3] = {
          {0.10128650732345633880098736191512, 0.10128650732345633880098736191512},
           0.5 * 0.12593918054482715259568394550018};
        (*this)[4] = {
          {0.05971587178976982045911758097311, 0.47014206410511508977044120951345},
           0.5 * 0.13239415278850618073764938783315};
        (*this)[5] = {
          {0.47014206410511508977044120951345, 0.05971587178976982045911758097311},
           0.5 * 0.13239415278850618073764938783315};
        (*this)[6] = {
          {0.47014206410511508977044120951345, 0.47014206410511508977044120951345},
           0.5 * 0.13239415278850618073764938783315};
        break;

      // polynomial degree 6
      /* 12 inner Gauss points, positive weights */

      // Rule t2-6-12a of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: Appendix II, D.A. Dunavant, High degree efficient symmetrical Gaussian quadrature rules for the triangle

      case 6:
        this->order_ = 6;
        this->resize(12);
        (*this)[0] = {
          {0.063089014491502228340331602870819, 0.063089014491502228340331602870819},
           0.5 * 0.050844906370206816920936809106869};
        (*this)[1] = {
          {0.063089014491502228340331602870819, 0.87382197101699554331933679425836},
           0.5 * 0.050844906370206816920936809106869};
        (*this)[2] = {
          {0.87382197101699554331933679425836, 0.063089014491502228340331602870819},
           0.5 * 0.050844906370206816920936809106869};
        (*this)[3] = {
          {0.24928674517091042129163855310702, 0.24928674517091042129163855310702},
           0.5 * 0.11678627572637936602528961138558};
        (*this)[4] = {
          {0.24928674517091042129163855310702, 0.50142650965817915741672289378596},
           0.5 * 0.11678627572637936602528961138558};
        (*this)[5] = {
          {0.50142650965817915741672289378596, 0.24928674517091042129163855310702},
           0.5 * 0.11678627572637936602528961138558};
        (*this)[6] = {
          {0.053145049844816947353249671631398, 0.31035245103378440541660773395655},
           0.5 * 0.082851075618373575193553456420442};
        (*this)[7] = {
          {0.053145049844816947353249671631398, 0.63650249912139864723014259441205},
           0.5 * 0.082851075618373575193553456420442};
        (*this)[8] = {
          {0.31035245103378440541660773395655, 0.053145049844816947353249671631398},
           0.5 * 0.082851075618373575193553456420442};
        (*this)[9] = {
          {0.31035245103378440541660773395655, 0.63650249912139864723014259441205},
           0.5 * 0.082851075618373575193553456420442};
        (*this)[10] = {
          {0.63650249912139864723014259441205, 0.053145049844816947353249671631398},
           0.5 * 0.082851075618373575193553456420442};
        (*this)[11] = {
          {0.63650249912139864723014259441205, 0.31035245103378440541660773395655},
           0.5 * 0.082851075618373575193553456420442};
        break;

      // polynomial degree 7
      /* 12 inner Gauss points, positive weights */
      // Rule t2-7-12 of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: Table 5, K. Gatermann, The construction of symmetric cubature formulas for the square and the triangle

      case 7:
        this->order_ = 7;
        this->resize(12);
        (*this)[0] = {
          {0.0623822650944021181736830009963499, 0.0675178670739160854425571310508685},
           0.5 * 0.053034056314872502857508360921478};
        (*this)[1] = {
          {0.0675178670739160854425571310508685, 0.870099867831681796383759867952782},
           0.5 * 0.053034056314872502857508360921478};
        (*this)[2] = {
          {0.870099867831681796383759867952782, 0.0623822650944021181736830009963499},
           0.5 * 0.053034056314872502857508360921478};
        (*this)[3] = {
          {0.0552254566569266117374791902756449, 0.321502493851981822666307849199202},
           0.5 * 0.087762817428892110073539806278575};
        (*this)[4] = {
          {0.321502493851981822666307849199202, 0.623272049491091565596212960525153},
           0.5 * 0.087762817428892110073539806278575};
        (*this)[5] = {
          {0.623272049491091565596212960525153, 0.0552254566569266117374791902756449},
           0.5 * 0.087762817428892110073539806278575};
        (*this)[6] = {
          {0.0343243029450971464696306424839376, 0.660949196186735657611980310197799},
           0.5 * 0.057550085569963171476890993800437};
        (*this)[7] = {
          {0.660949196186735657611980310197799, 0.304726500868167195918389047318263},
           0.5 * 0.057550085569963171476890993800437};
        (*this)[8] = {
          {0.304726500868167195918389047318263, 0.0343243029450971464696306424839376},
           0.5 * 0.057550085569963171476890993800437};
        (*this)[9] = {
          {0.515842334353591779257463386826430, 0.277716166976391782569581871393723},
           0.5 * 0.13498637401960554892539417233284};
        (*this)[10] = {
          {0.277716166976391782569581871393723, 0.20644149867001643817295474177985},
           0.5 * 0.13498637401960554892539417233284};
        (*this)[11] = {
          {0.20644149867001643817295474177985, 0.515842334353591779257463386826430},
           0.5 * 0.13498637401960554892539417233284};
        break;

      // polynomial degree 8
      /* 16 inner Gauss points, positive weights */
      // Rule t2-8-16a of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: Appendix II, A. Dunavant, High degree efficient symmetrical Gaussian quadrature rules for the triangle

      case 8:
        this->order_ = 8;
        this->resize(16);
        (*this)[0] = {
          {0.33333333333333333333333333333333, 0.33333333333333333333333333333333},
           0.5 * 0.14431560767778716825109111048906};
        (*this)[1] = {
          {0.17056930775176020662229350149146, 0.17056930775176020662229350149146},
           0.5 * 0.10321737053471825028179155029213};
        (*this)[2] = {
          {0.17056930775176020662229350149146, 0.65886138449647958675541299701707},
           0.5 * 0.10321737053471825028179155029213};
        (*this)[3] = {
          {0.65886138449647958675541299701707, 0.17056930775176020662229350149146},
           0.5 * 0.10321737053471825028179155029213};
        (*this)[4] = {
          {0.050547228317030975458423550596599, 0.050547228317030975458423550596599},
           0.5 * 0.032458497623198080310925928341780};
        (*this)[5] = {
          {0.050547228317030975458423550596599, 0.89890554336593804908315289880680},
           0.5 * 0.032458497623198080310925928341780};
        (*this)[6] = {
          {0.89890554336593804908315289880680, 0.050547228317030975458423550596599},
           0.5 * 0.032458497623198080310925928341780};
        (*this)[7] = {
          {0.45929258829272315602881551449417, 0.45929258829272315602881551449417},
           0.5 * 0.095091634267284624793896104388584};
        (*this)[8] = {
          {0.45929258829272315602881551449417, 0.08141482341455368794236897101166},
           0.5 * 0.095091634267284624793896104388584};
        (*this)[9] = {
          {0.08141482341455368794236897101166, 0.45929258829272315602881551449417},
           0.5 * 0.095091634267284624793896104388584};
        (*this)[10] = {
          {0.72849239295540428124100037917606, 0.26311282963463811342178578628464},
           0.5 * 0.027230314174434994264844690073909};
        (*this)[11] = {
          {0.72849239295540428124100037917606, 0.00839477740995760533721383453930},
           0.5 * 0.027230314174434994264844690073909};
        (*this)[12] = {
          {0.26311282963463811342178578628464, 0.72849239295540428124100037917606},
           0.5 * 0.027230314174434994264844690073909};
        (*this)[13] = {
          {0.26311282963463811342178578628464, 0.00839477740995760533721383453930},
           0.5 * 0.027230314174434994264844690073909};
        (*this)[14] = {
          {0.00839477740995760533721383453930, 0.72849239295540428124100037917606},
           0.5 * 0.027230314174434994264844690073909};
        (*this)[15] = {
          {0.00839477740995760533721383453930, 0.26311282963463811342178578628464},
           0.5 * 0.027230314174434994264844690073909};
        break;

      // polynomial degree 9
      /* 19 inner Gauss points, positive weights */

      // Rule t2-9-19 of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: Appendix II, A. Dunavant, High degree efficient symmetrical Gaussian quadrature rules for the triangle

      case 9:
        this->order_ = 9;
        this->resize(19);
        (*this)[0] = {
          {0.333333333333333333333333333333333, 0.333333333333333333333333333333333},
           0.5 * 0.097135796282798833819241982507289};
        (*this)[1] = {
          {0.48968251919873762778370692483619, 0.48968251919873762778370692483619},
           0.5 * 0.031334700227139070536854831287209};
        (*this)[2] = {
          {0.48968251919873762778370692483619, 0.02063496160252474443258615032762},
           0.5 * 0.031334700227139070536854831287209};
        (*this)[3] = {
          {0.02063496160252474443258615032762, 0.48968251919873762778370692483619},
           0.5 * 0.031334700227139070536854831287209};
        (*this)[4] = {
          {0.43708959149293663726993036443535, 0.43708959149293663726993036443535},
           0.5 * 0.077827541004774279316739356299404};
        (*this)[5] = {
          {0.43708959149293663726993036443535, 0.12582081701412672546013927112929},
           0.5 * 0.077827541004774279316739356299404};
        (*this)[6] = {
          {0.12582081701412672546013927112929, 0.43708959149293663726993036443535},
           0.5 * 0.077827541004774279316739356299404};
        (*this)[7] = {
          {0.18820353561903273024096128046733, 0.18820353561903273024096128046733},
           0.5 * 0.079647738927210253032891774264045};
        (*this)[8] = {
          {0.18820353561903273024096128046733, 0.62359292876193453951807743906533},
           0.5 * 0.079647738927210253032891774264045};
        (*this)[9] = {
          {0.62359292876193453951807743906533, 0.18820353561903273024096128046733},
           0.5 * 0.079647738927210253032891774264045};
        (*this)[10] = {
          {0.044729513394452709865106589966276, 0.044729513394452709865106589966276},
           0.5 * 0.025577675658698031261678798559000};
        (*this)[11] = {
          {0.044729513394452709865106589966276, 0.91054097321109458026978682006745},
           0.5 * 0.025577675658698031261678798559000};
        (*this)[12] = {
          {0.91054097321109458026978682006745, 0.044729513394452709865106589966276},
           0.5 * 0.025577675658698031261678798559000};
        (*this)[13] = {
          {0.74119859878449802069007987352342, 0.036838412054736283634817598783385},
           0.5 * 0.043283539377289377289377289377289};
        (*this)[14] = {
          {0.74119859878449802069007987352342, 0.22196298916076569567510252769319},
           0.5 * 0.043283539377289377289377289377289};
        (*this)[15] = {
          {0.036838412054736283634817598783385, 0.74119859878449802069007987352342},
           0.5 * 0.043283539377289377289377289377289};
        (*this)[16] = {
          {0.036838412054736283634817598783385, 0.22196298916076569567510252769319},
           0.5 * 0.043283539377289377289377289377289};
        (*this)[17] = {
          {0.22196298916076569567510252769319, 0.74119859878449802069007987352342},
           0.5 * 0.043283539377289377289377289377289};
        (*this)[18] = {
          {0.22196298916076569567510252769319, 0.036838412054736283634817598783385},
           0.5 * 0.043283539377289377289377289377289};
        break;

      // polynomial degree 10
      /* 25 inner Gauss points, positive weights */

      // Rule t2-10-25a of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: M.E. Laursen and M. Gellert, Some criteria for numerically integrated matrices and quadrature formulas for triangles

      case 10:
        this->order_ = 10;
        this->resize(25);
        (*this)[0] = {
          {0.333333333333333333333333333333333, 0.333333333333333333333333333333333},
           0.5 * 0.079894504741239707831247045213386};
        (*this)[1] = {
          {0.42508621060209057296952951163804, 0.42508621060209057296952951163804},
           0.5 * 0.071123802232377334639291287398658};
        (*this)[2] = {
          {0.42508621060209057296952951163804, 0.14982757879581885406094097672391},
           0.5 * 0.071123802232377334639291287398658};
        (*this)[3] = {
          {0.14982757879581885406094097672391, 0.42508621060209057296952951163804},
           0.5 * 0.071123802232377334639291287398658};
        (*this)[4] = {
          {0.023308867510000190714466386895980, 0.023308867510000190714466386895980},
           0.5 * 0.0082238186904641955186466203624719};
        (*this)[5] = {
          {0.023308867510000190714466386895980, 0.95338226497999961857106722620804},
           0.5 * 0.0082238186904641955186466203624719};
        (*this)[6] = {
          {0.95338226497999961857106722620804, 0.023308867510000190714466386895980},
           0.5 * 0.0082238186904641955186466203624719};
        (*this)[7] = {
          {0.62830740021349255642083766607883, 0.22376697357697300622568649026820},
           0.5 * 0.045430592296170018007073629243933};
        (*this)[8] = {
          {0.62830740021349255642083766607883, 0.14792562620953443735347584365296},
           0.5 * 0.045430592296170018007073629243933};
        (*this)[9] = {
          {0.22376697357697300622568649026820, 0.62830740021349255642083766607883},
           0.5 * 0.045430592296170018007073629243933};
        (*this)[10] = {
          {0.22376697357697300622568649026820, 0.14792562620953443735347584365296},
           0.5 * 0.045430592296170018007073629243933};
        (*this)[11] = {
          {0.14792562620953443735347584365296, 0.62830740021349255642083766607883},
           0.5 * 0.045430592296170018007073629243933};
        (*this)[12] = {
          {0.14792562620953443735347584365296, 0.22376697357697300622568649026820},
           0.5 * 0.045430592296170018007073629243933};
        (*this)[13] = {
          {0.61131382618139764891875500225390, 0.35874014186443146457815530072385},
           0.5 * 0.037359856234305276826236499001975};
        (*this)[14] = {
          {0.61131382618139764891875500225390, 0.02994603195417088650308969702225},
           0.5 * 0.037359856234305276826236499001975};
        (*this)[15] = {
          {0.35874014186443146457815530072385, 0.61131382618139764891875500225390},
           0.5 * 0.037359856234305276826236499001975};
        (*this)[16] = {
          {0.35874014186443146457815530072385, 0.02994603195417088650308969702225},
           0.5 * 0.037359856234305276826236499001975};
        (*this)[17] = {
          {0.02994603195417088650308969702225, 0.61131382618139764891875500225390},
           0.5 * 0.037359856234305276826236499001975};
        (*this)[18] = {
          {0.02994603195417088650308969702225, 0.35874014186443146457815530072385},
           0.5 * 0.037359856234305276826236499001975};
        (*this)[19] = {
          {0.82107206998562937337354441347218, 0.14329537042686714530585663061732},
           0.5 * 0.030886656884563988782513077004629};
        (*this)[20] = {
          {0.82107206998562937337354441347218, 0.03563255958750348132059895591050},
           0.5 * 0.030886656884563988782513077004629};
        (*this)[21] = {
          {0.14329537042686714530585663061732, 0.82107206998562937337354441347218},
           0.5 * 0.030886656884563988782513077004629};
        (*this)[22] = {
          {0.14329537042686714530585663061732, 0.03563255958750348132059895591050},
           0.5 * 0.030886656884563988782513077004629};
        (*this)[23] = {
          {0.03563255958750348132059895591050, 0.82107206998562937337354441347218},
           0.5 * 0.030886656884563988782513077004629};
        (*this)[24] = {
          {0.03563255958750348132059895591050, 0.14329537042686714530585663061732},
           0.5 * 0.030886656884563988782513077004629};
        break;

      // polynomial degree 11
      /* 28 inner Gauss points, positive weights */

      // Rule t2-11-28 of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: J.N. Lyness and D. Jespersen, Moderate degree symmetric quadrature rules for the triangle

      case 11:
        this->order_ = 11;
        this->resize(28);
        (*this)[0] = {
          {0.858870281282636704039173938058347, 0.141129718717363295960826061941652},
           0.5 * 0.0073623837833005542642588950473806};
        (*this)[1] = {
          {0.858870281282636704039173938058347, 0.0},
           0.5 * 0.0073623837833005542642588950473806};
        (*this)[2] = {
          {0.141129718717363295960826061941652, 0.858870281282636704039173938058347},
           0.5 * 0.0073623837833005542642588950473806};
        (*this)[3] = {
          {0.141129718717363295960826061941652, 0.0},
           0.5 * 0.0073623837833005542642588950473806};
        (*this)[4] = {
          {0.0, 0.858870281282636704039173938058347},
           0.5 * 0.0073623837833005542642588950473806};
        (*this)[5] = {
          {0.0, 0.141129718717363295960826061941652},
           0.5 * 0.0073623837833005542642588950473806};
        (*this)[6] = {
          {0.333333333333333333333333333333333, 0.333333333333333333333333333333333},
           0.5 * 0.087977301162232238798093169321456};
        (*this)[7] = {
          {0.025989140928287395260032485498841, 0.025989140928287395260032485498841},
           0.5 * 0.0087443115537360230495164287998252};
        (*this)[8] = {
          {0.025989140928287395260032485498841, 0.94802171814342520947993502900232},
           0.5 * 0.0087443115537360230495164287998252};
        (*this)[9] = {
          {0.94802171814342520947993502900232, 0.025989140928287395260032485498841},
           0.5 * 0.0087443115537360230495164287998252};
        (*this)[10] = {
          {0.094287502647922495630569776275405, 0.094287502647922495630569776275405},
           0.5 * 0.038081571993934937515024339435614};
        (*this)[11] = {
          {0.094287502647922495630569776275405, 0.81142499470415500873886044744919},
           0.5 * 0.038081571993934937515024339435614};
        (*this)[12] = {
          {0.81142499470415500873886044744919, 0.094287502647922495630569776275405},
           0.5 * 0.038081571993934937515024339435614};
        (*this)[13] = {
          {0.49463677501721381374163260230644, 0.49463677501721381374163260230644},
           0.5 * 0.018855448056131292058476782591115};
        (*this)[14] = {
          {0.49463677501721381374163260230644, 0.01072644996557237251673479538713},
           0.5 * 0.018855448056131292058476782591115};
        (*this)[15] = {
          {0.01072644996557237251673479538713, 0.49463677501721381374163260230644},
           0.5 * 0.018855448056131292058476782591115};
        (*this)[16] = {
          {0.20734338261451133345293402411297, 0.20734338261451133345293402411297},
           0.5 * 0.072159697544739526124029988586463};
        (*this)[17] = {
          {0.20734338261451133345293402411297, 0.58531323477097733309413195177407},
           0.5 * 0.072159697544739526124029988586463};
        (*this)[18] = {
          {0.58531323477097733309413195177407, 0.20734338261451133345293402411297},
           0.5 * 0.072159697544739526124029988586463};
        (*this)[19] = {
          {0.43890780570049209506106538163613, 0.43890780570049209506106538163613},
           0.5 * 0.069329138705535899841765650903814};
        (*this)[20] = {
          {0.43890780570049209506106538163613, 0.12218438859901580987786923672775},
           0.5 * 0.069329138705535899841765650903814};
        (*this)[21] = {
          {0.12218438859901580987786923672775, 0.43890780570049209506106538163613},
           0.5 * 0.069329138705535899841765650903814};
        (*this)[22] = {
          {0.67793765488259040154212614118875, 0.044841677589130443309052391468801},
           0.5 * 0.041056315429288566641652314907294};
        (*this)[23] = {
          {0.67793765488259040154212614118875, 0.27722066752827915514882146734245},
           0.5 * 0.041056315429288566641652314907294};
        (*this)[24] = {
          {0.044841677589130443309052391468801, 0.67793765488259040154212614118875},
           0.5 * 0.041056315429288566641652314907294};
        (*this)[25] = {
          {0.044841677589130443309052391468801, 0.27722066752827915514882146734245},
           0.5 * 0.041056315429288566641652314907294};
        (*this)[26] = {
          {0.27722066752827915514882146734245, 0.67793765488259040154212614118875},
           0.5 * 0.041056315429288566641652314907294};
        (*this)[27] = {
          {0.27722066752827915514882146734245, 0.044841677589130443309052391468801},
           0.5 * 0.041056315429288566641652314907294};
        break;

      // polynomial degree 12
      /* 33 inner Gauss points, positive weights */

      // Rule t2-12-33 of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: Appendix II, A. Dunavant, High degree efficient symmetrical Gaussian quadrature rules for the triangle

      case 12:
        this->order_ = 12;
        this->resize(33);
        (*this)[0] = {
          {0.02356522045239, 0.488217389773805},
           0.5 * 0.025731066440455};
        (*this)[1] = {
          {0.488217389773805, 0.02356522045239},
           0.5 * 0.025731066440455};
        (*this)[2] = {
          {0.488217389773805, 0.488217389773805},
           0.5 * 0.025731066440455};
        (*this)[3] = {
          {0.43972439229446, 0.43972439229446},
           0.5 * 0.043692544538038};
        (*this)[4] = {
          {0.43972439229446, 0.120551215411079},
           0.5 * 0.043692544538038};
        (*this)[5] = {
          {0.120551215411079, 0.43972439229446},
           0.5 * 0.043692544538038};
        (*this)[6] = {
          {0.271210385012116, 0.271210385012116},
           0.5 * 0.062858224217885};
        (*this)[7] = {
          {0.271210385012116, 0.457579229975768},
           0.5 * 0.062858224217885};
        (*this)[8] = {
          {0.457579229975768, 0.271210385012116},
           0.5 * 0.062858224217885};
        (*this)[9] = {
          {0.127576145541586, 0.127576145541586},
           0.5 * 0.034796112930709};
        (*this)[10] = {
          {0.127576145541586, 0.7448477089168279},
           0.5 * 0.034796112930709};
        (*this)[11] = {
          {0.7448477089168279, 0.127576145541586},
           0.5 * 0.034796112930709};
        (*this)[12] = {
          {0.02131735045321, 0.02131735045321},
           0.5 * 0.006166261051559};
        (*this)[13] = {
          {0.02131735045321, 0.9573652990935799},
           0.5 * 0.006166261051559};
        (*this)[14] = {
          {0.9573652990935799, 0.02131735045321},
           0.5 * 0.006166261051559};
        (*this)[15] = {
          {0.115343494534698, 0.275713269685514},
           0.5 * 0.040371557766381};
        (*this)[16] = {
          {0.115343494534698, 0.6089432357797879},
           0.5 * 0.040371557766381};
        (*this)[17] = {
          {0.275713269685514, 0.115343494534698},
           0.5 * 0.040371557766381};
        (*this)[18] = {
          {0.275713269685514, 0.6089432357797879},
           0.5 * 0.040371557766381};
        (*this)[19] = {
          {0.6089432357797879, 0.115343494534698},
           0.5 * 0.040371557766381};
        (*this)[20] = {
          {0.6089432357797879, 0.275713269685514},
           0.5 * 0.040371557766381};
        (*this)[21] = {
          {0.022838332222257, 0.28132558098994},
           0.5 * 0.022356773202303};
        (*this)[22] = {
          {0.022838332222257, 0.6958360867878031},
           0.5 * 0.022356773202303};
        (*this)[23] = {
          {0.28132558098994, 0.022838332222257},
           0.5 * 0.022356773202303};
        (*this)[24] = {
          {0.28132558098994, 0.6958360867878031},
           0.5 * 0.022356773202303};
        (*this)[25] = {
          {0.6958360867878031, 0.022838332222257},
           0.5 * 0.022356773202303};
        (*this)[26] = {
          {0.6958360867878031, 0.28132558098994},
           0.5 * 0.022356773202303};
        (*this)[27] = {
          {0.02573405054833, 0.116251915907597},
           0.5 * 0.017316231108659};
        (*this)[28] = {
          {0.02573405054833, 0.858014033544073},
           0.5 * 0.017316231108659};
        (*this)[29] = {
          {0.116251915907597, 0.02573405054833},
           0.5 * 0.017316231108659};
        (*this)[30] = {
          {0.116251915907597, 0.858014033544073},
           0.5 * 0.017316231108659};
        (*this)[31] = {
          {0.858014033544073, 0.02573405054833},
           0.5 * 0.017316231108659};
        (*this)[32] = {
          {0.858014033544073, 0.116251915907597},
           0.5 * 0.017316231108659};
        break;

      default:
        DUNE_THROW(QuadratureOrderOutOfRange,
                   "QuadratureRule for order " << p << " and GeometryType "
                                               << this->type() << " not available");
    }
  }

  template<typename ct>
  SimplexQuadratureRule<ct,3>::SimplexQuadratureRule(int p)
    : QuadratureRule<ct,3>(GeometryTypes::tetrahedron)
  {
    // helper variables used to define the quadrature rules
    const ct m_4_a = 0.585410196624968500L;
    const ct m_4_b = 0.138196601125010500L;
    const ct w_4 = 1.0L/4.0L/6.0L;
    const ct s_1 = 0.09197107805272303279L;   /* (7 - sqrt(15) ) / 34 */
    const ct s_2 = 0.31979362782962990839L;   /* (7 + sqrt(15) ) / 34 */
    const ct t_1 = 0.72408676584183090164L;   /* (13 + 3*sqrt(15) ) / 34 */
    const ct t_2 = 0.04061911651111027484L;   /* (13 - 3*sqrt(15) ) / 34 */
    const ct u   = 0.05635083268962915574L;   /* (10 - 2*sqrt(15) ) / 40 */
    const ct v   = 0.44364916731037084426L;   /* (10 + 2*sqrt(15) ) / 40 */
    const ct A   = 0.019753086419753086420L;  /* 16 / 135 / vol */
    const ct B_1 = 0.011989513963169770001L;  /* (2665 + 14*sqrt(15) )/37800/vol */
    const ct B_2 = 0.011511367871045397547L;  /* (2665 - 14*sqrt(15) )/37800/vol */
    const ct C   = 0.0088183421516754850088L; /* 20 / 378 / vol */

    switch (p)
    {
      // polynom degree 1

      // Rule t3-1-1 of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: Rule 1-1, P. 307, A.H. Stroud, Approximate Calculation of Multiple Integrals

      case 0:
      case 1:
        this->order_ = 1;
        this->resize(1);
        (*this)[0] = {{0.25, 0.25, 0.25}, 1.0L/6.0L};
        break;

      // polynom degree 2
      // symmetric

      // Rule t3-2-4a of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: Rule 2-1, P. 307, A.H. Stroud, Approximate Calculation of Multiple Integrals

      case 2:
        this->order_ = 2;
        this->resize(4);
        (*this)[0] = {{m_4_a, m_4_b, m_4_b}, w_4};
        (*this)[1] = {{m_4_b, m_4_a, m_4_b}, w_4};
        (*this)[2] = {{m_4_b, m_4_b, m_4_a}, w_4};
        (*this)[3] = {{m_4_b, m_4_b, m_4_b}, w_4};
        break;

      // polynom degree 3
      // symmetric

      // Rule t3-3-8b of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: Rule 3-7, P. 309, A.H. Stroud, Approximate Calculation of Multiple Integrals

      case 3:
        this->order_ = 3;
        this->resize(8);
        (*this)[0] = {{0.0, 0.0, 0.0}, 0.025L/6.0L};
        (*this)[1] = {{1.0, 0.0, 0.0}, 0.025L/6.0L};
        (*this)[2] = {{0.0, 1.0, 0.0}, 0.025L/6.0L};
        (*this)[3] = {{0.0, 0.0, 1.0}, 0.025L/6.0L};
        (*this)[4] = {{1.0/3.0, 1.0/3.0, 0.0}, 0.225L/6.0L};
        (*this)[5] = {{1.0/3.0, 0.0, 1.0/3.0}, 0.225L/6.0L};
        (*this)[6] = {{0.0, 1.0/3.0, 1.0/3.0}, 0.225L/6.0L};
        (*this)[7] = {{1.0/3.0, 1.0/3.0, 1.0/3.0}, 0.225L/6.0L};
        break;


      // polynomial degree 5
      // symmetric points

      // Rule t3-5-15a (actual values for weights etc. not available here) of the "Encyclopaedia of Cubature Formulas" at
      // http://www.cs.kuleuven.ac.be/~nines/research/ecf/ecf.html
      // maintained by Ronald Cools.

      // For further reference: Rule 5-1, P. 315, A.H. Stroud, Approximate Calculation of Multiple Integrals

      case 4:
      case 5:
        this->order_ = 5;
        this->resize(15);
        (*this)[0] = {{0.25, 0.25, 0.25}, A};
        (*this)[1] = {{s_1, s_1, s_1}, B_1};
        (*this)[2] = {{t_1, s_1, s_1}, B_1};
        (*this)[3] = {{s_1, t_1, s_1}, B_1};
        (*this)[4] = {{s_1, s_1, t_1}, B_1};
        (*this)[5] = {{s_2, s_2, s_2}, B_2};
        (*this)[6] = {{t_2, s_2, s_2}, B_2};
        (*this)[7] = {{s_2, t_2, s_2}, B_2};
        (*this)[8] = {{s_2, s_2, t_2}, B_2};
        (*this)[9]  = {{v, u, u}, C};
        (*this)[10] = {{u, v, u}, C};
        (*this)[11] = {{u, u, v}, C};
        (*this)[12] = {{v, v, u}, C};
        (*this)[13] = {{v, u, v}, C};
        (*this)[14] = {{u, v, v}, C};
        break;

      default:
        DUNE_THROW(QuadratureOrderOutOfRange,
                  "QuadratureRule for order " << p << " and GeometryType "
                                              << this->type() << " not available");
    }
  }

} // end namespace Dune

#endif // DUNE_GEOMETRY_QUADRATURE_SIMPLEX_HH
