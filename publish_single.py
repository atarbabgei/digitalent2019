#!/usr/bin/python
import paho.mqtt.publish as publish

publish.single("suhu", "21C", hostname="localhost")
