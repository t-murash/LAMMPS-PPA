# PPA

This is a LAMMPS package for Primitive Path Analysis (PPA).

<p align="center">
<img src="https://github.com/t-murash/LAMMPS-PPA/blob/master/img/ppa.png" title="M=100, N=100 Kremer-Grest chains during PPA" width=600/>
</p>

<p align="center">
<img src="https://github.com/t-murash/LAMMPS-PPA/blob/master/img/ppa.gif" title="M=100, N=100 Kremer-Grest chains during PPA" width=300/>
</p>
<p align="center">
M=100, N=100 Kremer-Grest chains during PPA
</p>

<p align="center">
<img src="https://github.com/t-murash/LAMMPS-PPA/blob/master/img/ppa-ring-line.gif" title="Ring (red) & Linear chains" width=300/>
</p>
<p align="center">
Ring (red) & Linear chains (pastel color)
</p>



Authored by:
[Takahiro Murashima](https://github.com/t-murash)<br>
Tohoku University, Japan<br>
Initial commit: Nov 07, 2019<br>
Last updated: Aug 25, 2022<br>
Support provided via [issues](https://github.com/t-murash/LAMMPS-PPA/issues) and/or [email](mailto:murasima@cmpt.phys.tohoku.ac.jp).


## Installation

Download and install LAMMPS according to the following site.

* [LAMMPS](https://lammps.org/)

## Build LAMMPS with cmake
```
wget https://download.lammps.org/tars/lammps-stable.tar.gz
tar xvf lammps-stable.tar.gz
git clone https://github.com/t-murash/LAMMPS-PPA.git
cp -r LAMMPS-PPA/PPA lammps-*/src/.
```
Edit the following files to include `PPA`
```
lammps-*/cmake/CMakeLists.txt
lammps-*/cmake/presets/all_off.cmake
lammps-*/cmake/presets/all_on.cmake
```
The easiest way is, find `POEM` in the above files and place `PPA` below `POEM`.

Then, build using `cmake` with `-DPKG_PPA=yes`

```
cd lammps-*
mkdir build
cd build
cmake ../cmake -DBUILD_MPI=yes -DPKG_MOLECULE=yes -DPKG_PPA=yes
make
```

## Build LAMMPS with make
```
wget http://download.lammps.org/tars/lammps-stable.tar.gz
tar xvf lammps-stable.tar.gz
cd lammps-*/src/
make yes-molecule
```
(`yes-molecule` is necessary for examples.)

Then, get this package and install.

```
git clone https://github.com/t-murash/LAMMPS-PPA.git
cp -r LAMMPS-PPA/PPA lammps-*/src/.
cd lammps-*/src/
make yes-ppa
```

Finally, compile LAMMPS.

```
cd lammps-*/src/
make mpi
```

## For old version users (29Sep2021, 29Oct20, 3Mar20)
You can find `2021-Sep-29`, `2020-Oct-29`, and `2020-Mar-3` directories in `LAMMPS-PPA/PPA/old`. `2021-Sep-29` contains source files compatible with `29Sep2021` of LAMMPS. `2020-Oct-29` and `2020-Mar-3` are compatible with `29Oct20` and `3Mar20`, respectively. Copy the source files to the `lammps-*/src/PPA` directory according to your versions. Then, make or cmake in the same way as described above.

**(Note)** These old versions are not up-to-date.


## Usage
You can find example files in `LAMMPS-PPA/examples`.
```
mpirun ./lmp_mpi -in in.example
```

## Citing the PPA package

Users of this package are encouraged to cite the following articles in scientific publications:

* S. K. Sukumaran, G. S. Grest, K. Kremer, R. Everaers, "Identifying the Primitive Path Mesh in Entangled Polymer Liquids", Journal of Polymer Science: Part B: Polymer Physics, **43**, 917-933 (2005), https://doi.org/10.1002/polb.20384.

* K. Hagita, T. Murashima, "Effect of Chain-Penetration on Ring Shape for Mixtures of Rings and Linear Polymers", Polymer, **218**, 123493 (2021), https://doi.org/10.1016/j.polymer.2021.123493.
