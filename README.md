# README for Skin Patch Simulations
## Introduction 
The purpose of this simulation is to generate a dose heatmap for the development of a <sup>166</sup>Ho skin patch used in skin cancer treatments. It is based on the examples `/basic/rdecay01` and `/extended/REO3` included in GEANT4. 

- Author: Connor Natzke 
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
not in your PATH variable via 

`cmake -DGeant4_DIR=/path/to/geant4 ../`

Make the simulation

`make -j` 

Congrats! You know have a compiled simulation. 

## Usage
The simulation comes with a run macro for generating a dose heatmap from 100,000 decays of <sup>166</sup>Ho uniformly distributed in a 1 cm<sup>2</sup>, 2 um thick patch. The soft tissue block is 3x3x2 (height x width x depth) with the patch placed on the surface of the tissue block. The block is scored in 1 mm<sup>2</sup> increments, for a grid of 30x30x20 pixels.   

The simulation will output a csv text file with the dose (Gy) in each scoring element and when run interactively will display a dose projection when the simulation is finished. To run interactively:

`./rdecay01`

in the build directory. This will open the simulation GUI where commands should be entered. To run the scoring macro simply type 

`/control/execute scoring.mac` 

in the command field in the GUI. Upon finishing, a file titled `dose.txt` will be generated with the dose in each scoring element recorded. 

If you would like to run the simulation without graphics, run the command ```./rdecay01 scoring.mac``` in the build directory. This will generate the dose file without the GUI and projection graphics.

## Macro Commands
*I will update this if I need to or there is interest*

## Errors and Bug Reporting 
Please use the Issues tab in this repository if there are any issues or discussions. I will reply as best I can. 
