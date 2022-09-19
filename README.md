## Building the App

`ng build --configuration production --aot`  

## Building the App with Docker

go to the root folder of the repo  

```
docker build -t angular-app -f web_app.Dockerfile ./hello-world
docker run -it --rm -p 4201:80 angular-app or docker-compose up -d
```  

and to push it:  

```
docker tag angular-app:latest mzandtheraspberrypi/angular-app:latest
```

running in the cloud

```
docker run -itd -p 9000:80 --restart=always mzandtheraspberrypi/angular-app:latest
```
