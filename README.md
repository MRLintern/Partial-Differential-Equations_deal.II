## Application of the deal.II library for Solving Partial Differential Equations in Applied Mathematics and the Physical Sciences

## Introduction

deal.II is a free, open-source library to solve partial differential equations using the finite element method.

## Requirements

1. Compiler: `g++ (9.4.0)`
2. OS: `Ubuntu 20.04`
3. `CMake`
4. Text editor: Any will do. `Sublime Text` was used
5. Image viewer for results. Some will be `.eps` or `.svg` image files. For `.eps` files use the document viewer `evince`. For the `.svg` files, use    `inkview`.

## Instalation & Configuration

[Download](https://www.dealii.org/download.html) the library and go to the current release box.
Now follow the instructions:

        $ tar -xvf dealii-9.4.1.tar.gz
        $ mv dealii-9.4.1 /to-your-desired-location
        $ cd dealii-9.4.1
        $ cmake .
        $ make
       
       
See each sub-repository for intructions
