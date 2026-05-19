#!/bin/sh

cat /proc/cpuinfo | grep "model name" | head -1
free -h | grep "Mem"
echo Anzahl der laufenden Prozesse: $(ps aux | wc -l)
