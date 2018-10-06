#!/bin/bash

docker exec tex /bin/sh -c "cd /assignment3;
                            pdflatex hw.tex;
                            rm *.log *.aux"
docker cp tex:/assignment3/hw.pdf .

evince hw.pdf

