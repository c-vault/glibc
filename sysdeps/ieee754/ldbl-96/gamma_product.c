/* Compute a product of X, X+1, ..., with an error estimate.
   Copyright (C) 2013-2025 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <math.h>
#include <math-narrow-eval.h>
#include <math_private.h>
#include <float.h>

/* Compute the product of X + X_EPS, X + X_EPS + 1, ..., X + X_EPS + N
   - 1, in the form R * (1 + *EPS) where the return value R is an
   approximation to the product and *EPS is set to indicate the
   approximate error in the return value.  X is such that all the
   values X + 1, ..., X + N - 1 are exactly representable, and X_EPS /
   X is small enough that factors quadratic in it can be
   neglected.  */

double
__gamma_product (double x, double x_eps, int n, double *eps)
{
  long double x_full = (long double) x + (long double) x_eps;
  long double ret = x_full;
  for (int i = 1; i < n; i++)
    ret *= x_full + i;

  double fret = math_narrow_eval ((double) ret);
  *eps = (ret - fret) / fret;

  return fret;
}
