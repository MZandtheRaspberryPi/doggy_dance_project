## Building the App

`ng build --configuration production --aot`  

## Building the App with Docker

go to the root folder of the repo  

```
docker build -t mzandtheraspberrypi/doggy-dance-web-app:2023-03-05 -f web_app.Dockerfile ./angular-robo-dance-project
docker run -it -p --rm 80:80 mzandtheraspberrypi/doggy-dance-web-app:2023-03-05 or docker-compose up -d
```  

and to push it:  

```
docker tag angular-app:latest mzandtheraspberrypi/doggy-dance-web-app:20221223
```

running in the cloud

```
docker run -itd -p 80:80 --restart=always mzandtheraspberrypi/angular-app:latest
```

## Building REST API with Docker

From root of repo:

```
docker build -t mzandtheraspberrypi/doggy-dance-rest-api-app:2023-03-05 -f rest_api.Dockerfile ./oatpp-robo-dance-project
```

```
docker run -p 8000:8000 mzandtheraspberrypi/doggy-dance-rest-api-app:2022-12-23
```


## TODO
* add caching to api
* trim floats to 2 decimal places, or serialize data with protobuffer or something else
* server multithreaded for large requests
* implement forward kinematics api
* implement inverse kinematics api
* implement walking ago api
* implement master control panel in web app
* implement sub control panel for forward kinematics in web app
* implement sub control panel for inverse kinematics in web app
* implement sub control panel for wealking in web app
* implement time slider in web app
* implement pose saving in web app