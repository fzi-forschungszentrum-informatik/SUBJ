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

#include <subj/HyperOpinion.h>

namespace subj {

HyperOpinion::HyperOpinion() = default;

HyperOpinion::HyperOpinion(const HyperOpinion::RVector& belief,
                           const double& uncertainty,
                           const HyperOpinion::DVector& base_rate)
{
  updateBelief(belief);
  updateUncertainty(uncertainty);
  updateBaseRate(base_rate);
}

void HyperOpinion::update(const HyperOpinion::RVector& belief,
                          const double& uncertainty,
                          const HyperOpinion::DVector& base_rate)
{
  updateBelief(belief);
  updateUncertainty(uncertainty);
  updateBaseRate(base_rate);
}

void HyperOpinion::updateBelief(const HyperOpinion::RVector& belief)
{
  m_belief       = belief;
  m_prior_weight = ((int)std::pow(2, belief.rows())) - 2;
}

HyperOpinion::RVector HyperOpinion::belief() const
{
  return m_belief;
}

void HyperOpinion::updateUncertainty(const double& uncertainty)
{
  m_uncertainty = uncertainty;
}

double HyperOpinion::uncertainty() const
{
  return m_uncertainty;
}

void HyperOpinion::updateBaseRate(const HyperOpinion::DVector& base_rate)
{
  m_base_rate = base_rate;
}

HyperOpinion::DVector HyperOpinion::baseRate() const
{
  return m_base_rate;
}

void HyperOpinion::updateOwner(const OpinionOwner& owner)
{
  m_owner = owner;
}

OpinionOwner HyperOpinion::owner() const
{
  return m_owner;
}


} // namespace subj