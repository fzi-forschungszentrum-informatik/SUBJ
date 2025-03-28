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

#include <subj/Operators.h>

#include <Eigen/Dense>
#include <limits>
#include <stdexcept>
#include <vector>

namespace subj {

double projectedDistance(const MultinomialOpinion& a, const MultinomialOpinion& b)
{
  return (a.projectionMat() - b.projectionMat()).cwiseAbs().sum() / 2.0;
}

double pd(const MultinomialOpinion& a, const MultinomialOpinion& b)
{
  return projectedDistance(a, b);
}

double conjunctiveCertainty(const MultinomialOpinion& a, const MultinomialOpinion& b)
{
  return (1.0 - a.uncertainty()) * (1.0 - b.uncertainty());
}

double cc(const MultinomialOpinion& a, const MultinomialOpinion& b)
{
  return conjunctiveCertainty(a, b);
}

double degreeOfConflict(const MultinomialOpinion& a, const MultinomialOpinion& b)
{
  return projectedDistance(a, b) * conjunctiveCertainty(a, b);
}

double doc(const MultinomialOpinion& a, const MultinomialOpinion& b)
{
  return degreeOfConflict(a, b);
}

MultinomialOpinion averagingBeliefFusion(const std::vector<MultinomialOpinion>& opinions)
{
  // TODO check preconditions, handle special cases
  if (opinions.size() < 2)
  {
    throw std::invalid_argument("At least 2 opinions must be given!");
  }

  size_t size      = opinions.size();
  Eigen::Index dim = opinions[0].dim();

  for (const MultinomialOpinion& o : opinions)
  {
    if (o.dim() != dim)
    {
      throw std::runtime_error("All opinions must have the same dimensions!");
    }
  }

  Eigen::VectorXd u_t(size);
  double u_a = 1.0;
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> b_mat(dim, size);
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> a_mat(dim, size);

  for (const MultinomialOpinion& o : opinions)
  {
    u_a *= o.u();
  }

  if (!(size <= static_cast<size_t>(std::numeric_limits<Eigen::Index>::max())))
  {
    // TODO consider throwing an exception
    return MultinomialOpinion(2);
  }

  for (Eigen::Index i = 0; i < static_cast<Eigen::Index>(size); ++i)
  {
    u_t[i]       = u_a / opinions[i].u();
    b_mat.col(i) = opinions[i].bMat();
    a_mat.col(i) = opinions[i].aMat();
  }

  MultinomialOpinion op(dim);
  op.b((b_mat.array().rowwise() * u_t.transpose().array()).rowwise().sum() / u_t.sum());
  op.u(static_cast<double>(size) * u_a);
  op.a(((a_mat.array().rowwise() * u_t.transpose().array()).rowwise().sum() -
        (a_mat.array() * u_a).rowwise().sum()) /
       (u_t.sum() - static_cast<double>(size) * u_a));
  return op;
}

MultinomialOpinion abf(const std::vector<MultinomialOpinion>& opinions)
{
  return averagingBeliefFusion(opinions);
}

MultinomialOpinion aleatoryCumulativeBeliefFusion(const std::vector<MultinomialOpinion>& opinions)
{
  // TODO check preconditions, handle special cases
  if (opinions.size() < 2)
  {
    throw std::runtime_error("At least 2 opinions must be given!");
  }

  bool all_vacuous = true;
  for (const MultinomialOpinion& o : opinions)
  {
    if (o.u() != 1.0)
    {
      all_vacuous = false;
      break;
    }
  }
  if (all_vacuous)
  {
    return opinions[0];
  }

  size_t size      = opinions.size();
  Eigen::Index dim = opinions[0].dim();

  for (const MultinomialOpinion& o : opinions)
  {
    if (o.dim() != dim)
    {
      throw std::runtime_error("All opinions must have the same dimensions!");
    }
  }

  Eigen::VectorXd u_t(size);
  double u_a = 1.0;
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> b_mat(dim, size);
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> a_mat(dim, size);

  for (const MultinomialOpinion& o : opinions)
  {
    u_a *= o.u();
  }

  if (!(size <= static_cast<size_t>(std::numeric_limits<Eigen::Index>::max())))
  {
    // TODO consider throwing an exception
    throw std::runtime_error("Too many opinions given!");
  }

  for (Eigen::Index i = 0; i < static_cast<Eigen::Index>(size); ++i)
  {
    u_t[i]       = u_a / opinions[i].u();
    b_mat.col(i) = opinions[i].bMat();
    a_mat.col(i) = opinions[i].aMat();
  }

  MultinomialOpinion op(dim);
  op.b((b_mat.array().rowwise() * u_t.transpose().array()).rowwise().sum() /
       (u_t.sum() - (static_cast<double>(size) - 1) * u_a));
  op.u(u_a / (u_t.sum() - (static_cast<double>(size) - 1) * u_a));
  op.a(((a_mat.array().rowwise() * u_t.transpose().array()).rowwise().sum() -
        (a_mat.array() * u_a).rowwise().sum()) /
       (u_t.sum() - static_cast<double>(size) * u_a));
  return op;
}

MultinomialOpinion aleatoryCumulativeBeliefFusion(const MultinomialOpinion& opinion_a,
                                                  const MultinomialOpinion& opinion_b)
{
  std::vector<MultinomialOpinion> opinions;
  opinions.push_back(opinion_a);
  opinions.push_back(opinion_b);
  return aleatoryCumulativeBeliefFusion(opinions);
}

MultinomialOpinion cbf(const std::vector<MultinomialOpinion>& opinions)
{
  return aleatoryCumulativeBeliefFusion(opinions);
}

MultinomialOpinion cbf(const MultinomialOpinion& opinion_a, const MultinomialOpinion& opinion_b)
{
  return aleatoryCumulativeBeliefFusion(opinion_a, opinion_b);
}

MultinomialOpinion cumulativeUnfusion(const MultinomialOpinion& fused_opinion,
                                      const MultinomialOpinion& opinion,
                                      const Eigen::VectorXd& base_rate)
{
  // TODO handle special cases

  MultinomialOpinion res_op(fused_opinion.dim());
  res_op.b(((fused_opinion.bMat() * opinion.u()) - (opinion.bMat() * fused_opinion.u())) /
           (opinion.u() - fused_opinion.u() + opinion.u() * fused_opinion.u()));
  res_op.u((opinion.u() * fused_opinion.u()) /
           (opinion.u() - fused_opinion.u() + opinion.u() * fused_opinion.u()));
  res_op.a(base_rate);

  return res_op;
}

MultinomialOpinion trustDiscounting(const MultinomialOpinion& opinion,
                                    const double& discount_probability)
{
  MultinomialOpinion op(opinion.dim());
  op.b(opinion.bMat() * discount_probability);
  op.u(1 - discount_probability * opinion.bMat().sum());
  op.a(opinion.aMat());

  return op;
}

MultinomialOpinion td(const MultinomialOpinion& opinion, const double& discount_probability)
{
  return trustDiscounting(opinion, discount_probability);
}

} // namespace subj