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

#ifndef SUBJ_HISTOGRAM_H_INCLUDED
#define SUBJ_HISTOGRAM_H_INCLUDED

#include <Eigen/Dense>

namespace subj {

class Histogram
{
public:
  Histogram();
  // Histogram(size_t interval_count);
  Histogram(size_t interval_count, double min_value, double max_value);
  Histogram(size_t interval_count, const Eigen::Matrix<double, Eigen::Dynamic, 1>& data);
  Histogram(size_t interval_count,
            const Eigen::Matrix<double, Eigen::Dynamic, 1>& data,
            double min_value,
            double max_value);

  void insert(double value);
  void insertIntoBin(size_t bin);
  void insert(const Eigen::Matrix<double, Eigen::Dynamic, 1>& data);

  Eigen::Matrix<size_t, Eigen::Dynamic, 1> histogram() const { return m_hist; };

  Eigen::Matrix<double, Eigen::Dynamic, 2> intervals() const { return m_ivls; };

  Eigen::Matrix<double, Eigen::Dynamic, 1> normalizedHistogram() const;

  size_t dataSize() const { return m_data_count; };

  size_t binIndex(double value) const;

private:
  Eigen::Matrix<size_t, Eigen::Dynamic, 1> m_hist;
  Eigen::Matrix<double, Eigen::Dynamic, 2> m_ivls;
  size_t m_data_count;
};

} // namespace subj
#endif /* SUBJ_HISTOGRAM_H_INCLUDED */