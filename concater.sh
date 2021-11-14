#!/bin/bash

sed '/\#include \"header\.hpp"/d' src/app/main.cpp | cat src/app/header.hpp - |  xsel --clipboard --input
