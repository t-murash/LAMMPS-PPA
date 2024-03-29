/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

/*
  2022/8/25
  by T. Murashima @ Tohoku Univ.
 */

#ifdef BOND_CLASS

BondStyle(fene/ppa,BondFENEPPA)

#else

#ifndef LMP_BOND_FENE_PPA_H
#define LMP_BOND_FENE_PPA_H

#include "bond.h"

namespace LAMMPS_NS {

class BondFENEPPA : public Bond {
 public:
  BondFENEPPA(class LAMMPS *_lmp) : Bond(_lmp){};
  ~BondFENEPPA()override;
  void compute(int, int)override;
  void coeff(int, char **)override;
  void init_style()override;
  double equilibrium_distance(int)override;
  void write_restart(FILE *)override;
  void read_restart(FILE *)override;
  void write_data(FILE *)override;
  double single(int, double, int, int, double &)override;
  void *extract(const char *, int &) override;

 protected:
  double *k,*r0,*epsilon,*sigma;

  virtual void allocate();
};

}

#endif
#endif

/* ERROR/WARNING messages:

W: FENE bond too long: %ld %d %d %g

A FENE bond has stretched dangerously far.  It's interaction strength
will be truncated to attempt to prevent the bond from blowing up.

E: Bad FENE bond

Two atoms in a FENE bond have become so far apart that the bond cannot
be computed.

E: Incorrect args for bond coefficients

Self-explanatory.  Check the input script or data file.

W: Use special bonds = 0,1,1 with bond style fene

Most FENE models need this setting for the special_bonds command.

W: FENE bond too long: %ld %g

A FENE bond has stretched dangerously far.  It's interaction strength
will be truncated to attempt to prevent the bond from blowing up.

*/
