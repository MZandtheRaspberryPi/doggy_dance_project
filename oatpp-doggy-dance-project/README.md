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
