# USER-PPA

This is a LAMMPS package for Primitive Path Analysis (PPA).

<img src="https://github.com/t-murash/USER-PPA/blob/master/img/ppa.png" title="M=100, N=100 Kremer-Grest chains during PPA" width=600/>

<img src="https://github.com/t-murash/USER-PPA/blob/master/img/ppa.gif" title="M=100, N=100 Kremer-Grest chains during PPA" width=300/>

<img src="https://github.com/t-murash/USER-PPA/blob/master/img/ppa-ring-line.gif" title="Ring (red) & Linear chains" width=300/>

Authored by:
[Takahiro Murashima](https://github.com/t-murash)<br>
Tohoku University, Japan<br>
Initial commit: Nov 07, 2019<br>
Last updated: Dec 7, 2020<br>
Support provided via [issues](https://github.com/t-murash/USER-PPA/issues) and/or [email](mailto:murasima@cmpt.phys.tohoku.ac.jp).


## Installation

Download and install LAMMPS according to the following site.

* [LAMMPS](https://lammps.sandia.gov/)

```
wget http://lammps.sandia.gov/tars/lammps-stable.tar.gz
tar xvf lammps-stable.tar.gz
cd lammps-*/src/
make yes-molecule
```
(`yes-molecule` is necessary for examples.)

Then, get this package and install.

```
git clone https://github.com/t-murash/USER-PPA.git
cp -r USER-PPA/USER-PPA lammps-*/src/.
cd lammps-*/src/
make yes-user-ppa
```

Finally, compile LAMMPS.

```
cd lammps-*/src/
make mpi
```

## Usage
You can find example files in `USER-PPA/examples`.
```
mpirun ./lmp_mpi -in in.example
```

## Citing the USER-PPA package

Users of this package are encouraged to cite the following articles in scientific publications:

* S. K. Sukumaran, G. S. Grest, K. Kremer, R. Everaers, "Identifying the Primitive Path Mesh in Entangled Polymer Liquids", Journal of Polymer Science: Part B: Polymer Physics, **43**, 917-933 (2005), https://onlinelibrary.wiley.com/doi/full/10.1002/polb.20384.

* K. Hagita, T. Murashima, "Effect of Chain-Penetration on the Shape of Ring in Mixtures of Ring and Linear Polymers" in preparation.