# Picture To Ascii

## Description

You stumble upon a program that converts any image into Ascii art. Part of the implementation takes into account the **Luminance** of a pixel which is Calculated as $r * 0.2126 + g * 0.7152 + b * 0.0722$ and you round up each weighted colour component before adding them up. You also don't want to luminate every pixel so if the red > 250 and green > 250 and blue > 240. It's considered bright enough to not be used.

This program runs its own executable so you will have to check if you downloaded the correct version. Currently only mac (or unix) but will addfor windows and linux soon

## Hint

You could test every photo in your phone to try to crash the program or use a painting software (paint.net for windows or Paint S for mac)

## Solution

Simply create an image that is barely below the Luninance threshold (255,255,239) and the program would have luminance that is more than 255. This can't happen so the program panics and prints the flag (but no ascii photo :( )
