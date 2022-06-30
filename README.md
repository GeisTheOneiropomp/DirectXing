DirectXing: A DirectX 12 Demo
====================================================================================================

## Digest

This project implements several computer graphics effects. These include:

  * Basic Lighting and Texturing
  * Cube Mapping (Skybox)
  * Normal Mapping
  * Precomputed Environment Mapping
  * Shadow Mapping
  * Screen Space ambient occlusion
  * Irradiance Environment Mapping (work in progress)

Because this is a DirectX12 demo, it takes advantage of resource aliasing, transitions, and the like.  

## Usage

	- The movement controls are a basic WASD layout (w is up, s is down, a is left, and r is right.)
	- The mouse is used to change angles.
	- Press F1 to toggle shadow mapping on\off.
	- Press F2 to toggle screen space ambient occlusion on\off.

## Image Gallery

### Basic Lighting and Texturing

| ![tex dem][texture]          | ![tex note][textureNote] | 
|:----------------------------:|:---------------------------:|
| Texturing and Lighting.      | (Nearest Neighbor and Anisotropic Filtering)  |

### Normal Mapping

| ![norm dem][normMap]       | ![norm note][normMapNote] | 
|:----------------------------:|:---------------------------:|
| Loaded from File.      | (Provides more detail to the textures.)  |

### Precomputed Environment Mapping:

| ![environ dem][envMap]       | ![environ note][envMapNote] | 
|:----------------------------:|:---------------------------:|
| Mapped from the skybox.      | (Unfortunately, the environment mapping is precomputed using the skybox, so the geometry is not reflected in the spheres.)  |

### Shadow Mapping:

| ![shadowmapping dem][shadow] | ![shadowmapping note][shadowNote]      | 
|:----------------------------:|:---------------------------:|
| In the demo, the shadows are dynamic and move with the light.       | Percentage Closer Filtering is used.  |

### Screen space ambient occlusion comparison:

#### Screen space ambient occlusion turned on:

| ![SSAO dem][SSAO]            | ![SSAO note][SSAONote]      | 
|:----------------------------:|:---------------------------:|

#### Screen space ambient occlusion turned off:

| ![noSSAO dem][noSSAO]        | ![noSSAO note][noSSAONote]  | 
|:----------------------------:|:---------------------------:|

## Credits:

The base project of the code is derived from Frank Luna's book on Graphics.

[SSAO]:          ImageGallery/SSAOWithRefined.png
[SSAONote]:          ImageGallery/SSAOWithNote.png
[noSSAO]:          ImageGallery/SSAOWithoutRefined.png
[noSSAONote]:          ImageGallery/SSAOWithoutNote.png

[shadow]:          ImageGallery/ShadowMappingRefined.png
[shadowNote]:          ImageGallery/ShadowMappingNote.png

[envMap]:          ImageGallery/EnvironmentMappingRefined.png
[envMapNote]:          ImageGallery/EnvironmentMappingNote.png

[normMap]:          ImageGallery/NormalMappingRefined.png
[normMapNote]:          ImageGallery/NormalMappingNote.png

[texture]:          ImageGallery/TexturingRefined.png
[textureNote]:          ImageGallery/TexturingNote.png
