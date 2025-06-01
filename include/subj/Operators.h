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

#ifndef SUBJ_OPERATORS_H_INCLUDED
#define SUBJ_OPERATORS_H_INCLUDED

#include <subj/subj.h>

#include <Eigen/Dense>
#include <vector>

namespace subj {

double projectedDistance(const MultinomialOpinion& a, const MultinomialOpinion& b);

double pd(const MultinomialOpinion& a, const MultinomialOpinion& b);

double conjunctiveCertainty(const MultinomialOpinion& a, const MultinomialOpinion& b);

double cc(const MultinomialOpinion& a, const MultinomialOpinion& b);

double degreeOfConflict(const MultinomialOpinion& a, const MultinomialOpinion& b);

double doc(const MultinomialOpinion& a, const MultinomialOpinion& b);

MultinomialOpinion averagingBeliefFusion(const std::vector<MultinomialOpinion>& opinions);

MultinomialOpinion abf(const std::vector<MultinomialOpinion>& opinions);

MultinomialOpinion aleatoryCumulativeBeliefFusion(const std::vector<MultinomialOpinion>& opinions);

MultinomialOpinion aleatoryCumulativeBeliefFusion(const MultinomialOpinion& opinion_a,
                                                  const MultinomialOpinion& opinion_b);

MultinomialOpinion cbf(const std::vector<MultinomialOpinion>& opinions);

MultinomialOpinion cbf(const MultinomialOpinion& opinion_a, const MultinomialOpinion& opinion_b);

MultinomialOpinion cumulativeUnfusion(const MultinomialOpinion& fused_opinion,
                                      const MultinomialOpinion& opinion,
                                      const Eigen::VectorXd& base_rate);

MultinomialOpinion trustDiscounting(const MultinomialOpinion& opinion,
                                    const double& discount_probability);

MultinomialOpinion td(const MultinomialOpinion& opinion, const double& discount_probability);

MultinomialOpinion normalMultiplication(const MultinomialOpinion& a, const MultinomialOpinion& b);

} // namespace subj

#endif /* SUBJ_OPERATORS_H_INCLUDED */
