# Test using docker

## Build the image-it image

In this repository root directory:

`sudo docker build -t image-it .`

You should use *image-it* as the name of the image

## Build the test image

In this directory:

`sudo docker build -t image-it-test .`

## Copy the result

```
$> id=$(sudo docker create image-it-test)
$> sudo docker cp $id:/file.png - > file.png
$> docker rm -v $id
```
