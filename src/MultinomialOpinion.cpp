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
#include <subj/MultinomialOpinion.h>
#include <subj/OpinionOwner.h>

#include <Eigen/Dense>
#include <iostream>
#include <limits>

namespace subj {

MultinomialOpinion::MultinomialOpinion(const uint32_t& dimensions)
{
  // Check dimensions > 0!
  m_dim          = dimensions;
  m_belief       = Eigen::VectorXd::Zero(dimensions);
  m_base_rate    = Eigen::VectorXd::Constant(dimensions, 1.0 / dimensions);
  m_uncertainty  = 1.0;
  m_prior_weight = dimensions;
}

MultinomialOpinion::MultinomialOpinion(const std::initializer_list<double>& belief,
                                       const double& uncertainty,
                                       const std::initializer_list<double>& base_rate)
  : MultinomialOpinion(std::vector<double>(belief), uncertainty, std::vector<double>(base_rate))
{
}

MultinomialOpinion::MultinomialOpinion(const std::vector<double>& belief,
                                       const double& uncertainty,
                                       const std::vector<double>& base_rate)
  : MultinomialOpinion(Eigen::Map<const Eigen::VectorXd, Eigen::Unaligned>(
                         belief.data(), (Eigen::Index)belief.size()),
                       uncertainty,
                       Eigen::Map<const Eigen::VectorXd, Eigen::Unaligned>(
                         base_rate.data(), (Eigen::Index)base_rate.size()))
{
}

MultinomialOpinion::MultinomialOpinion(const MultinomialOpinion::Vector& belief,
                                       const double& uncertainty,
                                       const MultinomialOpinion::Vector& base_rate)
{
  update(belief, uncertainty, base_rate);
}

bool MultinomialOpinion::update(const std::initializer_list<double>& belief,
                                const double& uncertainty,
                                const std::initializer_list<double>& base_rate)
{
  return update(std::vector<double>(belief), uncertainty, std::vector<double>(base_rate));
}

bool MultinomialOpinion::update(const std::vector<double>& belief,
                                const double& uncertainty,
                                const std::vector<double>& base_rate)
{
  return update(
    Eigen::Map<const Eigen::VectorXd, Eigen::Unaligned>(belief.data(), (Eigen::Index)belief.size()),
    uncertainty,
    Eigen::Map<const Eigen::VectorXd, Eigen::Unaligned>(base_rate.data(),
                                                        (Eigen::Index)base_rate.size()));
}

bool MultinomialOpinion::update(const MultinomialOpinion::Vector& belief,
                                const double& uncertainty,
                                const MultinomialOpinion::Vector& base_rate)
{
  bool b = updateBelief(belief);
  bool u = updateUncertainty(uncertainty);
  bool a = updateBaseRate(base_rate);
  return (b || u || a);
}

bool MultinomialOpinion::updateBelief(const std::initializer_list<double>& belief)
{
  return updateBelief(std::vector<double>(belief));
}

bool MultinomialOpinion::updateBelief(const std::vector<double>& belief)
{
  return updateBelief(Eigen::Map<const Eigen::VectorXd, Eigen::Unaligned>(
    belief.data(), (Eigen::Index)belief.size()));
}

bool MultinomialOpinion::updateBelief(const MultinomialOpinion::Vector& belief)
{
  Eigen::Index rows = belief.rows();
  Eigen::Index cols = belief.cols();

  if (cols == 1)
  {
    if (m_dim < 0)
    {
      m_dim          = rows;
      m_belief       = belief;
      m_prior_weight = static_cast<int>(rows); // TODO handle loss of precision for large values
    }
    else if (m_dim == rows)
    {
      m_belief = belief;
    }
    else
    {
      return false;
    }
  }
  else
  {
    // TODO Error, raise exception?
    return false;
  }

  return true;
}

bool MultinomialOpinion::b(const std::initializer_list<double>& belief)
{
  return b(std::vector<double>(belief));
}

bool MultinomialOpinion::b(const std::vector<double>& belief)
{
  return b(Eigen::Map<const Eigen::VectorXd, Eigen::Unaligned>(belief.data(),
                                                               (Eigen::Index)belief.size()));
}

bool MultinomialOpinion::b(const MultinomialOpinion::Vector& belief)
{
  return updateBelief(belief);
}

std::vector<double> MultinomialOpinion::belief() const
{
  return std::vector<double>(m_belief.data(), m_belief.data() + m_belief.size());
}

MultinomialOpinion::Vector MultinomialOpinion::beliefMat() const
{
  return m_belief;
}

std::vector<double> MultinomialOpinion::b() const
{
  return belief();
}

MultinomialOpinion::Vector MultinomialOpinion::bMat() const
{
  return beliefMat();
}

bool MultinomialOpinion::updateUncertainty(const double& uncertainty)
{
  double sum = m_belief.sum();

  if ((sum + uncertainty) == 1)
  {
    m_uncertainty = uncertainty;
  }
  else
  {
    m_uncertainty = 1 - m_belief.sum();
  }

  return true;
}

bool MultinomialOpinion::u(const double& uncertainty)
{
  return updateUncertainty(uncertainty);
}

double MultinomialOpinion::uncertainty() const
{
  return m_uncertainty;
}

double MultinomialOpinion::u() const
{
  return uncertainty();
}

bool MultinomialOpinion::updateBaseRate(const std::initializer_list<double>& base_rate)
{
  return updateBaseRate(std::vector<double>(base_rate));
}

bool MultinomialOpinion::updateBaseRate(const std::vector<double>& base_rate)
{
  return updateBaseRate(Eigen::Map<const Eigen::VectorXd, Eigen::Unaligned>(
    base_rate.data(), (Eigen::Index)base_rate.size()));
}

bool MultinomialOpinion::updateBaseRate(const MultinomialOpinion::Vector& base_rate)
{
  Eigen::Index rows = base_rate.rows();
  Eigen::Index cols = base_rate.cols();

  if (cols == 1)
  {
    if (m_dim < 0)
    {
      m_dim       = rows;
      m_base_rate = base_rate;
    }
    else if (m_dim == rows)
    {
      m_base_rate = base_rate;
    }
    else
    {
      return false;
    }
  }
  else
  {
    // TODO Error, raise exception?
    return false;
  }

  return true;
}

bool MultinomialOpinion::a(const std::initializer_list<double>& base_rate)
{
  return a(std::vector<double>(base_rate));
}

bool MultinomialOpinion::a(const std::vector<double>& base_rate)
{
  return a(Eigen::Map<const Eigen::VectorXd, Eigen::Unaligned>(base_rate.data(),
                                                               (Eigen::Index)base_rate.size()));
}

bool MultinomialOpinion::a(const MultinomialOpinion::Vector& base_rate)
{
  return updateBaseRate(base_rate);
}

std::vector<double> MultinomialOpinion::baseRate() const
{
  return std::vector<double>(m_base_rate.data(), m_base_rate.data() + m_base_rate.size());
}

MultinomialOpinion::Vector MultinomialOpinion::baseRateMat() const
{
  return m_base_rate;
}

std::vector<double> MultinomialOpinion::a() const
{
  return baseRate();
}

MultinomialOpinion::Vector MultinomialOpinion::aMat() const
{
  return baseRateMat();
}

OpinionOwner MultinomialOpinion::owner() const
{
  return m_owner;
}

void MultinomialOpinion::updateOwner(const OpinionOwner& owner)
{
  m_owner = owner;
}

DirichletPDF MultinomialOpinion::dirichletPdf() const
{
  DirichletPDF dp;
  MultinomialOpinion::Vector r;

  if (m_uncertainty != 0)
  {
    r = (m_prior_weight * m_belief) / m_uncertainty;
    // TODO assertion 1 = m_uncertainty + m_belief.sum();
  }
  else
  {
    r = m_belief * std::numeric_limits<double>::infinity();
    // TODO assertion 1 = m_belief.sum();
  }

  dp.updateEvidence(r);
  dp.updateBaseRate(m_base_rate);

  return dp;
}

DirichletPDF MultinomialOpinion::dir() const
{
  return dirichletPdf();
}

void MultinomialOpinion::update(DirichletPDF& pdf)
{
  Eigen::VectorXd evidMat = pdf.evidenceMat();
  double evidence_sum     = evidMat.sum();
  m_base_rate             = pdf.baseRateMat();
  m_prior_weight =
    static_cast<double>(m_base_rate.rows()); // TODO handle loss of precision for large values
  m_belief      = evidMat / (m_prior_weight + evidence_sum);
  m_dim         = m_belief.rows();
  m_uncertainty = m_prior_weight / (m_prior_weight + evidence_sum);
}

std::vector<double> MultinomialOpinion::projection() const
{
  MultinomialOpinion::Vector projMat = projectionMat();
  return std::vector<double>(projMat.data(), projMat.data() + projMat.size());
}

MultinomialOpinion::Vector MultinomialOpinion::projectionMat() const
{
  return m_belief + (m_base_rate * m_uncertainty);
}

std::vector<double> MultinomialOpinion::p() const
{
  return projection();
}

MultinomialOpinion::Vector MultinomialOpinion::pMat() const
{
  return projectionMat();
}

std::vector<double> MultinomialOpinion::variance() const
{
  MultinomialOpinion::Vector varMat = varianceMat();
  return std::vector<double>(varMat.data(), varMat.data() + varMat.size());
}

MultinomialOpinion::Vector MultinomialOpinion::varianceMat() const
{
  MultinomialOpinion::Vector p = projectionMat();
  return (p.array() * (1 - p.array()) * m_uncertainty) / (m_prior_weight * m_uncertainty);
}

std::vector<double> MultinomialOpinion::var() const
{
  return variance();
}

MultinomialOpinion::Vector MultinomialOpinion::varMat() const
{
  return varianceMat();
}

double MultinomialOpinion::uncertaintyMaximum() const
{
  double min_u                 = 1.0;
  MultinomialOpinion::Vector p = projectionMat();

  for (int i = 0; i < Eigen::Dynamic; ++i)
  {
    double u = p(i) / m_base_rate(i);
    if (u < min_u)
    {
      min_u = u;
    }
  }
  return min_u;
}

double MultinomialOpinion::uMax() const
{
  return uncertaintyMaximum();
}

std::ostream& operator<<(std::ostream& os, const MultinomialOpinion& opinion)
{
  os << "(b=(" << opinion.m_belief(0);
  for (int i = 1; i < opinion.m_belief.rows(); ++i)
  {
    os << ", " << opinion.m_belief(i);
  }

  os << "), u=" << opinion.m_uncertainty << ", a=(" << opinion.m_base_rate(0);
  for (int i = 1; i < opinion.m_base_rate.rows(); ++i)
  {
    os << ", " << opinion.m_base_rate(i);
  }

  os << "))";

  return os;
}

Eigen::Index MultinomialOpinion::dim() const
{
  return m_dim;
}


} // namespace subj