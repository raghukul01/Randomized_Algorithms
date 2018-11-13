#!/bin/bash

docker exec tex /bin/sh -c "cd /assignment4;
                            pdflatex hw.tex;
                            rm *.log *.aux"
docker cp tex:/assignment4/hw.pdf .

evince hw.pdf

# docker pull blang/latex
# docker run -it --name tex -v $(pwd):/assignment3 blang/latex bash
