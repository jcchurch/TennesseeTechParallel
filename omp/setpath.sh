#!/bin/bash

export OMP4J_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
alias omp4j="java -jar $OMP4J_PATH/omp4j-1.2.jar"