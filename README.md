# QT-Book-Tracker

This is my second QT Project, I believe it is better organized than the previous one.

The project is called **Book Tracker**..

## Features:

(Features tagged as [In Development] are as the name suggest, still being develop and will most likely be integrated soon)

- User-Friendly GUI
- Search the internet for the specified book and mark it as (Read, Reading, Want to Read)
- Display book basic information (author, title, etc)
- Login System with SQL Integration (must be changed on code)
- Upload data to DB (SQL)
- [In Development] Show details more details upon clicking on book
- [In Development] Profile page with information as: books read, pages read, etc.

## Information

This project uses GoogleBooks API and looks for the determined search query, the results are then sorted into a list and the list allows the user to mark the books as either Read, Reading or Want to Read. This project was a very interesting learning experience since it is my first time messing around with APIs and not only that, for the visuals I also used a bit of CSS here and there, in that case this was probably one of the biggest learning experiences so far. 

The code might be confusing in some parts but the database name can be changed in the function connectToDatabase(), the icon and images are also uploaded within the program but will most likely require the user to correct the paths in the functions on which they are used since I wasn't sure if it would work without using the full path. The css is usually tagged between //CSS and //CSS END and can be changed if the user wants it to.

The visual colors and the icon was designed by my brother, who wanted to help when I was developing the project. Because of this I had to learn how to properly use CSS and how to style stuff inside QT Widget Designer and QT in general (HLayout, VLayout, etc).

I will probably be updating this project from time to time and maybe in the future connecting it to a working server and managing the information from there, making so that the user can sync information between devices (althrough that might be a little too high level atm). Of course, before that I want to make it a usable book tracker that can be used for personal usage and I also want to learn a bit more on how to actually release a project, adding an installer or an script to add the necessary dependencies, libraries, etc.

This project was compiled on VS Community 2022 combined with QT for Visual Studio, QT Version: 6.8.1

## Requirements

QT 6.8.1 (Default modules):
-QtSQL
-QtWebView
-QtXML
-QtWebEngine (and related modules) 
-QtNework (and authorization)
-SQLite or another SQL DB (must be either updated or removed manually on the code)


