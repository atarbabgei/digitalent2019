#!/usr/bin/python
import paho.mqtt.subscribe as subscribe

topics = ['#']

m = subscribe.simple(topics, hostname="localhost", retained=False)
print(m.topic)
print(m.payload)
