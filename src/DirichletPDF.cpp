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

#include <subj/DirichletPDF.h>

#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <utility>

namespace subj {

DirichletPDF::DirichletPDF() = default;

void DirichletPDF::updateEvidence(const std::initializer_list<double>& evidence)
{
  updateEvidence(std::vector<double>(evidence));
}

void DirichletPDF::updateEvidence(const std::vector<double>& evidence)
{
  updateEvidence(Eigen::Map<const Eigen::VectorXd, Eigen::Unaligned>(
    evidence.data(), (Eigen::Index)evidence.size()));
}

void DirichletPDF::updateEvidence(const Eigen::Matrix<double, Eigen::Dynamic, 1>& evidence)
{
  // TODO Check dimensions
  m_evidence = evidence;
}

void DirichletPDF::updateBaseRate(const std::initializer_list<double>& base_rate)
{
  updateBaseRate(std::vector<double>(base_rate));
}

void DirichletPDF::updateBaseRate(const std::vector<double>& base_rate)
{
  updateBaseRate(Eigen::Map<const Eigen::VectorXd, Eigen::Unaligned>(
    base_rate.data(), (Eigen::Index)base_rate.size()));
}

void DirichletPDF::updateBaseRate(const Eigen::Matrix<double, Eigen::Dynamic, 1>& base_rate)
{
  // TODO Check dimensions
  m_base_rate = base_rate;
}

std::vector<double> DirichletPDF::evidence() const
{
  return std::vector<double>(m_evidence.data(), m_evidence.data() + m_evidence.size());
}

Eigen::VectorXd DirichletPDF::evidenceMat() const
{
  return m_evidence;
}

std::vector<double> DirichletPDF::baseRate() const
{
  return std::vector<double>(m_base_rate.data(), m_base_rate.data() + m_base_rate.size());
}

Eigen::VectorXd DirichletPDF::baseRateMat() const
{
  return m_base_rate;
}

std::vector<double> DirichletPDF::strength() const
{
  Eigen::VectorXd strength_vec = m_evidence + m_base_rate * m_prior_weight;
  return std::vector<double>(strength_vec.data(), strength_vec.data() + strength_vec.size());
}

Eigen::VectorXd DirichletPDF::strengthMat() const
{
  return m_evidence + m_base_rate * m_prior_weight;
}

double DirichletPDF::density(const std::initializer_list<double>& x) const
{
  return density(std::vector<double>(x));
}

double DirichletPDF::density(const std::vector<double>& x) const
{
  return density(
    Eigen::Map<const Eigen::VectorXd, Eigen::Unaligned>(x.data(), (Eigen::Index)x.size()));
}

double DirichletPDF::density(const Eigen::Matrix<double, Eigen::Dynamic, 1>& x) const
{
  // TODO check size?
  Eigen::Matrix<double, Eigen::Dynamic, 1> alpha = Eigen::Map<Eigen::VectorXd, Eigen::Unaligned>(
    strength().data(), (Eigen::Index)strength().size());

  double gamma_prod = 1.0;
  for (int i = 0; i < x.rows(); ++i)
  {
    gamma_prod =
      gamma_prod * static_cast<double>(std::tgammal(alpha(i))); // TODO handle loss of precision
  }

  double pow_prod = 1.0;
  for (int i = 0; i < x.rows(); ++i)
  {
    pow_prod = pow_prod * std::pow(x(i), alpha(i) - 1.0);
  }

  return (static_cast<double>(std::tgammal(alpha.sum())) / gamma_prod) *
         pow_prod; // TODO handle loss of precision
}

std::ostream& operator<<(std::ostream& os, const DirichletPDF& pdf)
{
  os << "Dir^e(p, r=(" << pdf.m_evidence(0);
  for (int i = 1; i < pdf.m_evidence.rows(); ++i)
  {
    os << ", " << pdf.m_evidence(i);
  }

  os << "), a=(" << pdf.m_base_rate(0);
  for (int i = 1; i < pdf.m_evidence.rows(); ++i)
  {
    os << ", " << pdf.m_base_rate(i);
  }

  os << "))";
  return os;
}

} // namespace subj