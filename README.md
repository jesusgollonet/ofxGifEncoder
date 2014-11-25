# ofxGifEncoder

Export animated gifs from openframeworks. 

![Shameless plug](http://ofxgif.jesusgollonet.com/img/plug1.gif)

Tested with [openframeworks](http://openframeworks.cc/) 0.8.1 osx. 

___

## USAGE:

There is a simple example included

create an instance of ofxGifEncoder

```C++
ofxGifEncoder gifEncoder;
```

call setup 

```C++
gifEncoder.setup(frameW, frameH, frameDuration, nColors);
```

(`frameDuration` is a float in seconds and `nColors` is an int from 0 to 256.)

optionally  :) (see dithering patterns on the h file)

```C++
gifEncoder.setDitherMode(OFX_GIF_DITHER_BAYER4x4);
```

then add frames, either as ofImages or unsigned char * 

```C++
gifEncoder.addFrame(foo.getPixels(), frameW, frameH);
```

when you're ready to save

```C++
gifEncoder.save("test.gif");
```

If you want to do something when saving is finished, you can subscribe to the event OFX_GIF_SAVE_FINISHED *

```C++
ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &testApp::onGifSaved);
...
onGifSaved(string & fileName)
```
## THANKS!	
	
threaded saving, events, error checking and frame managing adapted from [Nick Hardeman](https://github.com/NickHardeman/ofxGifEncoder/tree/threaded  "Nick Hardeman"). 
	

## TODO:

- (x) Transaparent gifs (currently testing)
- Provide option to choose palette
- proper frame compression

## NOTES:

### Transparency:

Experimental transparency support has been added. However, I haven't found a nice way to gracefully convert from a 32bit alpha image to an 8bit alpha image with Freeimage (openframeworks image library). 

The process I'm following is sort of a green screen (check `ofxGifEncoder::convertTo24BitsWithGreenScreen`):

- substitute the values in the alpha channel of the 32bit transparent image by a predefined color (`ofColor(0,255,0)` -> bright green)
- convert to 24bit 
- convert to 8 bit using FreeImage_ColorQuantize, which takes care of palettizing the image (and therefore choosing the final colors)
- find in the palette the color closest to our predefined color, and set that as transparent.

At the moment there are 2 flaws with transparency:

- If there is a color in your image which it's closest to the palettized green screen color, that one will be picked for alpha. You'll probably see big green areas in your exported gif.
- Images with alpha gradients will have green added on the semi transparent parts.

I'm thinking of fixes for both. 

### Gif size

one thing that it's not quite there yet is appropiate gif compression, so if your images are big or you have many frames you may end up with unnecesarily fat gifs. 

If you use it, I'd love to see what for. Let me know: me@jesusgollonet.com
	
![Shameless plug](http://ofxgif.jesusgollonet.com/img/plug2.gif)

### LICENSE

This addon is distributed under the [MIT License](https://en.wikipedia.org/wiki/MIT_License) which means you can use it in any context: commercial or non-commercial, public or private, open or closed source.
