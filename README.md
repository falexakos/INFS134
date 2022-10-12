# INFS134
Implementation of the Discrete Cosine Transformation for a number of raw video frames.<hr>
Syntax: ./extractf [Width] [Height] [-nNumber] filename<br>
Output is the average of each MacroBlock energy values. (Please refer to the H.264 algorithm for details).<br>
Syntax is: <i>extractf [Width] [Height] [-nNumber] filename</i><br>
Where '<i>Number</i>' is the number of frames we wish to perform DCT upon. <i>Filename</i> is a raw (YUV) video file with a resolution of W x H pixels<br>
