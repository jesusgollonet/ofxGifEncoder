//
//  ofxGifDitherTypes.h
//  ofxGifEncoderDev
//
//  Created by jesus gollonet on 4/15/14.
//
//

#pragma once

// done for consistency. feel free to use Freeimage versions
enum ditherTypes {
    OFX_GIF_DITHER_NONE         = -1,
    OFX_GIF_DITHER_FS           = FID_FS,           // Floyd & Steinberg error diffusion
    OFX_GIF_DITHER_BAYER4x4     = FID_BAYER4x4,		// Bayer ordered dispersed dot dithering (order 2 dithering matrix)
    OFX_GIF_DITHER_BAYER8x8     = FID_BAYER8x8, 	// Bayer ordered dispersed dot dithering (order 3 dithering matrix)
    OFX_GIF_DITHER_CLUSTER6x6   = FID_CLUSTER6x6,	// Ordered clustered dot dithering (order 3 - 6x6 matrix)
    OFX_GIF_DITHER_CLUSTER8x8   = FID_CLUSTER8x8,	// Ordered clustered dot dithering (order 4 - 8x8 matrix)
    OFX_GIF_DITHER_CLUSTER16x16 = FID_CLUSTER16x16, // Ordered clustered dot dithering (order 8 - 16x16 matrix)
    OFX_GIF_DITHER_BAYER16x16   = FID_BAYER16x16,	// Bayer ordered dispersed dot dithering (order 4 dithering matrix)
};