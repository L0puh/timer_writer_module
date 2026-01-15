#!/bin/bash

make 
sudo insmod timer_writer.ko
sudo rmmod timer_writer.ko

# show logs 
sudo dmesg | tail
