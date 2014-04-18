# ofxGifEncoder

Export animated gifs from openframeworks. 

![Shameless plug](http://ofxgif.jesusgollonet.com/img/plug1.gif)

Tested with [openframeworks](http://openframeworks.cc/) 0.8.1 osx. 

___

## USAGE:

There is a simple example included

create an instance of ofxGifEncoder

	ofxGifEncoder gifEncoder;
		
call setup 
	
	gifEncoder.setup(frameW, frameH, frameDuration, nColors);
	
(frameDuration is a float in seconds and nColors is an int from 0 to 256.)

optionally  :) (see dithering patterns on the h file)
		
	gifEncoder.setDitherMode(OFX_GIF_DITHER_BAYER4x4);
    
then add frames, either as ofImages or unsigned char * 
	
	gifEncoder.addFrame(foo.getPixels(), frameW, frameH);
	
when you're ready to save
	
	gifEncoder.save("test.gif");
	
If you want to do something when saving is finished, you can subscribe to the event OFX_GIF_SAVE_FINISHED *
	
	ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &testApp::onGifSaved);
	...
	onGifSaved(string & fileName)
	
## THANKS!	
	
threaded saving, events, error checking and frame managing adapted from [Nick Hardeman](https://github.com/NickHardeman/ofxGifEncoder/tree/threaded  "Nick Hardeman"). 
	

## TODO:

	x Transaparent gifs (currently testing)
	- Provide option to choose palette
	- proper frame compression
	
## NOTES:

one thing that it's not quite there yet is appropiate gif compression, so if your images are big or you have many frames you may end up with unnecesarily fat gifs. 

If you use it, I'd love to see what for. Let me know at {myname}@{nameandsurname}.com !
	
![Shameless plug](http://ofxgif.jesusgollonet.com/img/plug2.gif)