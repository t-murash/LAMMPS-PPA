from ovito.data import *
import numpy as np

def get_wrapped_pos(upos,e0,e1,e2,N0,N1,N2,wpos):
    wpos[2] = upos[2] % e2[2]
    N2 = upos[2] / e2[2]
    uc=np.zeros(3)
    for i in range(3):
        uc[i]=upos[i]-N2*e2[i]

    wpos[1] = uc[1] % e1[1]
    N1 = uc[1] / e1[1]
    ucb=np.zeros(3)
    for i in range(3):
        ucb[i]=uc[i]-N1*e1[i]

    wpos[0] = ucb[0] % e0[0]
    N0 = ucb[0] / e0[0]


def modify(frame, data, odata):
    
    cell=data.cell
    ocell=odata.cell_

    pos=data.particles['Position']
    pbc=data.particles['Periodic Image']
    upos=odata.particles_['Position_']
    mol=odata.particles['Molecule Identifier']
    M=max(mol[:])
    NM=mol.size
    print(M,NM)

    mol_center=np.zeros((M,3))
    mol_size=np.zeros(M)
    mol_center_wrapped=np.zeros((M,3))

    for i in range(NM):
        for k in range(3):
            upos[i,k]=pos[i,k]+cell[k,0]*pbc[i,0]+cell[k,1]*pbc[i,1]+cell[k,2]*pbc[i,2]-cell[k,3]

    for k in range(3):
        ocell[k,3]=ocell[k,3]-cell[k,3]

    for i in range(NM):
        imol=mol[i]-1
        mol_size[imol] += 1.0
        for k in range(3):
            mol_center[imol,k] += upos[i,k]

    e0=cell[:,0]
    e1=cell[:,1]
    e2=cell[:,2]
    N0=0
    N1=0
    N2=0
    for i in range(M):
        for k in range(3):
            mol_center[i,k] /= mol_size[i]

        get_wrapped_pos(mol_center[i],e0,e1,e2,N0,N1,N2,mol_center_wrapped[i])

    for i in range(NM):
        imol=mol[i]-1
        for k in range(3):
            upos[i,k]=upos[i,k]-mol_center[imol,k]+mol_center_wrapped[imol,k]

    if data.particles != None:
        print("There are %i particles with the following properties:" % data.particles.count)
        for property_name in data.particles.keys():
            print("  '%s'" % property_name)
