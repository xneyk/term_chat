# TERM_CHAT
Hey there! My name is Edgar and I'm a software engineering student.

That's a small project just for figuring out how sockets work. The main focus is to make a simple terminal chat where two known friends can talk on a temporary chat.

## Instalation
Here I will explain how to install this project and how you can run it :)

## Build and Run!
Firstly, you need to compile everything to get the binary file. You can do that by running the following on the root directory of the project.
```
make
```
At this point, you have the `term_chat` executable. Now, this program has two sides:
### Server
If you want to create the "chat room" you can do it by running
```
./term_chat create <port>
```
Where `<port>` is the number of the port where you want to run the server part.

Now the chat is running, and you can share your IP and port with your friend and ask him to connect to the chat! You will only need to share with him your IP address and the port where you had started the server.

## Client
If a friend (or whoever you want to talk with) had already created the chat, you only need to know which IP address and port it has. Knowing that, you can connect to the chat by running
```
./term_chat connect <IP> <port>
```
