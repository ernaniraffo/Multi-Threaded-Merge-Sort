#!/bin/bash

pdflatex writeup.tex >/dev/null
rm time-eps-converted-to.pdf *.log *.aux
open writeup.pdf
