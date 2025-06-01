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

#include "subj/Histogram.h"

namespace subj {

Histogram::Histogram() {}

// Histogram::Histogram(size_t interval_count)
//   : m_hist(Eigen::Matrix<size_t, Eigen::Dynamic, 1>(interval_count))
//   , m_ivls(Eigen::Matrix<double, Eigen::Dynamic, 2>(interval_count, 2))
//   , m_data_count(0)
// {
//   m_hist = Eigen::Matrix<size_t, Eigen::Dynamic, 1>::Constant(interval_count, 1, 0);
// }

Histogram::Histogram(size_t interval_count, double min_value, double max_value)
  : m_hist(Eigen::Matrix<size_t, Eigen::Dynamic, 1>(interval_count))
  , m_ivls(Eigen::Matrix<double, Eigen::Dynamic, 2>(interval_count, 2))
  , m_data_count(0)
{
  m_hist = Eigen::Matrix<size_t, Eigen::Dynamic, 1>::Constant(interval_count, 1, 0);
  for (size_t i = 0; i < interval_count; ++i)
  {
    m_ivls(i, 0) = min_value + ((max_value - min_value) / interval_count) * i;
    m_ivls(i, 1) = min_value + ((max_value - min_value) / interval_count) * (i + 1);
  }
}

Histogram::Histogram(size_t interval_count, const Eigen::Matrix<double, Eigen::Dynamic, 1>& data)
  : Histogram(interval_count, data.minCoeff(), data.maxCoeff())
{
  insert(data);
}

Histogram::Histogram(size_t interval_count,
                     const Eigen::Matrix<double, Eigen::Dynamic, 1>& data,
                     double min_value,
                     double max_value)
  : Histogram(interval_count, min_value, max_value)
{
  insert(data);
}

void Histogram::insert(double value)
{
  m_hist[binIndex(value)]++;
  m_data_count++;
}

void Histogram::insertIntoBin(size_t bin)
{
  m_hist[bin]++;
  m_data_count++;
}

void Histogram::insert(const Eigen::Matrix<double, Eigen::Dynamic, 1>& data)
{
  for (int i = 0; i < data.rows(); ++i)
  {
    insert(data[i]);
  }
}

Eigen::Matrix<double, Eigen::Dynamic, 1> Histogram::normalizedHistogram() const
{
  if (m_data_count > 0)
  {
    return m_hist.cast<double>() / m_data_count;
  }
  else
  {
    return Eigen::Matrix<double, Eigen::Dynamic, 1>::Constant(m_hist.rows(), 1, 0);
  }
}

size_t Histogram::binIndex(double value) const
{
  size_t index = 0;
  if (value < m_ivls(0, 1))
  {
    index = 0;
  }
  else
  {
    for (Eigen::Index i = 1; i < m_ivls.rows() - 1; ++i)
    {
      if (value >= m_ivls(i, 0) && value < m_ivls(i, 1))
      {
        index = i;
        break;
      }
    }
    if (value > m_ivls(m_ivls.rows() - 1, 0))
    {
      index = m_ivls.rows() - 1;
    }
  }
  return index;
}

} // namespace subj