#!/bin/bash

pdflatex writeup.tex >/dev/null
rm time-* *.log *.aux
open writeup.pdf
