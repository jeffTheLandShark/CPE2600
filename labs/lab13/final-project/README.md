# CPE 2600 Lab 13 - Chat Room Project
By: Alex Roe-Gulke & Leigh Goetsch

## Overview
This project consists of the server progam and client programs to create a chatroom. If the chatroom server is already open, a client can be opened with either a username as an assitional arguement or as a guest. Through unix sockets, the clients can send messages to the server, which will send it back to all the other open clients along with the username associated.

## How to Use
compile: make
executables: chat_server chat_client

The chat_server program must be open first, or the clients will just fail to connect. After the server is opened, in a different terminal a client can be opened, where a username can be choosen.
Ex: ./chat_client Alex
If there is no additional arguement, the username will default to "Guest". The server will then display that a user has joined that chat. The amount of terminals with the client program open determines the amount of users in the chatroom. Then typing messages into a client program will send it to the others!

