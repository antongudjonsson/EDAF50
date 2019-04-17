#C++ Project - EDAF50 2019
In this project a sustem for distributing news has been developed.

##Installation
Navigate to the /src/ directory and execute the following:
```
make all
make install
```

To run the program, navigate to the /bin/ directory
```
cd ../bin
```
To run the server with a persistent database use the command
```
./newsserver PORT
```

To run the server using only main memory use the command
```
./newsserverMem PORT
```
where PORT is the number of the port you wish to use.

To run the client, use the command:
```
./newsclient HOSTNAME PORT
```
where HOSTNAME is the IP-address where the server is hosted (localhost if it's the same computer) and PORT is the number of the port you wish to use.

EXAMPLE:
```
make all
make install
cd ../bin
./newsserver 3000
./newsclient localhost 3000
```
