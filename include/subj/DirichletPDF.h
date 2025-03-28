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

#ifndef SUBJ_DIRICHLET_PDF_H_INCLUDED
#define SUBJ_DIRICHLET_PDF_H_INCLUDED

#include <Eigen/Dense>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <vector>

namespace subj {

class DirichletPDF
{
public:
  DirichletPDF();

  void updateEvidence(const std::initializer_list<double>& evidence);
  void updateEvidence(const std::vector<double>& evidence);
  void updateEvidence(const Eigen::Matrix<double, Eigen::Dynamic, 1>& evidence);

  void updateBaseRate(const std::initializer_list<double>& base_rate);
  void updateBaseRate(const std::vector<double>& base_rate);
  void updateBaseRate(const Eigen::Matrix<double, Eigen::Dynamic, 1>& base_rate);

  std::vector<double> evidence() const;
  Eigen::VectorXd evidenceMat() const;

  std::vector<double> baseRate() const;
  Eigen::VectorXd baseRateMat() const;

  std::vector<double> strength() const;
  Eigen::VectorXd strengthMat() const;

  double density(const std::initializer_list<double>& x) const;
  double density(const std::vector<double>& x) const;
  double density(const Eigen::Matrix<double, Eigen::Dynamic, 1>& x) const;

  friend std::ostream& operator<<(std::ostream& os, const DirichletPDF& pdf);

private:
  Eigen::Matrix<double, Eigen::Dynamic, 1> m_evidence;
  Eigen::Matrix<double, Eigen::Dynamic, 1> m_base_rate;
  double m_prior_weight = 2;
};

} // namespace subj

#endif /* SUBJ_DIRICHLET_PDF_H_INCLUDED */