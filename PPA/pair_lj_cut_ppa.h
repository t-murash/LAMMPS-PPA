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

#ifdef PAIR_CLASS

PairStyle(lj/cut/ppa,PairLJCutPPA)

#else

#ifndef LMP_PAIR_LJ_CUT_PPA_H
#define LMP_PAIR_LJ_CUT_PPA_H

#include "pair.h"

namespace LAMMPS_NS {

class PairLJCutPPA : public Pair {
 public:
  PairLJCutPPA(class LAMMPS *);
  ~PairLJCutPPA()override;
  void compute(int, int)override;
  void settings(int, char **)override;
  void coeff(int, char **)override;
  void init_style()override;
  double init_one(int, int)override;
  void write_restart(FILE *)override;
  void read_restart(FILE *)override;
  void write_restart_settings(FILE *)override;
  void read_restart_settings(FILE *)override;
  void write_data(FILE *)override;
  void write_data_all(FILE *) override;
  double single(int, int, int, int, double, double, double, double &) override;
  void born_matrix(int, int, int, int, double, double, double, double &, double &) override;
  void *extract(const char *, int &) override;

  void compute_inner() override;
  void compute_middle() override;
  void compute_outer(int, int) override;

 protected:
  double cut_global;
  double **cut;
  double **epsilon,**sigma;
  double **lj1,**lj2,**lj3,**lj4,**offset;
  double *cut_respa;

  virtual void allocate();
};

}

#endif
#endif

/* ERROR/WARNING messages:

E: Illegal ... command

Self-explanatory.  Check the input script syntax and compare to the
documentation for the command.  You can use -echo screen as a
command-line option when running LAMMPS to see the offending line.

E: Incorrect args for pair coefficients

Self-explanatory.  Check the input script or data file.

E: Pair cutoff < Respa interior cutoff

One or more pairwise cutoffs are too short to use with the specified
rRESPA cutoffs.

*/
