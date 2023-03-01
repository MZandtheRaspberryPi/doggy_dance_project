# OATPP Doggy Dance Project

This is a repo that uses [oatpp](https://oatpp.io/) to serve up an api for the doggy dance project that will calculate kinematics for the supported robot models.  

Install Eigen. Clone repo, checkout 3.4.0, checkinstall it or whatnot.

```
mkdir build
cd build
cmake ..
make
```

Usage

Run the server

```
./doggy-dance-project.exe
```

Call the API

```
mz@mz-VirtualBox:~$ curl 0.0.0.0:8000/robomodels
{"descriptions":[{"id":0,"name":"Robot Dog"}]}
```

## Coordinate System of the Legs

To get from the coordinate system of the main body to the legs:
rotate in Y and translate in X and Z.

For the left side, they rotate by -pi/2 in y.

so if before we are:
    z   x
     \  |
      \ |
------y--

we rotate by Y by neg pi/2. positive rotation is clockwise when looking from origin out. so we rotate counterclockwise 90 degrees.

------y--
       /|
      / |
     x  z
    /   |

then we translate. for back left, we translate z back by w/2, and we translate x up by l/2.

what if we did translation before rotation?

we go l/2 forward in x, which is right, then we go -w/2 in z, which puts us somewhere. underneath xy plane, forward l/2.
when we rotate around y, we end up with a point in y/z plane, still no y position.
