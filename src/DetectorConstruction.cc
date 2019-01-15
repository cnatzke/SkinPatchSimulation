//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file runAndEvent/RE03/src/DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
// $Id: DetectorConstruction.cc 101905 2016-12-07 11:34:39Z gunter $
//

#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SDParticleFilter.hh"

#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
DetectorConstruction::DetectorConstruction()
  :G4VUserDetectorConstruction(),
   fAir(0),fWater(0),fWorldPhys(0),fPhantomPhys(0),
   fConstructed(false)
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
DetectorConstruction::~DetectorConstruction()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  if(!fConstructed)
  {
    fConstructed = true;
    DefineMaterials();
    SetupGeometry();
  }
  return fWorldPhys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::DefineMaterials()
{
  //-------- NIST Materials -----------------------------------------------
  //  Material Information imported from NIST database.
  G4NistManager* NISTman = G4NistManager::Instance();
  fWater = NISTman->FindOrBuildMaterial("G4_WATER");
  fAir   = NISTman->FindOrBuildMaterial("G4_AIR");
  fTissue= NISTman->FindOrBuildMaterial("G4_A-150_TISSUE");
  
  // Define required materials

  G4double A;  // atomic mass
  G4double Z;  // atomic number
  G4double d;  // density
 
  // General elements
 
  A = 1.01*g/mole;
  G4Element* elH = new G4Element ("Hydrogen","H",Z = 1.,A);

  A = 12.011*g/mole;
  G4Element* elC = new G4Element("Carbon","C",Z = 6.,A);  

  A = 14.01*g/mole;
  G4Element* elN = new G4Element("Nitrogen","N",Z = 7.,A);

  A = 16.00*g/mole;
  G4Element* elO = new G4Element("Oxygen","O",Z = 8.,A);

  A = 22.99*g/mole;
  G4Element* elNa = new G4Element("Sodium","Na",Z = 11.,A);

  A = 24.305*g/mole;
  G4Element* elMg = new G4Element("Magnesium","Mg",Z = 12.,A);

  A = 30.974*g/mole;
  G4Element* elP = new G4Element("Phosphorus","P",Z = 15.,A);
 
  A = 32.064*g/mole;
  G4Element* elS = new G4Element("Sulfur","S",Z = 16.,A);
 
  A = 35.453*g/mole;
  G4Element* elCl = new G4Element("Chlorine","Cl",Z = 17.,A);
 
  A = 39.098*g/mole;
  G4Element* elK = new G4Element("Potassium","K",Z = 19.,A);

  A = 55.85*g/mole;
  G4Element* elFe  = new G4Element("Iron","Fe",Z = 26.,A);
 
  A = 65.38*g/mole;
  G4Element* elZn = new G4Element("Zinc","Zn",Z = 30.,A);

  A = 85.47 *g/mole;
  G4Element* elRb = new G4Element("Rb","Rb",Z = 37.,A);

  A = 87.62 *g/mole;
  G4Element* elSr = new G4Element("Sr","Sr",Z = 38.,A);

  A = 91.22 *g/mole;
  G4Element* elZr = new G4Element("Zr","Zr",Z = 40.,A);

  A = 207.19 *g/mole;
  G4Element* elPb = new G4Element("Lead","Pb", Z = 82.,A);

  // MIRD soft tissue
  d = 0.9869 *g/cm3;
  fSoftTissue = new G4Material("soft_tissue",d,16);
  fSoftTissue->AddElement(elH,0.1047);
  fSoftTissue->AddElement(elC,0.2302);
  fSoftTissue->AddElement(elN,0.0234);
  fSoftTissue->AddElement(elO,0.6321);
  fSoftTissue->AddElement(elNa,0.0013);
  fSoftTissue->AddElement(elMg,0.00015);
  fSoftTissue->AddElement(elP,0.0024);
  fSoftTissue->AddElement(elS,0.0022);
  fSoftTissue->AddElement(elCl,0.0014);
  fSoftTissue->AddElement(elK,0.0021);
  fSoftTissue->AddElement(elFe,0.000063);
  fSoftTissue->AddElement(elZn,0.000032);
  fSoftTissue->AddElement(elRb,0.0000057);
  fSoftTissue->AddElement(elSr,0.00000034);
  fSoftTissue->AddElement(elZr,0.000008);
  fSoftTissue->AddElement(elPb,0.00000016);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::SetupGeometry()
{
  //
  // World
  //
  G4VSolid* worldSolid = new G4Box("World",2.*cm,2.*cm,2.*cm);
  G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid,fAir,"World");
  worldLogical->SetVisAttributes(G4VisAttributes::Invisible);
  fWorldPhys = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"World",
                        0,false,0);

  //
  // Phantom
  //
  G4VSolid* phantomSolid = new G4Box("Calor",1.5*cm,1.5*cm,1.*cm);
  G4LogicalVolume* phantomLogical = new G4LogicalVolume(phantomSolid, fSoftTissue, "Phantom");
  //G4LogicalVolume* phantomLogical = new G4LogicalVolume(phantomSolid,fWater,"Phantom");
  fPhantomPhys = new G4PVPlacement(0,G4ThreeVector(0., 0., -1.*cm),phantomLogical,"Phantom",
                         worldLogical,false,0);
  //
  // Visualization attributes
  //
  // worldLogical->SetVisAttributes(G4VisAttributes::GetInvisible());
  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);
  phantomLogical->SetVisAttributes(simpleBoxVisAtt);
}

void DetectorConstruction::ConstructSDandField()
{;}

