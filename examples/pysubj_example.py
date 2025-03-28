# -- BEGIN LICENSE BLOCK ----------------------------------------------
#
# Copyright 2025 FZI Forschungszentrum Informatik
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# “Software”), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
# -- END LICENSE BLOCK ------------------------------------------------

# ---------------------------------------------------------------------
# !\file
#
# \author  Stefan Orf <orf@fzi.de>
# \date    2025-01-25
#
#
# ---------------------------------------------------------------------

import pysubj as sj

# You can create binomial and multinomial opinions

# A binomial opinion takes with belief = 0.1, disbelief = 0.5,
# uncertainty = 0.4 and base rate of 0.5 is created with:
print("Creating a binomial opinion bin_op1 with belief = 0.1, disbelief = 0.5, "
      "uncertainty = 0.2 and base rate of 0.3.")
bin_op1 = sj.BinomialOpinion(0.1, 0.5, 0.4, 0.5)
print(f"bin_op1 = {bin_op1}")


# Binomial opinion with belief = 0.8, disbelief = 0.1,
# uncertainty = 0.1 and base rate = 0.5:
print("Creating a binomial opinion bin_op2 with belief = 0.8, disbelief = 0.1, "
      "uncertainty = 0.1 and base rate of 0.3.")
bin_op2 = sj.BinomialOpinion(0.8, 0.1, 0.1, 0.3)
print(f"bin_op2 = {bin_op2}\n")


# Binomial opinions are just 2-dimensional multinomial opinions.
# The BinomialOpinion class provides a few convenience functions,
# but can be used just like MultinomialOpinions.

# Multinomial opinions are created similar.
# Here 4-dimensional multinomial opinions are created:
print("Creating a multinomial opinion mult_op1 with belief = [0.1, 0.1, 0.4, 0.2], "
      "uncertainty = 0.2 and base rate of [0.25, 0.25, 0.25, 0.25].")
mult_op1 = sj.MultinomialOpinion([0.1, 0.1, 0.4, 0.2], 0.2, [0.25, 0.25, 0.25, 0.25])
print(f"mult_op1 = {mult_op1}")

print(
    "Creating a multinomial opinion mult_op2 with belief = [0.3, 0.1, 0.0, 0.0], "
    "uncertainty = 0.4 and base rate of [0.1, 0.5, 0.2, 0.2].")
mult_op2 = sj.MultinomialOpinion([0.3, 0.1, 0.0, 0.0], 0.4, [0.10, 0.50, 0.20, 0.20])
print(f"mult_op2 = {mult_op2}\n")

# Functions for updating of opinions also exist
print("Updating belief of mult_op1 with [0.0, 0.0, 0.4, 0.1].")
mult_op1.updateBelief([0.0, 0.0, 0.4, 0.1])
print("Updating uncertainty of mult_op1 with 0.5.")
mult_op1.updateUncertainty(0.5)
print("Updating base rate of mult_op1 with [0.0, 0.3, 0.7, 0.0].")
mult_op1.updateBaseRate([0.0, 0.3, 0.7, 0.0])


# Belief, uncertainty and base rate of opinions can be retrieved with:
print(f"Belief of mult_op1 is {mult_op1.belief()}")
print(f"Uncertainty of mult_op1 is {mult_op1.uncertainty()}")
print(f"Base rate of mult_op1 is {mult_op1.baseRate()}\n")


# Short-hand aliases for these getter and setter functions
# are available:
print("Updating belief of mult_op1 with [0.05, 0.05, 0.25, 0.15].")
mult_op1.b([0.05, 0.05, 0.25, 0.15])

print(f"Belief of mult_op1 is {mult_op1.b()}")
print(f"Uncertainty of mult_op1 is {mult_op1.u()}")
print(f"Base rate of mult_op1 is {mult_op1.a()}\n")


# The projection of an opinion can be calculated with:
print(f"Projection of bin_op1 = {bin_op1.projection()}")
print(f"Projection of bin_op2 = {bin_op2.p()}")

# The opinion's variance:
print(f"Variance of bin_op1 = {bin_op1.variance()}")
print(f"Variance of bin_op2 = {bin_op2.var()}\n")

# The corresponding dirichlet PDF of an opinion can be retrieved with:
dir1 = mult_op1.dir()
print(f"Dirichlet PDF of mult_op1 = {dir1}")

# And the density at a given point can then be calculated with:
print(
    f"Density of the Dirichlet PDF of mult_op1 at [0.2, 0.3, 0.6, 0.1] = {dir1.density([0.2, 0.3, 0.6, 0.1])}\n")

# Combination of opinions can be done with one of the several operators.
# For example the aleatory cumulative belief fusion of two opinions is
# calculated with:
print("Applying aleatory cumulative belief fusion (CBF) to mult_op1 and mult_op2.")
fuse_op = sj.cbf(mult_op1, mult_op2)
print(f"CBF(mult_op1, mult_op2) = {fuse_op}\n")

# The degree of conflict of two opinions is calculated with:
print(f"Degree of conflict DOC(bin_op1, bin_op2) = {sj.doc(bin_op1, bin_op2)}")
print(f"DOC(mult_op1, mult_op2) = {sj.doc(mult_op1, mult_op2)}\n")

print("There are a lot more operators. See help(pysubj) for reference.")
