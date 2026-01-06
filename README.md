# In-Memory Key-Value Store (C)

A Redis-like in-memory key-value store implemented in C, which supports multiple concurrent clients over TCP, using multithreading and mutex-based synchronization.

This project focuses on understanding how real backend systems work internally, rather than building a UI or application.

## 🎯 Goal of the Project

The main goal of this project is to:

- Learn systems programming using C
- Understand client–server architecture
- Handle multiple users at the same time
- Manage shared memory safely
- Build a fast, in-memory data system

## About the project

This project is a server program that stores data in RAM (memory) in the form of:
<pre> key → value </pre>

Users (clients) can:

- Add data (SET)
- Read data (GET)
- Delete data (DEL)

Multiple users can connect simultaneously, and all users see the same shared data.

This is similar in concept to tools like Redis, but implemented from scratch for learning purposes.

## ⚙️ Tech Stack Used

| category | Technology |
|----------|------------|
| Language | C |
| OS | Linux(via WSL/Ubuntu) |
| Networking | TCP sockets(POSIX) |
| Concurrency | POSIX Threads(pthreads) |
| Synchronization | Mutex (pthread_mutex) |
| Data Structure | Hash Table |
| Tools | gcc, make, netcat (nc) |
| Version Control | Git, GitHub |

## 🧩 Features

- In-memory data storage (very fast)
- Hash table with O(1) average lookup
- Multiple clients supported concurrently
- Thread-safe access using mutex
- Simple text-based protocol
- No external libraries or databases

## 📝 Supported Commands

- `SET key value`   → store/update a value
- `GET key`         → retrieve a value
- `DEL key`         → delete a key
- `EXIT`            → disconnect client

## > ⚠️ Important Assumptions (VERY IMPORTANT)

This project is built with the following assumptions:

Single shared datastore
- All clients see the same data
- Last write wins

In-memory only
- Data is stored in RAM
- Data is lost when server stops

Thread-per-client model
- Each client gets its own thread
- Suitable for learning, not massive scale

No authentication
- Anyone who connects can read/write data

Single-server
- No clustering or replication

## How to Run

Requirements
- Windows with WSL (Ubuntu) OR Linux
- gcc and pthread
- netcat (nc)

## Step 1: Open Ubuntu (WSL)
<pre>
sudo apt update
sudo apt install build-essential netcat
</pre>

## Step 2: Go to Project Directory

<pre> cd /mnt/c/Users/<your-username>/OneDrive/Desktop/kv-store </pre>

## Step 3: Compile the Server

<pre> gcc -Wall -Iinclude src/main.c src/datastore.c -o kvstore -pthread </pre>

## Step 4: Run the Server

<pre> ./kvstore </pre>


## Step 5: Connect as Client (New Terminal)

<pre> nc localhost 6379 </pre>
