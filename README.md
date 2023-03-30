# 2023-group-11


# Autonomous Obstacle Avoidance Steering :racing_car:
Do you have a small scale vehichle that you which had a simple obstacle avoidence system? Do you have bunch of sensors lying around and space on your raspberry pi? 

These are exactly the problems this project solves! The goal of this project is to create a data-driven algorithm that will take in data from multiple sources and sensors to output a steering value to avoid obstacles. The project is made to run in a docker which can be used by devices such as a raspberry pi. 

## Badges
![coverage](https://git.chalmers.se/courses/dit638/students/2023-group-11/badges/main/coverage.svg?job=coverage)
![pipeline](https://git.chalmers.se/courses/dit638/students/2023-group-11/badges/main/pipeline.svg)

## Visuals
The goal looks like the following:

TODO: Add video from OpenDLV with the given recording. 

## Pre-Requirements

The following instructions require a Linux distribution installed on your machine. Ubuntu 22.04 is recommended.

To make use of the system following sensors are required on the model vehichle:

*The list is not yet complete. Please check again later!*
- Sensor 1
- Sensor 2
- Sensor 3

TODO: Add information on how sensors can pass data to our application.

## Installation

### Make sure that your system is up to date. Run the following in a terminal:
>sudo apt-get update
> 
>sudo apt-get upgrade
> 

### Install software development tools. Run the following in a terminal:
> sudo apt-get update
>
> sudo apt-get install build-essential cmake git
> 

### Install docker

#### 1. For non-Gnome Desktop environments, gnome-terminal must be installed:

> sudo apt install gnome-terminal
> 
#### 2. Uninstall the tech preview or beta version of Docker Desktop for Linux. Run:


> sudo apt remove docker-desktop
> 
For a complete cleanup, remove configuration and data files at $HOME/.docker/desktop, the symlink at /usr/local/bin/com.docker.cli, and purge the remaining systemd service files.


> rm -r $HOME/.docker/desktop
> 
> sudo rm /usr/local/bin/com.docker.cli
> 
> sudo apt purge docker-desktop

#### 3. Set up the repository

Update the apt package index and install packages to allow apt to use a repository over HTTPS:


> sudo apt-get update
> 
> sudo apt-get install \
> 
> ca-certificates \
> 
> curl \
> 
> gnupg
>
Add Docker’s official GPG key:


>sudo mkdir -m 0755 -p /etc/apt/keyrings
> 
> curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
>
Use the following command to set up the repository:


> echo \
"deb [arch="$(dpkg --print-architecture)" signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
"$(. /etc/os-release && echo "$VERSION_CODENAME")" stable" | \
> sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

#### 4. [Download latest DEB package.](https://desktop.docker.com/linux/main/amd64/docker-desktop-4.17.0-amd64.deb?utm_source=docker&utm_medium=webreferral&utm_campaign=docs-driven-download-linux-amd64)

#### 5. Install the package with apt as follows:

>sudo apt-get update
> 
>sudo apt-get install ./docker-desktop-<version>-<arch>.deb
> 
#### 6. Give admin privileges to docker for easier use. (optional)

> sudo adduser ubuntu docker

## Usage

### 1. Clone the repository

In a terminal, use the following command:

> git clone https://git.chalmers.se/courses/dit638/students/2023-group-11.git

### 2. Build the docker image

> docker build -t antongol/example:latest -f Dockerfile .
>

### 3. Run the docker image

> docker run --rm antongol/example:latest 42

## Authors and acknowledgment
Below is the list of developers who are actively working on this project.
- Aditya: @adityaa 
- Anton: @antongol
- Askan: @askan
- Dragos: @florinel
- Oscar Reina: @scarr

## License
This project makes use of the MIT license. No contributions can be done to this project by non-maintainers.

## Project status
Project is on-going. 
