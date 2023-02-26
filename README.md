## Building the App

`ng build --configuration production --aot`  

## Building the App with Docker

go to the root folder of the repo  

```
docker build -t mzandtheraspberrypi/doggy-dance-web-app:20221223 -f web_app.Dockerfile ./angular-doggy-dance-project
docker run -it -p --rm 80:80 mzandtheraspberrypi/doggy-dance-web-app:20221223 or docker-compose up -d
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
docker build -t mzandtheraspberrypi/doggy-dance-rest-api-app:2022-12-23 -f rest_api.Dockerfile ./oatpp-doggy-dance-project/
```

```
docker run -p 8000:8000 mzandtheraspberrypi/doggy-dance-rest-api-app:2022-12-23
```
