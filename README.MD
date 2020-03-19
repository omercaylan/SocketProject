TOPDIR-- Makefile
|
|-- Client
|   |-- checkValidNumber.c
|   |-- checkValidNumber.h
|   |-- client.c
|   |-- client.h
|   |-- Makefile_Client
|-- Common
|   |-- common.h
|-- Server
|   `-- Makefile_Server
|   `-- server.c
|   `-- server.h
|   `-- Timeout.c
|   `-- Timeout.h


----->For Running

Client
command: make -f Makefile_Client
./client

Server
command: make -f Makefile_Server
./Server
