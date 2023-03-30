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

## Tools

### **Code Analysis**

These are the tools that we intend to use in order analyze and improve te quality of the C++ code developed. 

Each tool has its own **strengths** and **weaknesses**
 and can be used to improve different aspects of code quality. Using a combination of these tools can help ensure that **C++ code is of high quality, maintainable, and secure**.

- <details>
  <summary>Clang-tidy</summary>
  Clang-tidy is a static analysis tool for C++ code that can detect and suggest fixes for potential bugs, coding violations, and performance issues. It is built on top of the Clang compiler and uses LLVM for analyzing the code's abstract syntax tree. Clang-tidy can generate reports with detailed information on the issues found, including severity, location, and suggestions for remediation. It supports a range of coding standards, including Google C++ Style Guide and LLVM Coding Standards, and can also be customized with user-defined checks
</details>

- <details>
  <summary>Cppcheck</summary>
  Cppcheck is a static analysis tool for C++ code that can detect and suggest fixes for potential bugs, coding violations, and security issues. It analyzes the code for various types of errors, including buffer overflows, null pointer dereferences, and memory leaks, and can generate reports with detailed information on the issues found.
</details>

- <details>
  <summary>OCLint</summary>
  OCLint is a static code analysis tool that can detect potential bugs, coding violations, and design issues in C++, C, and Objective-C codebases. It works by analyzing the code's abstract syntax tree and generating reports with detailed information on the issues found. OCLint supports a range of coding standards, can be customized, and can be used in the command line or integrated with other tools such as Jenkins, SonarQube, and Visual Studio.
</details>

- <details>
  <summary>Pmccabe</summary>
  PCCabe is a software complexity analysis tool that can be used to measure the complexity of C++ code. It analyzes the code's control flow graph and generates reports that provide information on various complexity metrics, including cyclomatic complexity, essential complexity, and design complexity. The reports can be used to identify code that is difficult to maintain, understand, or test, and to make informed decisions about code refactoring and optimization.
</details>

- <details>
  <summary>lCov</summary>
  lCov is a code coverage analysis tool for C++ code that can be used to measure the effectiveness of test suites in exercising the codebase. It works by instrumenting the code to generate coverage data, and then generating reports that provide information on the percentage of code executed by the tests.
</details>

- <details>
  <summary>doctest</summary>
  [doctest](https://github.com/doctest/doctest) is a high-performance testing framework for C++ that is built on Catch testing framework. However, compared to Catch, doctest has a significantly lower compile runtime while executing test cases. We will use doctest framework in order to implement and enhance test-driven development testing before creating new features. 
</details>


## Commit  & Pull Request Conventions

All commits and pull requests follow [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/). 
The conventions dictates that the messages will start with a keyword which specifies the type of change. It is then followed by a description of the change.

Few common keywords:
- feat = adds a new feature
- fix = fixes a bug
- docs = works on readme type documents
- ci = related to CI/CD
- test = related to tests
- ! = used in addition to other keywords to represent importance or impact of change

*feat!: added markdown to textboxes*

*docs: added the commit & merge request conventions section to readme*

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
