# Just a Class File

## Description

A fellow detective stumbled upon a clue that is hidden behind a java class file. You recieve the file but then your friend went off a tangent saying something about how he was using **Windows** and never specified if the file was a text document or an executable. Alas you are unable to open the file and don't know what to do.

## Hints
1. What does Unix and Windows based system do differently when you write a essay and how it stores it?

## Solution

Open the class file in a hex editor. You will notice that there is extra bytes added where it is not needed. Mainly for every newline (\n) it has a (\r) preceding it. In hex it is `0D 0A` Simply delete the 0D from the files and win 

Note: you can use a java class decompiler but change later so you can't just do a decompiler. 
