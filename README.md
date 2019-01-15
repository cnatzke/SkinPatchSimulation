# README for Skin Patch Simulations
## Introduction 
The purpose of this simulation is to generate a dose heatmap for the development of a <sup>166</sup>Ho skin patch used in skin cancer treatments. It is based on the examples `/basic/rdecay01` and `/extended/REO3` included in GEANT4. 

- Author: Connor Natzke cnatzke@mines.edu
- Date: Jan. 2019
- Geant4 Version: geant4.10.04p2

## Installation
Clone the simulation from github via 
`git clone https://github.com/cnatzke/SkinPatchSimulation.git`


Change directories into the new simulation directory
`cd SkinPatchSimulation`


Create a build directory and change into it
`mkdir myBuild && cd myBuild`


Configure simulation build files
`cmake ../`
**NOTE** You will have to specify the location of your GEANT4 install if it is
not in your path via `cmake -DGeant4_DIR=/path/to/geant4`
