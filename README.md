# R-Type

The Goal of the project is to implement a multi-threaded server and a graphical client for the game called [R-Type](https://en.wikipedia.org/wiki/R-Type), using an engine of our own design. In contrast to the original we will create a network game for one-to-four players.

Made by: Gylian Karsch, Josefine Mende, Marc Pister and Ramon Werner

## Overview

* [Client](overview/client.md)
* [Server](overview/server.md)
* [Game Engine](overview/game-engine.md)
* [Protocol](overview/protocol.md)
* [Libraries](overview/libraries.md)

## Fundamentals

* [Getting started](fundamentals/getting-started.md)
* [Controls](fundamentals/controls.md)

## Technical Documentation

* [Code Guidelines](technical-documentation/code-guidlines.md)
* [Commit Policy](technical-documentation/commit-policy.md)
* [Linter and Formatter](technical-documentation/linter-and-formatter.md)

## Getting started

To build the project you need to have cmake 3.6 or newer installed. Everything else will be installed automatically, if its not already installed.

First open a terminal and move to the "Client" folder. There first generate a makefile by calling following command:

```
cmake .
```

After the makefile is generated execute it.

```
make
```

Once the binary is built you have multiple options to start the game.

The executable needs at least one argument. 0 for server or 1 for client.

```
./r-type_client 0 // starts server
```

```
./r-type_client 1 // starts client
```

The second argument is the IP address of the server. In case only one argument is given the server runs on the localhost.

```
./r-type_client 0 // starts server
```

```
./r-type_client 1 [ip_address_of_server] // starts client
```

The third argument you can give it is the path to a sprite you want to use as a player.

```
./r-type_client 0 // starts server
```

```
./r-type_client 1 [ip_address_of_server] [path_to_sprite] // starts client
```
