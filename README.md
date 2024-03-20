![command line program](https://github.com/Urpagin/McConnectBot/assets/72459611/f0b54f49-50ca-461e-985a-deff9ba00b7c)
![five bots saying the same thing at the same time](https://github.com/Urpagin/McConnectBot/assets/72459611/c9dbb529-a0b7-43b0-838b-5b9c36739de6)

## Purpose
Made to connect *n* number of bots to a Mincraft server, in offline mode though.
Then those bots all have the possibility to send simultaneously a command.

## Disclaimer
This is, for now, a quick project done swiftly to get to learn C++.
So this is no good-looking repo.

## Requirements
### Building
- Git
- CMake & Make
- g++
### Dependencies
- Boost
- OpenSSL
### Ubuntu cheat command
Command to install all required packages on Debian-based Linux distributions.
```bash
sudo apt-get install libssl-dev g++ git openssl cmake libboost-all-dev -y
```
### Cheat cheat all
```bash
sudo apt-get install libssl-dev g++ git openssl cmake libboost-all-dev -y && git clone --recurse-submodules https://github.com/Urpagin/McConnectBot.git && cd McConnectBot && mkdir build && cd build && cmake .. && make -j$(nproc) && echo 'Now execute with ./bin/McConnectBot'
```

## How to install

```bash
git clone --recurse-submodules https://github.com/Urpagin/McConnectBot.git
```

```bash
cd McConnectBot && mkdir build && cd build
```

```bash
cmake ..
```
Good luck if you only have a few cores. Grab a drink
```bash
make -j$(nproc)
```
Congratulations! (hopefully nothing explodes or bugs out)
```bash
./bin/McConnectBot
```
