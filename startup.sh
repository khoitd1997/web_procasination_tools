#!/bin/bash

process_name="$(head /dev/urandom | tr -dc A-Za-z0-9 | head -c 18)"
# process_name="/usr/bin/containerd"

sudo bash -c "exec -a ${process_name} ./web_procasination.out"