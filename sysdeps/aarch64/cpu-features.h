/* Initialize CPU feature data.  AArch64 version.
   This file is part of the GNU C Library.
   Copyright (C) 2017-2025 Free Software Foundation, Inc.
   Copyright The GNU Toolchain Authors.

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

#ifndef _CPU_FEATURES_AARCH64_H
#define _CPU_FEATURES_AARCH64_H

#include <stdint.h>
#include <stdbool.h>

#define MIDR_PARTNUM_SHIFT	4
#define MIDR_PARTNUM_MASK	(0xfff << MIDR_PARTNUM_SHIFT)
#define MIDR_PARTNUM(midr)	\
	(((midr) & MIDR_PARTNUM_MASK) >> MIDR_PARTNUM_SHIFT)
#define MIDR_ARCHITECTURE_SHIFT	16
#define MIDR_ARCHITECTURE_MASK	(0xf << MIDR_ARCHITECTURE_SHIFT)
#define MIDR_ARCHITECTURE(midr)	\
	(((midr) & MIDR_ARCHITECTURE_MASK) >> MIDR_ARCHITECTURE_SHIFT)
#define MIDR_VARIANT_SHIFT	20
#define MIDR_VARIANT_MASK	(0xf << MIDR_VARIANT_SHIFT)
#define MIDR_VARIANT(midr)	\
	(((midr) & MIDR_VARIANT_MASK) >> MIDR_VARIANT_SHIFT)
#define MIDR_IMPLEMENTOR_SHIFT	24
#define MIDR_IMPLEMENTOR_MASK	(0xff << MIDR_IMPLEMENTOR_SHIFT)
#define MIDR_IMPLEMENTOR(midr)	\
	(((midr) & MIDR_IMPLEMENTOR_MASK) >> MIDR_IMPLEMENTOR_SHIFT)

#define IS_EMAG(midr) (MIDR_IMPLEMENTOR(midr) == 'P'			      \
                       && MIDR_PARTNUM(midr) == 0x000)

#define IS_KUNPENG920(midr) (MIDR_IMPLEMENTOR(midr) == 'H'			   \
                        && MIDR_PARTNUM(midr) == 0xd01)

#define IS_A64FX(midr) (MIDR_IMPLEMENTOR(midr) == 'F'			      \
			&& MIDR_PARTNUM(midr) == 0x001)

#define IS_ORYON1(midr) (MIDR_IMPLEMENTOR(midr) == 'Q'			\
		         && (MIDR_PARTNUM(midr) == 0x001		\
			     || (MIDR_PARTNUM(midr) == 0x002		\
			         && MIDR_VARIANT(midr) == 0)))

struct cpu_features
{
  uint64_t midr_el1;
  unsigned zva_size;
  bool bti;
  /* Currently, the GLIBC memory tagging tunable only defines 8 bits.  */
  uint8_t mte_state;
  bool sve;
  bool prefer_sve_ifuncs;
  bool mops;
};

#endif /* _CPU_FEATURES_AARCH64_H  */
