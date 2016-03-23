# The Laundry Rails Server

##Project Debrief
![LaundryMachines](https://pixabay.com/static/uploads/photo/2015/04/05/16/26/laundromat-708176_960_720.jpg)

This repository is part of a largescale project to bring the laundry machines of college campuses into the 21st Century.

As college students, we have all experienced the pains of having to find an open laundry machine in our dorm and the gruling task of timing exactly when then next load comes out.

The rotary washing machine (which is what we more or less see today) was invented by Hamilton Smith in 1858, and ever since, the only real innovation was the integration with electricity in the early 20th Century.

However, with the advent of microcomputing technology as well as the steady decline in hardware prices, we saw new opportunity.

##Project Goals

As software engineers, our primary goal is to be able to go on a simple website which updates us in real time which machines are in use in which dorm. We plan to eventually expand this project to include dedeicated mobile apps.

##Project Strategy
(DISCLAIMER: SUBJECT TO CHANGE)

Our plan is to install a microcomputer in each laundry room on campus. We are still debating what kind of computer we will use, but we are planning to go with either the new [C.H.I.P](https://chip.hackster.io). computer, or a Raspberry Pi.

We will then attach a [primative vibration sensor](https://www.adafruit.com/products/1767) to each machine, and connect that with the microcomputer. The microcomputer will then send state changes (on or off) as well as the time this occured to a centrally located server.

The central server will then receive the information, and then update the information on the databases to reflect the changes, and the web server will communicate to the end user through a web application.

Here is a rough sketch of what might be implemented.
[graph](https://41.media.tumblr.com/5cd79325fc59b28a264cb996b0e0934d/tumblr_o4hgz1YyMh1s5a4bko1_1280.jpg)

##Programming

We are planning to use primarily C++ for programming the state-handlers on the microcomputers as well as the information relay system between the microcomputers and central server. However, we plan to use Ruby on Rails to develop the web application since Ruby has the capacity to communicate with C/C++, and Rails will allow us to create the web server quickly and focusing our energy to develop and improve the underlying functionality for the hardware code.


#Information About this Repository Specifically

This repository is strictly for keeping the Rails Web Code.


##Contact Us

We always welcome advice so please feel free to contact us at leeas@stolaf.edu for ideas or improvements.


#Thanks!