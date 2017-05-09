Readme
-------------
First, using Makefile by type: make

Client part:
To test Client.c on normal website:
cmd line: ./client http://www.csc.uvic.ca/index.htm

To Server.c 200 ok
Create a folder named : web
 and creat a txt file named: haha.txt 

cmd line on server side: ./server 8070 web/
cmd line on client side: ./client 10.10.1.100:8070/haha.txt

It will shows the message in haha.txt file.


To test 404
cmd line on server side: ./server 8071 web/
cmd line on client side: ./client 10.10.1.100:8070/hha.txt

To test 501
Modify client.c and find "GET " Then change the line HTTP/1.0 to something else ex:HTTP/1.5
and use Makefile again.

cmd line on server side: ./server 8072 web/
cmd line on client side: ./client 10.10.1.100:8072/haha.txt
