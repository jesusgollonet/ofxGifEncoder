# ofxGifEncoder

Export animated gifs from openframeworks. 

___

## USAGE:

There is a simple example included

create an instance of ofxGifEncoder

	ofxGifEncoder gifEncoder;
		
call setup 
	
	gifEncoder.setup(frameW, frameH, nColors, frameDuration);

optionally  :) (see dithering patterns on the h file)
		
	gifEncoder.setDitherMode(OFX_GIF_DITHER_BAYER4x4);
    
then add frames, either as ofImages or unsigned char * 
	
	gifEncoder.addFrame(foo.getPixels(), frameW, frameH);
	
when you're ready to save
	
	gifEncoder.save("test.gif");
	
the saving is now threaded, so it won't block your app. If you want to do something when saving is finished, you can subscribe to the event OFX_GIF_SAVE_FINISHED
	
	ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &testApp::onGifSaved);
	...
	onGifSaved(string & fileName)
	
## THANKS!	
	
threaded saving, events, error checking and frame managing adapted from [Nick Hardeman](https://github.com/NickHardeman/ofxGifEncoder/tree/threaded  "Nick Hardeman"). 
	

## TODO:

	- Transaparent gifs!
	- Provide option to choose palette?
	
	



