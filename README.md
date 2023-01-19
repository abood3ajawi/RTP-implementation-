# RTP-implementation
<h2>Real-time Transport Protocol (RTP) is a network protocol for delivering audio and video over IP networks .</br>
The server packetize the video data into RTP packets ,  create
an RTP packet, set the fields in the RTP header and copy the payload into the packet and client  able
to handle the received RTP packets then display data . 
 </h2>
 <h3>running code : </h3>
<ol>
<h4>server :</h4> 
<ol>
<li>g++ -g udpserver.cpp -o udpserver</li>
<li>./udpserver</li>
</ol>
<h4>client :</h4>
<ol>
<li>g++ -g  udpclient.cpp -o udpclient -O2 -L/usr/X11R6/lib -lm -lpthread -lX11</li>
<li>./udpclient</<li>
</ol>

 <h3>note :</h3>
 <ul>
 <li>you should run code in this directory that contains testvid and vid directory and there content images</li>
  <li>you should run this two code in 2 terminal</li>
</ul>
</ol>
