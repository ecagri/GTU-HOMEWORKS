To compile: 
	$make in server dir.
	$make in client dir.
To run:
	$./biboServer dirname #ofClients in server dir.
	$./biboServer connect/tryConnect PID in client dir.

To clean:
	$make clean in server dir.
	$make clean in client dir.

!!!NOTES!!!
	There is no input error checking in this project, so please try to adhere to the midterm PDF as closely as possible when providing the input.
	client.c and server.c is put in different files to show that client can communicate with server.
