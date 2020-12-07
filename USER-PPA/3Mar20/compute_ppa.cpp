/* ----------------------------------------------------------------------
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
  2019/11/07
  by T. Murashima @ Tohoku Univ.
 */

#include <mpi.h>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "compute_ppa.h"
#include "atom.h"
#include "neighbor.h"
#include "comm.h"
#include "update.h"
#include "modify.h"
#include "domain.h"
#include "memory.h"
#include "error.h"

using namespace LAMMPS_NS;

enum{ONCE,NFREQ,EVERY};

/* ---------------------------------------------------------------------- */

ComputePPA::ComputePPA(LAMMPS *lmp, int narg, char **arg) :
  Compute(lmp, narg, arg),distance(NULL),distance_all(NULL)
{
  if (narg < 3) error->all(FLERR,"Illegal compute ppa command");

  /*
  if (narg == 4){
  }
  else {
    if (narg < 4) error->all(FLERR,"Illegal compute ppa command");
  }
  */

  scalar_flag=vector_flag=1;
  size_vector=4;
  extscalar=0;
  extvector=0;
  vector=new double[size_vector];



  init();
  allocate();
}

/* ---------------------------------------------------------------------- */

ComputePPA::~ComputePPA()
{
  delete [] vector;
  memory->destroy(distance);
  memory->destroy(distance_all);
}

/* ---------------------------------------------------------------------- */

void ComputePPA::init()
{
  int i,nlocal=atom->nlocal;
  tagint *mol=atom->molecule;
  tagint max_mol_id=-1;
  
  for(i=0;i<nlocal;i++){
    tagint mol_id=mol[i];
    if(max_mol_id<mol_id){
      max_mol_id=mol_id;
    }
  }

  MPI_Allreduce(&max_mol_id,&nmol,1,MPI_INTEGER,MPI_MAX,world);

  Z=0.0;
  a=0.0;
  R2=0.0;
  L=0.0;
}

/* ---------------------------------------------------------------------- */

void ComputePPA::compute_vector()
{
  int i,n,i1,i2;
  int nlocal=atom->nlocal;
  int nbondlist=neighbor->nbondlist;
  int **bondlist=neighbor->bondlist;
  tagint mol_id;
  tagint *mol=atom->molecule;
  double **x=atom->x;
  double dx,dy,dz,dr;
  invoked_vector = update->ntimestep;

  for(i=0;i<nmol;i++){
    distance[i][0]=0.0;
    distance[i][1]=0.0;
    distance[i][2]=0.0;
    distance[i][3]=0.0;
    distance_all[i][0]=0.0;
    distance_all[i][1]=0.0;
    distance_all[i][2]=0.0;
    distance_all[i][3]=0.0;
  }

  
  for(n=0;n<nbondlist;n++){
    i1=bondlist[n][0];
    i2=bondlist[n][1];
    mol_id=mol[i1];
    dx=x[i1][0]-x[i2][0];
    dy=x[i1][1]-x[i2][1];
    dz=x[i1][2]-x[i2][2];
    dr=sqrt(dx*dx+dy*dy+dz*dz);
    distance[mol_id-1][0]+=dx;
    distance[mol_id-1][1]+=dy;
    distance[mol_id-1][2]+=dz;
    distance[mol_id-1][3]+=dr;
  }

  MPI_Allreduce(&distance[0][0],&distance_all[0][0],nmol*4,MPI_DOUBLE,MPI_SUM,world);





  R2=0.0;L=0.0;Z=0.0;a=0.0;
  double moli_r2;
  for(i=0;i<nmol;i++){
    moli_r2=distance_all[i][0]*distance_all[i][0]
      +distance_all[i][1]*distance_all[i][1]
      +distance_all[i][2]*distance_all[i][2];
    R2+=moli_r2;
    L+=distance_all[i][3];
  }
  R2/= nmol;
  L /= nmol;
  a = R2/L;
  Z = L/a;
  vector[0]=Z;
  vector[1]=a;
  vector[2]=R2;
  vector[3]=L;
}


/* ---------------------------------------------------------------------- */


void ComputePPA::allocate()
{
  memory->destroy(distance);
  memory->destroy(distance_all);
  memory->create(distance,nmol,4,"PPA:distance");
  memory->create(distance_all,nmol,4,"PPA:distance_all");
}

/* ---------------------------------------------------------------------- */

double ComputePPA::memory_usage()
{
  double bytes = 0.0;
  // distance + distance_all
  bytes += (bigint) 2 * nmol * 4 * sizeof(double);
  return bytes;
}
