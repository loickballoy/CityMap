## CityMap

## About / Synopsis

We are tring to create an app able to create a functioning city with a given number of inhabitants. At this stage the program is working however there is still room for improvement.

## Table of contents

> * [CityMap](#CityMap)
>   * [About / Synopsis](#about--synopsis)
>   * [Table of contents](#table-of-contents)
>   * [Installation](#installation)
>   * [Usage](#usage)
>     * [Screenshots](#screenshots)
>     * [Features](#features)
>   * [Resources (Documentation and other links)](#resources-documentation-and-other-links)
>   * [WebSite](#website)

## Installation

To install and run our project you first need to install our source code with this command:

```shell
git clone git@github.com:loickballoy/CityMap.git
```

Once that is done you have to make your way to the interface directory, make and run the executable given:

```shell
cd interface
make
./input_gtk
```

This method of installation will soon be improved. 

## Usage

We use GTK and SDL libraries to create the city. We use methods such as L-systems to create this city. Furthermore, to add on to our app, a subway network is created for each city that has a minimum of 2000 inhabitants.

### Screenshots

![alt text](https://media.discordapp.net/attachments/937331808515817482/975712089651949578/unknown.png?width=1425&height=683)
![alt-text](https://media.discordapp.net/attachments/937331808515817482/975672979088355388/unknown.png?width=1381&height=683)

### Features

You can now add biases to fit your city necessities. For instance, by increasing the value of the security bias you will obtain a city with more comissaries. 
Have fun with those biases to obtain different cities!! 

## Resources (Documentation and other links)

To have further documentation on our code execute the following commmand from the source directory:

```shell
firefox doc/html/index.html
```

## WebSite

Our project's Website :
https://thefoxell.github.io/CityMapWebsite/index.html
