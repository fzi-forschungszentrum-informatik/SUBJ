// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Stefan Orf <orf@fzi.de>
 * \date    2025-01-25
 *
 */
//----------------------------------------------------------------------

#include <Eigen/Dense>
#include <iostream>
#include <subj/subj.h>

std::ostream& operator<<(std::ostream& os, const std::vector<double>& vector)
{
  os << "{";
  for (auto it = vector.begin(); it != --vector.end(); ++it)
  {
    os << *it << ", ";
  }
  os << *(--vector.end()) << "}";

  return os;
}

int main(int argc, char** argv)
{
  // A binomial opinion takes with belief = 0.1, disbelief = 0.5,
  // uncertainty = 0.4 and base rate of 0.5 is created with:
  std::cout << "Creating a binomial opinion bin_op1 with belief = 0.1, disbelief = 0.5, "
               "uncertainty = 0.2 and base rate of 0.3."
            << std::endl;
  subj::BinomialOpinion bin_op1 = subj::BinomialOpinion(0.1, 0.5, 0.4, 0.5);
  std::cout << "bin_op1 = " << bin_op1 << std::endl;

  // Binomial opinion with belief = 0.8, disbelief = 0.1,
  // uncertainty = 0.1 and base rate = 0.5:
  std::cout << "Creating a binomial opinion bin_op2 with belief = 0.8, disbelief = 0.1, "
               "uncertainty = 0.1 and base rate of 0.3."
            << std::endl;
  subj::BinomialOpinion bin_op2 = subj::BinomialOpinion(0.8, 0.1, 0.1, 0.3);
  std::cout << "bin_op2 = " << bin_op2 << std::endl << std::endl;

  // Binomial opinions are just 2-dimensional multinomial opinions.
  // The BinomialOpinion class provides a few convenience functions,
  // but can be used just like MultinomialOpinions.

  // Multinomial opinions are created similar.
  // Here 4-dimensional multinomial opinions are created:
  std::cout << "Creating a multinomial opinion mult_op1 with belief = {0.1, 0.1, 0.4, 0.2}, "
               "uncertainty = 0.2 and base rate of {0.25, 0.25, 0.25, 0.25}."
            << std::endl;
  subj::MultinomialOpinion mult_op1 =
    subj::MultinomialOpinion({0.1, 0.1, 0.4, 0.2}, 0.2, {0.25, 0.25, 0.25, 0.25});
  std::cout << "mult_op1 = " << mult_op1 << std::endl;

  std::cout << "Creating a multinomial opinion mult_op2 with belief = {0.3, 0.1, 0.0, 0.0}, "
               "uncertainty = 0.4 and base rate of {0.1, 0.5, 0.2, 0.2}."
            << std::endl;
  subj::MultinomialOpinion mult_op2 =
    subj::MultinomialOpinion({0.3, 0.1, 0.0, 0.0}, 0.4, {0.10, 0.50, 0.20, 0.20});
  std::cout << "mult_op2 = " << mult_op2 << std::endl << std::endl;

  // Functions for updating of opinions also exist
  std::cout << "Updating belief of mult_op1 with {0.0, 0.0, 0.4, 0.1}." << std::endl;
  mult_op1.updateBelief({0.0, 0.0, 0.4, 0.1});
  std::cout << "Updating uncertainty of mult_op1 with 0.5." << std::endl;
  mult_op1.updateUncertainty(0.5);
  std::cout << "Updating base rate of mult_op1 with {0.0, 0.3, 0.7, 0.0}." << std::endl;
  mult_op1.updateBaseRate({0.0, 0.3, 0.7, 0.0});


  // Belief, uncertainty and base rate of opinions can be retrieved with:
  std::cout << "Belief of mult_op1 is " << mult_op1.belief() << std::endl;
  std::cout << "Uncertainty of mult_op1 is " << mult_op1.uncertainty() << std::endl;
  std::cout << "Base rate of mult_op1 is " << mult_op1.baseRate() << std::endl;


  // Short-hand aliases for these getter and setter functions
  // are available:
  std::cout << "Updating belief of mult_op1 with {0.05, 0.05, 0.25, 0.15}." << std::endl;
  mult_op1.b({0.05, 0.05, 0.25, 0.15});

  std::cout << "Belief of mult_op1 is " << mult_op1.b() << std::endl;
  std::cout << "Uncertainty of mult_op1 is " << mult_op1.u() << std::endl;
  std::cout << "Base rate of mult_op1 is " << mult_op1.a() << std::endl << std::endl;


  // The projection of an opinion can be calculated with:
  std::cout << "Projection of bin_op1 = " << bin_op1.projection() << std::endl;
  std::cout << "Projection of bin_op2 = " << bin_op2.p() << std::endl;
  std::cout << "Projection of mult_op1 = " << mult_op1.projection() << std::endl;
  std::cout << "Projection of mult_op2 = " << mult_op2.p() << std::endl;

  // The opinion's variance:
  std::cout << "Variance of bin_op1 = " << bin_op1.variance() << std::endl;
  std::cout << "Variance of bin_op2 = " << bin_op2.var() << std::endl << std::endl;

  // The corresponding dirichlet PDF of an opinion can be retrieved with:
  subj::DirichletPDF dir1 = mult_op1.dir();
  std::cout << "Dirichlet PDF of mult_op1 = " << dir1 << std::endl;

  // And the density at a given point can then be calculated with:
  std::cout << "Density of the Dirichlet PDF of mult_op1 at {0.2, 0.3, 0.6, 0.1} = "
            << dir1.density({0.2, 0.3, 0.6, 0.1}) << std::endl
            << std::endl;

  // Combination of opinions can be done with one of the several operators.
  // For example the aleatory cumulative belief fusion of two opinions is
  // calculated with:
  std::cout << "Applying aleatory cumulative belief fusion (CBF) to mult_op1 and mult_op2."
            << std::endl;
  subj::MultinomialOpinion fuse_op = subj::cbf(mult_op1, mult_op2);
  std::cout << "CBF(mult_op1, mult_op2) = " << fuse_op << std::endl << std::endl;

  // The degree of conflict of two opinions is calculated with:
  std::cout << "Degree of conflict DOC(bin_op1, bin_op2) = " << subj::doc(bin_op1, bin_op2)
            << std::endl;
  std::cout << "DOC(mult_op1, mult_op2) = " << subj::doc(mult_op1, mult_op2) << std::endl
            << std::endl;

  std::cout << "There are a lot more operators. See Operators.h for reference." << std::endl;

  return 0;
}