/* Common definition for memset/memset_chk ifunc selections.
   All versions must be listed in ifunc-impl-list.c.
   Copyright (C) 2017-2025 Free Software Foundation, Inc.
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

#include <init-arch.h>

extern __typeof (REDIRECT_NAME) OPTIMIZE (erms) attribute_hidden;

extern __typeof (REDIRECT_NAME) OPTIMIZE (avx512_unaligned)
  attribute_hidden;
extern __typeof (REDIRECT_NAME) OPTIMIZE (avx512_unaligned_erms)
  attribute_hidden;
extern __typeof (REDIRECT_NAME) OPTIMIZE (avx512_no_vzeroupper)
  attribute_hidden;

extern __typeof (REDIRECT_NAME) OPTIMIZE (evex_unaligned)
  attribute_hidden;
extern __typeof (REDIRECT_NAME) OPTIMIZE (evex_unaligned_erms)
  attribute_hidden;

extern __typeof (REDIRECT_NAME) OPTIMIZE (avx2_unaligned) attribute_hidden;
extern __typeof (REDIRECT_NAME) OPTIMIZE (avx2_unaligned_erms)
  attribute_hidden;
extern __typeof (REDIRECT_NAME) OPTIMIZE (avx2_unaligned_rtm)
  attribute_hidden;
extern __typeof (REDIRECT_NAME) OPTIMIZE (avx2_unaligned_erms_rtm)
  attribute_hidden;

extern __typeof (REDIRECT_NAME) OPTIMIZE (sse2_unaligned)
  attribute_hidden;
extern __typeof (REDIRECT_NAME) OPTIMIZE (sse2_unaligned_erms)
  attribute_hidden;

static inline int
prefer_erms_nt_impl (const struct cpu_features *cpu_features)
{
  return CPU_FEATURE_USABLE_P (cpu_features, ERMS)
	 || !CPU_FEATURES_ARCH_P (cpu_features, Avoid_Non_Temporal_Memset);
}

static inline void *
IFUNC_SELECTOR (void)
{
  const struct cpu_features *cpu_features = __get_cpu_features ();

  if (CPU_FEATURES_ARCH_P (cpu_features, Prefer_ERMS))
    return OPTIMIZE (erms);

  if (X86_ISA_CPU_FEATURE_USABLE_P (cpu_features, AVX512F)
      && !CPU_FEATURES_ARCH_P (cpu_features, Prefer_No_AVX512))
    {
      if (X86_ISA_CPU_FEATURE_USABLE_P (cpu_features, AVX512VL)
	  && X86_ISA_CPU_FEATURE_USABLE_P (cpu_features, AVX512BW)
	  && X86_ISA_CPU_FEATURE_USABLE_P (cpu_features, BMI2))
	{
	  if (prefer_erms_nt_impl (cpu_features))
	    return OPTIMIZE (avx512_unaligned_erms);

	  return OPTIMIZE (avx512_unaligned);
	}

      return OPTIMIZE (avx512_no_vzeroupper);
    }

  if (X86_ISA_CPU_FEATURE_USABLE_P (cpu_features, AVX2))
    {
      if (X86_ISA_CPU_FEATURE_USABLE_P (cpu_features, AVX512VL)
	  && X86_ISA_CPU_FEATURE_USABLE_P (cpu_features, AVX512BW)
	  && X86_ISA_CPU_FEATURE_USABLE_P (cpu_features, BMI2))
	{
	  if (prefer_erms_nt_impl (cpu_features))
	    return OPTIMIZE (evex_unaligned_erms);

	  return OPTIMIZE (evex_unaligned);
	}

      if (CPU_FEATURE_USABLE_P (cpu_features, RTM))
	{
	  if (prefer_erms_nt_impl (cpu_features))
	    return OPTIMIZE (avx2_unaligned_erms_rtm);

	  return OPTIMIZE (avx2_unaligned_rtm);
	}

      if (X86_ISA_CPU_FEATURES_ARCH_P (cpu_features,
				       Prefer_No_VZEROUPPER, !))
	{
	  if (prefer_erms_nt_impl (cpu_features))
	    return OPTIMIZE (avx2_unaligned_erms);

	  return OPTIMIZE (avx2_unaligned);
	}
    }

  if (CPU_FEATURE_USABLE_P (cpu_features, ERMS)
      || !CPU_FEATURES_ARCH_P (cpu_features, Avoid_Non_Temporal_Memset))
    return OPTIMIZE (sse2_unaligned_erms);

  return OPTIMIZE (sse2_unaligned);
}
