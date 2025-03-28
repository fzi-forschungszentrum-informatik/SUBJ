// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
//
// Copyright 2025 FZI Forschungszentrum Informatik
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// “Software”), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Stefan Orf <orf@fzi.de>
 * \date    2025-01-25
 *
 */
//----------------------------------------------------------------------

#ifndef SUBJ_MULTINOMIALOPINION_H
#define SUBJ_MULTINOMIALOPINION_H

#include <subj/DirichletPDF.h>
#include <subj/OpinionOwner.h>

#include <Eigen/Dense>
#include <initializer_list>
#include <iostream>
#include <vector>

namespace subj {

class MultinomialOpinion
{
public:
  using Vector = Eigen::Matrix<double, Eigen::Dynamic, 1>;

  MultinomialOpinion() = delete;
  MultinomialOpinion(const uint32_t& dimensions);
  MultinomialOpinion(const std::initializer_list<double>& belief,
                     const double& uncertainty,
                     const std::initializer_list<double>& base_rate);
  MultinomialOpinion(const std::vector<double>& belief,
                     const double& uncertainty,
                     const std::vector<double>& base_rate);
  MultinomialOpinion(const Vector& belief, const double& uncertainty, const Vector& base_rate);

  bool update(const std::initializer_list<double>& belief,
              const double& uncertainty,
              const std::initializer_list<double>& base_rate);
  bool update(const std::vector<double>& belief,
              const double& uncertainty,
              const std::vector<double>& base_rate);
  bool update(const Vector& belief, const double& uncertainty, const Vector& base_rate);

  bool updateBelief(const std::initializer_list<double>& belief);
  bool updateBelief(const std::vector<double>& belief);
  bool updateBelief(const Vector& belief);

  bool b(const std::initializer_list<double>& belief);
  bool b(const std::vector<double>& belief);
  bool b(const Vector& belief);

  std::vector<double> belief() const;
  Vector beliefMat() const;

  std::vector<double> b() const;
  Vector bMat() const;

  bool updateUncertainty(const double& uncertainty);

  bool u(const double& uncertainty);

  double uncertainty() const;

  double u() const;

  bool updateBaseRate(const std::initializer_list<double>& base_rate);
  bool updateBaseRate(const std::vector<double>& base_rate);
  bool updateBaseRate(const Vector& base_rate);

  bool a(const std::initializer_list<double>& base_rate);
  bool a(const std::vector<double>& base_rate);
  bool a(const Vector& base_rate);

  std::vector<double> baseRate() const;
  Vector baseRateMat() const;

  std::vector<double> a() const;
  Vector aMat() const;

  OpinionOwner owner() const;

  void updateOwner(const OpinionOwner& owner);

  DirichletPDF dirichletPdf() const;

  DirichletPDF dir() const;

  void update(DirichletPDF& pdf);

  std::vector<double> projection() const;
  Vector projectionMat() const;

  std::vector<double> p() const;
  Vector pMat() const;

  std::vector<double> variance() const;
  Vector varianceMat() const;

  std::vector<double> var() const;
  Vector varMat() const;

  double uncertaintyMaximum() const;

  double uMax() const;

  friend std::ostream& operator<<(std::ostream& os, const MultinomialOpinion& opinion);

  Eigen::Index dim() const;

protected:
  OpinionOwner m_owner;

  Vector m_belief;
  double m_uncertainty;
  Vector m_base_rate;

  double m_prior_weight;

  Eigen::Index m_dim = -1;
};

} // namespace subj

#endif /* SUBJ_MULTINOMIALOPINION_H */