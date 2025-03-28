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

#include <subj/BinomialOpinion.h>

#include <stdexcept>

namespace subj {

BinomialOpinion::BinomialOpinion()
  : BinomialOpinion(0.0, 0.0, 1.0, 0.5)
{
}

BinomialOpinion::BinomialOpinion(double belief,
                                 double disbelief,
                                 double uncertainty,
                                 double base_rate)
  : MultinomialOpinion(2)
{
  m_belief    = Vector(2);
  m_base_rate = Vector(2);

  updateBelief(belief);
  updateDisbelief(disbelief);
  MultinomialOpinion::updateUncertainty(uncertainty);
  updateBaseRate(base_rate);
}

bool BinomialOpinion::update(double belief, double disbelief, double uncertainty, double base_rate)
{
  bool b = updateBelief(belief);
  bool d = updateDisbelief(disbelief);
  bool u = updateUncertainty(uncertainty);
  bool a = updateBaseRate(base_rate);

  return (b || d || u || a);
}

bool BinomialOpinion::updateBelief(double belief)
{
  MultinomialOpinion::m_belief(0) = belief;

  return true;
}

bool BinomialOpinion::b(double belief)
{
  return updateBelief(belief);
}

bool BinomialOpinion::updateDisbelief(double disbelief)
{
  MultinomialOpinion::m_belief(1) = disbelief;

  return true;
}

bool BinomialOpinion::d(double disbelief)
{
  return updateDisbelief(disbelief);
}

bool BinomialOpinion::updateBaseRate(double base_rate)
{
  Vector br_vec(2);
  br_vec << base_rate, 1.0 - base_rate;
  MultinomialOpinion::updateBaseRate(br_vec);

  return true;
}

bool BinomialOpinion::a(double base_rate)
{
  return updateBaseRate(base_rate);
}

double BinomialOpinion::belief() const
{
  return MultinomialOpinion::beliefMat()(0);
}

double BinomialOpinion::b() const
{
  return belief();
}

double BinomialOpinion::disbelief() const
{
  return MultinomialOpinion::beliefMat()(1);
}

double BinomialOpinion::d() const
{
  return disbelief();
}

double BinomialOpinion::baseRate() const
{
  return MultinomialOpinion::baseRateMat()(0);
}

double BinomialOpinion::a() const
{
  return baseRate();
}

double BinomialOpinion::projection() const
{
  return MultinomialOpinion::projectionMat()(0);
}

double BinomialOpinion::p() const
{
  return projection();
}

double BinomialOpinion::variance() const
{
  return MultinomialOpinion::varianceMat()(0);
}

double BinomialOpinion::var() const
{
  return variance();
}

std::ostream& operator<<(std::ostream& os, const BinomialOpinion& opinion)
{
  os << "(b=" << opinion.belief() << ", d=" << opinion.disbelief()
     << ", u=" << opinion.uncertainty() << ", a=" << opinion.baseRate() << ")";
  return os;
}


} // namespace subj